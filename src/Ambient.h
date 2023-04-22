#ifndef AMBIENT_H
#define AMBIENT_H

#pragma once

#include <Arduino.h>

class Ambient {
    private:

    bool systemEnable = 1;

    uint8_t disabledBrightness = 0;

    // This defines the speed of the fade
    uint8_t disabledBrightnessFade = 2; // This should be powers of two (1, 2, 4, 8, 16, 32, 64, etc)

    public: 
        Ambient();

        void loop();

        void emergencyStopExit();
        void emergencyStopEnter();

        bool isSystemEnabled();
};

extern Ambient *ambient;

#endif