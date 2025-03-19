#include <Arduino.h>
#include "Enable.h"
#include "configuration.h"
#include "NovaIO.h"
#include "output/StarSequence.h"
#include "utilities/PreferencesManager.h"
#include "LightUtils.h"

/*

This is the Enable class. It is responsible for the emergency stop functionality.

*/

Enable *enable = NULL;
extern LightUtils *lightUtils;

Enable::Enable()
{

    // Setup goes in here
}

void Enable::loop()
{

    if (systemEnable == true && digitalRead(ENABLE_DEVICE_PIN) == true)
    {
        // Serial.println("No enabled effects are running.");
        yield();
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

        delay(2);
    }
}

/*
This function is called when the emergency stop is exited. It checks if the system should reboot or not. If rebootOnEmergencyStopExit is true, the system will reboot. Otherwise, the system will be enabled and the disabledBrightness will be set to 0.

@param None
@return None
*/
void Enable::emergencyStopExit()
{

    bool rebootOnEmergencyStopExit = false;

    if (rebootOnEmergencyStopExit)
    {
        Serial.println("System is returning from emergency stop. Rebooting...");

        // Set the brightness to 0.
        disabledBrightness = 0;

        // Set pin modes back to output (disable analog)

        analogWrite(BUTTON_RED_OUT, disabledBrightness);
        analogWrite(BUTTON_GREEN_OUT, disabledBrightness);
        analogWrite(BUTTON_BLUE_OUT, disabledBrightness);
        analogWrite(BUTTON_YELLOW_OUT, disabledBrightness);
        delay(100);

        // When the emergency button is disabled (set to active) reboot the system.
        ESP.restart();
    }
    else
    {
        Serial.println("System is returning from emergency stop. Not Rebooting...");

        // Incase a sequence was running, turn it off.
        starSequence->setSequence(starSequence->SEQ_OFF);

        // Resume game task if it exists
        TaskHandle_t gameTaskHandle = xTaskGetHandle("Game Task");
        if (gameTaskHandle != NULL) {
            vTaskResume(gameTaskHandle);
            Serial.println("Game task resumed");
        }

        // Resume NovaNow task if it exists
        TaskHandle_t novaNowHandle = xTaskGetHandle("NovaNow");
        if (novaNowHandle != NULL) {
            vTaskResume(novaNowHandle);
            Serial.println("NovaNow task resumed");
        }

        systemEnable = true;
    }
}

/*
This function is called when the emergency stop is entered. It turns off all the outputs and sets the systemEnable to false.

@param None
@return None
*/
void Enable::emergencyStopEnter()
{
    Serial.println("Emergency Stop Activated. Entering fail safe.");

    // Incase a sequence was running, turn it off.
    starSequence->setSequence(starSequence->SEQ_OFF);

    // Suspend game task if it exists
    TaskHandle_t gameTaskHandle = xTaskGetHandle("Game Task");
    if (gameTaskHandle != NULL) {
        vTaskSuspend(gameTaskHandle);
        lightUtils->unprotectAllLeds();
        Serial.println("Game task suspended and LEDs unprotected");
    }

    // Suspend NovaNow task if it exists
    TaskHandle_t novaNowHandle = xTaskGetHandle("NovaNow");
    if (novaNowHandle != NULL) {
        vTaskSuspend(novaNowHandle);
        Serial.println("NovaNow task suspended");
    }

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

/*
This function returns the current state of the systemEnable variable.

@param None
@return bool - The current state of the systemEnable variable.
*/
bool Enable::isSystemEnabled(void)
{
    // Serial.print("Is System Enabled? ");
    // Serial.println(systemEnable);
    return systemEnable;
}

/*
This function returns the current state of the cfgDrunktard variable.

@param None
@return bool - The current state of the cfgDrunktard variable.
*/
bool Enable::isDrunktard(void)
{
    bool result = PreferencesManager::getBool("cfgDrunktard", false);
    //Serial.print("isDrunktard returning: ");
    //Serial.println(result);
    return result;
}