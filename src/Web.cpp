#include "Web.h"
#include <DNSServer.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include "ESPAsyncWebServer.h"
#include <WiFi.h>
#include "main.h"
#include <ESPUI.h>
#include <Arduino.h>
#include "LightUtils.h"
#include "Enable.h"

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

uint16_t switchOne;
uint16_t status;
uint16_t controlMillis;

uint16_t lightingBrightnessSlider, lightingSinSlider, lightingProgramSelect, lightingUpdatesSlider, lightingReverseSwitch, lightingFireSwitch, lightingLocalDisable;
uint16_t mainDrunktardSwitch;
uint16_t resetConfigSwitch, resetRebootSwitch;

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

    if (sender->id == lightingBrightnessSlider)
    {
        lightUtils->setCfgBrightness(sender->value.toInt());
    }
    if (sender->id == lightingSinSlider)
    {
        lightUtils->setCfgSin(sender->value.toInt());
    }
    if (sender->id == lightingUpdatesSlider)
    {
        lightUtils->setCfgUpdates(sender->value.toInt());
    }
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
}

void switchExample(Control *sender, int value)
{

    if (sender->id == lightingReverseSwitch)
    {
        lightUtils->setCfgReverse(sender->value.toInt());
    }
    else if (sender->id == lightingFireSwitch)
    {

        lightUtils->setCfgFire(sender->value.toInt());
    }
    else if (sender->id == lightingLocalDisable)
    {

        lightUtils->setCfgLocalDisable(sender->value.toInt());
    }
    else if (sender->id == mainDrunktardSwitch)
    {
        manager.set("cfgDrunktard", sender->value.toInt());
        if (manager.save())
        {
            Serial.println("cfgDrunktard Data saved successfully.");
        }
        else
        {
            Serial.println("cfgDrunktard Failed to save data.");
        }
    }
    else if (sender->id == resetConfigSwitch)
    {
        // TODO:
        //    - Give the user a chance to cancel the config reset.
        if (sender->value.toInt())
        {
            manager.clear();
            manager.save();
            delay(50);
            ESP.restart();
        }
    }
    else if (sender->id == resetRebootSwitch)
    {
        if (sender->value.toInt())
        {
            // Todo:
            //    - Give the user a chance to cancel the reboot.
            Serial.println("Rebooting device from switch...");
            ESP.restart();
        }
    }

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

    if (sender->id == lightingProgramSelect)
    {
        lightUtils->setCfgProgram(sender->value.toInt());
    }
}

void webSetup()
{
    // Add tabs
    uint16_t mainTab = ESPUI.addControl(ControlType::Tab, "Main", "Main");
    uint16_t settingsTab = ESPUI.addControl(ControlType::Tab, "Settings", "Settings");
    uint16_t sequencesTab = ESPUI.addControl(ControlType::Tab, "Sequences", "Sequences");
    uint16_t programsTab = ESPUI.addControl(ControlType::Tab, "Programs", "Programs");
    uint16_t lightingTab = ESPUI.addControl(ControlType::Tab, "Lighting", "Lighting");
    uint16_t resetTab = ESPUI.addControl(ControlType::Tab, "Reset", "Reset");

    // Add status label above all tabs
    status = ESPUI.addControl(ControlType::Label, "Status:", "Unknown Status", ControlColor::Turquoise);

    //----- Tab 1 (Main) -----
    controlMillis = ESPUI.addControl(ControlType::Label, "Uptime", "0", ControlColor::Emerald, mainTab);
    mainDrunktardSwitch = ESPUI.addControl(ControlType::Switcher, "Drunktard", String(enable->isDrunktard()), ControlColor::None, mainTab, &switchExample);

    //----- Tab 2 (Settings) -----
    ESPUI.addControl(ControlType::Switcher, "Sleep (Disable)", "", ControlColor::None, settingsTab, &switchExample);

    //---- Tab 3 (Sequences) -----
    switchOne = ESPUI.addControl(ControlType::Switcher, "Switch one", "", ControlColor::Alizarin, sequencesTab, &switchExample);
    ESPUI.addControl(ControlType::Button, "Boomers", "All", ControlColor::Peterriver, sequencesTab, &buttonCallback);
    ESPUI.addControl(ControlType::Button, "Boomers", "Left to Right", ControlColor::Peterriver, sequencesTab, &buttonCallback);
    ESPUI.addControl(ControlType::Button, "Boomers", "Right to Left", ControlColor::Peterriver, sequencesTab, &buttonCallback);

    //---- Tab -- Lighting
    lightingBrightnessSlider = ESPUI.addControl(ControlType::Slider, "Brightness", String(lightUtils->getCfgBrightness()), ControlColor::Alizarin, lightingTab, &slider);
    ESPUI.addControl(Min, "", "0", None, lightingBrightnessSlider);
    ESPUI.addControl(Max, "", "255", None, lightingBrightnessSlider);

    lightingProgramSelect = ESPUI.addControl(ControlType::Select, "Select Program", String(lightUtils->getCfgProgram()), ControlColor::Alizarin, lightingTab, &selectExample);
    ESPUI.addControl(ControlType::Option, "RainbowColors_p", "1", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "RainbowStripeColors_p", "2", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "CloudColors_p", "3", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "PartyColors_p", "4", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "myRedWhiteBluePalette_p", "5", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "Random", "6", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "BlackWhite Stripped", "7", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "quagga_gp", "8", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "purplefly_gp", "9", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "butterflytalker_gp", "10", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "carousel_gp", "11", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "autumnrose_gp", "12", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "Purple Gradient - bhw1_33_gp", "13", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "bhw1_22_gp", "14", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "heatmap_gp", "15", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "HeatColors_p", "16", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "LavaColors_p", "17", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "OceanColors_p", "18", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "ForestColors_p", "19", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "All White", "20", ControlColor::Alizarin, lightingProgramSelect);

    //    lightingUpdatesSlider = ESPUI.addControl(ControlType::Slider, "Updates Per Second", "100", ControlColor::Alizarin, lightingTab, &slider);
    lightingUpdatesSlider = ESPUI.addControl(ControlType::Slider, "Updates Per Second", String(lightUtils->getCfgUpdates()), ControlColor::Alizarin, lightingTab, &slider);
    ESPUI.addControl(Min, "", "1", None, lightingUpdatesSlider);
    ESPUI.addControl(Max, "", "255", None, lightingUpdatesSlider);

    //    lightingSinSlider = ESPUI.addControl(ControlType::Slider, "Sin", "0", ControlColor::Alizarin, lightingTab, &slider);
    lightingSinSlider = ESPUI.addControl(ControlType::Slider, "Sin", String(lightUtils->getCfgSin()), ControlColor::Alizarin, lightingTab, &slider);
    ESPUI.addControl(Min, "", "0", None, lightingSinSlider);
    ESPUI.addControl(Max, "", "32", None, lightingSinSlider);

    lightingReverseSwitch = ESPUI.addControl(ControlType::Switcher, "Reverse", String(lightUtils->getCfgReverse()), ControlColor::Alizarin, lightingTab, &switchExample);
    lightingFireSwitch = ESPUI.addControl(ControlType::Switcher, "Fire", String(lightUtils->getCfgFire()), ControlColor::Alizarin, lightingTab, &switchExample);
    lightingLocalDisable = ESPUI.addControl(ControlType::Switcher, "Local Disable", String(lightUtils->getCfgLocalDisable()), ControlColor::Alizarin, lightingTab, &switchExample);

    // Reset tab
    ESPUI.addControl(ControlType::Label, "**WARNING**", "Don't even think of doing anything in this tab unless you want to break something!!", ControlColor::Sunflower, resetTab);
    resetConfigSwitch = ESPUI.addControl(ControlType::Switcher, "Reset Configurations", "0", ControlColor::Sunflower, resetTab, &switchExample);
    resetRebootSwitch = ESPUI.addControl(ControlType::Switcher, "Reboot", "0", ControlColor::Sunflower, resetTab, &switchExample);

    // Enable this option if you want sliders to be continuous (update during move) and not discrete (update on stop)
    // ESPUI.sliderContinuous = true;

    // Optionally use HTTP BasicAuth
    // ESPUI.server->addHandler(new CaptiveRequestHandler()).setFilter(ON_AP_FILTER); // only when requested from AP
    // ESPUI->server->begin();

    ESPUI.captivePortal = true;

    ESPUI.list(); // List all files on LittleFS, for info
    ESPUI.begin("NOVA Core");
}

/**
 * Updates the web interface controls every n-second.
 */
void webLoop()
{
    // Initialize static variables
    static long oldTime = 0;
    static bool switchState = false;

    unsigned long currentMillis = millis();
    unsigned long seconds = (currentMillis / 1000) % 60;
    unsigned long minutes = (currentMillis / (1000 * 60)) % 60;
    unsigned long hours = (currentMillis / (1000 * 60 * 60)) % 24;
    unsigned long days = (currentMillis / (1000 * 60 * 60 * 24));

    String formattedTime = String(days) + "d " + String(hours) + "h " + String(minutes) + "m " + String(seconds) + "s";

    // Update controls every two second
    if (millis() - oldTime > 2000)
    {
        // Toggle switch state
        switchState = !switchState;

        // Update switch and millis controls
        // ESPUI.updateControlValue(switchOne, switchState ? "1" : "0");
        ESPUI.updateControlValue(controlMillis, formattedTime);

        // Update oldTime
        oldTime = millis();

        if (enable->isSystemEnabled())
        {
            if (enable->isDrunktard())
            {
                ESPUI.updateControlValue(status, "Drunktard");
            }
            else
            {
                ESPUI.updateControlValue(status, "Enabled");
            }
        }
        else
        {
            if (enable->isDrunktard())
            {
                ESPUI.updateControlValue(status, "System Disabled (Drunktard)");
            }
            else
            {
                ESPUI.updateControlValue(status, "System Disabled (Emergency Stop)");
            }
        }
    }
}