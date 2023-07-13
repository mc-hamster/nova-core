#ifndef LIGHTUTILS
#define LIGHTUTILS

#pragma once

#include "main.h"
#include "configuration.h"
#include <FastLED.h>

extern PersistenceManager manager;

// COOLING: How much does the air cool as it rises?
// Less cooling = taller flames.  More cooling = shorter flames.
// Default 55, suggested range 20-100
#define COOLING 55

// SPARKING: What chance (out of 255) is there that a new spark will be lit?
// Higher chance = more roaring fire.  Lower chance = more flickery fire.
// Default 120, suggested range 50-200.
#define SPARKING 120

#define NUM_LEDS 18
#define LED_TYPE APA102
#define COLOR_ORDER BGR

class LightUtils
{
private:
    CRGBPalette16 getPalette(uint32_t paletteSelect);
    void FillLEDsFromPaletteColors(uint8_t colorIndex);
    void Fire2012WithPalette(void);

    uint8_t cfgSin = 0;
    uint8_t cfgProgram = 1;
    uint8_t cfgBrightness = 255;
    uint16_t cfgUpdates = 100;
    bool cfgReverse = 0;
    bool cfgFire = 0;
    bool cfgLocalDisable = 0;
    CRGB leds[NUM_LEDS];

public:
    LightUtils();

    void loop();

    void setCfgSin(uint8_t sin);
    void setCfgReverse(bool reverse);
    void setCfgFire(bool fire);
    void setCfgLocalDisable(bool localDisable);
    void setCfgProgram(uint8_t program);
    void setCfgBrightness(uint8_t brightness);
    void setCfgUpdates(uint16_t updates);

    bool getCfgReverse(void);
    bool getCfgFire(void);
    bool getCfgLocalDisable(void);
    uint8_t getCfgSin(void);
    uint8_t getCfgProgram(void);
    uint8_t getCfgBrightness(void);
    uint16_t getCfgUpdates(void);

    CRGB* getLeds(void);
    uint16_t getNumberOfLeds(void);

};

extern LightUtils *lightUtils;

#endif