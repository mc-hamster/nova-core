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

        

/*
Frame Buffer: Flame - For flame effects only. These effects work from the GPIO
  expanders. Write only.
        - Poofer
        - Boomer
        - Blower
        - Igniter

  Variables:

        Current Frame Buffer

        Future Frame Buffer

        Is Future Frame Buffer "dirty"?
                * If not dirty, then the future should match current

  Functions
        Write to GPIO
                * Write update to future frame buffer
                * (optionally) Flush write bufffer to the network

        
        Flush
                * Write future frame buffer to the network
                * Copy future frame buffer to current frame buffer


Frame Buffer: Extended - Extended functions. This is for everything that uses the
  digital interface. These values can be updated by both the controller
  and represent a dynamic state from the stars.
        - Lasers
        - Fog Machines
        - LED effects
        - Other?
*/



        bool expansionDigitalRead(int pin);

        void setStarlink(u_int8_t u_int8_t, uint8_t star);

        xSemaphoreHandle mutex_i2c;
};

extern NovaIO *novaIO;

#endif