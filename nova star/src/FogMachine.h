#ifndef FOGMACHINE_H
#define FOGMACHINE_H

#pragma once

#include <Arduino.h>

// State machine states for fog control
// IDLE: Waiting for fog status ready and fog enabled
// ACTIVE: Fog machine is currently producing fog for a specified duration
enum class FogState {
    IDLE,
    ACTIVE
};

class FogMachine
{
private:
    uint32_t lastAmnesiaMessageTime = 0;  // Tracks last received heartbeat message
    FogState currentState = FogState::IDLE;  // Current state of the fog machine
    uint32_t stateStartTime = 0;  // Time when current state began (for non-blocking delays)
    uint32_t currentStateDelay = 0;  // Duration the current state should last

public:
    // Timing configuration for fog operation (in milliseconds)
    uint32_t fogOutputOffMinTime = 5 * 1000;
    uint32_t fogOutputOffMaxTime = 20 * 1000;
    uint32_t fogOutputOnMinTime = 200;
    uint32_t fogOutputOnMaxTime = 1000;
    bool fogEnabled = false;  // Master enable/disable for fog operation

    void setFogOutputOffMinTime(uint32_t time);
    void setFogOutputOffMaxTime(uint32_t time);
    void setFogOutputOnMinTime(uint32_t time);
    void setFogOutputOnMaxTime(uint32_t time);
    void setFogEnabled(bool enabled);
    void updateLastAmnesiaMessageTime();

    bool getFogEnabled();
    uint32_t getLastAmnesiaMessageTime();
    uint32_t getTimeSinceLastAmnesiaMessage();

    FogMachine();

    void loop();
};

extern FogMachine *fogMachine;

#endif