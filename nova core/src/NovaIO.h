#ifndef NOVAIOH
#define NOVAIOH

#pragma once

#include "main.h"
#include "configuration.h"
#include <Adafruit_MCP23X17.h>
#include <Arduino.h>

#define BLOCK_TIME 200

enum expansionIO
{
        expA,
        expB,
        expC,
        expD,
        expE,
        expF,
        expG,
        expH
};

class NovaIO
{
private:

        /*
        Maintain the state of the outputs for each expansion IC.
        */
        uint16_t expOutPort_A;
        uint16_t expOutPort_B;
        uint16_t expOutPort_C;
        uint16_t expOutPort_D;
        uint16_t expOutPort_E;
        uint16_t expOutPort_F;
        uint16_t expOutPort_G;
        uint16_t expOutPort_H;

        // I2C statistics
        unsigned long i2c_bytes_transferred;
        unsigned long i2c_last_second;
        float i2c_utilization;

public:
        NovaIO();

        Adafruit_MCP23X17 mcp_a;
        Adafruit_MCP23X17 mcp_b;
        Adafruit_MCP23X17 mcp_c;
        Adafruit_MCP23X17 mcp_d;
        Adafruit_MCP23X17 mcp_e;
        Adafruit_MCP23X17 mcp_f;
        Adafruit_MCP23X17 mcp_g;
        Adafruit_MCP23X17 mcp_h; // Button inputs are on h

        void mcpA_writeGPIOAB(uint16_t value);
        void mcpB_writeGPIOAB(uint16_t value);
        void mcpC_writeGPIOAB(uint16_t value);
        void mcpD_writeGPIOAB(uint16_t value);
        void mcpE_writeGPIOAB(uint16_t value);
        void mcpF_writeGPIOAB(uint16_t value);
        void mcpG_writeGPIOAB(uint16_t value);
        void mcpH_writeGPIOAB(uint16_t value);

        void mcpA_digitalWrite(uint8_t pin, uint8_t value);
        void mcpB_digitalWrite(uint8_t pin, uint8_t value);
        void mcpC_digitalWrite(uint8_t pin, uint8_t value);
        void mcpD_digitalWrite(uint8_t pin, uint8_t value);
        void mcpE_digitalWrite(uint8_t pin, uint8_t value);
        void mcpF_digitalWrite(uint8_t pin, uint8_t value);
        void mcpG_digitalWrite(uint8_t pin, uint8_t value);
        void mcpH_digitalWrite(uint8_t pin, uint8_t value);

        void mcp_digitalWrite(uint8_t pin, uint8_t value, uint8_t expander);

        void ledRed (bool value);
        void ledGreen (bool value);
        void ledBlue (bool value);
        void ledYellow (bool value);
        void ledWhite (bool value);
        

        bool expansionDigitalRead(int pin);

        void setStarlink(u_int8_t u_int8_t, uint8_t star);

        xSemaphoreHandle mutex_i2c;

        // I2C statistics methods
        void trackI2CTransfer(size_t bytes);
        float getI2CUtilization();
        void updateI2CStats();
};

extern NovaIO *novaIO;

#endif