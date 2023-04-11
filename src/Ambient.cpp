#include <Arduino.h>
#include "Ambient.h"
#include "configuration.h"
#include "NovaIO.h"

Ambient *ambient = NULL;

Ambient::Ambient()
{

    // Setup goes in here
}

void Ambient::loop()
{

    if (systemEnable == true && digitalRead(ENABLE_DEVICE_PIN) == true)
    {
        if (0)
        {
            novaIO->mcpA_writeGPIOAB(0b1111111111111111);
            novaIO->mcpB_writeGPIOAB(0b1111111111111111);
            novaIO->mcpC_writeGPIOAB(0b1111111111111111);
            novaIO->mcpD_writeGPIOAB(0b1111111111111111);
            novaIO->mcpE_writeGPIOAB(0b1111111111111111);
            delay(2000);

            novaIO->mcpA_writeGPIOAB(0b0000000000000000);
            novaIO->mcpB_writeGPIOAB(0b0000000000000000);
            novaIO->mcpC_writeGPIOAB(0b0000000000000000);
            novaIO->mcpD_writeGPIOAB(0b0000000000000000);
            novaIO->mcpE_writeGPIOAB(0b0000000000000000);
            delay(2000);
            // Play ambient display
        } else {
            //Serial.println("No ambient effects are running.");
            yield();
        }
    }
    else if (systemEnable == false && digitalRead(ENABLE_DEVICE_PIN) == true)
    {
        // System was disabled but it is now enabled.

        emergencyStopExit();
    }
    else if (systemEnable == true && digitalRead(ENABLE_DEVICE_PIN) == false)
    {
        emergencyStopEnter();
    }
    else if (systemEnable == false && digitalRead(ENABLE_DEVICE_PIN) == false)
    {
        // We are in the safety mode.

        analogWrite(BUTTON_RED_OUT, disabledBrightness);
        analogWrite(BUTTON_GREEN_OUT, disabledBrightness);
        analogWrite(BUTTON_BLUE_OUT, disabledBrightness);
        analogWrite(BUTTON_YELLOW_OUT, disabledBrightness);

        disabledBrightness = disabledBrightness + disabledBrightnessFade;
        // Serial.println("Safety!");
        // Serial.println(disabledBrightness);
        delay(2);
    }
}

/*
This will initilaize our system back to a safe spot after emergency stop is exited.
*/
void Ambient::emergencyStopExit()
{

    Serial.println("System is returning from emergency stop. Rebooting...");

    // Set the brightness to 0.
    disabledBrightness = 0;
    analogWrite(BUTTON_RED_OUT, disabledBrightness);
    analogWrite(BUTTON_GREEN_OUT, disabledBrightness);
    analogWrite(BUTTON_BLUE_OUT, disabledBrightness);
    analogWrite(BUTTON_YELLOW_OUT, disabledBrightness);

    // Set pin modes back to output (disable analog)

    //systemEnable = true;

    delay(100);
    // When the emergency button is disabled (set to active) reboot the system.
    ESP.restart();


}

/*
Emergency stop has been called. We need to begin shutdown.
*/
void Ambient::emergencyStopEnter()
{

    Serial.println("Emergency Stop Activated. Entering fail safe.");

    // Turn off all the outputs a few times incase there is a problem in the i2c bus

    for (int i = 0; i <= 4; i++)
    {
        // Turn off all the outputs.
        novaIO->mcpA_writeGPIOAB(0b0000000000000000);
        novaIO->mcpB_writeGPIOAB(0b0000000000000000);
        novaIO->mcpC_writeGPIOAB(0b0000000000000000);
        novaIO->mcpD_writeGPIOAB(0b0000000000000000);
        novaIO->mcpE_writeGPIOAB(0b0000000000000000);

        // Add a small delay to let the i2c bus settle down
        delay(1);
    }

    systemEnable = false;
}

bool Ambient::isSystemEnabled(void)
{
    //Serial.print("Is System Enabled? ");
    //Serial.println(systemEnable);
    return systemEnable;
}