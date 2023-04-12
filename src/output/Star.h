#ifndef STAR_H
#define STAR_H

#pragma once

#include <Arduino.h>

class Star
{
private:
    bool systemEnable = 1;

    uint8_t disabledBrightness = 0;
    uint8_t disabledBrightnessFade = 1; // This should be powers of two (1, 2, 4, 8, 16, 32, 64, etc)

    uint32_t pooferInterval = 750;


    uint32_t redPreviousMillis = 0;
    bool redPooferOn = 0;

    uint32_t greenPreviousMillis = 0;
    bool greenPooferOn = 0;

    uint32_t bluePreviousMillis = 0;
    bool bluePooferOn = 0;

    uint32_t yellowPreviousMillis = 0;
    bool yellowPooferOn = 0;

public:
    enum RedButtonState
    {
        RED_OFF,
        RED_POOF,
        RED_BOOM
    };

    enum GreenButtonState
    {
        GREEN_OFF,
        GREEN_POOF,
        GREEN_BOOM
    };

    enum BlueButtonState
    {
        BLUE_OFF,
        BLUE_POOF,
        BLUE_BOOM
    };

    enum YellowButtonState
    {
        YELLOW_OFF,
        YELLOW_POOF,
        YELLOW_BOOM
    };

    Star();

    void loop(void);

    void red_loop(void);
    void green_loop(void);
    void blue_loop(void);
    void yellow_loop(void);

    void red(RedButtonState state);

    void green(GreenButtonState state);

    void blue(BlueButtonState state);

    void yellow(YellowButtonState state);

    uint8_t redState;
    uint8_t greenState;
    uint8_t blueState;
    uint8_t yellowState;
};

extern Star *star;

#endif