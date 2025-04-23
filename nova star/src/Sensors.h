#pragma once

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_ADXL343.h>
#include "NovaIO.h"

class Sensors {
public:
    Sensors(NovaIO* novaio);
    void begin();
    void startTask();
    
    // Getter methods for sensor data
    float getTemperature();
    void getAcceleration(float &x, float &y, float &z);
    
    // Serial output control
    void setSerialOutput(bool enabled) { _serialOutputEnabled = enabled; }
    bool getSerialOutput() const { return _serialOutputEnabled; }
    
    // Task control
    void runTask() { taskFunction(this); }
    
    // Calibration methods
    bool calibrateAccelerometer(bool assumeLevel = false);  // On-demand calibration
    
private:
    static void taskFunction(void* parameter);
    
    NovaIO* _novaio;  // For mutex access
    Adafruit_ADXL343 _accel;
    const uint8_t _tmp102_addr = 0x48;  // TMP102 I2C address
    
    // Private methods for TMP102
    float readTMP102Temperature();
    
    // Data storage
    float _temperature;
    float _accelX, _accelY, _accelZ;
    
    // Task handle
    TaskHandle_t _taskHandle;
    
    // Serial output control
    bool _serialOutputEnabled;
    
    // Calibration methods and state
    bool performAccelCalibration(bool assumeLevel);
    bool _accelCalibrated;
    int8_t _accelOffsetX;
    int8_t _accelOffsetY;
    int8_t _accelOffsetZ;
    
    // ADXL343 Register addresses for offset calibration
    static const uint8_t ADXL343_REG_OFSX = 0x1E;
    static const uint8_t ADXL343_REG_OFSY = 0x1F;
    static const uint8_t ADXL343_REG_OFSZ = 0x20;
    
    // Update intervals
    static const uint32_t TEMPERATURE_UPDATE_MS = 1000;  // Update temp every 1 second
    static const uint32_t ACCEL_UPDATE_MS = 100;        // Update accel every 100ms
};
