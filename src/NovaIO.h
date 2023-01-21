#ifndef NOVAIOH
#define NOVAIOH

#pragma once

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

        bool digitalRead(int which, int pin);
};

extern NovaIO *novaIO;

#endif