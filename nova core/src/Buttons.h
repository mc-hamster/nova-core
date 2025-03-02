#ifndef BUTTONS_H
#define BUTTONS_H

#pragma once

#include <Arduino.h>

class Buttons
{
private:
public:
    enum TheButtons
    {
        BUTTON_RED,
        BUTTON_GREEN,
        BUTTON_BLUE,
        BUTTON_YELLOW
    };

    Buttons();

    void loop();

    static void red_click(void);
    static void red_doubleClick(void);
    static void red_longPressStart(void);
    static void red_longPressStop(void);

    static void green_click(void);
    static void green_doubleClick(void);
    static void green_longPressStart(void);
    static void green_longPressStop(void);

    static void blue_click(void);
    static void blue_doubleClick(void);
    static void blue_longPressStart(void);
    static void blue_longPressStop(void);

    static void yellow_click(void);
    static void yellow_doubleClick(void);
    static void yellow_longPressStart(void);
    static void yellow_longPressStop(void);
};


extern Buttons *buttons;

#endif
