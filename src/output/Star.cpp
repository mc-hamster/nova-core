#include <Arduino.h>
#include "Star.h"
#include "configuration.h"
#include "NovaIO.h"

Star *star = NULL;

Star::Star()
{

    // Setup the stars
    setupStar();
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
    uint8_t outputStar = 0;
    uint16_t pooferInterval = random(pooferIntervalMin, pooferIntervalMax);

    //Serial.println(pooferInterval);

    if (redState == RED_POOF)
    {
        if (goPoof(0, pooferInterval, pooferInterval / 2))
        {
            redState = RED_OFF;
        }
    }
    else if (redState == RED_POOF_MULTI)
    {
        if (cluster.stars[outputStar].pooferCountsRemaining == 0)
        {
            cluster.stars[outputStar].pooferCountsRemaining = 30;
        }

        if (cluster.stars[outputStar].pooferCountsRemaining)
        {
            if (goPoof(outputStar, pooferInterval, pooferInterval * 3))
            {
                cluster.stars[outputStar].pooferCountsRemaining--;
            }
        }

        if (cluster.stars[outputStar].pooferCountsRemaining == 0)
        {
            redState = RED_OFF;
        }
    }
    else if (redState == RED_BOOM)
    {
    }
}

void Star::green_loop(void)
{
    uint8_t outputStar = 1;
    uint16_t pooferInterval = random(pooferIntervalMin, pooferIntervalMax);

    if (greenState == GREEN_POOF)
    {

        if (goPoof(outputStar, pooferInterval, pooferInterval / 2))
        {
            greenState = GREEN_OFF;
        }
    }
    else if (greenState == GREEN_POOF_MULTI)
    {
        if (cluster.stars[outputStar].pooferCountsRemaining == 0)
        {
            cluster.stars[outputStar].pooferCountsRemaining = 30;
        }

        if (cluster.stars[outputStar].pooferCountsRemaining)
        {
            if (goPoof(outputStar, pooferInterval, pooferInterval * 3))
            {
                cluster.stars[outputStar].pooferCountsRemaining--;
            }
        }

        if (cluster.stars[outputStar].pooferCountsRemaining == 0)
        {
            greenState = GREEN_OFF;
        }
    }
}

void Star::blue_loop(void)
{
    uint8_t outputStar = 2;
    uint16_t pooferInterval = random(pooferIntervalMin, pooferIntervalMax);

    if (blueState == BLUE_POOF)
    {

        if (goPoof(2, pooferInterval, pooferInterval / 2))
        {
            blueState = BLUE_OFF;
        }
    }
    else if (blueState == BLUE_POOF_MULTI)
    {
        if (cluster.stars[outputStar].pooferCountsRemaining == 0)
        {
            cluster.stars[outputStar].pooferCountsRemaining = 30;
        }

        if (cluster.stars[outputStar].pooferCountsRemaining)
        {
            if (goPoof(outputStar, pooferInterval, pooferInterval * 3))
            {
                cluster.stars[outputStar].pooferCountsRemaining--;
            }
        }

        if (cluster.stars[outputStar].pooferCountsRemaining == 0)
        {
            blueState = BLUE_OFF;
        }
    }
}

void Star::yellow_loop(void)
{
    uint8_t outputStar = 3;
    uint16_t pooferInterval = random(pooferIntervalMin, pooferIntervalMax);

    if (yellowState == YELLOW_POOF)
    {

        if (goPoof(3, pooferInterval, pooferInterval / 2))
        {
            yellowState = YELLOW_OFF;
        }
    }
    else if (yellowState == YELLOW_POOF_MULTI)
    {
        if (cluster.stars[outputStar].pooferCountsRemaining == 0)
        {
            cluster.stars[outputStar].pooferCountsRemaining = 30;
        }

        if (cluster.stars[outputStar].pooferCountsRemaining)
        {
            if (goPoof(outputStar, pooferInterval, pooferInterval * 3))
            {
                cluster.stars[outputStar].pooferCountsRemaining--;
            }
        }

        if (cluster.stars[outputStar].pooferCountsRemaining == 0)
        {
            yellowState = YELLOW_OFF;
        }
    }
}

void Star::red(RedButtonState state)
{
    Serial.println("RED POOF");
    redState = state;
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

/*
    Setup the mapping between stars and the outputs that control the star.
    Note: We assume all devices are on the same GPIO Expansion chip.
*/
void Star::setupStar(void)
{

    cluster.stars[0].expander = 0;
    cluster.stars[0].blowerOutput = 0;
    cluster.stars[0].fuelOutput = 1;
    cluster.stars[0].igniterOutput = 2;
    cluster.stars[0].pooferOutput = 3;
    cluster.stars[0].blowerOutputDuty = 255;

    cluster.stars[1].expander = 0;
    cluster.stars[1].blowerOutput = 4;
    cluster.stars[1].fuelOutput = 5;
    cluster.stars[1].igniterOutput = 6;
    cluster.stars[1].pooferOutput = 7;
    cluster.stars[1].blowerOutputDuty = 255;

    cluster.stars[2].expander = 0;
    cluster.stars[2].blowerOutput = 8;
    cluster.stars[2].fuelOutput = 9;
    cluster.stars[2].igniterOutput = 10;
    cluster.stars[2].pooferOutput = 11;
    cluster.stars[2].blowerOutputDuty = 255;

    cluster.stars[3].expander = 0;
    cluster.stars[3].blowerOutput = 12;
    cluster.stars[3].fuelOutput = 13;
    cluster.stars[3].igniterOutput = 14;
    cluster.stars[3].pooferOutput = 15;
    cluster.stars[3].blowerOutputDuty = 255;

    for (uint32_t i = 0; i < 20; i++)
    {
        cluster.stars[i].pooferCountsRemaining = 0;
        cluster.stars[i].pooferOutputState = 0;
        cluster.stars[i].pooferOutputState = 0;
    }
}

bool Star::goPoof(uint8_t star, uint32_t intervalOn, uint32_t intervalOff)
{
    uint32_t currentMillis = millis();
    //Serial.println("1");
    if (cluster.stars[star].pooferOutputState == POOF_ON)
    {
        //Serial.println("2");
        Serial.print("goPoof: On ");
        Serial.print(star);
        Serial.println();
        cluster.stars[star].pooferPreviousMillis = currentMillis;
        novaIO->mcpA_digitalWrite(cluster.stars[star].pooferOutput, HIGH);
        cluster.stars[star].pooferOutputState = POOF_ON_IDLE;
    }

    if (cluster.stars[star].pooferOutputState == POOF_ON_IDLE)
    {
        if (currentMillis - cluster.stars[star].pooferPreviousMillis >= intervalOn)
        {
            cluster.stars[star].pooferOutputState = POOF_OFF;
        }
    }

    if (cluster.stars[star].pooferOutputState == POOF_OFF)
    {
        novaIO->mcpA_digitalWrite(cluster.stars[star].pooferOutput, LOW);
        cluster.stars[star].pooferOutputState = POOF_OFF_IDLE;
    }

    if (cluster.stars[star].pooferOutputState == POOF_OFF_IDLE)
    {
        if (currentMillis - cluster.stars[star].pooferPreviousMillis >= intervalOn + intervalOff)
        {
            cluster.stars[star].pooferOutputState = POOF_ON;
            return 1;
        }
    }

    return 0; // We are not yet done with our task
}