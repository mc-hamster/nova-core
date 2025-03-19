#ifndef WEB_H
#define WEB_H

#pragma once

#include <Arduino.h>
#include <DNSServer.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include "ESPAsyncWebServer.h"
#include <ESPUI.h>

// Runtime variables
extern bool SIMONA_CHEAT_MODE;  // Managed by web interface
extern bool GAME_ENABLED;
extern bool SEQUENCE_LOCAL_ECHO;

extern AsyncWebServer *server;
extern DNSServer dnsServer;

// Forward declarations
void webSetup(void);
void webLoop(void);
ControlColor getColorForName(const char* colorName);

// Simple captive portal handler
class CaptiveRequestHandler : public AsyncWebHandler 
{
public:
    CaptiveRequestHandler() {}
    virtual ~CaptiveRequestHandler() {}

    bool canHandle(AsyncWebServerRequest *request)
    {
      // request->addInterestingHeader("ANY");
      return true;
    }
    void handleRequest(AsyncWebServerRequest *request) override {
        request->send(200, "text/html", "<!DOCTYPE html><html><head><title>NOVA</title></head><body><p>NOVA Web Interface</p></body></html>");
    }
};

#endif