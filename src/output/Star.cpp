#include <Arduino.h>
#include "Star.h"
#include "configuration.h"
#include "NovaIO.h"

Star *star = NULL;

Star::Star()
{

    // Setup goes in here
}

void Star::loop()
{

    if (systemEnable == true && digitalRead(ENABLE_DEVICE_PIN) == true)
    {
        /*
        novaIO->mcpA_digitalWrite(1, HIGH);
        delay(500);
        novaIO->mcpA_digitalWrite(1, LOW);
        delay(500);
        */

        red_loop();
        green_loop();
        blue_loop();
        yellow_loop();
    }
}

void Star::red_loop(void)
{
    const uint32_t interval = pooferInterval;

    if (redState == RED_POOF)
    {

        uint32_t currentMillis = millis();

        if (!redPooferOn && currentMillis - redPreviousMillis >= interval)
        {

            Serial.println("in the timer - A");
            Serial.println(currentMillis);
            Serial.println(redPreviousMillis);
            Serial.println(currentMillis - redPreviousMillis);

            redPreviousMillis = currentMillis;

            digitalWrite(BUTTON_RED_OUT, HIGH);
            novaIO->mcpA_digitalWrite(3, HIGH);
            redPooferOn = 1;
        }

        if (redPooferOn && currentMillis - redPreviousMillis >= interval)
        {
            Serial.println("in the timer - B");
            Serial.println(currentMillis);
            Serial.println(redPreviousMillis);
            Serial.println(currentMillis - redPreviousMillis);

            digitalWrite(BUTTON_RED_OUT, LOW);
            novaIO->mcpA_digitalWrite(3, LOW);
            redPooferOn = 0;
            redState = RED_OFF;
        }
    }
}

void Star::green_loop(void)
{
    const uint32_t interval = pooferInterval;

    if (greenState == GREEN_POOF)
    {

        uint32_t currentMillis = millis();

        if (!greenPooferOn && currentMillis - greenPreviousMillis >= interval)
        {

            Serial.println("in the timer - A");
            Serial.println(currentMillis);
            Serial.println(greenPreviousMillis);
            Serial.println(currentMillis - greenPreviousMillis);

            greenPreviousMillis = currentMillis;

            digitalWrite(BUTTON_GREEN_OUT, HIGH);
            novaIO->mcpA_digitalWrite(7, HIGH);
            greenPooferOn = 1;
        }

        if (greenPooferOn && currentMillis - greenPreviousMillis >= interval)
        {
            Serial.println("in the timer - B");
            Serial.println(currentMillis);
            Serial.println(greenPreviousMillis);
            Serial.println(currentMillis - greenPreviousMillis);

            digitalWrite(BUTTON_GREEN_OUT, LOW);
            novaIO->mcpA_digitalWrite(7, LOW);
            greenPooferOn = 0;
            greenState = GREEN_OFF;
        }
    }
}

void Star::blue_loop(void)
{
    const uint32_t interval = pooferInterval;

    if (blueState == BLUE_POOF)
    {

        uint32_t currentMillis = millis();

        if (!bluePooferOn && currentMillis - bluePreviousMillis >= interval)
        {

            Serial.println("in the timer - A");
            Serial.println(currentMillis);
            Serial.println(bluePreviousMillis);
            Serial.println(currentMillis - bluePreviousMillis);

            bluePreviousMillis = currentMillis;

            digitalWrite(BUTTON_BLUE_OUT, HIGH);
            novaIO->mcpA_digitalWrite(11, HIGH);
            bluePooferOn = 1;
        }

        if (bluePooferOn && currentMillis - bluePreviousMillis >= interval)
        {
            Serial.println("in the timer - B");
            Serial.println(currentMillis);
            Serial.println(bluePreviousMillis);
            Serial.println(currentMillis - bluePreviousMillis);

            digitalWrite(BUTTON_BLUE_OUT, LOW);
            novaIO->mcpA_digitalWrite(11, LOW);
            bluePooferOn = 0;
            blueState = BLUE_OFF;
        }
    }
}

void Star::yellow_loop(void)
{
    const uint32_t interval = pooferInterval;

    if (yellowState == YELLOW_POOF)
    {

        uint32_t currentMillis = millis();

        if (!yellowPooferOn && currentMillis - yellowPreviousMillis >= interval)
        {

            Serial.println("in the timer - A");
            Serial.println(currentMillis);
            Serial.println(yellowPreviousMillis);
            Serial.println(currentMillis - yellowPreviousMillis);

            yellowPreviousMillis = currentMillis;

            digitalWrite(BUTTON_YELLOW_OUT, HIGH);
            novaIO->mcpA_digitalWrite(15, HIGH);
            yellowPooferOn = 1;
        }

        if (yellowPooferOn && currentMillis - yellowPreviousMillis >= interval)
        {
            Serial.println("in the timer - B");
            Serial.println(currentMillis);
            Serial.println(yellowPreviousMillis);
            Serial.println(currentMillis - yellowPreviousMillis);

            digitalWrite(BUTTON_YELLOW_OUT, LOW);
            novaIO->mcpA_digitalWrite(15, LOW);
            yellowPooferOn = 0;
            yellowState = YELLOW_OFF;
        }
    }

}

void Star::red(RedButtonState state)
{
    Serial.println("RED POOF");
    redState = state;
    // redHasPoofed = 0;
}

void Star::green(GreenButtonState state)
{
    Serial.println("GREEN POOF");
    greenState = state;
}

void Star::blue(BlueButtonState state)
{
    Serial.println("BLUE POOF");
    blueState = state;
}

void Star::yellow(YellowButtonState state)
{
    Serial.println("YELLOW POOF");
    yellowState = state;
}