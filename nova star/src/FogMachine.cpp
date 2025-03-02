#include <Arduino.h>
#include "main.h"
#include "configuration.h"
#include "NovaIO.h"
#include "FogMachine.h"


FogMachine *fogMachine = NULL;

FogMachine::FogMachine()
{


    // Setup goes in here
}

void FogMachine::loop()
{

  novaIO->mcpA_digitalWrite(FOG_POWER, HIGH);
  // mcp_a.digitalWrite(FOG_POWER, HIGH);

  // Todo -- Need to update this to a threadsafe wrapper
  if (novaIO->mcp_a.digitalRead(FOG_STATUS))
  //if (1)
  {

    uint32_t fogRandomDelayOff = 0;
    uint32_t fogRandomDelayOn = 0;
    fogRandomDelayOff = random(fogOutputOffMinTime, fogOutputOffMaxTime);
    fogRandomDelayOn = random(fogOutputOnMinTime, fogOutputOnMaxTime);

    Serial.print("Fog Machine: Will activate for ");
    Serial.print(fogRandomDelayOn);
    Serial.println(" ms.");
    novaIO->mcpA_digitalWrite(FOG_ACTIVATE, HIGH);
    delay(fogRandomDelayOn);

    Serial.print("Fog Machine: Will delay for ");
    Serial.print(fogRandomDelayOff);
    Serial.println(" seconds.");
    novaIO->mcpA_digitalWrite(FOG_ACTIVATE, LOW);
    delay(fogRandomDelayOff);
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