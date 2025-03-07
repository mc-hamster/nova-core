#pragma once

//#include "modes/Simona.h"
#include "NovaIO.h"

//#include "modes/Buttons.h"

#include <DNSServer.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include "ESPAsyncWebServer.h"
#include "utilities/PreferencesManager.h"


// Add LED control function declaration
void setLedBrightness(uint8_t led, bool isOn);
