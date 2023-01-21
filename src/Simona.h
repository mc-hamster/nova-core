#ifndef SIMONA_H
#define SIMONA_H

#pragma once

#include <Arduino.h>

class Simona {
    private:

        uint32_t LENGTH = 400;
        uint32_t gamepattern[20];
        uint32_t difficulty = 1;

    public: 
        Simona();

        void loop();

        void main_menu();

        void setPins();

        void play_game();

        void generate_game();

        void play_note(int index, int notespeed);

        void game_over(bool win);

        void testButtons();


};

extern Simona *simona;

#endif