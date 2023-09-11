#ifndef STAR_H
#define STAR_H

#pragma once

#include <Arduino.h>
#include "buttons.h"

class Star
{
private:
    uint32_t pooferDuration = 100;

    uint32_t boomerTimeBlowerOn = 50;
    uint32_t boomerTimeFuelOn = 2500;
    uint32_t boomerTimeFuelOff = 200;
    uint32_t boomerTimeBomerBlowerOff = 30;
    uint32_t boomerTimeBomerZap = 100;
    uint32_t boomerTimeExhaust = 7000;

    struct boomerData
    {
        uint32_t previousMillis;
        uint8_t outputState;
        bool abort; // If true, abort the boomer sequence
    };

    struct novaNet
    {
        uint8_t expander;
        uint8_t re;
        uint8_t de;
        uint8_t cache_re;
        uint8_t cache_de;
    };

    enum PooferButtonState
    {
        POOFER_OFF,
        POOFER_POOF
    };

    enum BoomerButtonState
    {
        BOOMER_ON,
        BOOMER_OFF,
        BOOMER_IDLE
    };
    struct starStates
    {
        // uint8_t cache_de;
        PooferButtonState pooferButtonState;
        BoomerButtonState boomerButtonState;
    };

    struct star
    {
        bool disablePoofer;
        bool disableBoomer;
        starStates starState;
        boomerData boomer;
        novaNet net;
        uint32_t pooferPreviousMillis;
        uint8_t expander;
        uint8_t blowerOutput;
        uint8_t fuelOutput;
        uint8_t igniterOutput;
        uint8_t pooferOutput;
        uint8_t blowerOutputDuty;
        uint8_t pooferOutputState;
    };

    struct starCluster
    {
        // char groupName[20];
        //         int numSensors;
        star stars[20]; // Array of stars structs
    };

    starCluster cluster;

public:
    uint8_t sequenceRed = 0;
    uint8_t sequenceGreen = 0;
    uint8_t sequenceBlue = 0;
    uint8_t sequenceYellow = 0;

    enum RedButtonState
    {
        RED_OFF,
        RED_POOF,
        RED_POOF_MULTI,
        RED_BOOM
    };

    enum GreenButtonState
    {
        GREEN_OFF,
        GREEN_POOF,
        GREEN_POOF_MULTI,
        GREEN_BOOM
    };

    enum BlueButtonState
    {
        BLUE_OFF,
        BLUE_POOF,
        BLUE_POOF_MULTI,
        BLUE_BOOM
    };

    enum YellowButtonState
    {
        YELLOW_OFF,
        YELLOW_POOF,
        YELLOW_POOF_MULTI,
        YELLOW_BOOM
    };

    enum PooferStates
    {
        POOF_ON,
        POOF_ON_IDLE,
        POOF_OFF,
        POOF_OFF_IDLE
    };

    enum BoomerStates
    {
        BOOMER_READY,                   // Boomer is ready for a Boom
        BOOMER_DEACTIVATED,             // Boomer is disabled. Here for administrative purposes.
        BOOMER_ABORT,                   // Begin the abort sequence. (Turn off fuel, turn off igniter, enter BOOMER_BLOWER_EXHAUST)
        BOOMER_BLOWER_ON,               // Turn on the blower
        BOOMER_BLOWER_ON_IDLE,          // Wait for x-ms
        BOOMER_BLOWER_ON_FUEL_ON,       // Turn on the fuel fill
        BOOMER_BLOWER_ON_FUEL_ON_IDLE,  // Wait for x-ms
        BOOMER_BLOWER_ON_FUEL_OFF,      // Turn off the fuel fill
        BOOMER_BLOWER_ON_FUEL_OFF_IDLE, // Wait for x-ms. Run this for maybe 50ms. This is just to clear the fill tube.
        BOOMER_BLOWER_OFF,              // Turn the blower off
        BOOMER_BLOWER_OFF_IDLE,         // Wait for x-ms. This will let the flap on the baffle close
        BOOMER_ZAP_ON,                  // Turn on the igniter
        BOOMER_ZAP_ON_IDLE,             // Leave it on for a moment
        BOOMER_ZAP_OFF,                 // Turn the zapper off
        BOOMER_ZAP_OFF_IDLE,            // Wait for a moment (Do we need this?)
        BOOMER_BLOWER_EXHAUST,          // Begin to exhaust the boomer. This can't be aborted.
        BOOMER_BLOWER_EXHAUST_IDLE,     // Boomer exhausting. This can't be aborted.
        BOOMER_BLOWER_EXHAUST_OFF       // Turn the exhaust off.
    };

    enum StarColors
    {
        STAR_RED,
        STAR_GREEN,
        STAR_BLUE,
        STAR_YELLOW
    };

    Star();

    void loop(void);

    void star_loop(void);

    void poof(uint8_t star);
    void boom(uint8_t star);

    void red_loop(void);
    void green_loop(void);
    void blue_loop(void);
    void yellow_loop(void);

    void redPoof();
    void redBoom();

    void greenPoof();
    void greenBoom();

    void bluePoof();
    void blueBoom();

    void yellowPoof();
    void yellowBoom();

    void setupStar(void);

    bool goPoof(uint8_t star, uint32_t intervalOn, uint32_t intervalOff);
    bool goBoom(uint8_t star);
    void goBoomAbort(StarColors color, bool abort);
    void boomAbort(uint8_t star);

    bool netOut(uint8_t star);
    bool netIn(uint8_t star);

    bool isBoomerRedActive();
    bool isBoomerGreenActive();
    bool isBoomerBlueActive();
    bool isBoomerYellowActive();

    void manualPoof(uint8_t star, bool state);
    void manualBlow(uint8_t star, bool state);
    void manualBlowFuel(uint8_t star, bool state);
    void manualFuel(uint8_t star, bool state);
    void manualZap(uint8_t star, bool state);

    uint32_t whatBoomerFullTime();
};

extern Star *star;

#endif