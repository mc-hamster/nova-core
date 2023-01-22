#ifndef NOVAIOH
#define NOVAIOH

#pragma once

#include "main.h"
#include "configuration.h"
#include <Adafruit_MCP23X17.h>
#include <Arduino.h>

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

        void digitalWrite(enum expansionIO, int pin, bool state);

        void mcpA_writeGPIOAB(uint16_t value);
        void mcpB_writeGPIOAB(uint16_t value);
        void mcpC_writeGPIOAB(uint16_t value);
        void mcpD_writeGPIOAB(uint16_t value);
        void mcpE_writeGPIOAB(uint16_t value);
        void mcpF_writeGPIOAB(uint16_t value);
        void mcpG_writeGPIOAB(uint16_t value);
        void mcpH_writeGPIOAB(uint16_t value);

        bool expansionDigitalRead(int pin);
        xSemaphoreHandle mutex_i2c;
};

extern NovaIO *novaIO;

#endif