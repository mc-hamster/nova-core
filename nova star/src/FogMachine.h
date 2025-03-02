#ifndef FOGMACHINE_H
#define FOGMACHINE_H

#pragma once

#include <Arduino.h>

class FogMachine
{
private:
public:
    uint32_t fogOutputOffMinTime = 5 * 1000;
    uint32_t fogOutputOffMaxTime = 20 * 1000;
    uint32_t fogOutputOnMinTime = 200;
    uint32_t fogOutputOnMaxTime = 1000;

    void setFogOutputOffMinTime(uint32_t time);
    void setFogOutputOffMaxTime(uint32_t time);
    void setFogOutputOnMinTime(uint32_t time);
    void setFogOutputOnMaxTime(uint32_t time);

    FogMachine();

    void loop();
};

extern FogMachine *fogMachine;

#endif