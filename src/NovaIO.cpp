#include <Arduino.h>
#include <Adafruit_MCP23X17.h>
// #include <Arduino_FreeRTOS.h>
// #include <semphr.h>

#include "NovaIO.h"
#include "configuration.h"

// AirTime *airTime = NULL;

NovaIO *novaIO = NULL;

NovaIO::NovaIO()
{
    // Do nothing


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

        //mcp_h.pinMode(i, OUTPUT);
    }

    mcp_h.pinMode(BUTTON_GREEN_IN_PIN, INPUT);


    // Turn off all outputs
    mcp_a.writeGPIOAB(0b0000000000000000);
    mcp_b.writeGPIOAB(0b0000000000000000);
    mcp_c.writeGPIOAB(0b0000000000000000);
    mcp_d.writeGPIOAB(0b0000000000000000);
    mcp_e.writeGPIOAB(0b0000000000000000);

}

void NovaIO::digitalWrite(enum expansionIO, int pin, bool state)
{

    mcp_a.writeGPIOAB(0b1111111111111111);

    delay(100);

    mcp_a.writeGPIOAB(0b0000000000000000);

    delay(100);
}

bool NovaIO::digitalRead(int which, int pin)
{
    Serial.print("digitalRead ");
    Serial.println(which);


    bool readValue = mcp_h.digitalRead(pin);
    Serial.println("read value ");

    return readValue;
    
    if (which == expA)
    {
    }
    else if (which == expB)
    {
    }
    else if (which == expC)
    {
    }
    else if (which == expD)
    {
    }
    else if (which == expE)
    {
    }
    else if (which == expF)
    {
    }
    else if (which == expH)
    {
    }
    else if (which == expH)
    {
    }

    return 0;
}