#include "Sensors.h"
#include <cfloat> // For FLT_MAX

/*
 * Temperature Sensor (TMP102) Datasheet:
 * https://www.ti.com/lit/ds/symlink/tmp102.pdf
 *
 * Accelerometer (ADXL343) Datasheet:
 * https://www.analog.com/media/en/technical-documentation/data-sheets/adxl343.pdf
 */

Sensors::Sensors(NovaIO *novaio) : _novaio(novaio),
                                   _accel(-1, &Wire),
                                   _temperature(0),
                                   _accelX(0), _accelY(0), _accelZ(0),
                                   _serialOutputEnabled(true),
                                   _accelCalibrated(false),
                                   _accelOffsetX(0), _accelOffsetY(0), _accelOffsetZ(0)
{
}

void Sensors::begin()
{
    // Initialize sensors when we can get the I2C bus
    while (1)
    {
        if (xSemaphoreTake(_novaio->mutex_i2c, BLOCK_TIME) == pdTRUE)
        {
            // Initialize ADXL343 with address 0x1D
            if (!_accel.begin(0x1D))
            {
                Serial.println("Could not find ADXL343!");
                xSemaphoreGive(_novaio->mutex_i2c);
                continue;
            }

            _accel.setRange(ADXL343_RANGE_16_G);
            _accel.setDataRate(ADXL343_DATARATE_100_HZ);

            // Give sensor time to stabilize after configuration
            delay(100);

            // Perform initial calibration, assuming device might not be level
            performAccelCalibration(true);

            // Check if TMP102 is responding at address 0x48
            Wire.beginTransmission(_tmp102_addr);
            if (Wire.endTransmission() != 0)
            {
                Serial.println("Could not find TMP102!");
                xSemaphoreGive(_novaio->mutex_i2c);
                continue;
            }

            xSemaphoreGive(_novaio->mutex_i2c);
            break;
        }
        yield();
    }

    Serial.println("Sensors initialized successfully!");
}

void Sensors::startTask()
{
    xTaskCreate(
        taskFunction,
        "SensorTask",
        2048,        // Stack size
        this,        // Task parameter
        2,           // Priority
        &_taskHandle // Task handle
    );
}

void Sensors::taskFunction(void *parameter)
{
    Sensors *sensors = (Sensors *)parameter;
    TickType_t lastTempUpdate = xTaskGetTickCount();
    bool boomIgnitePrevState = false;
    float maxAccelZ = -FLT_MAX; // Initialize to smallest possible value
    float minAccelZ = FLT_MAX;  // Initialize to largest possible value
    TickType_t boomStartTime = 0;
    bool measuringBoom = false;
    int sampleCount = 0; // Counter for the number of samples taken

    while (1)
    {
        TickType_t currentTick = xTaskGetTickCount();

        // Temperature update
        if ((currentTick - lastTempUpdate) >= pdMS_TO_TICKS(TEMPERATURE_UPDATE_MS))
        {
            if (xSemaphoreTake(sensors->_novaio->mutex_i2c, BLOCK_TIME) == pdTRUE)
            {
                sensors->_temperature = sensors->readTMP102Temperature();
                sensors->_storedTemperature = sensors->_temperature; // Save the temperature
                if (sensors->_serialOutputEnabled)
                {
                    Serial.print("Temperature: ");
                    Serial.print(sensors->_temperature);
                    Serial.println("°C");
                }
                xSemaphoreGive(sensors->_novaio->mutex_i2c);
                lastTempUpdate = currentTick;
            }
        }

        // Monitor BOOM_IGNITE_PIN
        bool boomIgniteState = digitalRead(BOOM_IGNITE_PIN);
        if (boomIgniteState && !boomIgnitePrevState)
        {
            // Transition to true detected
            maxAccelZ = -FLT_MAX;
            minAccelZ = FLT_MAX;
            boomStartTime = currentTick;
            measuringBoom = true;
            sampleCount = 0; // Reset sample counter
        }
        boomIgnitePrevState = boomIgniteState;

        if (measuringBoom)
        {
            if (xSemaphoreTake(sensors->_novaio->mutex_i2c, BLOCK_TIME) == pdTRUE)
            {
                sensors_event_t accel;
                sensors->_accel.getEvent(&accel);
                if (accel.acceleration.z > maxAccelZ)
                {
                    maxAccelZ = accel.acceleration.z;
                    sensors->_timeSinceBoomForMaxAccelZ = (currentTick - boomStartTime) * portTICK_PERIOD_MS;
                }
                if (accel.acceleration.z < minAccelZ)
                {
                    minAccelZ = accel.acceleration.z;
                }
                sampleCount++; // Increment sample counter
                xSemaphoreGive(sensors->_novaio->mutex_i2c);
            }

            // Check if 1000ms has passed
            if ((currentTick - boomStartTime) >= pdMS_TO_TICKS(1000))
            {
                Serial.print("Max Acceleration Z: ");
                Serial.print(maxAccelZ);
                Serial.println(" m/s²");
                Serial.print("Min Acceleration Z: ");
                Serial.print(minAccelZ);
                Serial.println(" m/s²");
                Serial.print("Number of samples: ");
                Serial.println(sampleCount);

                // Save min and max values
                sensors->_storedMinAccelZ = minAccelZ;
                sensors->_storedMaxAccelZ = maxAccelZ;

                measuringBoom = false;
            }
        }

        // Small delay to prevent task starvation
        vTaskDelay(pdMS_TO_TICKS(1));
    }
}

float Sensors::getTemperature()
{
    return _temperature;
}

void Sensors::getAcceleration(float &x, float &y, float &z)
{
    x = _accelX;
    y = _accelY;
    z = _accelZ;
}

// Getter for min Z acceleration
// Returns the minimum Z-axis acceleration recorded during the last measurement window.
// Example usage:
// Sensors sensors;
// float minZ = sensors.getMinAccelZ();
// Serial.print("Min Z Acceleration: ");
// Serial.println(minZ);
float Sensors::getMinAccelZ() const
{
    return _storedMinAccelZ;
}

// Getter for max Z acceleration
// Returns the maximum Z-axis acceleration recorded during the last measurement window.
// Example usage:
// Sensors sensors;
// float maxZ = sensors.getMaxAccelZ();
// Serial.print("Max Z Acceleration: ");
// Serial.println(maxZ);
float Sensors::getMaxAccelZ() const
{
    return _storedMaxAccelZ;
}

// Getter for the last temperature reading
// Returns the most recent temperature reading from the TMP102 sensor.
// Example usage:
// Sensors sensors;
// float temperature = sensors.getStoredTemperature();
// Serial.print("Temperature: ");
// Serial.print(temperature);
// Serial.println("°C");
float Sensors::getStoredTemperature() const
{
    return _storedTemperature;
}

// ...existing code...

float Sensors::readTMP102Temperature()
{
    // Read temperature register (0x00)
    Wire.beginTransmission(_tmp102_addr);
    Wire.write(0x00);
    if (Wire.endTransmission() != 0)
    {
        if (_serialOutputEnabled)
        {
            Serial.println("TMP102: Failed to write to device");
        }
        return -273.15;
    }

    // Request 2 bytes from TMP102
    uint8_t bytesReceived = Wire.requestFrom(_tmp102_addr, (uint8_t)2);
    if (bytesReceived != 2)
    {
        if (_serialOutputEnabled)
        {
            Serial.println("TMP102: Failed to read from device");
        }
        return -273.15;
    }

    // Read the two bytes
    uint8_t msb = Wire.read();
    uint8_t lsb = Wire.read();

    // Combine the bytes and convert to temperature
    int16_t temp = ((msb << 8) | lsb) >> 4; // 12-bit resolution

    // Convert to Celsius
    // For 12-bit resolution, each bit represents 0.0625°C
    float tempC = temp * 0.0625;

    // Sanity check the temperature (TMP102 range is -40°C to +125°C)
    if (tempC < -40.0 || tempC > 125.0)
    {
        if (_serialOutputEnabled)
        {
            Serial.print("TMP102: Temperature out of range: ");
            Serial.println(tempC);
        }
        return -273.15;
    }

    return tempC;
}

// Performs actual calibration logic
bool Sensors::performAccelCalibration(bool assumeLevel)
{
    if (!assumeLevel)
    {
        if (_serialOutputEnabled)
        {
            Serial.println("Manual calibration requires device to be level!");
            Serial.println("Place device on level surface with Z-axis pointing up");
            Serial.println("Calibrating in 3 seconds...");
        }
        delay(3000); // Give time to ensure device is steady
    }

    // Clear any existing offsets first
    _accel.writeRegister(ADXL343_REG_OFSX, 0);
    _accel.writeRegister(ADXL343_REG_OFSY, 0);
    _accel.writeRegister(ADXL343_REG_OFSZ, 0);
    delay(50); // Give time for offsets to take effect

    // Take multiple readings and average them for stability
    const int numSamples = 20; // Increased number of samples
    float sumX = 0, sumY = 0, sumZ = 0;

    for (int i = 0; i < numSamples; i++)
    {
        sensors_event_t event;
        _accel.getEvent(&event);
        sumX += event.acceleration.x;
        sumY += event.acceleration.y;
        sumZ += event.acceleration.z;
        delay(10); // Shorter delay between readings, but more samples
    }

    // Calculate average readings
    float avgX = sumX / numSamples;
    float avgY = sumY / numSamples;
    float avgZ = sumZ / numSamples;

    // First convert readings from m/s² to g (1g = 9.81 m/s²)
    float gX = avgX / 9.81f;
    float gY = avgY / 9.81f;
    float gZ = avgZ / 9.81f;

    // Calculate required offsets (15.6 mg per LSB)
    // Negative because we want to counter the current reading
    _accelOffsetX = (int8_t)(-(gX - 0.0f) * (1000.0f / 15.6f)); // Expected X = 0g
    _accelOffsetY = (int8_t)(-(gY - 0.0f) * (1000.0f / 15.6f)); // Expected Y = 0g
    _accelOffsetZ = (int8_t)(-(gZ - 1.0f) * (1000.0f / 15.6f)); // Expected Z = 1g

    // Clamp offsets to valid range (-128 to +127)
    _accelOffsetX = constrain(_accelOffsetX, -128, 127);
    _accelOffsetY = constrain(_accelOffsetY, -128, 127);
    _accelOffsetZ = constrain(_accelOffsetZ, -128, 127);

    // Apply offsets to the sensor
    _accel.writeRegister(ADXL343_REG_OFSX, _accelOffsetX);
    _accel.writeRegister(ADXL343_REG_OFSY, _accelOffsetY);
    _accel.writeRegister(ADXL343_REG_OFSZ, _accelOffsetZ);

    if (_serialOutputEnabled)
    {
        Serial.println("Calibration complete!");
        Serial.print("Offsets - X: ");
        Serial.print(_accelOffsetX);
        Serial.print(" Y: ");
        Serial.print(_accelOffsetY);
        Serial.print(" Z: ");
        Serial.println(_accelOffsetZ);
    }

    _accelCalibrated = true;
    return true;
}

// Public method for on-demand calibration
bool Sensors::calibrateAccelerometer(bool assumeLevel)
{
    if (!xSemaphoreTake(_novaio->mutex_i2c, BLOCK_TIME) == pdTRUE)
    {
        return false;
    }

    bool result = performAccelCalibration(assumeLevel);
    xSemaphoreGive(_novaio->mutex_i2c);
    return result;
}
