#ifndef LIGHTUTILS
#define LIGHTUTILS
#pragma once
#include "main.h"
#include "configuration.h"
#include <FastLED.h>
#include "utilities/PreferencesManager.h"
extern PreferencesManager manager;
// COOLING: How much does the air cool as it rises?
// Less cooling = taller flames.  More cooling = shorter flames.
// Default 55, suggested range 20-100
#define COOLING 55
// SPARKING: What chance (out of 255) is there that a new spark will be lit?
// Higher chance = more roaring fire.  Lower chance = more flickery fire.
// Default 120, suggested range 50-200.
#define SPARKING 120
#define NUM_LEDS 30
#define LED_TYPE APA102
#define COLOR_ORDER BGR
class LightUtils
{
private:
    CRGBPalette16 getPalette(uint32_t paletteSelect, bool saveSelection);
    void FillLEDsFromPaletteColors(uint8_t colorIndex);
    void Fire2012WithPalette(void);
    uint8_t cfgSin = 0;
    uint8_t cfgProgram = 1;
    uint8_t cfgBrightness = 255;
    uint16_t cfgUpdates = 100;
    bool cfgReverse = 0;
    bool cfgFire = 0;
    bool cfgLocalDisable = 0;
    bool cfgCircularMode = 0; // New flag for circular animation mode
    CRGB leds[NUM_LEDS];
    bool protectedLeds[NUM_LEDS] = {false}; // Track which LEDs are protected from pattern updates
    uint32_t cfgAutoTime = 0;
    bool cfgAuto = 0;
    bool cfgReverseSecondRow = false;
    uint16_t mapLedIndex(uint16_t index);
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
    void setCfgAuto(bool autoLight);
    void setCfgAutoTime(uint32_t updates);
    void setCfgReverseSecondRow(bool reverse);
    void setCfgCircularMode(bool circularMode); // New setter for circular mode
    bool getCfgReverseSecondRow(void);
    bool getCfgReverse(void);
    bool getCfgFire(void);
    bool getCfgLocalDisable(void);
    bool getCfgAuto(void);
    bool getCfgCircularMode(void); // New getter for circular mode
    uint32_t getCfgAutoTime(void);
    uint8_t getCfgSin(void);
    uint8_t getCfgProgram(void);
    uint8_t getCfgBrightness(void);
    uint16_t getCfgUpdates(void);
    CRGB *getLeds(void);
    uint16_t getNumberOfLeds(void);
    
    // New methods for protected LEDs
    void protectLedRange(uint16_t start, uint16_t end, CRGB color); // Protect LEDs and set them to a specific color
    void unprotectAllLeds(); // Unprotect all LEDs
    bool isLedProtected(uint16_t index); // Check if an LED is protected
};
extern LightUtils *lightUtils;
#endif