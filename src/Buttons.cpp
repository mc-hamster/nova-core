#include "main.h"
#include <Arduino.h>
#include "OneButton.h"

#include "output/Star.h"


OneButton *button_red = new OneButton();
OneButton *button_green = new OneButton();
OneButton *button_blue = new OneButton();
OneButton *button_yellow = new OneButton();
OneButton *button_white = new OneButton();

Buttons *buttons = NULL;

Buttons::Buttons()
{
    Serial.println("Setting up buttons");
    button_red->attachClick(red_click);
    button_red->attachDoubleClick(red_doubleClick);
    button_red->attachLongPressStart(red_longPressStart);
    button_red->attachLongPressStop(red_longPressStop);

    button_green->attachClick(green_click);
    button_green->attachDoubleClick(green_doubleClick);
    button_green->attachLongPressStart(green_longPressStart);
    button_green->attachLongPressStop(green_longPressStop);

    button_blue->attachClick(blue_click);
    button_blue->attachDoubleClick(blue_doubleClick);
    button_blue->attachLongPressStart(blue_longPressStart);
    button_blue->attachLongPressStop(blue_longPressStop);

    button_yellow->attachClick(yellow_click);
    button_yellow->attachDoubleClick(yellow_doubleClick);
    button_yellow->attachLongPressStart(yellow_longPressStart);
    button_yellow->attachLongPressStop(yellow_longPressStop);
}

void Buttons::loop(void)
{
    // Serial.println("In Buttons Loops");
    button_red->tick(novaIO->expansionDigitalRead(BUTTON_RED_IN) == LOW);
    button_green->tick(novaIO->expansionDigitalRead(BUTTON_GREEN_IN) == LOW);
    button_blue->tick(novaIO->expansionDigitalRead(BUTTON_BLUE_IN) == LOW);
    button_yellow->tick(novaIO->expansionDigitalRead(BUTTON_YELLOW_IN) == LOW);
    button_white->tick(novaIO->expansionDigitalRead(BUTTON_WHITE_IN) == LOW);
}

void Buttons::red_click(void)
{
    Serial.println("Red Click");
    star->red(star->RED_POOF);
    
}
void Buttons::red_doubleClick(void)
{
    Serial.println("Red Double Click");
}
void Buttons::red_longPressStart(void)
{
    Serial.println("Red Long Start");
}
void Buttons::red_longPressStop(void)
{
    Serial.println("Red Long Stop");
}



void Buttons::green_click(void)
{
    Serial.println("Green Click");
    star->green(star->GREEN_POOF);

}
void Buttons::green_doubleClick(void)
{
    Serial.println("Green Double Click");
}
void Buttons::green_longPressStart(void)
{
    Serial.println("Green Long Start");
}
void Buttons::green_longPressStop(void)
{
    Serial.println("Green Long Stop");
}



void Buttons::blue_click(void)
{
    Serial.println("Blue Click");
    star->blue(star->BLUE_POOF);
}
void Buttons::blue_doubleClick(void)
{
    Serial.println("Blue Double Click");
}
void Buttons::blue_longPressStart(void)
{
    Serial.println("Blue Long Start");
}
void Buttons::blue_longPressStop(void)
{
    Serial.println("Blue Long Stop");
}



void Buttons::yellow_click(void)
{
    Serial.println("Yellow Click");
    star->yellow(star->YELLOW_POOF);
}
void Buttons::yellow_doubleClick(void)
{
    Serial.println("Yellow Double Click");
}
void Buttons::yellow_longPressStart(void)
{
    Serial.println("Yellow Long Start");
}
void Buttons::yellow_longPressStop(void)
{
    Serial.println("Yellow Long Stop");
}