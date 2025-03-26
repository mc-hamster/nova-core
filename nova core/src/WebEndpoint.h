#ifndef WEB_ENDPOINT_H
#define WEB_ENDPOINT_H

#pragma once

#include <Arduino.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include "ESPAsyncWebServer.h"
#include <ArduinoJson.h>

// Forward declarations
class AsyncWebServer;

// WebEndpoint namespace to avoid conflicts with Web.cpp functions
namespace WebEndpoint {

// Setup function to register all API endpoints
void setupApiEndpoints(AsyncWebServer *server);

// API endpoint handlers
void handleStatusRequest(AsyncWebServerRequest *request);
void handleSimonaCommand(AsyncWebServerRequest *request);
void handleStarCommand(AsyncWebServerRequest *request);
void handleSequenceCommand(AsyncWebServerRequest *request);
void handleLightingCommand(AsyncWebServerRequest *request);
void handleFogSettingsCommand(AsyncWebServerRequest *request);
void handleSystemCommand(AsyncWebServerRequest *request);

// API helpers - renamed to avoid conflict with global functions
void sendJsonResponseEndpoint(AsyncWebServerRequest *request, const JsonDocument &doc);
void sendErrorResponseEndpoint(AsyncWebServerRequest *request, int code, const String &message);

} // namespace WebEndpoint

#endif // WEB_ENDPOINT_H