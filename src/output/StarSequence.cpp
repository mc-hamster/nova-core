#include <Arduino.h>
#include "StarSequence.h"
#include "configuration.h"
#include "Star.h"

/*

This is the Enable class. It is responsible for the emergency stop functionality.

*/

StarSequence *starSequence = NULL;

StarSequence::StarSequence()
{
    current_sequence = SEQ_OFF;

    Serial.println("StarSequence constructor");
    delay(100);
    // Setup goes in here
}

void StarSequence::loop()
{
    // Serial.println("StarSequence loop");

    if (starSequence->current_sequence == SEQ_OFF)
    {
        // Do nothing
    }
    else if (starSequence->current_sequence == SEQ_POOF_END_TO_END)
    {
        for (int i = 0; i <= 11; i++)
        {
            star->poof(i);
            delay(50);

            if (starSequence->current_sequence == SEQ_OFF)
                return;
        }
        for (int i = 11; i >= 0; i--)
        {
            star->poof(i);
            delay(50);

            if (starSequence->current_sequence == SEQ_OFF)
                return;
        }
    }
    else if (starSequence->current_sequence == SEQ_BOOMER_LEFT_TO_RIGHT)
    {
        for (int i = 0; i <= 11; i++)
        {
            star->boom(i);
            delay((star->whatBoomerFullTime() / 12) + 10);

            if (starSequence->current_sequence == SEQ_OFF)
                return;
        }
    }
    else if (starSequence->current_sequence == SEQ_BOOMER_RIGHT_TO_LEFT)
    {
        for (int i = 11; i >= 0; i--)
        {
            star->boom(i);
            delay((star->whatBoomerFullTime() / 12) + 10);

            if (starSequence->current_sequence == SEQ_OFF)
                return;
        }
    }
    else if (starSequence->current_sequence == SEQ_BOOM_FAST)
    {
        if (starSequence->current_sequence == SEQ_OFF)
            return;

        for (int i = 11; i >= 0; i--)
        {
            star->boom(i);
            delay(20);

            if (starSequence->current_sequence == SEQ_OFF)
                return;
        }
    }
    else if (starSequence->current_sequence == SEQ_BOOM_WAVE_IN)
    {
        if (starSequence->current_sequence == SEQ_OFF)
            return;

        star->boom(0);
        star->boom(11);
        delay(20);

        star->boom(1);
        star->boom(10);
        delay(20);

        star->boom(2);
        star->boom(9);
        delay(20);

        star->boom(3);
        star->boom(8);
        delay(20);

        star->boom(4);
        star->boom(7);
        delay(20);

        star->boom(5);
        star->boom(6);
        delay(20);
    }
    else if (starSequence->current_sequence == SEQ_BOOM_POOF)
    {
        for (int i = 11; i >= 0; i--)
        {
            star->boom(i);
            for (int j = 11; j >= 0; j--)
            {
                star->poof(j);
            }

            delay(((star->whatBoomerFullTime() / 12) + 10) / 2);

            for (int j = 11; j >= 0; j--)
            {
                star->poof(j);
            }

            delay(((star->whatBoomerFullTime() / 12) + 10) / 2);

            if (starSequence->current_sequence == SEQ_OFF)
                return;
        }
    }
    else
    {
        Serial.println("StarSequence loop: currentSequence == unknown");
    }
}

void StarSequence::setSequence(sequences sequence)
{
    starSequence->current_sequence = sequence;
}