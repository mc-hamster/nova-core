#include <Arduino.h>
#include <Adafruit_MCP23X17.h>

#include "NovaIO.h"
#include "configuration.h"
#include "main.h"

NovaIO *novaIO = NULL;

NovaIO::NovaIO()
{
    // Initialize I2C statistics
    i2c_bytes_transferred = 0;
    i2c_last_second = millis();
    i2c_utilization = 0;

    /*
    These should be initilized to 0 for us, but let's do it again
    anyway just to be sure. We can't let an unitilized variable be a safety
    problem.
    */
    expOutPort_A = 0x00;
    expOutPort_B = 0x00;
    expOutPort_C = 0x00;
    expOutPort_D = 0x00;
    expOutPort_E = 0x00;
    expOutPort_F = 0x00;
    expOutPort_G = 0x00;
    expOutPort_H = 0x00;

    /*
    Create the mutex semaphore for the i2c bus
    */
    mutex_i2c = xSemaphoreCreateMutex();

    /*
    Initilize all the devices on the bus.
    */
    Serial.println("MCP23X17 interfaces setup.");
    if (!mcp_a.begin_I2C(0x20))
    {
        Serial.println("Error - mcp_a");
        while (1)
            ;
    }
    if (!mcp_b.begin_I2C(0x21))
    {
        Serial.println("Error - mcp_b");
        while (1)
            ;
    }
    if (!mcp_c.begin_I2C(0x22))
    {
        Serial.println("Error - mcp_c");
        while (1)
            ;
    }
    if (!mcp_d.begin_I2C(0x23))
    {
        Serial.println("Error - mcp_d");
        while (1)
            ;
    }
    if (!mcp_e.begin_I2C(0x24))
    {
        Serial.println("Error - mcp_e");
        while (1)
            ;
    }
    if (!mcp_f.begin_I2C(0x25))
    {
        Serial.println("Error - mcp_f");
        while (1)
            ;
    }
    if (!mcp_g.begin_I2C(0x26))
    {
        Serial.println("Error - mcp_g");
        while (1)
            ;
    }

    // Note: mcp_h has the button inputs
    if (!mcp_h.begin_I2C(0x27))
    {
        Serial.println("Error - mcp_h");
        while (1)
            ;
    }

    Serial.println("MCP23X17 interfaces setup. - DONE");

    uint8_t i = 0;
    for (i = 0; i <= 15; ++i)
    {
        mcp_a.pinMode(i, OUTPUT);
        mcp_b.pinMode(i, OUTPUT);
        mcp_c.pinMode(i, OUTPUT);
        mcp_d.pinMode(i, OUTPUT);
        mcp_e.pinMode(i, OUTPUT);
        mcp_f.pinMode(i, OUTPUT);
        mcp_g.pinMode(i, OUTPUT);
        mcp_h.pinMode(i, OUTPUT);
    }

    mcp_h.pinMode(BUTTON_RED_IN, INPUT);
    mcp_h.pinMode(BUTTON_GREEN_IN, INPUT);
    mcp_h.pinMode(BUTTON_BLUE_IN, INPUT);
    mcp_h.pinMode(BUTTON_YELLOW_IN, INPUT);
    mcp_h.pinMode(BUTTON_WHITE_IN, INPUT);

    // Set all the outputs to the initilized state.
    mcp_a.writeGPIOAB(expOutPort_A);
    mcp_b.writeGPIOAB(expOutPort_B);
    mcp_c.writeGPIOAB(expOutPort_C);
    mcp_d.writeGPIOAB(expOutPort_D);
    mcp_e.writeGPIOAB(expOutPort_E);
    mcp_f.writeGPIOAB(expOutPort_F);
    mcp_g.writeGPIOAB(expOutPort_G);
    Serial.println("MCP23X17 interfaces outputs set to initilized value.");
}

/**
 * Reads the digital value of the specified pin on the MCP23017H expander.
 * 
 * The function caches the pin reading for a configurable period (CACHE_DURATION).
 * If the cached value is older than CACHE_DURATION, it is refreshed from hardware (cache miss);
 * otherwise, the cached value is returned (cache hit).
 * 
 * Additionally, report logging can be enabled or disabled via REPORT_LOGGING_ENABLED.
 *
 * @param pin The pin number to read.
 * @return The digital value of the pin (HIGH or LOW).
 */
bool NovaIO::expansionDigitalRead(int pin)
{
    // Configurable cache duration and logging settings
    const unsigned long CACHE_DURATION = 40;
    const bool REPORT_LOGGING_ENABLED = false;
    const uint8_t MAX_PINS = 16; // MCP23017 has 16 pins

    static unsigned long lastReportTime = millis();
    static int pollCounts[MAX_PINS] = {0};
    static int cacheHits[MAX_PINS] = {0};
    static int cacheMisses[MAX_PINS] = {0};
    static bool cachedValues[MAX_PINS] = { false };
    static unsigned long cachedTime[MAX_PINS] = { 0 };

    // Add bounds checking
    if (pin >= MAX_PINS) {
        return false;
    }

    pollCounts[pin]++; // Count poll for this pin
    unsigned long currentMillis = millis();
    const TickType_t xMaxBlockTime = pdMS_TO_TICKS(100); // 100ms timeout

    if (currentMillis - cachedTime[pin] >= CACHE_DURATION) { // Cache miss: cache older than CACHE_DURATION
        cacheMisses[pin]++;
        bool readValue = false;
        if (xSemaphoreTake(mutex_i2c, xMaxBlockTime) == pdTRUE) {
            readValue = mcp_h.digitalRead(pin);
            // Count actual I2C transaction bytes:
            // - Device address + write bit (1 byte)
            // - Register address (1 byte)
            // - Device address + read bit (1 byte)
            // - Data byte (1 byte)
            trackI2CTransfer(4);
            xSemaphoreGive(mutex_i2c);
        }
        cachedValues[pin] = readValue;
        cachedTime[pin] = currentMillis;
    } else {
        cacheHits[pin]++;
    }

    if (REPORT_LOGGING_ENABLED && (currentMillis - lastReportTime >= 1000)) { // 1 second elapsed
        Serial.println("Polling report:");
        for (int i = 0; i < MAX_PINS; i++) {
            if (pollCounts[i] > 0) {
                Serial.print("Pin ");
                Serial.print(i);
                Serial.print(": Hits = ");
                Serial.print(cacheHits[i]);
                Serial.print(", Misses = ");
                Serial.print(cacheMisses[i]);
                Serial.print(" (Total polls: ");
                Serial.print(pollCounts[i]);
                Serial.println(")");
                // Reset counters
                pollCounts[i] = 0;
                cacheHits[i] = 0;
                cacheMisses[i] = 0;
            }
        }
        lastReportTime = currentMillis;
    }
    
    return cachedValues[pin];
}

void NovaIO::mcpA_writeGPIOAB(uint16_t value)
{
    while (1) // After duration set Pins to end state
    {
        if (xSemaphoreTake(mutex_i2c, BLOCK_TIME) == pdTRUE)
        {
            mcp_a.writeGPIOAB(value);
            // Count actual I2C transaction bytes:
            // - Device address + write bit (1 byte)
            // - Register address (1 byte)
            // - Data bytes (2 bytes for GPIOAB)
            trackI2CTransfer(4);
            break;
        }
        yield(); // We yield to feed the watchdog.
    }

    xSemaphoreGive(novaIO->mutex_i2c); // Give back the mutex
}

void NovaIO::mcpB_writeGPIOAB(uint16_t value)
{
    while (1)
    {
        if (xSemaphoreTake(mutex_i2c, BLOCK_TIME) == pdTRUE)
        {
            mcp_b.writeGPIOAB(value);
            // Count actual I2C transaction bytes:
            // - Device address + write bit (1 byte)
            // - Register address (1 byte)
            // - Data bytes (2 bytes for GPIOAB)
            trackI2CTransfer(4);
            break;
        }
        yield();
    }
    xSemaphoreGive(novaIO->mutex_i2c);
}

void NovaIO::mcpC_writeGPIOAB(uint16_t value)
{
    while (1)
    {
        if (xSemaphoreTake(mutex_i2c, BLOCK_TIME) == pdTRUE)
        {
            mcp_c.writeGPIOAB(value);
            trackI2CTransfer(4);
            break;
        }
        yield();
    }
    xSemaphoreGive(novaIO->mutex_i2c);
}

void NovaIO::mcpD_writeGPIOAB(uint16_t value)
{
    while (1)
    {
        if (xSemaphoreTake(mutex_i2c, BLOCK_TIME) == pdTRUE)
        {
            mcp_d.writeGPIOAB(value);
            trackI2CTransfer(4);
            break;
        }
        yield();
    }
    xSemaphoreGive(novaIO->mutex_i2c);
}

void NovaIO::mcpE_writeGPIOAB(uint16_t value)
{
    while (1)
    {
        if (xSemaphoreTake(mutex_i2c, BLOCK_TIME) == pdTRUE)
        {
            mcp_e.writeGPIOAB(value);
            trackI2CTransfer(4);
            break;
        }
        yield();
    }
    xSemaphoreGive(novaIO->mutex_i2c);
}

void NovaIO::mcpF_writeGPIOAB(uint16_t value)
{
    while (1)
    {
        if (xSemaphoreTake(mutex_i2c, BLOCK_TIME) == pdTRUE)
        {
            mcp_f.writeGPIOAB(value);
            trackI2CTransfer(4);
            break;
        }
        yield();
    }
    xSemaphoreGive(novaIO->mutex_i2c);
}

void NovaIO::mcpG_writeGPIOAB(uint16_t value)
{
    while (1)
    {
        if (xSemaphoreTake(mutex_i2c, BLOCK_TIME) == pdTRUE)
        {
            mcp_g.writeGPIOAB(value);
            trackI2CTransfer(4);
            break;
        }
        yield();
    }
    xSemaphoreGive(novaIO->mutex_i2c);
}

void NovaIO::mcpH_writeGPIOAB(uint16_t value)
{
    while (1)
    {
        if (xSemaphoreTake(mutex_i2c, BLOCK_TIME) == pdTRUE)
        {
            mcp_h.writeGPIOAB(value);
            trackI2CTransfer(4);
            break;
        }
        yield();
    }
    xSemaphoreGive(novaIO->mutex_i2c);
}

void NovaIO::mcpA_digitalWrite(uint8_t pin, uint8_t value)
{
    while (1) // After duration set Pins to end state
    {
        if (xSemaphoreTake(mutex_i2c, BLOCK_TIME) == pdTRUE)
        {
            mcp_a.digitalWrite(pin, value);
            // Count actual I2C transaction bytes:
            // - Device address + write bit (1 byte)
            // - Register address (1 byte) 
            // - Data byte (1 byte)
            trackI2CTransfer(3);
            break;
        }
        yield(); // We yield to feed the watchdog.
    }

    xSemaphoreGive(novaIO->mutex_i2c); // Give back the mutex
}

/**
 * Writes a digital value to the specified pin on the selected MCP23017 expander.
 * 
 * @param pin The pin number to write to.
 * @param value The digital value to write (HIGH or LOW).
 * @param expander The expander number to write to (0-7).
 */
void NovaIO::mcp_digitalWrite(uint8_t pin, uint8_t value, uint8_t expander)
{
    while (1) {
        if (xSemaphoreTake(mutex_i2c, BLOCK_TIME) == pdTRUE) {
            switch(expander) {
                case 0: mcp_a.digitalWrite(pin, value); break;
                case 1: mcp_b.digitalWrite(pin, value); break;
                case 2: mcp_c.digitalWrite(pin, value); break;
                case 3: mcp_d.digitalWrite(pin, value); break;
                case 4: mcp_e.digitalWrite(pin, value); break;
                case 5: mcp_f.digitalWrite(pin, value); break;
                case 6: mcp_g.digitalWrite(pin, value); break;
                case 7: mcp_h.digitalWrite(pin, value); break;
            }
            // Count actual I2C transaction bytes:
            // - Device address + write bit (1 byte)
            // - Register address (1 byte) 
            // - Data byte (1 byte)
            trackI2CTransfer(3);
            xSemaphoreGive(novaIO->mutex_i2c);
            return;
        }
        yield(); // Feed the watchdog while waiting
    }
}

void NovaIO::mcpB_digitalWrite(uint8_t pin, uint8_t value)
{
    while (1)
    {
        if (xSemaphoreTake(mutex_i2c, BLOCK_TIME) == pdTRUE)
        {
            mcp_b.digitalWrite(pin, value);
            trackI2CTransfer(3);
            break;
        }
        yield();
    }
    xSemaphoreGive(novaIO->mutex_i2c);
}

void NovaIO::mcpC_digitalWrite(uint8_t pin, uint8_t value)
{
    while (1)
    {
        if (xSemaphoreTake(mutex_i2c, BLOCK_TIME) == pdTRUE)
        {
            mcp_c.digitalWrite(pin, value);
            trackI2CTransfer(3);
            break;
        }
        yield();
    }
    xSemaphoreGive(novaIO->mutex_i2c);
}

void NovaIO::mcpD_digitalWrite(uint8_t pin, uint8_t value)
{
    while (1)
    {
        if (xSemaphoreTake(mutex_i2c, BLOCK_TIME) == pdTRUE)
        {
            mcp_d.digitalWrite(pin, value);
            trackI2CTransfer(3);
            break;
        }
        yield();
    }
    xSemaphoreGive(novaIO->mutex_i2c);
}

void NovaIO::mcpE_digitalWrite(uint8_t pin, uint8_t value)
{
    while (1)
    {
        if (xSemaphoreTake(mutex_i2c, BLOCK_TIME) == pdTRUE)
        {
            mcp_e.digitalWrite(pin, value);
            trackI2CTransfer(3);
            break;
        }
        yield();
    }
    xSemaphoreGive(novaIO->mutex_i2c);
}

void NovaIO::mcpF_digitalWrite(uint8_t pin, uint8_t value)
{
    while (1)
    {
        if (xSemaphoreTake(mutex_i2c, BLOCK_TIME) == pdTRUE)
        {
            mcp_f.digitalWrite(pin, value);
            trackI2CTransfer(3);
            break;
        }
        yield();
    }
    xSemaphoreGive(novaIO->mutex_i2c);
}

void NovaIO::mcpG_digitalWrite(uint8_t pin, uint8_t value)
{
    while (1)
    {
        if (xSemaphoreTake(mutex_i2c, BLOCK_TIME) == pdTRUE)
        {
            mcp_g.digitalWrite(pin, value);
            trackI2CTransfer(3);
            break;
        }
        yield();
    }
    xSemaphoreGive(novaIO->mutex_i2c);
}

void NovaIO::mcpH_digitalWrite(uint8_t pin, uint8_t value)
{
    while (1)
    {
        if (xSemaphoreTake(mutex_i2c, BLOCK_TIME) == pdTRUE)
        {
            mcp_h.digitalWrite(pin, value);
            trackI2CTransfer(3);
            break;
        }
        yield();
    }
    xSemaphoreGive(novaIO->mutex_i2c);
}

/*
direction is one of:
  0 - Receive
  1 - Transmit
  3 - High Impedance
  4 - Shutdown
*/
void NovaIO::setStarlink(u_int8_t direction, uint8_t star)
{

    /*

        Source: https://www.analog.com/media/en/technical-documentation/data-sheets/MAX1487-MAX491.pdf
          See Function table from Page 10

        Receiving
            Receive Enable (RE) = Low
            Driver Enable (DE) = Low

        Transmitting
            Receive Enable (RE) = Low
            Driver Enable (DE) = High

        High Impedance
            Receive Enable (RE) = Low
            Driver Enable (DE) = Low

        Shutdown
            Receive Enable (RE) = High
            Driver Enable (DE) = Low


    */
}

/**
 * Sets the value of the red LED.
 * @param value The value to set the LED to. True for on, false for off.
 */
void NovaIO::ledRed(bool value)
{
    if (value)
    {
        analogWrite(BUTTON_RED_OUT, 255);
    }
    else
    {
        analogWrite(BUTTON_RED_OUT, 0);
    }
}

/**
 * Sets the value of the green LED.
 * @param value The value to set the LED to. True for on, false for off.
 */
void NovaIO::ledGreen(bool value)
{
    if (value)
    {
        analogWrite(BUTTON_GREEN_OUT, 255);
    }
    else
    {
        analogWrite(BUTTON_GREEN_OUT, 0);
    }
}

/**
 * Sets the value of the blue LED.
 * @param value The value to set the LED to. True for on, false for off.
 */
void NovaIO::ledBlue(bool value)
{
    if (value)
    {
        analogWrite(BUTTON_BLUE_OUT, 255);
    }
    else
    {
        analogWrite(BUTTON_BLUE_OUT, 0);
    }
}

/**
 * Sets the value of the yellow LED.
 * @param value The value to set the LED to. True for on, false for off.
 */
void NovaIO::ledYellow(bool value)
{
    if (value)
    {
        analogWrite(BUTTON_YELLOW_OUT, 255);
    }
    else
    {
        analogWrite(BUTTON_YELLOW_OUT, 0);
    }
}

/**
 * Sets the value of the white LED.
 * @param value The value to set the LED to. True for on, false for off.
 */
void NovaIO::ledWhite(bool value)
{
    if (value)
    {
        analogWrite(BUTTON_WHITE_OUT, 255);
    }
    else
    {
        analogWrite(BUTTON_WHITE_OUT, 0);
    }
}

void NovaIO::trackI2CTransfer(size_t bytes) {
    i2c_bytes_transferred += bytes;
    updateI2CStats();
}

float NovaIO::getI2CUtilization() {
    updateI2CStats();
    return i2c_utilization;
}

void NovaIO::updateI2CStats() {
    unsigned long current_time = millis();
    if (current_time - i2c_last_second >= 1000) {
        // Calculate utilization as percentage of theoretical maximum bandwidth
        // Each byte takes 9 bits (8 data + 1 ack)
        // Maximum bytes per second = clock_speed / 9
        // Using fixed 400kHz speed
        const float max_bytes_per_sec = 400000.0 / 9.0;
        i2c_utilization = (i2c_bytes_transferred / max_bytes_per_sec) * 100.0;
        
        // Reset for next second
        i2c_bytes_transferred = 0;
        i2c_last_second = current_time;
    }
}