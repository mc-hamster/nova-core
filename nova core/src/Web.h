#ifndef WEB_H
#define WEB_H

#pragma once

#include <Arduino.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include "ESPAsyncWebServer.h"
#include <ESPUI.h>

// Runtime variables
extern bool SIMONA_CHEAT_MODE;  // Managed by web interface
extern bool GAME_ENABLED;
extern bool SEQUENCE_LOCAL_ECHO;

extern AsyncWebServer *server;

// Forward declarations
void webSetup(void);
void webLoop(void);
ControlColor getColorForName(const char* colorName);


#endif