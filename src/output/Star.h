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

    uint32_t pooferIntervalMin = 90;
    uint32_t pooferIntervalMax = 90;

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
    };

    struct star
    {
        boomerData boomer;
        novaNet net;
        uint32_t pooferPreviousMillis;
        uint32_t pooferCountsRemaining;
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
//        POOF_ACTIVE,
//        POOF_DEACTIVATED,
        POOF_ON,
        POOF_ON_IDLE,
        POOF_OFF,
        POOF_OFF_IDLE
    };

    enum boomerButtonState {
        BOOMER_ON,
        BOOMER_OFF,
        BOOMER_IDLE
    };

    enum BoomerStates
    {
        BOOMER_ACTIVE, // Boomer is ready for a Boom
        BOOMER_DEACTIVATED, // Boomer is disabled. Here for administrative purposes.
        BOOMER_ABORT, // Begin the abort sequence. (Turn off fuel, turn off igniter, enter BOOMER_BLOWER_EXHAUST)
        BOOMER_BLOWER_ON, // Turn on the blower
        BOOMER_BLOWER_ON_IDLE, // Wait for x-ms
        BOOMER_BLOWER_ON_FUEL_ON, // Turn on the fuel fill
        BOOMER_BLOWER_ON_FUEL_ON_IDLE, // Wait for x-ms
        BOOMER_BLOWER_ON_FUEL_OFF, // Turn off the fuel fill
        BOOMER_BLOWER_ON_FUEL_OFF_IDLE, // Wait for x-ms. Run this for maybe 50ms. This is just to clear the fill tube.
        BOOMER_BLOWER_OFF, // Turn the blower off
        BOOMER_BLOWER_OFF_IDLE, // Wait for x-ms. This will let the flap on the baffle close
        BOOMER_ZAP_ON, // Turn on the igniter
        BOOMER_ZAP_ON_IDLE, // Leave it on for a moment
        BOOMER_ZAP_OFF, // Turn the zapper off
        BOOMER_ZAP_OFF_IDLE, // Wait for a moment (Do we need this?)
        BOOMER_BLOWER_EXHAUST, // Begin to exhaust the boomer. This can't be aborted.
        BOOMER_BLOWER_EXHAUST_IDLE, // Boomer exhausting. This can't be aborted.
        BOOMER_BLOWER_EXHAUST_OFF // Turn the exhaust off.
    };

    Star();

    void loop(void);

    void red_loop(void);
    void green_loop(void);
    void blue_loop(void);
    void yellow_loop(void);

    void redPoof(RedButtonState state);
    void redBoom(boomerButtonState state);

    void greenPoof(GreenButtonState state);
    void greenBoom(boomerButtonState state);

    void bluePoof(BlueButtonState state);
    void blueBoom(boomerButtonState state);

    void yellowPoof(YellowButtonState state);
    void yellowBoom(boomerButtonState state);

    void setupStar(void);

    bool goPoof(uint8_t star, uint32_t intervalOn, uint32_t intervalOff);
    bool goBoom(uint8_t star);
    void goBoomAbort(uint8_t star, bool abort);

    bool netOut(uint8_t star);
    bool netIn(uint8_t star);

    uint8_t redPooferState;
    uint8_t greenPooferState;
    uint8_t bluePooferState;
    uint8_t yellowPooferState;

    uint8_t redBoomerState;
    uint8_t greenBoomerState;
    uint8_t blueBoomerState;
    uint8_t yellowBoomerState;

};

extern Star *star;

#endif