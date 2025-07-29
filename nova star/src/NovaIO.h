#ifndef NOVAIOH
#define NOVAIOH

#pragma once

#include "configuration.h"
#include <Adafruit_MCP23X17.h>
#include <Arduino.h>

#define BLOCK_TIME 200

enum expansionIO
{
        expA
};

class NovaIO
{
private:
        uint16_t expOutPort_A;

public:
        NovaIO();
        Adafruit_MCP23X17 mcp_a;
        // Adafruit_MCP23X17 mcp_h; // Button inputs are on h

        void digitalWrite(enum expansionIO, int pin, bool state);
        void mcpA_digitalWrite(uint8_t pin, uint8_t value);
        void mcp_digitalWrite(uint8_t pin, uint8_t value, uint8_t expander);
        enum StarlinkDirection
        {
                STARLINK_RECEIVE = 0,
                STARLINK_TRANSMIT = 1,
                STARLINK_HIGH_IMPEDANCE = 3,
                STARLINK_SHUTDOWN = 4
        };
        void setStarlink(StarlinkDirection direction);

        xSemaphoreHandle mutex_i2c;
};

extern NovaIO *novaIO;

#endif