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
    cluster.stars[0].net.expander = 5;
    cluster.stars[0].net.re = 0;
    cluster.stars[0].net.de = 1;

    cluster.stars[1].expander = 0;
    cluster.stars[1].blowerOutput = 4;
    cluster.stars[1].fuelOutput = 5;
    cluster.stars[1].igniterOutput = 6;
    cluster.stars[1].pooferOutput = 7;
    cluster.stars[1].blowerOutputDuty = 255;
    cluster.stars[1].net.expander = 5;
    cluster.stars[1].net.re = 2;
    cluster.stars[1].net.de = 3;

    cluster.stars[2].expander = 0;
    cluster.stars[2].blowerOutput = 8;
    cluster.stars[2].fuelOutput = 9;
    cluster.stars[2].igniterOutput = 10;
    cluster.stars[2].pooferOutput = 11;
    cluster.stars[2].blowerOutputDuty = 255;
    cluster.stars[2].net.expander = 5;
    cluster.stars[2].net.re = 4;
    cluster.stars[2].net.de = 5;

    cluster.stars[3].expander = 0;
    cluster.stars[3].blowerOutput = 12;
    cluster.stars[3].fuelOutput = 13;
    cluster.stars[3].igniterOutput = 14;
    cluster.stars[3].pooferOutput = 15;
    cluster.stars[3].blowerOutputDuty = 255;
    cluster.stars[3].net.expander = 5;
    cluster.stars[3].net.re = 6;
    cluster.stars[3].net.de = 7;

    cluster.stars[4].expander = 1;
    cluster.stars[4].blowerOutput = 0;
    cluster.stars[4].fuelOutput = 1;
    cluster.stars[4].igniterOutput = 2;
    cluster.stars[4].pooferOutput = 3;
    cluster.stars[4].blowerOutputDuty = 255;
    cluster.stars[4].net.expander = 5;
    cluster.stars[4].net.re = 8;
    cluster.stars[4].net.de = 9;

    cluster.stars[5].expander = 1;
    cluster.stars[5].blowerOutput = 4;
    cluster.stars[5].fuelOutput = 5;
    cluster.stars[5].igniterOutput = 6;
    cluster.stars[5].pooferOutput = 7;
    cluster.stars[5].blowerOutputDuty = 255;
    cluster.stars[5].net.expander = 5;
    cluster.stars[5].net.re = 10;
    cluster.stars[5].net.de = 11;

    cluster.stars[6].expander = 1;
    cluster.stars[6].blowerOutput = 8;
    cluster.stars[6].fuelOutput = 9;
    cluster.stars[6].igniterOutput = 10;
    cluster.stars[6].pooferOutput = 11;
    cluster.stars[6].blowerOutputDuty = 255;
    cluster.stars[6].net.expander = 5;
    cluster.stars[6].net.re = 12;
    cluster.stars[6].net.de = 13;

    cluster.stars[7].expander = 1;
    cluster.stars[7].blowerOutput = 12;
    cluster.stars[7].fuelOutput = 13;
    cluster.stars[7].igniterOutput = 14;
    cluster.stars[7].pooferOutput = 15;
    cluster.stars[7].blowerOutputDuty = 255;
    cluster.stars[7].net.expander = 5;
    cluster.stars[7].net.re = 14;
    cluster.stars[7].net.de = 15;

    cluster.stars[8].expander = 2;
    cluster.stars[8].blowerOutput = 0;
    cluster.stars[8].fuelOutput = 1;
    cluster.stars[8].igniterOutput = 2;
    cluster.stars[8].pooferOutput = 3;
    cluster.stars[8].blowerOutputDuty = 255;
    cluster.stars[8].net.expander = 6;
    cluster.stars[8].net.re = 0;
    cluster.stars[8].net.de = 1;

    cluster.stars[9].expander = 2;
    cluster.stars[9].blowerOutput = 4;
    cluster.stars[9].fuelOutput = 5;
    cluster.stars[9].igniterOutput = 6;
    cluster.stars[9].pooferOutput = 7;
    cluster.stars[9].blowerOutputDuty = 255;
    cluster.stars[9].net.expander = 6;
    cluster.stars[9].net.re = 2;
    cluster.stars[9].net.de = 3;

    cluster.stars[10].expander = 2;
    cluster.stars[10].blowerOutput = 8;
    cluster.stars[10].fuelOutput = 9;
    cluster.stars[10].igniterOutput = 10;
    cluster.stars[10].pooferOutput = 11;
    cluster.stars[10].blowerOutputDuty = 255;
    cluster.stars[10].net.expander = 6;
    cluster.stars[10].net.re = 4;
    cluster.stars[10].net.de = 5;

    cluster.stars[11].expander = 2;
    cluster.stars[11].blowerOutput = 12;
    cluster.stars[11].fuelOutput = 13;
    cluster.stars[11].igniterOutput = 14;
    cluster.stars[11].pooferOutput = 15;
    cluster.stars[11].blowerOutputDuty = 255;
    cluster.stars[11].net.expander = 6;
    cluster.stars[11].net.re = 6;
    cluster.stars[11].net.de = 7;

    cluster.stars[12].expander = 3;
    cluster.stars[12].blowerOutput = 0;
    cluster.stars[12].fuelOutput = 1;
    cluster.stars[12].igniterOutput = 2;
    cluster.stars[12].pooferOutput = 3;
    cluster.stars[12].blowerOutputDuty = 255;
    cluster.stars[12].net.expander = 6;
    cluster.stars[12].net.re = 8;
    cluster.stars[12].net.de = 9;

    cluster.stars[13].expander = 3;
    cluster.stars[13].blowerOutput = 4;
    cluster.stars[13].fuelOutput = 5;
    cluster.stars[13].igniterOutput = 6;
    cluster.stars[13].pooferOutput = 7;
    cluster.stars[13].blowerOutputDuty = 255;
    cluster.stars[13].net.expander = 6;
    cluster.stars[13].net.re = 10;
    cluster.stars[13].net.de = 11;

    cluster.stars[14].expander = 3;
    cluster.stars[14].blowerOutput = 8;
    cluster.stars[14].fuelOutput = 9;
    cluster.stars[14].igniterOutput = 10;
    cluster.stars[14].pooferOutput = 11;
    cluster.stars[14].blowerOutputDuty = 255;
    cluster.stars[14].net.expander = 6;
    cluster.stars[14].net.re = 12;
    cluster.stars[14].net.de = 13;

    cluster.stars[15].expander = 3;
    cluster.stars[15].blowerOutput = 12;
    cluster.stars[15].fuelOutput = 13;
    cluster.stars[15].igniterOutput = 14;
    cluster.stars[15].pooferOutput = 15;
    cluster.stars[15].blowerOutputDuty = 255;
    cluster.stars[15].net.expander = 6;
    cluster.stars[15].net.re = 14;
    cluster.stars[15].net.de = 15;

    cluster.stars[16].expander = 4;
    cluster.stars[16].blowerOutput = 0;
    cluster.stars[16].fuelOutput = 1;
    cluster.stars[16].igniterOutput = 2;
    cluster.stars[16].pooferOutput = 3;
    cluster.stars[16].blowerOutputDuty = 255;
    cluster.stars[16].net.expander = 7;
    cluster.stars[16].net.re = 0;
    cluster.stars[16].net.de = 1;

    cluster.stars[17].expander = 4;
    cluster.stars[17].blowerOutput = 4;
    cluster.stars[17].fuelOutput = 5;
    cluster.stars[17].igniterOutput = 6;
    cluster.stars[17].pooferOutput = 7;
    cluster.stars[17].blowerOutputDuty = 255;
    cluster.stars[17].net.expander = 7;
    cluster.stars[17].net.re = 2;
    cluster.stars[17].net.de = 3;

    cluster.stars[18].expander = 4;
    cluster.stars[18].blowerOutput = 8;
    cluster.stars[18].fuelOutput = 9;
    cluster.stars[18].igniterOutput = 10;
    cluster.stars[18].pooferOutput = 11;
    cluster.stars[18].blowerOutputDuty = 255;
    cluster.stars[18].net.expander = 7;
    cluster.stars[18].net.re = 4;
    cluster.stars[18].net.de = 5;

    cluster.stars[19].expander = 4;
    cluster.stars[19].blowerOutput = 12;
    cluster.stars[19].fuelOutput = 13;
    cluster.stars[19].igniterOutput = 14;
    cluster.stars[19].pooferOutput = 15;
    cluster.stars[19].blowerOutputDuty = 255;
    cluster.stars[19].net.expander = 7;
    cluster.stars[19].net.re = 6;
    cluster.stars[19].net.de = 7;

    for (uint32_t i = 0; i < 20; i++)
    {
        cluster.stars[i].pooferCountsRemaining = 0;
        cluster.stars[i].pooferOutputState = 0;
        cluster.stars[i].pooferOutputState = 0;
        cluster.stars[i].boomer.outputState = BOOMER_ACTIVE;
        cluster.stars[i].boomer.previousMillis = 0;
        cluster.stars[i].boomer.abort = false;
        cluster.stars[i].net.cache_re = 0;
        cluster.stars[i].net.cache_de = 0;
    }
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
            if (goPoof(outputStar, pooferInterval, pooferInterval * 10))
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

            // Only set the state to IDLE if the button is high
            if (novaIO->expansionDigitalRead(BUTTON_RED_IN) == HIGH)
            {
                Serial.println("Setting: BOOMER_OFF - Turning off boomer");
                redBoomerState = BOOMER_IDLE;
            }
        }
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
            if (goPoof(outputStar, pooferInterval, pooferInterval * 10))
            {
                cluster.stars[outputStar].pooferCountsRemaining--;
            }
        }

        if (cluster.stars[outputStar].pooferCountsRemaining == 0)
        {
            greenPooferState = GREEN_OFF;
        }
    }

    if (greenBoomerState == BOOMER_ON)
    {
        if (goBoom(outputStar))
        {
            // Only set the state to IDLE if the button is high
            if (novaIO->expansionDigitalRead(BUTTON_GREEN_IN) == HIGH)
            {
                Serial.println("Setting: BOOMER_OFF - Turning off boomer");
                greenBoomerState = BOOMER_IDLE;
            }
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
            cluster.stars[outputStar].pooferCountsRemaining = 100;
        }

        if (cluster.stars[outputStar].pooferCountsRemaining)
        {
            if (goPoof(outputStar, pooferInterval, pooferInterval * 10))
            {
                cluster.stars[outputStar].pooferCountsRemaining--;
            }
        }

        if (cluster.stars[outputStar].pooferCountsRemaining == 0)
        {
            bluePooferState = BLUE_OFF;
        }
    }
    if (blueBoomerState == BOOMER_ON)
    {
        if (goBoom(outputStar))
        {
            // Only set the state to IDLE if the button is high
            if (novaIO->expansionDigitalRead(BUTTON_BLUE_IN) == HIGH)
            {
                Serial.println("Setting: BOOMER_OFF - Turning off boomer");
                blueBoomerState = BOOMER_IDLE;
            }
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
            if (goPoof(outputStar, pooferInterval, pooferInterval * 10))
            {
                cluster.stars[outputStar].pooferCountsRemaining--;
            }
        }

        if (cluster.stars[outputStar].pooferCountsRemaining == 0)
        {
            yellowPooferState = YELLOW_OFF;
        }
    }

    if (yellowBoomerState == BOOMER_ON)
    {
        if (goBoom(outputStar))
        {
            // Only set the state to IDLE if the button is high
            if (novaIO->expansionDigitalRead(BUTTON_YELLOW_IN) == HIGH)
            {
                Serial.println("Setting: BOOMER_OFF - Turning off boomer");
                yellowBoomerState = BOOMER_IDLE;
            }
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
    redBoomerState = state;
}

void Star::greenPoof(GreenButtonState state)
{
    // Serial.println("GREEN POOF");
    greenPooferState = state;
}

void Star::greenBoom(boomerButtonState state)
{
    greenBoomerState = state;
}

void Star::bluePoof(BlueButtonState state)
{
    // Serial.println("BLUE POOF");
    bluePooferState = state;
}

void Star::blueBoom(boomerButtonState state)
{
    blueBoomerState = state;
}

void Star::yellowPoof(YellowButtonState state)
{
    // Serial.println("YELLOW POOF");
    yellowPooferState = state;
}

void Star::yellowBoom(boomerButtonState state)
{
    yellowBoomerState = state;
}

void Star::goBoomAbort(uint8_t star, bool abort)
{
    Serial.print("Star - ");
    Serial.print(star);
    Serial.println(" - ABORT!!!!");
    cluster.stars[star].boomer.abort = abort;
}

bool Star::goBoom(uint8_t star)
{
    uint32_t currentMillis = millis();
    if (cluster.stars[star].boomer.outputState == BOOMER_ABORT)
    {
        Serial.print("Star - ");
        Serial.print(star);
        Serial.print(" - ");

        Serial.print("Current state - ");
        Serial.println(cluster.stars[star].boomer.outputState);
        Serial.println("BOOMER_ABORT RECEIVED");
        novaIO->mcp_digitalWrite(cluster.stars[star].blowerOutput, HIGH, cluster.stars[star].expander);
        novaIO->mcp_digitalWrite(cluster.stars[star].fuelOutput, LOW, cluster.stars[star].expander);
        novaIO->mcp_digitalWrite(cluster.stars[star].pooferOutput, LOW, cluster.stars[star].expander);

        cluster.stars[star].boomer.outputState = BOOMER_BLOWER_EXHAUST;
        cluster.stars[star].boomer.abort = false;
    }
    else if (cluster.stars[star].boomer.outputState == BOOMER_ACTIVE)
    {
        if (cluster.stars[star].boomer.abort)
        {
            Serial.println("In BOOMER_ACTIVE, entering BOOMER_ABORT");
            cluster.stars[star].boomer.outputState = BOOMER_ABORT;
        }
        else
        {
            cluster.stars[star].boomer.previousMillis = millis();
            Serial.print("Star - ");
            Serial.print(star);
            Serial.print(" - ");
            Serial.println("BOOMER_ACTIVE");
            // Serial.println(millis());
            cluster.stars[star].boomer.outputState = BOOMER_BLOWER_ON;
        }
    }
    else if (cluster.stars[star].boomer.outputState == BOOMER_BLOWER_ON)
    {
        if (cluster.stars[star].boomer.abort)
        {
            Serial.println("In BOOMER_BLOWER_ON, entering BOOMER_ABORT");
            cluster.stars[star].boomer.outputState = BOOMER_ABORT;
        }
        else
        {

            cluster.stars[star].boomer.previousMillis = millis();
            Serial.print("Star - ");
            Serial.print(star);
            Serial.print(" - ");
            Serial.println("BOOMER_BLOWER_ON");

            novaIO->mcp_digitalWrite(cluster.stars[star].blowerOutput, HIGH, cluster.stars[star].expander);
            cluster.stars[star].boomer.outputState = BOOMER_BLOWER_ON_IDLE;
        }
    }
    else if (cluster.stars[star].boomer.outputState == BOOMER_BLOWER_ON_IDLE)
    {
        if (cluster.stars[star].boomer.abort)
        {
            Serial.println("In BOOMER_BLOWER_ON_IDLE, entering BOOMER_ABORT");
            cluster.stars[star].boomer.outputState = BOOMER_ABORT;
        }
        else
        {
            if (currentMillis - cluster.stars[star].boomer.previousMillis >= 50)
            {
                cluster.stars[star].boomer.previousMillis = millis();
                Serial.print("Star - ");
                Serial.print(star);
                Serial.print(" - ");
                Serial.println("BOOMER_BLOWER_ON_IDLE");
                // Serial.println(currentMillis - cluster.stars[star].boomer.previousMillis);
                cluster.stars[star].boomer.outputState = BOOMER_BLOWER_ON_FUEL_ON;
            }
        }
    }
    else if (cluster.stars[star].boomer.outputState == BOOMER_BLOWER_ON_FUEL_ON)
    {
        if (cluster.stars[star].boomer.abort)
        {
            Serial.println("In BOOMER_BLOWER_ON_FUEL_ON, entering BOOMER_ABORT");
            cluster.stars[star].boomer.outputState = BOOMER_ABORT;
        }
        else
        {

            cluster.stars[star].boomer.previousMillis = millis();
            Serial.print("Star - ");
            Serial.print(star);
            Serial.print(" - ");
            Serial.println("BOOMER_BLOWER_ON_FUEL_ON");

            novaIO->mcp_digitalWrite(cluster.stars[star].blowerOutput, HIGH, cluster.stars[star].expander);
            novaIO->mcp_digitalWrite(cluster.stars[star].fuelOutput, HIGH, cluster.stars[star].expander);
            cluster.stars[star].boomer.outputState = BOOMER_BLOWER_ON_FUEL_ON_IDLE;
        }
    }
    else if (cluster.stars[star].boomer.outputState == BOOMER_BLOWER_ON_FUEL_ON_IDLE)
    {
        if (cluster.stars[star].boomer.abort)
        {
            Serial.println("In BOOMER_BLOWER_ON_FUEL_ON_IDLE, entering BOOMER_ABORT");
            cluster.stars[star].boomer.outputState = BOOMER_ABORT;
        }
        else
        {

            if (currentMillis - cluster.stars[star].boomer.previousMillis >= 2000)
            {
                cluster.stars[star].boomer.previousMillis = millis();
                Serial.print("Star - ");
                Serial.print(star);
                Serial.print(" - ");
                Serial.println("BOOMER_BLOWER_ON_FUEL_ON_IDLE");
                cluster.stars[star].boomer.outputState = BOOMER_BLOWER_ON_FUEL_OFF;
            }
        }
    }
    else if (cluster.stars[star].boomer.outputState == BOOMER_BLOWER_ON_FUEL_OFF)
    {
        if (cluster.stars[star].boomer.abort)
        {
            Serial.println("In BOOMER_BLOWER_ON_FUEL_OFF, entering BOOMER_ABORT");
            cluster.stars[star].boomer.outputState = BOOMER_ABORT;
        }
        else
        {

            cluster.stars[star].boomer.previousMillis = millis();
            Serial.print("Star - ");
            Serial.print(star);
            Serial.print(" - ");
            Serial.println("BOOMER_BLOWER_ON_FUEL_OFF");

            // novaIO->mcpA_digitalWrite(cluster.stars[star].blowerOutput, HIGH);
            novaIO->mcp_digitalWrite(cluster.stars[star].fuelOutput, LOW, cluster.stars[star].expander);
            novaIO->mcp_digitalWrite(cluster.stars[star].pooferOutput, HIGH, cluster.stars[star].expander);

            cluster.stars[star].boomer.outputState = BOOMER_BLOWER_ON_FUEL_OFF_IDLE;
        }
    }
    else if (cluster.stars[star].boomer.outputState == BOOMER_BLOWER_ON_FUEL_OFF_IDLE)
    {
        if (cluster.stars[star].boomer.abort)
        {
            Serial.println("In BOOMER_BLOWER_ON_FUEL_OFF_IDLE, entering BOOMER_ABORT");
            cluster.stars[star].boomer.outputState = BOOMER_ABORT;
        }
        else
        {

            if (currentMillis - cluster.stars[star].boomer.previousMillis >= 200)
            {
                cluster.stars[star].boomer.previousMillis = millis();
                Serial.print("Star - ");
                Serial.print(star);
                Serial.print(" - ");
                Serial.println("BOOMER_BLOWER_ON_FUEL_OFF_IDLE");
                cluster.stars[star].boomer.outputState = BOOMER_BLOWER_OFF;
            }
        }
    }
    else if (cluster.stars[star].boomer.outputState == BOOMER_BLOWER_OFF)
    {
        if (cluster.stars[star].boomer.abort)
        {
            Serial.println("In BOOMER_BLOWER_OFF, entering BOOMER_ABORT");
            cluster.stars[star].boomer.outputState = BOOMER_ABORT;
        }
        else
        {

            cluster.stars[star].boomer.previousMillis = millis();
            Serial.print("Star - ");
            Serial.print(star);
            Serial.print(" - ");
            Serial.println("BOOMER_BLOWER_OFF");
            novaIO->mcp_digitalWrite(cluster.stars[star].blowerOutput, LOW, cluster.stars[star].expander);

            cluster.stars[star].boomer.outputState = BOOMER_BLOWER_OFF_IDLE;
        }
    }
    else if (cluster.stars[star].boomer.outputState == BOOMER_BLOWER_OFF_IDLE)
    {
        if (cluster.stars[star].boomer.abort)
        {
            Serial.println("In BOOMER_BLOWER_OFF_IDLE, entering BOOMER_ABORT");
            cluster.stars[star].boomer.outputState = BOOMER_ABORT;
        }
        else
        {

            if (currentMillis - cluster.stars[star].boomer.previousMillis >= 30)
            {
                cluster.stars[star].boomer.previousMillis = millis();
                Serial.print("Star - ");
                Serial.print(star);
                Serial.print(" - ");
                Serial.println("BOOMER_BLOWER_OFF_IDLE");

                cluster.stars[star].boomer.outputState = BOOMER_ZAP_ON;
            }
        }
    }
    else if (cluster.stars[star].boomer.outputState == BOOMER_ZAP_ON)
    {
        if (cluster.stars[star].boomer.abort)
        {
            Serial.println("In BOOMER_ZAP_ON, entering BOOMER_ABORT");
            cluster.stars[star].boomer.outputState = BOOMER_ABORT;
        }
        else
        {

            cluster.stars[star].boomer.previousMillis = millis();
            Serial.print("Star - ");
            Serial.print(star);
            Serial.print(" - ");
            Serial.println("BOOMER_ZAP_ON");

            novaIO->mcp_digitalWrite(cluster.stars[star].igniterOutput, HIGH, cluster.stars[star].expander);
            novaIO->mcp_digitalWrite(cluster.stars[star].pooferOutput, HIGH, cluster.stars[star].expander);
            cluster.stars[star].boomer.outputState = BOOMER_ZAP_ON_IDLE;
        }
    }
    else if (cluster.stars[star].boomer.outputState == BOOMER_ZAP_ON_IDLE)
    {
        if (cluster.stars[star].boomer.abort)
        {
            Serial.println("In BOOMER_ZAP_ON_IDLE, entering BOOMER_ABORT");
            cluster.stars[star].boomer.outputState = BOOMER_ABORT;
        }
        else
        {

            if (currentMillis - cluster.stars[star].boomer.previousMillis >= 100)
            {
                cluster.stars[star].boomer.previousMillis = millis();

                Serial.print("Star - ");
                Serial.print(star);
                Serial.print(" - ");
                Serial.println("BOOMER_ZAP_ON_IDLE");
                cluster.stars[star].boomer.outputState = BOOMER_BLOWER_EXHAUST;
            }
        }
    }
    else if (cluster.stars[star].boomer.outputState == BOOMER_BLOWER_EXHAUST)
    {
        cluster.stars[star].boomer.previousMillis = millis();
        Serial.print("Star - ");
        Serial.print(star);
        Serial.print(" - ");
        Serial.println("BOOMER_BLOWER_EXHAUST");

        novaIO->mcp_digitalWrite(cluster.stars[star].blowerOutput, HIGH, cluster.stars[star].expander);
        novaIO->mcp_digitalWrite(cluster.stars[star].igniterOutput, LOW, cluster.stars[star].expander);
        novaIO->mcp_digitalWrite(cluster.stars[star].pooferOutput, LOW, cluster.stars[star].expander);

        cluster.stars[star].boomer.outputState = BOOMER_BLOWER_EXHAUST_IDLE;
    }
    else if (cluster.stars[star].boomer.outputState == BOOMER_BLOWER_EXHAUST_IDLE)
    {
        if (currentMillis - cluster.stars[star].boomer.previousMillis >= 4000)
        {
            cluster.stars[star].boomer.previousMillis = millis();
            Serial.print("Star - ");
            Serial.print(star);
            Serial.print(" - ");
            Serial.println("BOOMER_BLOWER_EXHAUST_IDLE");

            // novaIO->mcpA_digitalWrite(cluster.stars[star].blowerOutput, LOW);
            // if (cluster.stars[star].boomer.abort)
            //{
            // TODO: This if can be deleted if the loop is happening outside of this function.
            //    cluster.stars[star].boomer.abort = false;
            //    cluster.stars[star].boomer.outputState = BOOMER_BLOWER_EXHAUST_OFF;
            //}
            // else
            //{
            cluster.stars[star].boomer.outputState = BOOMER_BLOWER_EXHAUST_OFF;
            //}
        }
    }
    else if (cluster.stars[star].boomer.outputState == BOOMER_BLOWER_EXHAUST_OFF)
    {
        novaIO->mcp_digitalWrite(cluster.stars[star].blowerOutput, LOW, cluster.stars[star].expander);
        Serial.print("Star - ");
        Serial.print(star);
        Serial.print(" - ");
        Serial.println("BOOMER_BLOWER_EXHAUST_OFF");

        cluster.stars[star].boomer.outputState = BOOMER_ACTIVE;

        Serial.print("Next state - ");
        Serial.println(cluster.stars[star].boomer.outputState);

        // Setting abort to false after the boomer is done.
        cluster.stars[star].boomer.abort = false;

        return 1;
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
        novaIO->mcp_digitalWrite(cluster.stars[star].pooferOutput, HIGH, cluster.stars[star].expander);
        // novaIO->mcpA_digitalWrite(cluster.stars[star].pooferOutput, HIGH);

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
        novaIO->mcp_digitalWrite(cluster.stars[star].pooferOutput, LOW, cluster.stars[star].expander);
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

/*
    Sets the output of the selected star to transmit.
    The other stars will be set to high impedience.

    If the star is 0xff, then sets all stars to transmit.

    RE - Receiver Output Enable Active LOW
    DE - Driver Output Enable Active HIGH

    From SP3485EN-L_TR.pdf:

    RE
        A logic LOW on RE (pin 2) will enable the differential receiver. A logic HIGH on RE
        (pin 2) of the SP3485 will disable the receiver.
    DE
        A logic HIGH on DE (pin 3) will enable the differential driver outputs. A logic LOW
        on the DE (pin 3) will tri-state the driver outputs.

*/
bool Star::netOut(uint8_t star)
{

    for (uint32_t i = 0; i < 20; i++)
    {
        if (star == 0xff)
        {
            // Selected transceiver to output
            if (cluster.stars[i].net.cache_re == HIGH)
            {
                // If cache_re is already high, then we don't need ot do anything.
            }
            else
            {
                novaIO->mcp_digitalWrite(cluster.stars[i].net.re, HIGH, cluster.stars[i].net.expander);
                cluster.stars[i].net.cache_re = HIGH;
            }

            if (cluster.stars[i].net.cache_de == HIGH)
            {
                // If cache_de is already high, then we don't need ot do anything.
            }
            else
            {
                novaIO->mcp_digitalWrite(cluster.stars[i].net.de, HIGH, cluster.stars[i].net.expander);
                cluster.stars[i].net.cache_de = HIGH;
            }
        }
        else
        {

            if (star == i)
            {
                // *** Set RE to High and DE to High

                // Selected transceiver to output
                if (cluster.stars[i].net.cache_re == HIGH)
                {
                    // If cache_re is already high, then we don't need ot do anything.
                }
                else
                {
                    novaIO->mcp_digitalWrite(cluster.stars[i].net.re, HIGH, cluster.stars[i].net.expander);
                    cluster.stars[i].net.cache_re = HIGH;
                }

                if (cluster.stars[i].net.cache_de == HIGH)
                {
                    // If cache_de is already high, then we don't need ot do anything.
                }
                else
                {
                    novaIO->mcp_digitalWrite(cluster.stars[i].net.de, HIGH, cluster.stars[i].net.expander);
                    cluster.stars[i].net.cache_de = HIGH;
                }
            }
            else
            {
                // *** Set RE to High and DE Low

                // Everything else to high impediance
                // novaIO->mcp_digitalWrite(cluster.stars[i].net.re, HIGH, cluster.stars[i].net.expander);
                // novaIO->mcp_digitalWrite(cluster.stars[i].net.de, LOW, cluster.stars[i].net.expander);

                // Selected transceiver to output
                if (cluster.stars[i].net.cache_re == HIGH)
                {
                    // If cache_re is already high, then we don't need ot do anything.
                }
                else
                {
                    novaIO->mcp_digitalWrite(cluster.stars[i].net.re, HIGH, cluster.stars[i].net.expander);
                    cluster.stars[i].net.cache_re = HIGH;
                }

                if (cluster.stars[i].net.cache_de == HIGH)
                {
                    // If cache_de is high, then we don't need to set it low
                    novaIO->mcp_digitalWrite(cluster.stars[i].net.de, LOW, cluster.stars[i].net.expander);
                    cluster.stars[i].net.cache_de = LOW;
                }
                else
                {
                    // If cache_de is low, then we don't need to do anything
                }
            }
        }
    }
    return 1; // Success
}