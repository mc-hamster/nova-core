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
#include "output/Star.h"
#include "output/StarSequence.h"
#include "Ambient.h"

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

uint16_t lightingBrightnessSlider, lightingSinSlider, lightingProgramSelect, lightingUpdatesSlider, lightingReverseSwitch, lightingFireSwitch, lightingLocalDisable, lightingAuto, lightingAutoTime;
uint16_t mainDrunktardSwitch;
uint16_t resetConfigSwitch, resetRebootSwitch;

uint16_t pooferA1, pooferA2, pooferA3;
uint16_t pooferB1, pooferB2, pooferB3;
uint16_t pooferC1, pooferC2, pooferC3;
uint16_t pooferD1, pooferD2, pooferD3;

uint16_t boomerA1, boomerA2, boomerA3;
uint16_t boomerB1, boomerB2, boomerB3;
uint16_t boomerC1, boomerC2, boomerC3;
uint16_t boomerD1, boomerD2, boomerD3;

uint16_t starManualPoof, starManualBlow, starManuallowFuel, starManualFuel, starManualZap, starManualSelect;
uint8_t starManualSelectValue = 0;

uint16_t sysInfoSeqIndex;

uint16_t seqBoomAll, seqBoomLeftRight, seqBoomRightLeft;

uint16_t starSeq_SEQ_POOF_END_TO_END, starSeq_SEQ_BOOMER_LEFT_TO_RIGHT, starSeq_SEQ_BOOMER_RIGHT_TO_LEFT, starSeq_SEQ_BOOM_FAST, starSeq_SEQ_BOOM_WAVE_IN, starSeq_SEQ_OFF;
uint16_t starSeq_SEQ_BOOM_POOF;

uint16_t fogOutputOffMinTime, fogOutputOffMaxTime, fogOutputOnMinTime, fogOutputOnMaxTime;

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
    else if (sender->id == lightingSinSlider)
    {
        lightUtils->setCfgSin(sender->value.toInt());
    }
    else if (sender->id == lightingUpdatesSlider)
    {
        lightUtils->setCfgUpdates(sender->value.toInt());
    }
    else if (sender->id == fogOutputOffMinTime)
    {
        ambient->setFogOutputOffMinTime(sender->value.toInt());
    }
    else if (sender->id == fogOutputOffMaxTime)
    {
        ambient->setFogOutputOffMaxTime(sender->value.toInt());
    }
    else if (sender->id == fogOutputOnMinTime)
    {
        ambient->setFogOutputOnMinTime(sender->value.toInt());
    }
    else if (sender->id == fogOutputOnMaxTime)
    {
        ambient->setFogOutputOnMaxTime(sender->value.toInt());
    }
    else if (sender->id == lightingAutoTime)
    {
        lightUtils->setCfgAutoTime(sender->value.toInt());
    }
    else
    {
        Serial.println("Unknown slider");
    }
}

void buttonCallback(Control *sender, int type)
{

    /*
     * Poofers
     */
    if (sender->id == pooferA1)
    {
        if (type == B_DOWN)
        {
            star->poof(0);
        }
    }
    else if (sender->id == pooferA2)
    {
        if (type == B_DOWN)
        {
            star->poof(1);
        }
    }
    else if (sender->id == pooferA3)
    {
        if (type == B_DOWN)
        {
            star->poof(2);
        }
    }
    else if (sender->id == pooferB1)
    {
        if (type == B_DOWN)
        {
            star->poof(3);
        }
    }
    else if (sender->id == pooferB2)
    {
        if (type == B_DOWN)
        {
            star->poof(4);
        }
    }
    else if (sender->id == pooferB3)
    {
        if (type == B_DOWN)
        {
            star->poof(5);
        }
    }
    else if (sender->id == pooferC1)
    {
        if (type == B_DOWN)
        {
            star->poof(6);
        }
    }
    else if (sender->id == pooferC2)
    {
        if (type == B_DOWN)
        {
            star->poof(7);
        }
    }
    else if (sender->id == pooferC3)
    {
        if (type == B_DOWN)
        {
            star->poof(8);
        }
    }
    else if (sender->id == pooferD1)
    {
        if (type == B_DOWN)
        {
            star->poof(9);
        }
    }
    else if (sender->id == pooferD2)
    {
        if (type == B_DOWN)
        {
            star->poof(10);
        }
    }
    else if (sender->id == pooferD3)
    {
        if (type == B_DOWN)
        {
            star->poof(11);
        }
    }

    /*
     * Boomers
     */
    if (sender->id == boomerA1)
    {
        if (type == B_DOWN)
        {
            star->boom(0);
        }
    }
    else if (sender->id == boomerA2)
    {
        if (type == B_DOWN)
        {
            star->boom(1);
        }
    }
    else if (sender->id == boomerA3)
    {
        if (type == B_DOWN)
        {
            star->boom(2);
        }
    }
    else if (sender->id == boomerB1)
    {
        if (type == B_DOWN)
        {
            star->boom(3);
        }
    }
    else if (sender->id == boomerB2)
    {
        if (type == B_DOWN)
        {
            star->boom(4);
        }
    }
    else if (sender->id == boomerB3)
    {
        if (type == B_DOWN)
        {
            star->boom(5);
        }
    }
    else if (sender->id == boomerC1)
    {
        if (type == B_DOWN)
        {
            star->boom(6);
        }
    }
    else if (sender->id == boomerC2)
    {
        if (type == B_DOWN)
        {
            star->boom(7);
        }
    }
    else if (sender->id == boomerC3)
    {
        if (type == B_DOWN)
        {
            star->boom(8);
        }
    }
    else if (sender->id == boomerD1)
    {
        if (type == B_DOWN)
        {
            star->boom(9);
        }
    }
    else if (sender->id == boomerD2)
    {
        if (type == B_DOWN)
        {
            star->boom(10);
        }
    }
    else if (sender->id == boomerD3)
    {
        if (type == B_DOWN)
        {
            star->boom(11);
        }
    }

    if (sender->id == seqBoomAll)
    {
        if (type == B_DOWN)
        {
            for (int i = 0; i < 12; i++)
            {
                star->boom(i);
            }
        }
    }
    else if (sender->id == seqBoomLeftRight)
    {
        if (type == B_DOWN)
        {
            for (int i = 0; i < 12; i++)
            {
                star->boom(i);
                delay(100);
            }
        }
    }
    else if (sender->id == seqBoomRightLeft)
    {
        if (type == B_DOWN)
        {
            for (int i = 11; i >= 0; i--)
            {
                star->boom(i);
                delay(100);
            }
        }
    }

    if (sender->id == starManualPoof)
    {
        switch (type)
        {
        case B_DOWN:
            Serial.println("Poof DOWN");
            // novaIO->mcp_digitalWrite(cluster.stars[20].blowerOutput, HIGH, cluster.stars[20].expander);
            star->manualPoof(starManualSelectValue, HIGH);
            break;

        case B_UP:
            Serial.println("Poof UP");
            star->manualPoof(starManualSelectValue, LOW);
            break;
        }
    }
    else if (sender->id == starManualBlow)
    {
        switch (type)
        {
        case B_DOWN:
            Serial.println("Blow DOWN");
            star->manualBlow(starManualSelectValue, HIGH);
            break;

        case B_UP:
            Serial.println("Blow UP");
            star->manualBlow(starManualSelectValue, LOW);
            break;
        }
    }
    else if (sender->id == starManuallowFuel)
    {
        switch (type)
        {
        case B_DOWN:
            Serial.println("Blow DOWN");
            star->manualBlowFuel(starManualSelectValue, HIGH);
            break;

        case B_UP:
            Serial.println("Blow UP");
            star->manualBlowFuel(starManualSelectValue, LOW);
            break;
        }
    }
    else if (sender->id == starManualFuel)
    {
        switch (type)
        {
        case B_DOWN:
            Serial.println("Fuel DOWN");
            star->manualFuel(starManualSelectValue, HIGH);
            break;

        case B_UP:
            Serial.println("Fuel UP");
            star->manualFuel(starManualSelectValue, LOW);
            break;
        }
    }
    else if (sender->id == starManualZap)
    {
        switch (type)
        {
        case B_DOWN:
            Serial.println("Zap DOWN");
            star->manualZap(starManualSelectValue, HIGH);
            break;

        case B_UP:
            Serial.println("Zap UP");
            star->manualZap(starManualSelectValue, LOW);
            break;
        }
    }

    if (sender->id == starSeq_SEQ_POOF_END_TO_END)
    {
        switch (type)
        {
        case B_DOWN:
            Serial.println("starSeq_SEQ_POOF_END_TO_END DOWN");
            starSequence->setSequence(starSequence->SEQ_POOF_END_TO_END);
            break;

        case B_UP:
            Serial.println("starSeq_SEQ_POOF_END_TO_END UP");
            starSequence->setSequence(starSequence->SEQ_OFF);
            break;
        }
    }
    else if (sender->id == starSeq_SEQ_BOOM_FAST)
    {
        switch (type)
        {
        case B_DOWN:
            Serial.println("starSeq_SEQ_BOOM_FAST DOWN");
            starSequence->setSequence(starSequence->SEQ_BOOM_FAST);
            break;

        case B_UP:
            Serial.println("starSeq_SEQ_BOOM_FAST UP");
            starSequence->setSequence(starSequence->SEQ_OFF);
            break;
        }
    }
    else if (sender->id == starSeq_SEQ_BOOMER_LEFT_TO_RIGHT)
    {
        switch (type)
        {
        case B_DOWN:
            Serial.println("starSeq_SEQ_BOOMER_LEFT_TO_RIGHT DOWN");
            starSequence->setSequence(starSequence->SEQ_BOOMER_LEFT_TO_RIGHT);
            break;

        case B_UP:
            Serial.println("starSeq_SEQ_BOOMER_LEFT_TO_RIGHT UP");
            starSequence->setSequence(starSequence->SEQ_OFF);
            break;
        }
    }
    else if (sender->id == starSeq_SEQ_BOOMER_RIGHT_TO_LEFT)
    {
        switch (type)
        {
        case B_DOWN:
            Serial.println("starSeq_SEQ_BOOMER_LEFT_TO_RIGHT DOWN");
            starSequence->setSequence(starSequence->SEQ_BOOMER_RIGHT_TO_LEFT);
            break;

        case B_UP:
            Serial.println("starSeq_SEQ_BOOMER_RIGHT_TO_LEFT UP");
            starSequence->setSequence(starSequence->SEQ_OFF);
            break;
        }
    }
    else if (sender->id == starSeq_SEQ_BOOM_WAVE_IN)
    {
        switch (type)
        {
        case B_DOWN:
            Serial.println("starSeq_SEQ_BOOM_WAVE_IN DOWN");
            starSequence->setSequence(starSequence->SEQ_BOOM_WAVE_IN);
            break;

        case B_UP:
            Serial.println("starSeq_SEQ_BOOM_WAVE_IN UP");
            starSequence->setSequence(starSequence->SEQ_OFF);
            break;
        }
    }
    else if (sender->id == starSeq_SEQ_BOOM_POOF)
    {
        switch (type)
        {
        case B_DOWN:
            Serial.println("starSeq_SEQ_BOOM_POOF DOWN");
            starSequence->setSequence(starSequence->SEQ_BOOM_POOF);
            break;

        case B_UP:
            Serial.println("starSeq_SEQ_BOOM_POOF UP");
            starSequence->setSequence(starSequence->SEQ_OFF);
            break;
        }
    }


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
    else if (sender->id == lightingAuto)
    {
        lightUtils->setCfgAuto(sender->value.toInt());
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
            Serial.println("Rebooting device from web switch...");
            delay(50);
            ESP.restart();
        }
    }
    else
    {
        Serial.println("Unknown Switch");
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
    else if (sender->id == starManualSelect)
    {
        starManualSelectValue = sender->value.toInt();
    }
}

void webSetup()
{
    // Add tabs
    uint16_t mainTab = ESPUI.addControl(ControlType::Tab, "Main", "Main");
    // uint16_t settingsTab = ESPUI.addControl(ControlType::Tab, "Settings", "Settings");
    uint16_t manualTab = ESPUI.addControl(ControlType::Tab, "Manual", "Manual");
    uint16_t sequencesTab = ESPUI.addControl(ControlType::Tab, "Sequences", "Sequences");
    uint16_t lightingTab = ESPUI.addControl(ControlType::Tab, "Lighting", "Lighting");
    uint16_t fogTab = ESPUI.addControl(ControlType::Tab, "Fog", "Fog");
    uint16_t sysInfoTab = ESPUI.addControl(ControlType::Tab, "System Info", "System Info");
    uint16_t resetTab = ESPUI.addControl(ControlType::Tab, "Reset", "Reset");

    // Add status label above all tabs
    status = ESPUI.addControl(ControlType::Label, "Status:", "Unknown Status", ControlColor::Turquoise);

    //----- (Main) -----
    controlMillis = ESPUI.addControl(ControlType::Label, "Uptime", "0", ControlColor::Emerald, mainTab);
    mainDrunktardSwitch = ESPUI.addControl(ControlType::Switcher, "Drunktard", String(enable->isDrunktard()), ControlColor::None, mainTab, &switchExample);

    //----- (Settings) -----
    // ESPUI.addControl(ControlType::Switcher, "Sleep (Disable)", "", ControlColor::None, settingsTab, &switchExample);

    //----- (Manual) -----

    pooferA1 = ESPUI.addControl(ControlType::Button, "Star Cluster - A", "Poof 1", ControlColor::Alizarin, manualTab, buttonCallback);
    pooferA2 = ESPUI.addControl(ControlType::Button, "", "Poof 2", ControlColor::None, pooferA1, buttonCallback);
    pooferA3 = ESPUI.addControl(ControlType::Button, "", "Poof 3", ControlColor::None, pooferA1, buttonCallback);

    boomerA1 = ESPUI.addControl(ControlType::Button, "Star Cluster - A", "Boom 1", ControlColor::None, pooferA1, buttonCallback);
    boomerA2 = ESPUI.addControl(ControlType::Button, "", "Boom 2", ControlColor::None, pooferA1, buttonCallback);
    boomerA3 = ESPUI.addControl(ControlType::Button, "", "Boom 3", ControlColor::None, pooferA1, buttonCallback);

    pooferB1 = ESPUI.addControl(ControlType::Button, "Star Cluster - B", "Poof 1", ControlColor::Emerald, manualTab, buttonCallback);
    pooferB2 = ESPUI.addControl(ControlType::Button, "", "Poof 2", ControlColor::None, pooferB1, buttonCallback);
    pooferB3 = ESPUI.addControl(ControlType::Button, "", "Poof 3", ControlColor::None, pooferB1, buttonCallback);

    boomerB1 = ESPUI.addControl(ControlType::Button, "Star Cluster - B", "Boom 1", ControlColor::Emerald, pooferB1, buttonCallback);
    boomerB2 = ESPUI.addControl(ControlType::Button, "", "Boom 2", ControlColor::None, pooferB1, buttonCallback);
    boomerB3 = ESPUI.addControl(ControlType::Button, "", "Boom 3", ControlColor::None, pooferB1, buttonCallback);

    pooferC1 = ESPUI.addControl(ControlType::Button, "Star Cluster - C", "Poof 1", ControlColor::Peterriver, manualTab, buttonCallback);
    pooferC2 = ESPUI.addControl(ControlType::Button, "", "Poof 2", ControlColor::None, pooferC1, buttonCallback);
    pooferC3 = ESPUI.addControl(ControlType::Button, "", "Poof 3", ControlColor::None, pooferC1, buttonCallback);

    boomerC1 = ESPUI.addControl(ControlType::Button, "Star Cluster - C", "Boom 1", ControlColor::Peterriver, pooferC1, buttonCallback);
    boomerC2 = ESPUI.addControl(ControlType::Button, "", "Boom 2", ControlColor::None, pooferC1, buttonCallback);
    boomerC3 = ESPUI.addControl(ControlType::Button, "", "Boom 3", ControlColor::None, pooferC1, buttonCallback);

    pooferD1 = ESPUI.addControl(ControlType::Button, "Star Cluster - D", "Poof 1", ControlColor::Carrot, manualTab, buttonCallback);
    pooferD2 = ESPUI.addControl(ControlType::Button, "", "Poof 2", ControlColor::None, pooferD1, buttonCallback);
    pooferD3 = ESPUI.addControl(ControlType::Button, "", "Poof 3", ControlColor::None, pooferD1, buttonCallback);

    boomerD1 = ESPUI.addControl(ControlType::Button, "Star Cluster - D", "Boom 1", ControlColor::Carrot, pooferD1, buttonCallback);
    boomerD2 = ESPUI.addControl(ControlType::Button, "", "Boom 2", ControlColor::None, pooferD1, buttonCallback);
    boomerD3 = ESPUI.addControl(ControlType::Button, "", "Boom 3", ControlColor::None, pooferD1, buttonCallback);

    starManualPoof = ESPUI.addControl(ControlType::Button, "Star Manual", "Poof", ControlColor::Carrot, manualTab, buttonCallback);
    starManualBlow = ESPUI.addControl(ControlType::Button, "Star Manual", "Blow", ControlColor::Carrot, starManualPoof, buttonCallback);
    starManualFuel = ESPUI.addControl(ControlType::Button, "Star Manual", "Fuel", ControlColor::Carrot, starManualPoof, buttonCallback);
    starManuallowFuel = ESPUI.addControl(ControlType::Button, "Star Manual", "Blow & Fuel", ControlColor::Carrot, starManualPoof, buttonCallback);
    starManualZap = ESPUI.addControl(ControlType::Button, "Star Manual", "Zap", ControlColor::Carrot, starManualPoof, buttonCallback);

    starManualSelect = ESPUI.addControl(ControlType::Select, "Star 1", String(starManualSelectValue), ControlColor::Alizarin, starManualPoof, &selectExample);
    ESPUI.addControl(ControlType::Option, "Star 1", "0", ControlColor::Alizarin, starManualSelect);
    ESPUI.addControl(ControlType::Option, "Star 2", "1", ControlColor::Alizarin, starManualSelect);
    ESPUI.addControl(ControlType::Option, "Star 3", "2", ControlColor::Alizarin, starManualSelect);
    ESPUI.addControl(ControlType::Option, "Star 4", "3", ControlColor::Alizarin, starManualSelect);
    ESPUI.addControl(ControlType::Option, "Star 5", "4", ControlColor::Alizarin, starManualSelect);
    ESPUI.addControl(ControlType::Option, "Star 6", "5", ControlColor::Alizarin, starManualSelect);
    ESPUI.addControl(ControlType::Option, "Star 7", "6", ControlColor::Alizarin, starManualSelect);
    ESPUI.addControl(ControlType::Option, "Star 8", "7", ControlColor::Alizarin, starManualSelect);
    ESPUI.addControl(ControlType::Option, "Star 9", "8", ControlColor::Alizarin, starManualSelect);
    ESPUI.addControl(ControlType::Option, "Star 10", "9", ControlColor::Alizarin, starManualSelect);
    ESPUI.addControl(ControlType::Option, "Star 11", "10", ControlColor::Alizarin, starManualSelect);
    ESPUI.addControl(ControlType::Option, "Star 12", "11", ControlColor::Alizarin, starManualSelect);
    ESPUI.addControl(ControlType::Option, "Star 13", "12", ControlColor::Alizarin, starManualSelect);
    ESPUI.addControl(ControlType::Option, "Star 14", "13", ControlColor::Alizarin, starManualSelect);
    ESPUI.addControl(ControlType::Option, "Star 15", "14", ControlColor::Alizarin, starManualSelect);
    ESPUI.addControl(ControlType::Option, "Star 16", "15", ControlColor::Alizarin, starManualSelect);
    ESPUI.addControl(ControlType::Option, "Star 17", "16", ControlColor::Alizarin, starManualSelect);
    ESPUI.addControl(ControlType::Option, "Star 18", "17", ControlColor::Alizarin, starManualSelect);
    ESPUI.addControl(ControlType::Option, "Star 19", "18", ControlColor::Alizarin, starManualSelect);
    ESPUI.addControl(ControlType::Option, "Star 20", "19", ControlColor::Alizarin, starManualSelect);

    //---- Tab 3 (Sequences) -----
    seqBoomAll = ESPUI.addControl(ControlType::Button, "Direct Boomers", "All", ControlColor::Peterriver, sequencesTab, &buttonCallback);
    seqBoomLeftRight = ESPUI.addControl(ControlType::Button, "Boomers", "L to R (100ms)", ControlColor::Peterriver, seqBoomAll, &buttonCallback);
    seqBoomRightLeft = ESPUI.addControl(ControlType::Button, "Boomers", "R to L (100ms)", ControlColor::Peterriver, seqBoomAll, &buttonCallback);

    starSeq_SEQ_POOF_END_TO_END = ESPUI.addControl(ControlType::Button, "SEQ_POOF_END_TO_END", "SEQ_POOF_END_TO_END", ControlColor::Peterriver, sequencesTab, &buttonCallback);
    starSeq_SEQ_BOOMER_LEFT_TO_RIGHT = ESPUI.addControl(ControlType::Button, "Boomers", "BOOMER_LEFT_TO_RIGHT", ControlColor::Peterriver, starSeq_SEQ_POOF_END_TO_END, &buttonCallback);
    starSeq_SEQ_BOOMER_RIGHT_TO_LEFT = ESPUI.addControl(ControlType::Button, "Boomers", "SEQ_BOOMER_RIGHT_TO_LEFT", ControlColor::Peterriver, starSeq_SEQ_POOF_END_TO_END, &buttonCallback);
    starSeq_SEQ_BOOM_FAST = ESPUI.addControl(ControlType::Button, "Boomers", "SEQ_BOOM_FAST", ControlColor::Peterriver, starSeq_SEQ_POOF_END_TO_END, &buttonCallback);
    starSeq_SEQ_BOOM_WAVE_IN = ESPUI.addControl(ControlType::Button, "Boomers", "SEQ_BOOM_WAVE_IN", ControlColor::Peterriver, starSeq_SEQ_POOF_END_TO_END, &buttonCallback);
    starSeq_SEQ_BOOM_POOF = ESPUI.addControl(ControlType::Button, "Boomers", "SEQ_BOOM_POOF", ControlColor::Peterriver, starSeq_SEQ_POOF_END_TO_END, &buttonCallback);



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
    ESPUI.addControl(ControlType::Option, "All Red", "21", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "All Green", "22", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "All Blue", "23", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "All Purple", "24", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "All Cyan", "25", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "All Yellow", "26", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "White Dot", "50", ControlColor::Alizarin, lightingProgramSelect);

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

    lightingAuto = ESPUI.addControl(ControlType::Switcher, "Auto Light Program Selection", String(lightUtils->getCfgReverse()), ControlColor::Alizarin, lightingTab, &switchExample);
    lightingAutoTime = ESPUI.addControl(ControlType::Slider, "Auto Time", String(lightUtils->getCfgAutoTime() ? lightUtils->getCfgAutoTime() : 30), ControlColor::Alizarin, lightingAuto, &slider);
    ESPUI.addControl(Min, "", "1", None, fogOutputOffMinTime);
    ESPUI.addControl(Max, "", "3600", None, fogOutputOffMinTime);

    //--- Fog Tab ---

    fogOutputOffMinTime = ESPUI.addControl(ControlType::Slider, "Off Time (default: 5000 / 20000)", String(ambient->getFogOutputOffMinTime() ? ambient->getFogOutputOffMinTime() : 5000), ControlColor::Alizarin, fogTab, &slider);
    ESPUI.addControl(Min, "", "2000", None, fogOutputOffMinTime);
    ESPUI.addControl(Max, "", "60000", None, fogOutputOffMinTime);

    fogOutputOffMaxTime = ESPUI.addControl(ControlType::Slider, "", String(ambient->getFogOutputOffMaxTime() ? ambient->getFogOutputOffMaxTime() : 20000), ControlColor::Alizarin, fogOutputOffMinTime, &slider);
    ESPUI.addControl(Min, "", "2000", None, fogOutputOffMaxTime);
    ESPUI.addControl(Max, "", "60000", None, fogOutputOffMaxTime);

    fogOutputOnMinTime = ESPUI.addControl(ControlType::Slider, "On Time (default: 200 / 1000)", String(ambient->getFogOutputOnMinTime() ? ambient->getFogOutputOnMinTime() : 200), ControlColor::Alizarin, fogTab, &slider);
    ESPUI.addControl(Min, "", "200", None, fogOutputOnMinTime);
    ESPUI.addControl(Max, "", "2000", None, fogOutputOnMinTime);

    fogOutputOnMaxTime = ESPUI.addControl(ControlType::Slider, "", String(ambient->getFogOutputOnMaxTime() ? ambient->getFogOutputOnMaxTime() : 1000), ControlColor::Alizarin, fogOutputOnMinTime, &slider);
    ESPUI.addControl(Min, "", "200", None, fogOutputOnMaxTime);
    ESPUI.addControl(Max, "", "2000", None, fogOutputOnMaxTime);
    /*
     */

    // System Info Tab
    sysInfoSeqIndex = ESPUI.addControl(ControlType::Label, "Button Sequence Index", "Red: 0, Green: 0, Blue: 0, Yellow: 0", ControlColor::Sunflower, sysInfoTab);

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

    // Update controls every second
    if (millis() - oldTime > 1000)
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

        String sequenceString = "Red: " + String(star->sequenceRed) + ", Green: " + String(star->sequenceGreen) + "<br>Blue: " + String(star->sequenceBlue) + ", Yellow: " + String(star->sequenceYellow);
        ESPUI.updateControlValue(sysInfoSeqIndex, sequenceString);
    }
}