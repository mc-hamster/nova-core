#ifndef SCREEN_H
#define SCREEN_H

#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>
#include <WiFi.h>
#include <WiFiType.h>
#include <WiFiGeneric.h>
#include <WiFiSTA.h>
#include <WiFiAP.h>

class Screen {
public:
    Screen();
    bool begin();
    void displayMessage(const char* message);
    void updateNetworkInfo(const String& apIP, const String& clientIP);
    void clear();
private:
    static const int SCREEN_WIDTH = 128;
    static const int SCREEN_HEIGHT = 64;
    static const int OLED_RESET = -1;
    
    Adafruit_SSD1306 display;
    
    // Previous network info to check for changes
    String prevMacAddress;
    String prevApIP;
    String prevClientIP;
};

extern Screen* screen;
void TaskScreen(void* pvParameters);

#endif // SCREEN_H