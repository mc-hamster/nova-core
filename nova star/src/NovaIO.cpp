#include <Arduino.h>
#include <Adafruit_MCP23X17.h>

#include "NovaIO.h"
#include "configuration.h"
#include "main.h"

NovaIO::NovaIO()
{

    /*
    These should be initilized to 0 for us, but let's do it again
    anyway just to be sure. We can't let an unitilized variable be a safety
    problem.
    */
    expOutPort_A = 0x00;
    

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


    Serial.println("MCP23X17 interfaces setup. - DONE");

    uint8_t i = 0;
    for (i = 0; i <= 15; ++i)
    {
        mcp_a.pinMode(i, OUTPUT);
    }

    // Set all the outputs to the initilized state.
    mcp_a.writeGPIOAB(expOutPort_A);
    Serial.println("MCP23X17 interfaces outputs set to initilized value.");
}

void NovaIO::digitalWrite(enum expansionIO, int pin, bool state)
{

    mcp_a.writeGPIOAB(0b1111111111111111);

    delay(100);

    mcp_a.writeGPIOAB(0b0000000000000000);

    delay(100);
}

void NovaIO::mcpA_digitalWrite(uint8_t pin, uint8_t value)
{
    while (1) // After duration set Pins to end state
    {
        if (xSemaphoreTake(mutex_i2c, BLOCK_TIME) == pdTRUE)
        {
            mcp_a.digitalWrite(pin, value);
            break;
        }
        yield(); // We yield to feed the watchdog.
    }

    xSemaphoreGive(novaIO->mutex_i2c); // Give back the mutex
}

void NovaIO::mcp_digitalWrite(uint8_t pin, uint8_t value, uint8_t expander)
{
    while (1) // After duration set Pins to end state
    {
        if (xSemaphoreTake(mutex_i2c, BLOCK_TIME) == pdTRUE)
        {
            if (expander == 0)
            {
                mcp_a.digitalWrite(pin, value);
            }
            break;
        }
        yield(); // We yield to feed the watchdog.
    }

    xSemaphoreGive(novaIO->mutex_i2c); // Give back the mutex
}

/*
Set the function of the RS485 half duplex transceiver.
direction is one of StarlinkDirection enum:
  STARLINK_RECEIVE
  STARLINK_TRANSMIT
  STARLINK_HIGH_IMPEDANCE
  STARLINK_SHUTDOWN
*/
void NovaIO::setStarlink(StarlinkDirection direction)
{
    // Pin assignments for RS485 transceiver control
    // These should match the hardware wiring and configuration.h
    const uint8_t RE_PIN = NOVANET_RE; // Receive Enable
    const uint8_t DE_PIN = NOVANET_DE; // Driver Enable

    // Default states
    uint8_t re_state = LOW;
    uint8_t de_state = LOW;

    switch (direction) {
        case STARLINK_RECEIVE:
            re_state = LOW;
            de_state = LOW;
            break;
        case STARLINK_TRANSMIT:
            re_state = LOW;
            de_state = HIGH;
            break;
        case STARLINK_HIGH_IMPEDANCE:
            re_state = LOW;
            de_state = LOW;
            break;
        case STARLINK_SHUTDOWN:
            re_state = HIGH;
            de_state = LOW;
            break;
        default:
            // Invalid direction, default to receive
            re_state = LOW;
            de_state = LOW;
            break;
    }

    // Set the RE and DE pins using the port expander
    mcp_digitalWrite(RE_PIN, re_state, 0);
    mcp_digitalWrite(DE_PIN, de_state, 0);
}
