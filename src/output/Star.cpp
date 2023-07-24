#include <Arduino.h>
#include "Star.h"
#include "configuration.h"
#include "NovaIO.h"
#include "Enable.h"
#include "Buttons.h"

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

    for (uint32_t i = 0; i < 12; i++)
    {
        cluster.stars[i].starState.boomerButtonState = BOOMER_IDLE;
        cluster.stars[i].pooferCountsRemaining = 0;
        cluster.stars[i].pooferOutputState = 0;
        cluster.stars[i].pooferOutputState = 0;
        cluster.stars[i].boomer.outputState = BOOMER_READY;
        cluster.stars[i].boomer.previousMillis = 0;
        cluster.stars[i].boomer.abort = false;
        cluster.stars[i].net.cache_re = 0;
        cluster.stars[i].net.cache_de = 0;
    }
}

void Star::loop()
{

    // if (systemEnable == true && digitalRead(ENABLE_DEVICE_PIN) == true)
    if (enable->isSystemEnabled())
    {
        star_loop();

        // red_loop();
        // green_loop();
        // blue_loop();
        // yellow_loop();
    }
}

bool Star::isBoomerRedActive()
{

    // Red
    if (
        cluster.stars[0].boomer.outputState == BOOMER_READY && cluster.stars[1].boomer.outputState == BOOMER_READY && cluster.stars[2].boomer.outputState == BOOMER_READY

    )
    {
        return false;
    }
    else
    {
        return true;
    }
}

bool Star::isBoomerGreenActive()
{

    // Green
    if (
        cluster.stars[3].boomer.outputState == BOOMER_READY && cluster.stars[4].boomer.outputState == BOOMER_READY && cluster.stars[5].boomer.outputState == BOOMER_READY

    )
    {
        return false;
    }
    else
    {
        return true;
    }
}

bool Star::isBoomerBlueActive()
{

    // Blue
    if (
        cluster.stars[6].boomer.outputState == BOOMER_READY && cluster.stars[7].boomer.outputState == BOOMER_READY && cluster.stars[8].boomer.outputState == BOOMER_READY

    )
    {
        return false;
    }
    else
    {
        return true;
    }
}

bool Star::isBoomerYellowActive()
{
    // Yellow
    if (
        cluster.stars[9].boomer.outputState == BOOMER_READY && cluster.stars[10].boomer.outputState == BOOMER_READY && cluster.stars[11].boomer.outputState == BOOMER_READY

    )
    {
        return false;
    }
    else
    {
        return true;
    }
}

// Called by the modes task
void Star::star_loop(void)
{

    for (uint32_t outputStar = 0; outputStar < 20; outputStar++)
    {

        if (cluster.stars[outputStar].starState.pooferButtonState == POOFER_POOF)
        {
            if (goPoof(outputStar, pooferDuration, pooferDuration / 4))
            {
                cluster.stars[outputStar].starState.pooferButtonState = POOFER_OFF;
            }
        }
        if (cluster.stars[outputStar].starState.boomerButtonState == BOOMER_ON)
        {
            if (goBoom(outputStar))
            {
                // Only set the state to IDLE if the button is high
                // if (novaIO->expansionDigitalRead(BUTTON_RED_IN) == HIGH)
                //{
                Serial.println("Setting: BOOMER_OFF - Turning off boomer");
                cluster.stars[outputStar].starState.boomerButtonState = BOOMER_IDLE;
                //}
            }
        }
    }
}

/*
    This defines the poofing behavior for a the 'red' cluster of stars
*/
void Star::redPoof()
{
    Serial.print("Red Sequence - ");
    Serial.println(sequenceRed);

    switch (sequenceRed)
    {
    case 0:
        poof(0);
        break;
    case 1:
        poof(1);
        break;
    case 2:
        poof(2);
        break;
    case 3:
        poof(2);
        break;
    case 4:
        poof(1);
        break;
    case 5:
        poof(0);
        break;
    case 6:
        poof(0);
        break;
    case 7:
        poof(1);
        break;
    case 8:
        poof(2);
        break;
    case 9:
        poof(2);
        break;
    case 10:
        poof(1);
        break;
    case 11:
        poof(0);
        break;
    case 12:
        poof(0);
        poof(2);
        break;
    case 13:
        poof(1);
        break;
    case 14:
        poof(0);
        poof(1);
        poof(2);
        break;
    case 15:
        poof(0);
        poof(1);
        poof(2);
        break;
    }

    sequenceRed++;
    if (sequenceRed == 16)
    {
        sequenceRed = 0;
    }
}

void Star::redBoom()
{

    if (isBoomerRedActive())
    {
        Serial.println("Red Boom - Boomer is active. Aborting");
        return;
    }
    else
    {
        Serial.print("Red Sequence - ");
        Serial.println(sequenceRed);
    }

    switch (sequenceRed)
    {
    case 0:
        boom(0);
        break;
    case 1:
        boom(1);
        break;
    case 2:
        boom(2);
        break;
    case 3:
        boom(2);
        break;
    case 4:
        boom(1);
        break;
    case 5:
        boom(0);
        break;
    case 6:
        boom(0);
        break;
    case 7:
        boom(1);
        break;
    case 8:
        boom(2);
        break;
    case 9:
        boom(2);
        break;
    case 10:
        boom(1);
        break;
    case 11:
        boom(0);
        break;
    case 12:
        boom(0);
        boom(2);
        break;
    case 13:
        boom(1);
        break;
    case 14:
        boom(0);
        boom(1);
        boom(2);
        break;
    case 15:
        boom(0);
        boom(1);
        boom(2);
        break;
    }

    sequenceRed++;
    if (sequenceRed == 16)
    {
        sequenceRed = 0;
    }
}

void Star::greenPoof()
{

    Serial.print("Green Sequence - ");
    Serial.println(sequenceGreen);

    switch (sequenceGreen)
    {
    case 0:
        poof(3);
        break;
    case 1:
        poof(4);
        break;
    case 2:
        poof(5);
        break;
    case 3:
        poof(5);
        break;
    case 4:
        poof(4);
        break;
    case 5:
        poof(3);
        break;
    case 6:
        poof(3);
        break;
    case 7:
        poof(4);
        break;
    case 8:
        poof(5);
        break;
    case 9:
        poof(5);
        break;
    case 10:
        poof(4);
        break;
    case 11:
        poof(3);
        break;
    case 12:
        poof(3);
        poof(5);
        break;
    case 13:
        poof(4);
        break;
    case 14:
        poof(3);
        poof(4);
        poof(5);
        break;
    case 15:
        poof(3);
        poof(4);
        poof(5);
        break;
    }

    sequenceGreen++;
    if (sequenceGreen == 16)
    {
        sequenceGreen = 0;
    }
}

void Star::greenBoom()
{

    if (isBoomerGreenActive())
    {
        Serial.println("Green Boom - Boomer is active. Aborting");
        return;
    }
    else
    {
        Serial.print("Green Sequence - ");
        Serial.println(sequenceGreen);
    }

    switch (sequenceGreen)
    {
    case 0:
        boom(3);
        break;
    case 1:
        boom(4);
        break;
    case 2:
        boom(5);
        break;
    case 3:
        boom(5);
        break;
    case 4:
        boom(4);
        break;
    case 5:
        boom(3);
        break;
    case 6:
        boom(3);
        break;
    case 7:
        boom(4);
        break;
    case 8:
        boom(5);
        break;
    case 9:
        boom(5);
        break;
    case 10:
        boom(4);
        break;
    case 11:
        boom(3);
        break;
    case 12:
        boom(3);
        boom(5);
        break;
    case 13:
        boom(4);
        break;
    case 14:
        boom(3);
        boom(4);
        boom(5);
        break;
    case 15:
        boom(3);
        boom(4);
        boom(5);
        break;
    }

    sequenceGreen++;
    if (sequenceGreen == 16)
    {
        sequenceGreen = 0;
    }
}

void Star::bluePoof()
{

    Serial.print("Blue Sequence - ");
    Serial.println(sequenceBlue);

    switch (sequenceBlue)
    {
    case 0:
        poof(6);
        break;
    case 1:
        poof(7);
        break;
    case 2:
        poof(8);
        break;
    case 3:
        poof(8);
        break;
    case 4:
        poof(7);
        break;
    case 5:
        poof(6);
        break;
    case 6:
        poof(6);
        break;
    case 7:
        poof(7);
        break;
    case 8:
        poof(8);
        break;
    case 9:
        poof(8);
        break;
    case 10:
        poof(7);
        break;
    case 11:
        poof(6);
        break;
    case 12:
        poof(6);
        poof(8);
        break;
    case 13:
        poof(7);
        break;
    case 14:
        poof(6);
        poof(7);
        poof(8);
        break;
    case 15:
        poof(6);
        poof(7);
        poof(8);
        break;
    }

    sequenceBlue++;
    if (sequenceBlue == 16)
    {
        sequenceBlue = 0;
    }
}

void Star::blueBoom()
{

    if (isBoomerBlueActive())
    {
        Serial.println("Blue Boom - Boomer is active. Aborting");
        return;
    }
    else
    {
        Serial.print("Blue Sequence - ");
        Serial.println(sequenceBlue);
    }

    switch (sequenceBlue)
    {
    case 0:
        boom(6);
        break;
    case 1:
        boom(7);
        break;
    case 2:
        boom(8);
        break;
    case 3:
        boom(8);
        break;
    case 4:
        boom(7);
        break;
    case 5:
        boom(6);
        break;
    case 6:
        boom(6);
        break;
    case 7:
        boom(7);
        break;
    case 8:
        boom(8);
        break;
    case 9:
        boom(8);
        break;
    case 10:
        boom(7);
        break;
    case 11:
        boom(6);
        break;
    case 12:
        boom(6);
        boom(8);
        break;
    case 13:
        boom(7);
        break;
    case 14:
        boom(6);
        boom(7);
        boom(8);
        break;
    case 15:
        boom(6);
        boom(7);
        boom(8);
        break;
    }

    sequenceBlue++;
    if (sequenceBlue == 16)
    {
        sequenceBlue = 0;
    }
}

void Star::yellowPoof()
{

    Serial.print("Yellow Sequence - ");
    Serial.println(sequenceYellow);

    switch (sequenceYellow)
    {
    case 0:
        poof(9);
        break;
    case 1:
        poof(10);
        break;
    case 2:
        poof(11);
        break;
    case 3:
        poof(11);
        break;
    case 4:
        poof(10);
        break;
    case 5:
        poof(9);
        break;
    case 6:
        poof(9);
        break;
    case 7:
        poof(10);
        break;
    case 8:
        poof(11);
        break;
    case 9:
        poof(11);
        break;
    case 10:
        poof(10);
        break;
    case 11:
        poof(9);
        break;
    case 12:
        poof(9);
        poof(11);
        break;
    case 13:
        poof(10);
        break;
    case 14:
        poof(9);
        poof(10);
        poof(11);
        break;
    case 15:
        poof(9);
        poof(10);
        poof(11);
        break;
    }

    sequenceYellow++;
    if (sequenceYellow == 16)
    {
        sequenceYellow = 0;
    }
}

void Star::yellowBoom()
{

    if (isBoomerYellowActive())
    {
        Serial.println("Yellow Boom - Boomer is active. Aborting");
        return;
    }
    else
    {
        Serial.print("Yellow Sequence - ");
        Serial.println(sequenceYellow);
    }

    switch (sequenceYellow)
    {
    case 0:
        boom(9);
        break;
    case 1:
        boom(10);
        break;
    case 2:
        boom(11);
        break;
    case 3:
        boom(11);
        break;
    case 4:
        boom(10);
        break;
    case 5:
        boom(9);
        break;
    case 6:
        boom(9);
        break;
    case 7:
        boom(10);
        break;
    case 8:
        boom(11);
        break;
    case 9:
        boom(11);
        break;
    case 10:
        boom(10);
        break;
    case 11:
        boom(9);
        break;
    case 12:
        boom(9);
        boom(11);
        break;
    case 13:
        boom(10);
        break;
    case 14:
        boom(9);
        boom(10);
        boom(11);
        break;
    case 15:
        boom(9);
        boom(10);
        boom(11);
        break;
    }

    sequenceYellow++;
    if (sequenceYellow == 16)
    {
        sequenceYellow = 0;
    }
}

void Star::goBoomAbort(StarColors color, bool abort)
{

    if (color == STAR_RED)
    {
        boomAbort(0);
        boomAbort(1);
        boomAbort(2);
    }
    else if (color == STAR_GREEN)
    {
        boomAbort(3);
        boomAbort(4);
        boomAbort(5);
    }
    else if (color == STAR_BLUE)
    {
        boomAbort(6);
        boomAbort(7);
        boomAbort(8);
    }
    else if (color == STAR_YELLOW)
    {
        boomAbort(9);
        boomAbort(10);
        boomAbort(11);
    }
}

void Star::boomAbort(uint8_t star)
{
    if (cluster.stars[star].boomer.outputState != BOOMER_READY)
    {
        Serial.print("Star - ");
        Serial.print(star);
        Serial.println(" - ABORT!!!!");
        cluster.stars[star].boomer.abort = abort;
    }
    else
    {
        Serial.print("Star - ");
        Serial.print(star);
        Serial.println(" is in the ready state. No need to abort.");
    }
}

/**
 * Triggers a controlled boom of the specified star.
 *
 * @param star The index of the star to trigger the boom for.
 *
 * @return true if the boom is triggered successfully, false otherwise.
 */
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
    else if (cluster.stars[star].boomer.outputState == BOOMER_READY)
    {
        if (cluster.stars[star].boomer.abort)
        {
            Serial.println("In BOOMER_READY, entering BOOMER_ABORT");
            cluster.stars[star].boomer.outputState = BOOMER_ABORT;
        }
        else
        {
            cluster.stars[star].boomer.previousMillis = millis();
            Serial.print("Star - ");
            Serial.print(star);
            Serial.print(" - ");
            Serial.println("BOOMER_READY");
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
            if (currentMillis - cluster.stars[star].boomer.previousMillis >= boomerTimeBlowerOn)
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

            if (currentMillis - cluster.stars[star].boomer.previousMillis >= boomerTimeFuelOn)
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

            if (currentMillis - cluster.stars[star].boomer.previousMillis >= boomerTimeFuelOff)
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

            if (currentMillis - cluster.stars[star].boomer.previousMillis >= boomerTimeBomerBlowerOff)
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

            if (currentMillis - cluster.stars[star].boomer.previousMillis >= boomerTimeBomerZap)
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
        if (currentMillis - cluster.stars[star].boomer.previousMillis >= boomerTimeExhaust)
        {
            cluster.stars[star].boomer.previousMillis = millis();
            Serial.print("Star - ");
            Serial.print(star);
            Serial.print(" - ");
            Serial.println("BOOMER_BLOWER_EXHAUST_IDLE");

            cluster.stars[star].boomer.outputState = BOOMER_BLOWER_EXHAUST_OFF;
        }
    }
    else if (cluster.stars[star].boomer.outputState == BOOMER_BLOWER_EXHAUST_OFF)
    {
        novaIO->mcp_digitalWrite(cluster.stars[star].blowerOutput, LOW, cluster.stars[star].expander);
        Serial.print("Star - ");
        Serial.print(star);
        Serial.print(" - ");
        Serial.println("BOOMER_BLOWER_EXHAUST_OFF");

        cluster.stars[star].boomer.outputState = BOOMER_READY;

        // Serial.printf("Next state - %d\n", cluster.stars[star].boomer.outputState);

        // Setting abort to false after the boomer is done.
        if (cluster.stars[star].boomer.abort)
        {
            Serial.println("Abort is True in BOOMER_BLOWER_EXHAUST_OFF.");

            cluster.stars[star].boomer.abort = false;
        }

        // Boomer is done.
        return 1;
    }

    // Boomer is not done yet.
    return 0;
}

bool Star::goPoof(uint8_t star, uint32_t intervalOn, uint32_t intervalOff)
{
    uint32_t currentMillis = millis();
    // Serial.println("1");
    switch (cluster.stars[star].pooferOutputState)
    {
    case POOF_ON:
        Serial.print("goPoof: On ");
        Serial.print(star);
        Serial.println();
        cluster.stars[star].pooferPreviousMillis = currentMillis;
        novaIO->mcp_digitalWrite(cluster.stars[star].pooferOutput, HIGH, cluster.stars[star].expander);
        cluster.stars[star].pooferOutputState = POOF_ON_IDLE;
        break;

    case POOF_ON_IDLE:
        if (currentMillis - cluster.stars[star].pooferPreviousMillis >= intervalOn)
        {
            cluster.stars[star].pooferOutputState = POOF_OFF;
        }
        break;

    case POOF_OFF:
        novaIO->mcp_digitalWrite(cluster.stars[star].pooferOutput, LOW, cluster.stars[star].expander);
        cluster.stars[star].pooferOutputState = POOF_OFF_IDLE;
        break;

    case POOF_OFF_IDLE:
        if (currentMillis - cluster.stars[star].pooferPreviousMillis >= intervalOn + intervalOff)
        {
            cluster.stars[star].pooferOutputState = POOF_ON;
            return 1;
        }
        break;

    default:
        break;
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

void Star::poof(uint8_t star)
{
    cluster.stars[star].starState.pooferButtonState = POOFER_POOF;
}

void Star::boom(uint8_t star)
{
    cluster.stars[star].starState.boomerButtonState = BOOMER_ON;
    // cluster.stars[star].starState.pooferButtonState = POOFER_POOF;
}