#include "main.h"
#include <Arduino.h>
#include "OneButton.h"

#include "output/Star.h"
#include "NovaIO.h"
#include "Enable.h"

OneButton *button_red = new OneButton();
OneButton *button_green = new OneButton();
OneButton *button_blue = new OneButton();
OneButton *button_yellow = new OneButton();
OneButton *button_white = new OneButton();

Buttons *buttons = NULL;

Buttons::Buttons()
{
    uint32_t ticksDebounce = 25; // setDebounceTicks Period of time in which to ignore additional level changes.
    uint32_t ticksClicks = 60;   // setClickTicks  Timeout used to distinguish single clicks from double clicks.
    uint32_t ticksPress = 500;   // setPressTicks Duration to hold a button to trigger a long press

    Serial.println("Setting up buttons");
    button_red->attachClick(red_click);
    button_red->attachDoubleClick(red_doubleClick);
    button_red->attachLongPressStart(red_longPressStart);
    button_red->attachLongPressStop(red_longPressStop);
    button_red->setDebounceTicks(ticksDebounce);
    button_red->setClickTicks(ticksClicks);
    button_red->setPressTicks(ticksPress);

    button_green->attachClick(green_click);
    button_green->attachDoubleClick(green_doubleClick);
    button_green->attachLongPressStart(green_longPressStart);
    button_green->attachLongPressStop(green_longPressStop);
    button_green->setDebounceTicks(ticksDebounce);
    button_green->setClickTicks(ticksClicks);
    button_green->setPressTicks(ticksPress);

    button_blue->attachClick(blue_click);
    button_blue->attachDoubleClick(blue_doubleClick);
    button_blue->attachLongPressStart(blue_longPressStart);
    button_blue->attachLongPressStop(blue_longPressStop);
    button_blue->setDebounceTicks(ticksDebounce);
    button_blue->setClickTicks(ticksClicks);
    button_blue->setPressTicks(ticksPress);

    button_yellow->attachClick(yellow_click);
    button_yellow->attachDoubleClick(yellow_doubleClick);
    button_yellow->attachLongPressStart(yellow_longPressStart);
    button_yellow->attachLongPressStop(yellow_longPressStop);
    button_yellow->setDebounceTicks(ticksDebounce);
    button_yellow->setClickTicks(ticksClicks);
}

void Buttons::loop(void)
{
    // Serial.println("In Buttons Loops");
    button_red->tick(novaIO->expansionDigitalRead(BUTTON_RED_IN) == LOW);
    button_green->tick(novaIO->expansionDigitalRead(BUTTON_GREEN_IN) == LOW);
    button_blue->tick(novaIO->expansionDigitalRead(BUTTON_BLUE_IN) == LOW);
    button_yellow->tick(novaIO->expansionDigitalRead(BUTTON_YELLOW_IN) == LOW);
    button_white->tick(novaIO->expansionDigitalRead(BUTTON_WHITE_IN) == LOW);

    if (novaIO->expansionDigitalRead(BUTTON_RED_IN))
    {
        novaIO->ledRed(HIGH);
    }
    else
    {
        if ((millis() / 100) % 2)
        {
            novaIO->ledRed(HIGH);
        }
        else
        {
            novaIO->ledRed(LOW);
        }
    }
    if (novaIO->expansionDigitalRead(BUTTON_GREEN_IN))
    {
        novaIO->ledGreen(HIGH);
    }
    else
    {
        if ((millis() / 100) % 2)
        {
            novaIO->ledGreen(HIGH);
        }
        else
        {
            novaIO->ledGreen(LOW);
        }
    }

    if (novaIO->expansionDigitalRead(BUTTON_BLUE_IN))
    {
        novaIO->ledBlue(HIGH);
    }
    else
    {
        if ((millis() / 100) % 2)
        {
            novaIO->ledBlue(HIGH);
        }
        else
        {
            novaIO->ledBlue(LOW);
        }
    }

    if (novaIO->expansionDigitalRead(BUTTON_YELLOW_IN))
    {
        novaIO->ledYellow(HIGH);
    }
    else
    {
        if ((millis() / 100) % 2)
        {
            novaIO->ledYellow(HIGH);
        }
        else
        {
            novaIO->ledYellow(LOW);
        }
    }
}

void Buttons::red_click(void)
{
    if (!enable->isDrunktard())
    {
        Serial.println("Red Click");
        star->redPoof(star->RED_POOF);
    }
}
void Buttons::red_doubleClick(void)
{
    Serial.println("Red Double Click");
    star->redPoof(star->RED_POOF_MULTI);
}
void Buttons::red_longPressStart(void)
{
    if (!enable->isDrunktard())
    {
        Serial.println("Red Long Start");
        star->redBoom(star->BOOMER_ON);
    }
}
void Buttons::red_longPressStop(void)
{
    if (!enable->isDrunktard())
    {
        Serial.println("Red Long Stop");
        star->goBoomAbort(0, true);
    }
}

void Buttons::green_click(void)
{
    if (!enable->isDrunktard())
    {
        Serial.println("Green Click");
        star->greenPoof(star->GREEN_POOF);
    }
}
void Buttons::green_doubleClick(void)
{
    Serial.println("Green Double Click");
    star->greenPoof(star->GREEN_POOF_MULTI);
}
void Buttons::green_longPressStart(void)
{
    if (!enable->isDrunktard())
    {
        Serial.println("Green Long Start");
        star->greenBoom(star->BOOMER_ON);
    }
}
void Buttons::green_longPressStop(void)
{
    if (!enable->isDrunktard())
    {
        Serial.println("Green Long Stop");
        star->goBoomAbort(1, true);
    }
}

void Buttons::blue_click(void)
{
    if (!enable->isDrunktard())
    {
        Serial.println("Blue Click");
        star->bluePoof(star->BLUE_POOF);
    }
}
void Buttons::blue_doubleClick(void)
{
    Serial.println("Blue Double Click");
    star->bluePoof(star->BLUE_POOF_MULTI);
}
void Buttons::blue_longPressStart(void)
{
    if (!enable->isDrunktard())
    {
        Serial.println("Blue Long Start");
        star->blueBoom(star->BOOMER_ON);
    }
}
void Buttons::blue_longPressStop(void)
{
    if (!enable->isDrunktard())
    {
        Serial.println("Blue Long Stop");
        star->goBoomAbort(2, true);
    }
}

void Buttons::yellow_click(void)
{
    if (!enable->isDrunktard())
    {
        Serial.println("Yellow Click");
        star->yellowPoof(star->YELLOW_POOF);
    }
}
void Buttons::yellow_doubleClick(void)
{
    Serial.println("Yellow Double Click");
    star->yellowPoof(star->YELLOW_POOF_MULTI);
}
void Buttons::yellow_longPressStart(void)
{
    if (!enable->isDrunktard())
    {
        Serial.println("Yellow Long Start");
        star->yellowBoom(star->BOOMER_ON);
    }
}
void Buttons::yellow_longPressStop(void)
{
    if (!enable->isDrunktard())
    {
        Serial.println("Yellow Long Stop");
        star->goBoomAbort(3, true);
    }
}