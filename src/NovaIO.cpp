#include <Arduino.h>
#include <Adafruit_MCP23X17.h>

#include "NovaIO.h"
#include "configuration.h"
#include "main.h"

NovaIO *novaIO = NULL;

NovaIO::NovaIO()
{

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
    //mcp_g.writeGPIOAB(expOutPort_G);
    Serial.println("MCP23X17 interfaces outputs set to initilized value.");
}

void NovaIO::digitalWrite(enum expansionIO, int pin, bool state)
{

    mcp_a.writeGPIOAB(0b1111111111111111);

    delay(100);

    mcp_a.writeGPIOAB(0b0000000000000000);

    delay(100);
}

bool NovaIO::expansionDigitalRead(int pin)
{
    // return 0;
    bool readValue;
    while (1) // After duration set Pins to end state
    {
        if (xSemaphoreTake(mutex_i2c, BLOCK_TIME) == pdTRUE)
        {
            readValue = mcp_h.digitalRead(pin);
            break;
        }
        yield(); // We yield to feed the watchdog.
    }

    xSemaphoreGive(novaIO->mutex_i2c); // Give back the mutex
    return readValue;
}

void NovaIO::mcpA_writeGPIOAB(uint16_t value)
{
    bool readValue;
    while (1) // After duration set Pins to end state
    {
        if (xSemaphoreTake(mutex_i2c, BLOCK_TIME) == pdTRUE)
        {
            mcp_a.writeGPIOAB(value);
            break;
        }
        yield(); // We yield to feed the watchdog.
    }

    xSemaphoreGive(novaIO->mutex_i2c); // Give back the mutex
}

void NovaIO::mcpB_writeGPIOAB(uint16_t value)
{
    bool readValue;
    while (1) // After duration set Pins to end state
    {
        if (xSemaphoreTake(mutex_i2c, BLOCK_TIME) == pdTRUE)
        {
            mcp_b.writeGPIOAB(value);
            break;
        }
        yield(); // We yield to feed the watchdog.
    }

    xSemaphoreGive(novaIO->mutex_i2c); // Give back the mutex
}

void NovaIO::mcpC_writeGPIOAB(uint16_t value)
{
    bool readValue;
    while (1) // After duration set Pins to end state
    {
        if (xSemaphoreTake(mutex_i2c, BLOCK_TIME) == pdTRUE)
        {
            mcp_c.writeGPIOAB(value);
            break;
        }
        yield(); // We yield to feed the watchdog.
    }

    xSemaphoreGive(novaIO->mutex_i2c); // Give back the mutex
}

void NovaIO::mcpD_writeGPIOAB(uint16_t value)
{
    bool readValue;
    while (1) // After duration set Pins to end state
    {
        if (xSemaphoreTake(mutex_i2c, BLOCK_TIME) == pdTRUE)
        {
            mcp_d.writeGPIOAB(value);
            break;
        }
        yield(); // We yield to feed the watchdog.
    }

    xSemaphoreGive(novaIO->mutex_i2c); // Give back the mutex
}

void NovaIO::mcpE_writeGPIOAB(uint16_t value)
{
    bool readValue;
    while (1) // After duration set Pins to end state
    {
        if (xSemaphoreTake(mutex_i2c, BLOCK_TIME) == pdTRUE)
        {
            mcp_e.writeGPIOAB(value);
            break;
        }
        yield(); // We yield to feed the watchdog.
    }

    xSemaphoreGive(novaIO->mutex_i2c); // Give back the mutex
}

void NovaIO::mcpF_writeGPIOAB(uint16_t value)
{
    bool readValue;
    while (1) // After duration set Pins to end state
    {
        if (xSemaphoreTake(mutex_i2c, BLOCK_TIME) == pdTRUE)
        {
            mcp_f.writeGPIOAB(value);
            break;
        }
        yield(); // We yield to feed the watchdog.
    }

    xSemaphoreGive(novaIO->mutex_i2c); // Give back the mutex
}

void NovaIO::mcpG_writeGPIOAB(uint16_t value)
{
    bool readValue;
    while (1) // After duration set Pins to end state
    {
        if (xSemaphoreTake(mutex_i2c, BLOCK_TIME) == pdTRUE)
        {
            mcp_g.writeGPIOAB(value);
            break;
        }
        yield(); // We yield to feed the watchdog.
    }

    xSemaphoreGive(novaIO->mutex_i2c); // Give back the mutex
}

void NovaIO::mcpH_writeGPIOAB(uint16_t value)
{
    bool readValue;
    while (1) // After duration set Pins to end state
    {
        if (xSemaphoreTake(mutex_i2c, BLOCK_TIME) == pdTRUE)
        {
            mcp_h.writeGPIOAB(value);
            break;
        }
        yield(); // We yield to feed the watchdog.
    }

    xSemaphoreGive(novaIO->mutex_i2c); // Give back the mutex
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
        //return;
        if (xSemaphoreTake(mutex_i2c, BLOCK_TIME) == pdTRUE)
        {
            if (expander == 0)
            {
                mcp_a.digitalWrite(pin, value);
            }
            else if (expander == 1)
            {
                mcp_b.digitalWrite(pin, value);
            }
            else if (expander == 2)
            {
                mcp_c.digitalWrite(pin, value);
            }
            else if (expander == 3)
            {
                mcp_d.digitalWrite(pin, value);
            }
            else if (expander == 4)
            {
                mcp_e.digitalWrite(pin, value);
            }
            else if (expander == 5)
            {
                mcp_f.digitalWrite(pin, value);
            }
            else if (expander == 6)
            {
                mcp_g.digitalWrite(pin, value);
            }
            else if (expander == 7)
            {
                mcp_h.digitalWrite(pin, value);
            }
            break;
        }
        yield(); // We yield to feed the watchdog.
        //delay(1);
    }

    xSemaphoreGive(novaIO->mutex_i2c); // Give back the mutex
}

void NovaIO::mcpB_digitalWrite(uint8_t pin, uint8_t value)
{
    while (1) // After duration set Pins to end state
    {
        if (xSemaphoreTake(mutex_i2c, BLOCK_TIME) == pdTRUE)
        {
            mcp_b.digitalWrite(pin, value);
            break;
        }
        yield(); // We yield to feed the watchdog.
    }

    xSemaphoreGive(novaIO->mutex_i2c); // Give back the mutex
}

void NovaIO::mcpC_digitalWrite(uint8_t pin, uint8_t value)
{
    while (1) // After duration set Pins to end state
    {
        if (xSemaphoreTake(mutex_i2c, BLOCK_TIME) == pdTRUE)
        {
            mcp_c.digitalWrite(pin, value);
            break;
        }
        yield(); // We yield to feed the watchdog.
    }

    xSemaphoreGive(novaIO->mutex_i2c); // Give back the mutex
}

void NovaIO::mcpD_digitalWrite(uint8_t pin, uint8_t value)
{
    while (1) // After duration set Pins to end state
    {
        if (xSemaphoreTake(mutex_i2c, BLOCK_TIME) == pdTRUE)
        {
            mcp_d.digitalWrite(pin, value);
            break;
        }
        yield(); // We yield to feed the watchdog.
    }

    xSemaphoreGive(novaIO->mutex_i2c); // Give back the mutex
}

void NovaIO::mcpE_digitalWrite(uint8_t pin, uint8_t value)
{
    while (1) // After duration set Pins to end state
    {
        if (xSemaphoreTake(mutex_i2c, BLOCK_TIME) == pdTRUE)
        {
            mcp_e.digitalWrite(pin, value);
            break;
        }
        yield(); // We yield to feed the watchdog.
    }

    xSemaphoreGive(novaIO->mutex_i2c); // Give back the mutex
}

void NovaIO::mcpF_digitalWrite(uint8_t pin, uint8_t value)
{
    while (1) // After duration set Pins to end state
    {
        if (xSemaphoreTake(mutex_i2c, BLOCK_TIME) == pdTRUE)
        {
            mcp_f.digitalWrite(pin, value);
            break;
        }
        yield(); // We yield to feed the watchdog.
    }

    xSemaphoreGive(novaIO->mutex_i2c); // Give back the mutex
}

void NovaIO::mcpG_digitalWrite(uint8_t pin, uint8_t value)
{
    while (1) // After duration set Pins to end state
    {
        if (xSemaphoreTake(mutex_i2c, BLOCK_TIME) == pdTRUE)
        {
            mcp_g.digitalWrite(pin, value);
            break;
        }
        yield(); // We yield to feed the watchdog.
    }

    xSemaphoreGive(novaIO->mutex_i2c); // Give back the mutex
}

void NovaIO::mcpH_digitalWrite(uint8_t pin, uint8_t value)
{
    while (1) // After duration set Pins to end state
    {
        if (xSemaphoreTake(mutex_i2c, BLOCK_TIME) == pdTRUE)
        {
            mcp_h.digitalWrite(pin, value);
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