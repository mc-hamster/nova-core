#ifndef MIDICONTROL_HPP
#define MIDICONTROL_HPP

#include <MIDI.h>
#include "freertos/semphr.h"    // FreeRTOS semaphore header

// MIDI wrapper functions with mutex protection
void sendMidiNoteOn(byte note, byte velocity, byte channel);
void sendMidiNoteOff(byte note, byte velocity, byte channel);
void sendMidiProgramChange(byte program, byte channel);

// Original function declarations
void initializeMIDI();
void playGameIntro();
void playBuzzer(int x);
void playLost();
void playWin();
// New declaration for startup music
void playStartupMusic();
void playRoundTransitionMusic(uint8_t round);

#endif // MIDICONTROL_HPP