#include <Arduino.h>
#include <Adafruit_MCP23X17.h>

#include "NovaIO.h"
#include "configuration.h"
#include "main.h"

// AirTime *airTime = NULL;

NovaIO *novaIO = NULL;

NovaIO::NovaIO()
{
    // Do nothing

    mutex_i2c = xSemaphoreCreateMutex();

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

    Serial.println("All MCP23X17 interfaces setup.");

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

        // mcp_h.pinMode(i, OUTPUT);
    }

    mcp_h.pinMode(BUTTON_RED_IN, INPUT);
    mcp_h.pinMode(BUTTON_GREEN_IN, INPUT);
    mcp_h.pinMode(BUTTON_BLUE_IN, INPUT);
    mcp_h.pinMode(BUTTON_YELLOW_IN, INPUT);
    mcp_h.pinMode(BUTTON_WHITE_IN, INPUT);

    // Turn off all outputs
    mcp_a.writeGPIOAB(0b0000000000000000);
    mcp_b.writeGPIOAB(0b0000000000000000);
    mcp_c.writeGPIOAB(0b0000000000000000);
    mcp_d.writeGPIOAB(0b0000000000000000);
    mcp_e.writeGPIOAB(0b0000000000000000);
    Serial.println("All MCP23X17 interfaces setup. - Done");
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
        if (xSemaphoreTake(mutex_i2c, 100) == pdTRUE)
        {
            readValue = mcp_h.digitalRead(pin);
            break;
        }
        yield();
    }

    xSemaphoreGive(novaIO->mutex_i2c); // Give back the mutex
    return readValue;
}

void NovaIO::mcpA_writeGPIOAB(uint16_t value)
{
    bool readValue;
    while (1) // After duration set Pins to end state
    {
        if (xSemaphoreTake(mutex_i2c, 100) == pdTRUE)
        {
            mcp_a.writeGPIOAB(value);
            break;
        }
        yield();
    }

    xSemaphoreGive(novaIO->mutex_i2c); // Give back the mutex
}

void NovaIO::mcpB_writeGPIOAB(uint16_t value)
{
    bool readValue;
    while (1) // After duration set Pins to end state
    {
        if (xSemaphoreTake(mutex_i2c, 100) == pdTRUE)
        {
            mcp_b.writeGPIOAB(value);
            break;
        }
        yield();
    }

    xSemaphoreGive(novaIO->mutex_i2c); // Give back the mutex
}

void NovaIO::mcpC_writeGPIOAB(uint16_t value)
{
    bool readValue;
    while (1) // After duration set Pins to end state
    {
        if (xSemaphoreTake(mutex_i2c, 100) == pdTRUE)
        {
            mcp_c.writeGPIOAB(value);
            break;
        }
        yield();
    }

    xSemaphoreGive(novaIO->mutex_i2c); // Give back the mutex
}

void NovaIO::mcpD_writeGPIOAB(uint16_t value)
{
    bool readValue;
    while (1) // After duration set Pins to end state
    {
        if (xSemaphoreTake(mutex_i2c, 100) == pdTRUE)
        {
            mcp_d.writeGPIOAB(value);
            break;
        }
        yield();
    }

    xSemaphoreGive(novaIO->mutex_i2c); // Give back the mutex
}

void NovaIO::mcpE_writeGPIOAB(uint16_t value)
{
    bool readValue;
    while (1) // After duration set Pins to end state
    {
        if (xSemaphoreTake(mutex_i2c, 100) == pdTRUE)
        {
            mcp_e.writeGPIOAB(value);
            break;
        }
        yield();
    }

    xSemaphoreGive(novaIO->mutex_i2c); // Give back the mutex
}

void NovaIO::mcpF_writeGPIOAB(uint16_t value)
{
    bool readValue;
    while (1) // After duration set Pins to end state
    {
        if (xSemaphoreTake(mutex_i2c, 100) == pdTRUE)
        {
            mcp_f.writeGPIOAB(value);
            break;
        }
        yield();
    }

    xSemaphoreGive(novaIO->mutex_i2c); // Give back the mutex
}

void NovaIO::mcpG_writeGPIOAB(uint16_t value)
{
    bool readValue;
    while (1) // After duration set Pins to end state
    {
        if (xSemaphoreTake(mutex_i2c, 100) == pdTRUE)
        {
            mcp_g.writeGPIOAB(value);
            break;
        }
        yield();
    }

    xSemaphoreGive(novaIO->mutex_i2c); // Give back the mutex
}

void NovaIO::mcpH_writeGPIOAB(uint16_t value)
{
    bool readValue;
    while (1) // After duration set Pins to end state
    {
        if (xSemaphoreTake(mutex_i2c, 100) == pdTRUE)
        {
            mcp_h.writeGPIOAB(value);
            break;
        }
        yield();
    }

    xSemaphoreGive(novaIO->mutex_i2c); // Give back the mutex
}
