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
