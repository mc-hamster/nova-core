#include <Arduino.h>
#include <Adafruit_MCP23X17.h>

#include "NovaIO.h"
#include "configuration.h"
#include "main.h"

NovaIO *novaIO = NULL;

NovaIO::NovaIO()
{
    // Initialize output ports to 0
    expOutPort_A = 0x00;
    expOutPort_B = 0x00;
    expOutPort_C = 0x00;
    expOutPort_D = 0x00;
    expOutPort_E = 0x00;
    expOutPort_F = 0x00;
    expOutPort_G = 0x00;
    expOutPort_H = 0x00;

    // Create mutex semaphore for I2C bus
    mutex_i2c = xSemaphoreCreateMutex();

    // Initialize all devices on the bus
    Serial.println("MCP23X17 interfaces setup.");

    // Create an array of all the MCP23X17 devices
    Adafruit_MCP23X17 mcpDevices[] = {mcp_a, mcp_b, mcp_c, mcp_d, mcp_e, mcp_f, mcp_g, mcp_h};

    // Get the number of devices in the array
    const uint8_t numDevices = sizeof(mcpDevices) / sizeof(mcpDevices[0]);

    // Initialize each device on the bus
    for (uint8_t i = 0; i < numDevices; i++)
    {
        // Initialize the device at the current index
        if (!mcpDevices[i].begin_I2C(0x20 + i))
        {
            Serial.print("Error - mcp_");
            Serial.println(i);
            while (1)
                ;
        }

        // Set the pin mode of each pin on the device to OUTPUT
        for (uint8_t j = 0; j < 16; j++)
        {
            mcpDevices[i].pinMode(j, OUTPUT);
        }
    }

    // Set the pin mode of the button inputs separately
    mcp_h.pinMode(BUTTON_RED_IN, INPUT);
    mcp_h.pinMode(BUTTON_GREEN_IN, INPUT);
    mcp_h.pinMode(BUTTON_BLUE_IN, INPUT);
    mcp_h.pinMode(BUTTON_YELLOW_IN, INPUT);
    mcp_h.pinMode(BUTTON_WHITE_IN, INPUT);

    // Set all outputs to the initialized state
    mcp_a.writeGPIOAB(expOutPort_A);
    mcp_b.writeGPIOAB(expOutPort_B);
    mcp_c.writeGPIOAB(expOutPort_C);
    mcp_d.writeGPIOAB(expOutPort_D);
    mcp_e.writeGPIOAB(expOutPort_E);
    mcp_f.writeGPIOAB(expOutPort_F);
    mcp_g.writeGPIOAB(expOutPort_G);

    // Print a message to indicate that the MCP23X17 interfaces have been initialized
    Serial.println("MCP23X17 interfaces outputs set to initialized value.");
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
        if (xSemaphoreTake(mutex_i2c, 100) == pdTRUE)
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
        if (xSemaphoreTake(mutex_i2c, 100) == pdTRUE)
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
        if (xSemaphoreTake(mutex_i2c, 100) == pdTRUE)
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
        if (xSemaphoreTake(mutex_i2c, 100) == pdTRUE)
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
        if (xSemaphoreTake(mutex_i2c, 100) == pdTRUE)
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
        if (xSemaphoreTake(mutex_i2c, 100) == pdTRUE)
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
        if (xSemaphoreTake(mutex_i2c, 100) == pdTRUE)
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
        if (xSemaphoreTake(mutex_i2c, 100) == pdTRUE)
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
        if (xSemaphoreTake(mutex_i2c, 100) == pdTRUE)
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
        if (xSemaphoreTake(mutex_i2c, 100) == pdTRUE)
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
    }

    xSemaphoreGive(novaIO->mutex_i2c); // Give back the mutex
}

void NovaIO::mcpB_digitalWrite(uint8_t pin, uint8_t value)
{
    while (1) // After duration set Pins to end state
    {
        if (xSemaphoreTake(mutex_i2c, 100) == pdTRUE)
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
        if (xSemaphoreTake(mutex_i2c, 100) == pdTRUE)
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
        if (xSemaphoreTake(mutex_i2c, 100) == pdTRUE)
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
        if (xSemaphoreTake(mutex_i2c, 100) == pdTRUE)
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
        if (xSemaphoreTake(mutex_i2c, 100) == pdTRUE)
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
        if (xSemaphoreTake(mutex_i2c, 100) == pdTRUE)
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
        if (xSemaphoreTake(mutex_i2c, 100) == pdTRUE)
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
