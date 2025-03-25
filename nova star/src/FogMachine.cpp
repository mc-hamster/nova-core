#include <Arduino.h>
#include "main.h"
#include "configuration.h"
#include "NovaIO.h"
#include "FogMachine.h"

FogMachine *fogMachine = NULL;

FogMachine::FogMachine()
{
    // Initialize state machine variables
    lastAmnesiaMessageTime = 0;
    currentState = FogState::IDLE;
    stateStartTime = 0;
    currentStateDelay = 0;
}

void FogMachine::loop()
{
    // Safety check: Disable fog machine if no heartbeat received within 5 seconds
    if (getTimeSinceLastAmnesiaMessage() > 5 * 1000)
    {
        novaIO->mcpA_digitalWrite(FOG_POWER, false);
        static uint32_t lastMessagePrintTime = 0;
        if (millis() - lastMessagePrintTime >= 5000)
        {
            Serial.println("No Amnesia message received in 5 seconds. Turning off power to the Fog Machine.");
            lastMessagePrintTime = millis();
        }
        return;
    }
    else
    {
        // Control power to fog machine based on enabled state
        novaIO->mcpA_digitalWrite(FOG_POWER, getFogEnabled());
    }

    // State machine implementation using non-blocking delays
    uint32_t currentTime = millis();
    bool fogStatusReady = novaIO->mcp_a.digitalRead(FOG_STATUS);

    switch (currentState) {
        case FogState::IDLE:
            // Transition to ACTIVE if both conditions are met:
            // 1. Fog status signal indicates machine is ready
            // 2. Fog is enabled in software
            if (fogStatusReady && getFogEnabled()) {
                currentState = FogState::ACTIVE;
                // Set random duration for fog activation
                currentStateDelay = random(fogOutputOnMinTime, fogOutputOnMaxTime);
                stateStartTime = currentTime;
                novaIO->mcpA_digitalWrite(FOG_ACTIVATE, HIGH);
            }
            break;

        case FogState::ACTIVE:
            // Check if activation duration has elapsed using non-blocking delay
            if (currentTime - stateStartTime >= currentStateDelay) {
                currentState = FogState::IDLE;
                novaIO->mcpA_digitalWrite(FOG_ACTIVATE, LOW);
            }
            break;
    }
}

void FogMachine::setFogOutputOffMinTime(uint32_t time)
{
  fogOutputOffMinTime = time;
}

void FogMachine::setFogOutputOffMaxTime(uint32_t time)
{
  fogOutputOffMaxTime = time;
}

void FogMachine::setFogOutputOnMinTime(uint32_t time)
{
  fogOutputOnMinTime = time;
}

void FogMachine::setFogOutputOnMaxTime(uint32_t time)
{
  fogOutputOnMaxTime = time;
}

void FogMachine::setFogEnabled(bool enabled)
{
  fogEnabled = enabled;
  novaIO->mcp_a.digitalWrite(FOG_POWER, enabled);
}

bool FogMachine::getFogEnabled()
{
  return fogEnabled;
}

void FogMachine::updateLastAmnesiaMessageTime()
{
  lastAmnesiaMessageTime = millis();
}

uint32_t FogMachine::getLastAmnesiaMessageTime()
{
  return lastAmnesiaMessageTime;
}

uint32_t FogMachine::getTimeSinceLastAmnesiaMessage()
{
  return millis() - lastAmnesiaMessageTime;
}