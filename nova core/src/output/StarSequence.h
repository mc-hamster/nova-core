#ifndef STARSEQUENCE_H
#define STARSEQUENCE_H

#pragma once

#include <Arduino.h>

class StarSequence
{
private:

    uint8_t current_sequence = 0; // This is the current sequence that is running

public:
    enum sequences
    {
        SEQ_OFF,
        SEQ_POOF_END_TO_END,
        SEQ_BOOMER_LEFT_TO_RIGHT,
        SEQ_BOOMER_RIGHT_TO_LEFT,
        SEQ_BOOM_FAST,
        SEQ_BOOM_WAVE_IN,
        SEQ_BOOM_POOF
    };

    StarSequence();

    void loop();

    void setSequence(sequences sequence);
};

extern StarSequence *starSequence;

#endif