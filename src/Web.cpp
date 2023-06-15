#include "Web.h"
#include <DNSServer.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include "ESPAsyncWebServer.h"
#include <WiFi.h>
#include "main.h"
#include <ESPUI.h>
#include <Arduino.h>

void handleRequest(AsyncWebServerRequest *request)
{
    AsyncResponseStream *response = request->beginResponseStream("text/html");
    response->print("<!DOCTYPE html><html><head><title>Captive Portal - NOVA</title></head><body>");
    response->print("<p>NOVA</p>");
    response->print("<p>This is our captive portal front page.</p>");
    response->printf("<p>You were trying to reach: http://%s%s</p>", request->host().c_str(), request->url().c_str());
    response->printf("<p>Try opening <a href='http://%s'>this link</a> instead</p>", WiFi.softAPIP().toString().c_str());
    response->print("</body></html>");
    request->send(response);
}

uint16_t button1;
uint16_t switchOne;
uint16_t status;
uint16_t controlMillis;

void numberCall(Control *sender, int type)
{
    Serial.println(sender->value);
}

void textCall(Control *sender, int type)
{
    Serial.print("Text: ID: ");
    Serial.print(sender->id);
    Serial.print(", Value: ");
    Serial.println(sender->value);
}

void slider(Control *sender, int type)
{
    Serial.print("Slider: ID: ");
    Serial.print(sender->id);
    Serial.print(", Value: ");
    Serial.println(sender->value);
}

void buttonCallback(Control *sender, int type)
{
    switch (type)
    {
    case B_DOWN:
        Serial.println("Button DOWN");
        break;

    case B_UP:
        Serial.println("Button UP");
        break;
    }
}

void buttonExample(Control *sender, int type, void *param)
{
    Serial.println(String("param: ") + String(long(param)));
    switch (type)
    {
    case B_DOWN:
        Serial.println("Status: Start");
        ESPUI.updateControlValue(status, "Start");

        ESPUI.getControl(button1)->color = ControlColor::Carrot;
        ESPUI.updateControl(button1);
        break;

    case B_UP:
        Serial.println("Status: Stop");
        ESPUI.updateControlValue(status, "Stop");

        ESPUI.getControl(button1)->color = ControlColor::Peterriver;
        ESPUI.updateControl(button1);
        break;
    }
}

void switchExample(Control *sender, int value)
{
    switch (value)
    {
    case S_ACTIVE:
        Serial.print("Active:");
        break;

    case S_INACTIVE:
        Serial.print("Inactive");
        break;
    }

    Serial.print(" ");
    Serial.println(sender->id);
}

void selectExample(Control *sender, int value)
{
    Serial.print("Select: ID: ");
    Serial.print(sender->id);
    Serial.print(", Value: ");
    Serial.println(sender->value);
}

void otherSwitchExample(Control *sender, int value)
{
    switch (value)
    {
    case S_ACTIVE:
        Serial.print("Active:");
        break;

    case S_INACTIVE:
        Serial.print("Inactive");
        break;
    }

    Serial.print(" ");
    Serial.println(sender->id);
}

void webSetup()
{
    uint16_t tab1 = ESPUI.addControl(ControlType::Tab, "Main", "Main");
    uint16_t tab2 = ESPUI.addControl(ControlType::Tab, "Settings", "Settings");
    uint16_t tab3 = ESPUI.addControl(ControlType::Tab, "Sequences", "Sequences");
    uint16_t tab4 = ESPUI.addControl(ControlType::Tab, "Programs", "Programs");
    uint16_t tab5 = ESPUI.addControl(ControlType::Tab, "Reset", "Reset");

    // shown above all tabs
    status = ESPUI.addControl(ControlType::Label, "Status:", "Stop", ControlColor::Turquoise);

    //----- Tab 1 (Main) -----
    uint16_t select1 = ESPUI.addControl(ControlType::Select, "Select:", "", ControlColor::Alizarin, tab1, &selectExample);
    // ESPUI.addControl(ControlType::Option, "Option1", "Opt1", ControlColor::Alizarin, select1);
    // ESPUI.addControl(ControlType::Option, "Option2", "Opt2", ControlColor::Alizarin, select1);
    // ESPUI.addControl(ControlType::Option, "Option3", "Opt3", ControlColor::Alizarin, select1);
    // ESPUI.addControl(ControlType::Text, "Text Test:", "a Text Field", ControlColor::Alizarin, tab1, &textCall);
    controlMillis = ESPUI.addControl(ControlType::Label, "Millis:", "0", ControlColor::Emerald, tab1);

    ESPUI.addControl(ControlType::Switcher, "Drunktard", "", ControlColor::None, tab1, &otherSwitchExample);

    button1 = ESPUI.addControl(
        ControlType::Button, "Push Button", "Press", ControlColor::Peterriver, tab1, &buttonCallback);
    // ESPUI.addControl(ControlType::Button, "Other Button", "Press", ControlColor::Wetasphalt, tab1, &buttonExample, (void *)19);
    // ESPUI.addControl(ControlType::Slider, "Slider one", "30", ControlColor::Alizarin, tab1, &slider);

    //----- Tab 2 (Settings) -----
    // ESPUI.addControl(ControlType::Slider, "Sleep (Disable)", "30", ControlColor::Alizarin, tab2, &slider);
    ESPUI.addControl(ControlType::Switcher, "Sleep (Disable)", "", ControlColor::None, tab2, &otherSwitchExample);

    //---- Tab 3 (Sequences)

    switchOne = ESPUI.addControl(ControlType::Switcher, "Switch one", "", ControlColor::Alizarin, tab3, &switchExample);
    // ESPUI.addControl(ControlType::Switcher, "Switch two", "", ControlColor::None, tab3, &otherSwitchExample);
    // ESPUI.addControl(ControlType::Slider, "Slider two", "100", ControlColor::Alizarin, tab3, &slider);
    // ESPUI.addControl(ControlType::Number, "Number:", "50", ControlColor::Alizarin, tab3, &numberCall);

    ESPUI.addControl(
        ControlType::Button, "Boomers", "All", ControlColor::Peterriver, tab3, &buttonCallback);

    ESPUI.addControl(
        ControlType::Button, "Boomers", "Left to Right", ControlColor::Peterriver, tab3, &buttonCallback);

    ESPUI.addControl(
        ControlType::Button, "Boomers", "Right to Left", ControlColor::Peterriver, tab3, &buttonCallback);

    /*
     * .begin loads and serves all files from PROGMEM directly.
     * If you want to serve the files from LITTLEFS use ESPUI.beginLITTLEFS
     * (.prepareFileSystem has to be run in an empty sketch before)
     */

    // Enable this option if you want sliders to be continuous (update during move) and not discrete (update on stop)
    // ESPUI.sliderContinuous = true;

    /*
     * Optionally you can use HTTP BasicAuth. Keep in mind that this is NOT a
     * SECURE way of limiting access.
     * Anyone who is able to sniff traffic will be able to intercept your password
     * since it is transmitted in cleartext. Just add a string as username and
     * password, for example begin("ESPUI Control", "username", "password")
     */

    // ESPUI.server->addHandler(new CaptiveRequestHandler()).setFilter(ON_AP_FILTER); // only when requested from AP
    // ESPUI->server->begin();

    ESPUI.captivePortal = true;

    ESPUI.list(); // List all files on LittleFS, for info
    ESPUI.begin("NOVA Core");
}

void webLoop()
{
    static long oldTime = 0;
    static bool switchi = false;

    if (millis() - oldTime > 1000)
    {
        switchi = !switchi;
        ESPUI.updateControlValue(switchOne, switchi ? "1" : "0");
        ESPUI.updateControlValue(controlMillis, String(millis()));

        oldTime = millis();
        // Serial.print("Web oldTime: ");
        // Serial.println(oldTime);
    }
}