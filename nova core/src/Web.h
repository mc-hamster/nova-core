#ifndef WEB_H
#define WEB_H

#pragma once

#include <Arduino.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include "ESPAsyncWebServer.h"
#include <ESPUI.h>
#include <ArduinoJson.h>

// Runtime variables
extern bool SIMONA_CHEAT_MODE;  // Managed by web interface
extern bool GAME_ENABLED;
extern bool SEQUENCE_LOCAL_ECHO;

extern AsyncWebServer *server;

// Forward declarations
void webSetup(void);
void webLoop(void);
ControlColor getColorForName(const char* colorName);

// API endpoints
void handleStatusRequest(AsyncWebServerRequest *request);
void handleSimonaCommand(AsyncWebServerRequest *request, JsonVariant &json);
void handleStarCommand(AsyncWebServerRequest *request, JsonVariant &json);
void handleSequenceCommand(AsyncWebServerRequest *request, JsonVariant &json);
void handleLightingCommand(AsyncWebServerRequest *request, JsonVariant &json);
void handleFogSettingsCommand(AsyncWebServerRequest *request, JsonVariant &json);
void handleSystemCommand(AsyncWebServerRequest *request, JsonVariant &json);

// API helpers
void sendJsonResponse(AsyncWebServerRequest *request, JsonDocument &doc);
void sendErrorResponse(AsyncWebServerRequest *request, int code, const String &message);

#endif