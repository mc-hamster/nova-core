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

    // Serial.println(pooferInterval);

    if (redPooferState == RED_POOF)
    {
        if (goPoof(0, pooferInterval, pooferInterval / 2))
        {
            redPooferState = RED_OFF;
        }
    }
    else if (redPooferState == RED_POOF_MULTI)
    {
        if (cluster.stars[outputStar].pooferCountsRemaining == 0)
        {
            cluster.stars[outputStar].pooferCountsRemaining = 30;
        }

        if (cluster.stars[outputStar].pooferCountsRemaining)
        {
            if (goPoof(outputStar, pooferInterval, pooferInterval * 7))
            {
                cluster.stars[outputStar].pooferCountsRemaining--;
            }
        }

        if (cluster.stars[outputStar].pooferCountsRemaining == 0)
        {
            redPooferState = RED_OFF;
        }
    }

    if (redBoomerState == BOOMER_ON)
    {
        if (goBoom(outputStar))
        {
            Serial.println("Setting: BOOMER_OFF - Starting the boomer");
            redBoomerState = BOOMER_OFF;
        }
    }
    else if (redBoomerState == BOOMER_OFF)
    {
        // if (goBoom(outputStar))
        //{
        if (goBoom(outputStar))
        {
            redBoomerState = BOOMER_OFF;
        }
        else
        {
            Serial.println("Setting: BOOMER_ABORT - Aborting the boomer");
            redBoomerState = BOOMER_ABORT;
        }
        //}
    }
}

void Star::green_loop(void)
{
    uint8_t outputStar = 1;
    uint16_t pooferInterval = random(pooferIntervalMin, pooferIntervalMax);

    if (greenPooferState == GREEN_POOF)
    {

        if (goPoof(outputStar, pooferInterval, pooferInterval / 2))
        {
            greenPooferState = GREEN_OFF;
        }
    }
    else if (greenPooferState == GREEN_POOF_MULTI)
    {
        if (cluster.stars[outputStar].pooferCountsRemaining == 0)
        {
            cluster.stars[outputStar].pooferCountsRemaining = 30;
        }

        if (cluster.stars[outputStar].pooferCountsRemaining)
        {
            if (goPoof(outputStar, pooferInterval, pooferInterval * 7))
            {
                cluster.stars[outputStar].pooferCountsRemaining--;
            }
        }

        if (cluster.stars[outputStar].pooferCountsRemaining == 0)
        {
            greenPooferState = GREEN_OFF;
        }
    }
}

void Star::blue_loop(void)
{
    uint8_t outputStar = 2;
    uint16_t pooferInterval = random(pooferIntervalMin, pooferIntervalMax);

    if (bluePooferState == BLUE_POOF)
    {

        if (goPoof(2, pooferInterval, pooferInterval / 2))
        {
            bluePooferState = BLUE_OFF;
        }
    }
    else if (bluePooferState == BLUE_POOF_MULTI)
    {
        if (cluster.stars[outputStar].pooferCountsRemaining == 0)
        {
            cluster.stars[outputStar].pooferCountsRemaining = 30;
        }

        if (cluster.stars[outputStar].pooferCountsRemaining)
        {
            if (goPoof(outputStar, pooferInterval, pooferInterval * 7))
            {
                cluster.stars[outputStar].pooferCountsRemaining--;
            }
        }

        if (cluster.stars[outputStar].pooferCountsRemaining == 0)
        {
            bluePooferState = BLUE_OFF;
        }
    }
}

void Star::yellow_loop(void)
{
    uint8_t outputStar = 3;
    uint16_t pooferInterval = random(pooferIntervalMin, pooferIntervalMax);

    if (yellowPooferState == YELLOW_POOF)
    {

        if (goPoof(3, pooferInterval, pooferInterval / 2))
        {
            yellowPooferState = YELLOW_OFF;
        }
    }
    else if (yellowPooferState == YELLOW_POOF_MULTI)
    {
        if (cluster.stars[outputStar].pooferCountsRemaining == 0)
        {
            cluster.stars[outputStar].pooferCountsRemaining = 30;
        }

        if (cluster.stars[outputStar].pooferCountsRemaining)
        {
            if (goPoof(outputStar, pooferInterval, pooferInterval * 7))
            {
                cluster.stars[outputStar].pooferCountsRemaining--;
            }
        }

        if (cluster.stars[outputStar].pooferCountsRemaining == 0)
        {
            yellowPooferState = YELLOW_OFF;
        }
    }
}

void Star::redPoof(RedButtonState state)
{
    // Serial.println("RED POOF");
    redPooferState = state;
}

void Star::redBoom(boomerButtonState state)
{
    // Serial.println("RED BOOM");
    redBoomerState = state;
}

void Star::greenPoof(GreenButtonState state)
{
    // Serial.println("GREEN POOF");
    greenPooferState = state;
}

void Star::bluePoof(BlueButtonState state)
{
    // Serial.println("BLUE POOF");
    bluePooferState = state;
}

void Star::yellowPoof(YellowButtonState state)
{
    // Serial.println("YELLOW POOF");
    yellowPooferState = state;
}

/*
    Setup the mapping between stars and the outputs that control the star.
    Note: We assume all devices are on the same GPIO Expansion chip.
*/
void Star::setupStar(void)
{

    redPooferState = POOF_ON;
    greenPooferState = POOF_ON;
    bluePooferState = POOF_ON;
    yellowPooferState = POOF_ON;

    redBoomerState = BOOMER_IDLE;
    greenBoomerState = BOOMER_IDLE;
    blueBoomerState = BOOMER_IDLE;
    yellowBoomerState = BOOMER_IDLE;

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
        cluster.stars[i].boomer.outputState = BOOMER_ACTIVE;
        cluster.stars[i].boomer.previousMillis = 0;
    }
}

bool Star::goBoom(uint8_t star)
{
    uint32_t currentMillis = millis();

    // Serial.println("asdf");

    /*
        enum BoomerStates
        {
            BOOMER_ACTIVE, // Boomer is ready for a Boom
            BOOMER_DEACTIVATED, // Boomer is disabled. Here for administrative purposes.
            BOOMER_ABORT, // Begin the abort sequence. (Turn off fuel, turn off igniter, enter BOOMER_BLOWER_EXHAUST)
            BOOMER_BLOWER_ON, // Turn on the blower
            BOOMER_BLOWER_ON_IDLE, // Wait for x-ms
            BOOMER_BLOWER_ON_FUEL_ON, // Turn on the fuel fill
            BOOMER_BLOWER_ON_FUEL_ON_IDLE, // Wait for x-ms
            BOOMER_BLOWER_ON_FUEL_OFF, // Turn off the fuel fill
            BOOMER_BLOWER_ON_FUEL_OFF_IDLE, // Wait for x-ms. Run this for maybe 50ms. This is just to clear the fill tube.
            BOOMER_BLOWER_OFF, // Turn the blower off
            BOOMER_BLOWER_OFF_IDLE, // Wait for x-ms. This will let the flap on the baffle close
            BOOMER_ZAP_ON, // Turn on the igniter
            BOOMER_ZAP_ON_IDLE, // Leave it on for a moment
            BOOMER_ZAP_OFF, // Turn the zapper off
            BOOMER_ZAP_OFF_IDLE, // Wait for a moment (Do we need this?)
            BOOMER_BLOWER_EXHAUST, // Begin to exhaust the boomer. This can't be aborted.
            BOOMER_BLOWER_EXHAUST_IDLE, // Boomer exhausting. This can't be aborted.
        };
    */

    if (cluster.stars[star].boomer.outputState == BOOMER_ABORT)
    {
        Serial.println("BOOMER_ABORT RECEIVED");
        cluster.stars[star].boomer.outputState = BOOMER_BLOWER_EXHAUST;
    }
    else if (cluster.stars[star].boomer.outputState == BOOMER_ACTIVE)
    {
        cluster.stars[star].boomer.previousMillis = millis();
        Serial.println("BOOMER_ACTIVE");
        Serial.println(millis());
        cluster.stars[star].boomer.outputState = BOOMER_BLOWER_ON;
    }
    else if (cluster.stars[star].boomer.outputState == BOOMER_BLOWER_ON)
    {
        cluster.stars[star].boomer.previousMillis = millis();
        Serial.println("BOOMER_BLOWER_ON");

        novaIO->mcpA_digitalWrite(cluster.stars[star].blowerOutput, HIGH);
        cluster.stars[star].boomer.outputState = BOOMER_BLOWER_ON_IDLE;
    }
    else if (cluster.stars[star].boomer.outputState == BOOMER_BLOWER_ON_IDLE)
    {
        if (currentMillis - cluster.stars[star].boomer.previousMillis >= 50)
        {
            cluster.stars[star].boomer.previousMillis = millis();
            Serial.println("BOOMER_BLOWER_ON_IDLE");
            Serial.println(currentMillis - cluster.stars[star].boomer.previousMillis);
            cluster.stars[star].boomer.outputState = BOOMER_BLOWER_ON_FUEL_ON;
        }
    }
    else if (cluster.stars[star].boomer.outputState == BOOMER_BLOWER_ON_FUEL_ON)
    {
        cluster.stars[star].boomer.previousMillis = millis();
        Serial.println("BOOMER_BLOWER_ON_FUEL_ON");

        novaIO->mcpA_digitalWrite(cluster.stars[star].blowerOutput, HIGH);
        novaIO->mcpA_digitalWrite(cluster.stars[star].fuelOutput, HIGH);
        cluster.stars[star].boomer.outputState = BOOMER_BLOWER_ON_FUEL_ON_IDLE;
    }
    else if (cluster.stars[star].boomer.outputState == BOOMER_BLOWER_ON_FUEL_ON_IDLE)
    {
        if (currentMillis - cluster.stars[star].boomer.previousMillis >= 2000)
        {
            cluster.stars[star].boomer.previousMillis = millis();
            Serial.println("BOOMER_BLOWER_ON_FUEL_ON_IDLE");
            cluster.stars[star].boomer.outputState = BOOMER_BLOWER_ON_FUEL_OFF;
        }
    }
    else if (cluster.stars[star].boomer.outputState == BOOMER_BLOWER_ON_FUEL_OFF)
    {
        cluster.stars[star].boomer.previousMillis = millis();
        Serial.println("BOOMER_BLOWER_ON_FUEL_OFF");

        // novaIO->mcpA_digitalWrite(cluster.stars[star].blowerOutput, HIGH);
        novaIO->mcpA_digitalWrite(cluster.stars[star].fuelOutput, LOW);
        cluster.stars[star].boomer.outputState = BOOMER_BLOWER_ON_FUEL_OFF_IDLE;
    }
    else if (cluster.stars[star].boomer.outputState == BOOMER_BLOWER_ON_FUEL_OFF_IDLE)
    {
        if (currentMillis - cluster.stars[star].boomer.previousMillis >= 50)
        {
            cluster.stars[star].boomer.previousMillis = millis();
            Serial.println("BOOMER_BLOWER_ON_FUEL_OFF_IDLE");
            cluster.stars[star].boomer.outputState = BOOMER_BLOWER_OFF;
        }
    }
    else if (cluster.stars[star].boomer.outputState == BOOMER_BLOWER_OFF)
    {
        cluster.stars[star].boomer.previousMillis = millis();
        Serial.println("BOOMER_BLOWER_OFF");
        novaIO->mcpA_digitalWrite(cluster.stars[star].blowerOutput, LOW);

        cluster.stars[star].boomer.outputState = BOOMER_BLOWER_OFF_IDLE;
    }
    else if (cluster.stars[star].boomer.outputState == BOOMER_BLOWER_OFF_IDLE)
    {
        if (currentMillis - cluster.stars[star].boomer.previousMillis >= 100)
        {
            cluster.stars[star].boomer.previousMillis = millis();
            Serial.println("BOOMER_BLOWER_OFF_IDLE");

            cluster.stars[star].boomer.outputState = BOOMER_ZAP_ON;
        }
    }
    else if (cluster.stars[star].boomer.outputState == BOOMER_ZAP_ON)
    {
        cluster.stars[star].boomer.previousMillis = millis();
        Serial.println("BOOMER_ZAP_ON");

        novaIO->mcpA_digitalWrite(cluster.stars[star].igniterOutput, HIGH);
        cluster.stars[star].boomer.outputState = BOOMER_ZAP_ON_IDLE;
    }
    else if (cluster.stars[star].boomer.outputState == BOOMER_ZAP_ON_IDLE)
    {
        if (currentMillis - cluster.stars[star].boomer.previousMillis >= 200)
        {
            cluster.stars[star].boomer.previousMillis = millis();

            Serial.println("BOOMER_ZAP_ON_IDLE");
            cluster.stars[star].boomer.outputState = BOOMER_BLOWER_EXHAUST;
        }
    }
    else if (cluster.stars[star].boomer.outputState == BOOMER_BLOWER_EXHAUST)
    {
        cluster.stars[star].boomer.previousMillis = millis();
        Serial.println("BOOMER_BLOWER_EXHAUST");

        novaIO->mcpA_digitalWrite(cluster.stars[star].blowerOutput, HIGH);
        novaIO->mcpA_digitalWrite(cluster.stars[star].igniterOutput, LOW);
        cluster.stars[star].boomer.outputState = BOOMER_BLOWER_EXHAUST_IDLE;
    }
    else if (cluster.stars[star].boomer.outputState == BOOMER_BLOWER_EXHAUST_IDLE)
    {
        if (currentMillis - cluster.stars[star].boomer.previousMillis >= 10000)
        {
            cluster.stars[star].boomer.previousMillis = millis();
            Serial.println("BOOMER_BLOWER_EXHAUST_IDLE");

            novaIO->mcpA_digitalWrite(cluster.stars[star].blowerOutput, LOW);
            cluster.stars[star].boomer.outputState = BOOMER_ACTIVE;
            return 1;
        }
    }
    return 0;
}

bool Star::goPoof(uint8_t star, uint32_t intervalOn, uint32_t intervalOff)
{
    uint32_t currentMillis = millis();
    // Serial.println("1");
    if (cluster.stars[star].pooferOutputState == POOF_ON)
    {
        // Serial.println("2");
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