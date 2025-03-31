#include "Web.h"
#include "WebEndpoint.h"  // Added this include to fix the WebEndpoint not declared error
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
#include "utilities/PreferencesManager.h"
#include "Simona.h"
#include "freertos/semphr.h"
#include <Preferences.h>
#include <ArduinoJson.h>  // Added for JSON API

// Global game control variables
bool SIMONA_CHEAT_MODE = false;
bool GAME_ENABLED = true;
bool SEQUENCE_LOCAL_ECHO = true;

// Fog power manual control IDs
uint16_t fogPowerManual[12];

// Fog power cluster control IDs
uint16_t fogPowerClusterA, fogPowerClusterB, fogPowerClusterC, fogPowerClusterD;

// Mutex for API operations
SemaphoreHandle_t apiMutex = NULL;

// API response helpers
void sendJsonResponse(AsyncWebServerRequest *request, JsonDocument &doc) {
    AsyncResponseStream *response = request->beginResponseStream("application/json");
    serializeJson(doc, *response);
    request->send(response);
}

void sendErrorResponse(AsyncWebServerRequest *request, int code, const String &message) {
    AsyncResponseStream *response = request->beginResponseStream("application/json");
    JsonDocument doc;
    doc.to<JsonObject>(); // Initialize as object
    doc["success"] = false;
    doc["error"] = message;
    serializeJson(doc, *response);
    request->send(response);  // Changed from request->send(code, "application/json", response);
}

// API route handlers
void handleStatusRequest(AsyncWebServerRequest *request) {
    if (xSemaphoreTake(apiMutex, (TickType_t)1000) != pdTRUE) {
        sendErrorResponse(request, 503, "Server busy");
        return;
    }
    
    JsonDocument doc;  // Changed from DynamicJsonDocument
    doc.to<JsonObject>(); // Initialize as object
    doc["success"] = true;
    
    // System status
    doc["status"]["uptime"] = millis();
    doc["status"]["emergency_stop"] = !enable->isSystemEnabled();
    doc["status"]["drunktard_mode"] = enable->isDrunktard();
    
    // Simona game status
    Simona* simona = Simona::getInstance();
    if (simona) {
        doc["simona"]["game_enabled"] = GAME_ENABLED;
        doc["simona"]["cheat_mode"] = SIMONA_CHEAT_MODE;
        doc["simona"]["sequence_local_echo"] = SEQUENCE_LOCAL_ECHO;
        doc["simona"]["progress"] = simona->getProgress();
        doc["simona"]["expected_color"] = simona->getExpectedColorName();
        doc["simona"]["time_remaining"] = simona->getTimeRemaining();
    }
    
    // Lighting settings
    doc["lighting"]["brightness"] = lightUtils->getCfgBrightness();
    doc["lighting"]["program"] = lightUtils->getCfgProgram();
    doc["lighting"]["sin"] = lightUtils->getCfgSin();
    doc["lighting"]["updates"] = lightUtils->getCfgUpdates();
    doc["lighting"]["reverse"] = lightUtils->getCfgReverse() != 0;
    doc["lighting"]["fire"] = lightUtils->getCfgFire() != 0;
    doc["lighting"]["local_disable"] = lightUtils->getCfgLocalDisable() != 0;
    doc["lighting"]["auto"] = lightUtils->getCfgAuto() != 0;
    doc["lighting"]["auto_time"] = lightUtils->getCfgAutoTime();
    doc["lighting"]["reverse_second_row"] = lightUtils->getCfgReverseSecondRow() != 0;
    
    // Fog settings - Fix create method to modern syntax
    JsonArray fogArray = doc["fog_enabled"].to<JsonArray>();  // Changed from doc.createNestedArray
    for (int i = 0; i < 12; i++) {
        fogArray.add(star->getFogEnabled(i));
    }
    
    doc["fog_settings"]["off_min_time"] = ambient->getFogOutputOffMinTime();
    doc["fog_settings"]["off_max_time"] = ambient->getFogOutputOffMaxTime();
    doc["fog_settings"]["on_min_time"] = ambient->getFogOutputOnMinTime();
    doc["fog_settings"]["on_max_time"] = ambient->getFogOutputOnMaxTime();
    
    sendJsonResponse(request, doc);
    xSemaphoreGive(apiMutex);
}

// API command handlers
void handleSimonaCommand(AsyncWebServerRequest *request, const JsonVariant &json) {
    if (xSemaphoreTake(apiMutex, (TickType_t)500) != pdTRUE) {
        sendErrorResponse(request, 503, "Server busy");
        return;
    }
    
    JsonObject jsonObj = json.as<JsonObject>();
    bool updated = false;
    JsonDocument response;  // Using JsonDocument directly now
    response.to<JsonObject>(); // Initialize as object
    response["success"] = true;
    
    if (jsonObj["cheat_mode"].is<bool>()) {
        SIMONA_CHEAT_MODE = jsonObj["cheat_mode"].as<bool>();
        PreferencesManager::setBool("simonaCheatMode", SIMONA_CHEAT_MODE);
        Simona *simona = Simona::getInstance();
        if (simona) {
            simona->setCheatMode(SIMONA_CHEAT_MODE);
        }
        updated = true;
    }
    
    if (jsonObj["game_enabled"].is<bool>()) {
        GAME_ENABLED = jsonObj["game_enabled"].as<bool>();
        PreferencesManager::setBool("gameEn", GAME_ENABLED);
        updated = true;
    }
    
    if (jsonObj["sequence_local_echo"].is<bool>()) {
        SEQUENCE_LOCAL_ECHO = jsonObj["sequence_local_echo"].as<bool>();
        PreferencesManager::setBool("simonaSequenceLocalEcho", SEQUENCE_LOCAL_ECHO);
        Simona *simona = Simona::getInstance();
        if (simona) {
            simona->setSequenceLocalEcho(SEQUENCE_LOCAL_ECHO);
        }
        updated = true;
    }
    
    if (updated) {
        response["message"] = "Simona settings updated";
    } else {
        response["message"] = "No settings changed";
    }
    
    AsyncResponseStream *resp = request->beginResponseStream("application/json");
    serializeJson(response, *resp);
    request->send(resp);
    
    xSemaphoreGive(apiMutex);
}

void handleStarCommand(AsyncWebServerRequest *request, const JsonVariant &json) {
    if (xSemaphoreTake(apiMutex, (TickType_t)500) != pdTRUE) {
        sendErrorResponse(request, 503, "Server busy");
        return;
    }
    
    JsonObject jsonObj = json.as<JsonObject>();
    JsonDocument response;  // Using JsonDocument directly now
    response.to<JsonObject>(); // Initialize as object
    response["success"] = true;
    
    if (jsonObj["poof"].is<int>()) {
        int starIndex = jsonObj["poof"].as<int>();
        if (starIndex >= 0 && starIndex < 12) {
            star->poof(starIndex);
            response["message"] = "Poof command sent to star " + String(starIndex);
        } else {
            response["success"] = false;
            response["error"] = "Invalid star index (must be 0-11)";
        }
    } 
    else if (jsonObj["boom"].is<int>()) {
        int starIndex = jsonObj["boom"].as<int>();
        if (starIndex >= 0 && starIndex < 12) {
            star->boom(starIndex);
            response["message"] = "Boom command sent to star " + String(starIndex);
        } else {
            response["success"] = false;
            response["error"] = "Invalid star index (must be 0-11)";
        }
    }
    else if (jsonObj["fog_enabled"].is<JsonObject>()) {
        JsonObject fogSettings = jsonObj["fog_enabled"].as<JsonObject>();
        for (JsonPair kv : fogSettings) {
            int starIndex = atoi(kv.key().c_str());
            bool enabled = kv.value().as<bool>();
            if (starIndex >= 0 && starIndex < 12) {
                star->setFogEnabled(starIndex, enabled);
                response["updated"][String(starIndex)] = enabled;
            }
        }
        response["message"] = "Fog settings updated";
    }
    else if (jsonObj["manual"].is<JsonObject>()) {
        int starIndex = jsonObj["star_index"].as<int>();
        String action = jsonObj["action"].as<String>();
        bool state = jsonObj["state"].as<bool>();
        
        if (starIndex >= 0 && starIndex < 12) {
            if (action == "poof") {
                star->manualPoof(starIndex, state ? HIGH : LOW);
            } 
            else if (action == "blow") {
                star->manualBlow(starIndex, state ? HIGH : LOW);
            }
            else if (action == "blow_fuel") {
                star->manualBlowFuel(starIndex, state ? HIGH : LOW);
            }
            else if (action == "fuel") {
                star->manualFuel(starIndex, state ? HIGH : LOW);
            }
            else if (action == "zap") {
                star->manualZap(starIndex, state ? HIGH : LOW);
            }
            else {
                response["success"] = false;
                response["error"] = "Unknown action: " + action;
            }
            
            if (response["success"].as<bool>()) {
                response["message"] = action + " command sent with state " + (state ? "HIGH" : "LOW");
            }
        } else {
            response["success"] = false;
            response["error"] = "Invalid star index (must be 0-11)";
        }
    }
    else {
        response["success"] = false;
        response["error"] = "No valid command specified";
    }
    
    AsyncResponseStream *resp = request->beginResponseStream("application/json");
    serializeJson(response, *resp);
    request->send(resp);
    
    xSemaphoreGive(apiMutex);
}

void handleSequenceCommand(AsyncWebServerRequest *request, const JsonVariant &json) {
    if (xSemaphoreTake(apiMutex, (TickType_t)500) != pdTRUE) {
        sendErrorResponse(request, 503, "Server busy");
        return;
    }
    
    JsonObject jsonObj = json.as<JsonObject>();
    JsonDocument response;  // Using JsonDocument directly
    response.to<JsonObject>(); // Initialize as object
    response["success"] = true;
    
    if (jsonObj["sequence"].is<String>()) {
        String seq = jsonObj["sequence"].as<String>();
        bool activate = jsonObj["activate"].is<bool>() ? jsonObj["activate"].as<bool>() : true;
        
        if (seq == "POOF_END_TO_END") {
            starSequence->setSequence(activate ? starSequence->SEQ_POOF_END_TO_END : starSequence->SEQ_OFF);
            response["message"] = "POOF_END_TO_END sequence " + String(activate ? "activated" : "deactivated");
        }
        else if (seq == "BOOMER_LEFT_TO_RIGHT") {
            starSequence->setSequence(activate ? starSequence->SEQ_BOOMER_LEFT_TO_RIGHT : starSequence->SEQ_OFF);
            response["message"] = "BOOMER_LEFT_TO_RIGHT sequence " + String(activate ? "activated" : "deactivated");
        }
        else if (seq == "BOOMER_RIGHT_TO_LEFT") {
            starSequence->setSequence(activate ? starSequence->SEQ_BOOMER_RIGHT_TO_LEFT : starSequence->SEQ_OFF);
            response["message"] = "BOOMER_RIGHT_TO_LEFT sequence " + String(activate ? "activated" : "deactivated");
        }
        else if (seq == "BOOM_FAST") {
            starSequence->setSequence(activate ? starSequence->SEQ_BOOM_FAST : starSequence->SEQ_OFF);
            response["message"] = "BOOM_FAST sequence " + String(activate ? "activated" : "deactivated");
        }
        else if (seq == "BOOM_WAVE_IN") {
            starSequence->setSequence(activate ? starSequence->SEQ_BOOM_WAVE_IN : starSequence->SEQ_OFF);
            response["message"] = "BOOM_WAVE_IN sequence " + String(activate ? "activated" : "deactivated");
        }
        else if (seq == "BOOM_POOF") {
            starSequence->setSequence(activate ? starSequence->SEQ_BOOM_POOF : starSequence->SEQ_OFF);
            response["message"] = "BOOM_POOF sequence " + String(activate ? "activated" : "deactivated");
        }
        else if (seq == "OFF") {
            starSequence->setSequence(starSequence->SEQ_OFF);
            response["message"] = "All sequences deactivated";
        }
        else {
            response["success"] = false;
            response["error"] = "Unknown sequence: " + seq;
        }
    }
    else if (jsonObj["quick_sequence"].is<String>()) {
        String quickSeq = jsonObj["quick_sequence"].as<String>();
        
        if (quickSeq == "BOOM_ALL") {
            for (int i = 0; i < 12; i++) {
                star->boom(i);
            }
            response["message"] = "All boomers triggered";
        }
        else if (quickSeq == "BOOM_LEFT_RIGHT") {
            for (int i = 0; i < 12; i++) {
                star->boom(i);
                delay(100);
            }
            response["message"] = "Left to right boom sequence triggered";
        }
        else if (quickSeq == "BOOM_RIGHT_LEFT") {
            for (int i = 11; i >= 0; i--) {
                star->boom(i);
                delay(100);
            }
            response["message"] = "Right to left boom sequence triggered";
        }
        else {
            response["success"] = false;
            response["error"] = "Unknown quick sequence: " + quickSeq;
        }
    }
    else {
        response["success"] = false;
        response["error"] = "No sequence or quick_sequence specified";
    }
    
    AsyncResponseStream *resp = request->beginResponseStream("application/json");
    serializeJson(response, *resp);
    request->send(resp);
    
    xSemaphoreGive(apiMutex);
}

void handleLightingCommand(AsyncWebServerRequest *request, const JsonVariant &json) {
    if (xSemaphoreTake(apiMutex, (TickType_t)500) != pdTRUE) {
        sendErrorResponse(request, 503, "Server busy");
        return;
    }
    
    JsonObject jsonObj = json.as<JsonObject>();
    StaticJsonDocument<512> response;  // Changed from JsonDocument to StaticJsonDocument with size
    response.to<JsonObject>(); // Initialize as object
    response["success"] = true;
    bool updated = false;
    
    if (jsonObj["brightness"].is<int>()) {
        int value = jsonObj["brightness"].as<int>();
        if (value >= 0 && value <= 255) {
            lightUtils->setCfgBrightness(value);
            updated = true;
            response["brightness"] = value;
        }
    }
    
    if (jsonObj["program"].is<int>()) {
        int value = jsonObj["program"].as<int>();
        if (value >= 1 && value <= 50) {
            lightUtils->setCfgProgram(value);
            updated = true;
            response["program"] = value;
        }
    }
    
    if (jsonObj["sin"].is<int>()) {
        int value = jsonObj["sin"].as<int>();
        if (value >= 0 && value <= 32) {
            lightUtils->setCfgSin(value);
            updated = true;
            response["sin"] = value;
        }
    }
    
    if (jsonObj["updates"].is<int>()) {
        int value = jsonObj["updates"].as<int>();
        if (value >= 1 && value <= 255) {
            lightUtils->setCfgUpdates(value);
            updated = true;
            response["updates"] = value;
        }
    }
    
    if (jsonObj["reverse"].is<bool>()) {
        bool value = jsonObj["reverse"].as<bool>();
        lightUtils->setCfgReverse(value ? 1 : 0);
        updated = true;
        response["reverse"] = value;
    }
    
    if (jsonObj["fire"].is<bool>()) {
        bool value = jsonObj["fire"].as<bool>();
        lightUtils->setCfgFire(value ? 1 : 0);
        updated = true;
        response["fire"] = value;
    }
    
    if (jsonObj["local_disable"].is<bool>()) {
        bool value = jsonObj["local_disable"].as<bool>();
        lightUtils->setCfgLocalDisable(value ? 1 : 0);
        updated = true;
        response["local_disable"] = value;
    }
    
    if (jsonObj["auto"].is<bool>()) {
        bool value = jsonObj["auto"].as<bool>();
        lightUtils->setCfgAuto(value ? 1 : 0);
        updated = true;
        response["auto"] = value;
    }
    
    if (jsonObj["auto_time"].is<int>()) {
        int value = jsonObj["auto_time"].as<int>();
        if (value >= 1 && value <= 3600) {
            lightUtils->setCfgAutoTime(value);
            updated = true;
            response["auto_time"] = value;
        }
    }
    
    if (jsonObj["reverse_second_row"].is<bool>()) {
        bool value = jsonObj["reverse_second_row"].as<bool>();
        lightUtils->setCfgReverseSecondRow(value ? 1 : 0);
        updated = true;
        response["reverse_second_row"] = value;
    }
    
    if (updated) {
        response["message"] = "Lighting settings updated";
    } else {
        response["message"] = "No settings changed";
    }
    
    AsyncResponseStream *resp = request->beginResponseStream("application/json");
    serializeJson(response, *resp);
    request->send(resp);
    
    xSemaphoreGive(apiMutex);
}

void handleFogSettingsCommand(AsyncWebServerRequest *request, const JsonVariant &json) {
    if (xSemaphoreTake(apiMutex, (TickType_t)500) != pdTRUE) {
        sendErrorResponse(request, 503, "Server busy");
        return;
    }
    
    JsonObject jsonObj = json.as<JsonObject>();
    StaticJsonDocument<512> response;  // Changed from JsonDocument to StaticJsonDocument with size
    response.to<JsonObject>(); // Initialize as object
    response["success"] = true;
    bool updated = false;
    
    if (jsonObj["off_min_time"].is<int>()) {
        int value = jsonObj["off_min_time"].as<int>();
        if (value >= 2000 && value <= 60000) {
            ambient->setFogOutputOffMinTime(value);
            updated = true;
            response["off_min_time"] = value;
        }
    }
    
    if (jsonObj["off_max_time"].is<int>()) {
        int value = jsonObj["off_max_time"].as<int>();
        if (value >= 2000 && value <= 60000) {
            ambient->setFogOutputOffMaxTime(value);
            updated = true;
            response["off_max_time"] = value;
        }
    }
    
    if (jsonObj["on_min_time"].is<int>()) {
        int value = jsonObj["on_min_time"].as<int>();
        if (value >= 200 && value <= 2000) {
            ambient->setFogOutputOnMinTime(value);
            updated = true;
            response["on_min_time"] = value;
        }
    }
    
    if (jsonObj["on_max_time"].is<int>()) {
        int value = jsonObj["on_max_time"].as<int>();
        if (value >= 200 && value <= 2000) {
            ambient->setFogOutputOnMaxTime(value);
            updated = true;
            response["on_max_time"] = value;
        }
    }
    
    if (updated) {
        response["message"] = "Fog timing settings updated";
    } else {
        response["message"] = "No settings changed";
    }
    
    AsyncResponseStream *resp = request->beginResponseStream("application/json");
    serializeJson(response, *resp);
    request->send(resp);
    
    xSemaphoreGive(apiMutex);
}

void handleSystemCommand(AsyncWebServerRequest *request, const JsonVariant &json) {
    if (xSemaphoreTake(apiMutex, (TickType_t)500) != pdTRUE) {
        sendErrorResponse(request, 503, "Server busy");
        return;
    }
    
    JsonObject jsonObj = json.as<JsonObject>();
    StaticJsonDocument<512> response;  // Changed from JsonDocument to StaticJsonDocument with size
    response.to<JsonObject>(); // Initialize as object
    response["success"] = true;
    
    if (jsonObj["drunktard"].is<bool>()) {
        bool value = jsonObj["drunktard"].as<bool>();
        PreferencesManager::setBool("cfgDrunktard", value);
        response["message"] = "Drunktard mode " + String(value ? "enabled" : "disabled");
    }
    else if (jsonObj["reset_config"].is<bool>() && jsonObj["reset_config"].as<bool>()) {
        // PreferencesManager::clear();
        // PreferencesManager::save();
        response["message"] = "Config reset requested. Device will reboot.";
        
        // Schedule a reboot after response is sent
        xSemaphoreGive(apiMutex);  // Release mutex before reboot
        request->onDisconnect([](){
            delay(100);
            ESP.restart();
        });
    }
    else if (jsonObj["reboot"].is<bool>() && jsonObj["reboot"].as<bool>()) {
        response["message"] = "System reboot requested";
        
        // Schedule a reboot after response is sent
        xSemaphoreGive(apiMutex);  // Release mutex before reboot
        request->onDisconnect([](){
            delay(100);
            ESP.restart();
        });
    }
    else {
        response["success"] = false;
        response["error"] = "No valid command specified";
    }
    
    AsyncResponseStream *resp = request->beginResponseStream("application/json");
    serializeJson(response, *resp);
    request->send(resp);
    
    if (response["success"].as<bool>() && 
        !jsonObj["reset_config"].is<bool>() &&
        !jsonObj["reboot"].is<bool>()) {
        xSemaphoreGive(apiMutex);
    }
}

void handleRequest(AsyncWebServerRequest *request)
{
    AsyncResponseStream *response = request->beginResponseStream("text/html");
    response->print("<!DOCTYPE html><html><head><title>Captive Portal - NOVA</title></head><body>");
    response->print("<p>NOVA</p>");
    if (0)
    {
        response->print("<p>This is our captive portal front page.</p>");
        response->printf("<p>You were trying to reach: http://%s%s</p>", request->host().c_str(), request->url().c_str());
        response->printf("<p>Try opening <a href='http://%s'>this link</a> instead</p>", WiFi.softAPIP().toString().c_str());
    }
    response->print("</body></html>");
    request->send(response);
}

uint16_t switchOne;
uint16_t status;
uint16_t controlMillis;
uint16_t networkInfo;  // Add network info label

uint16_t simonaProgressLabel, expectedColorLabel, timeRemainingLabel;
uint16_t lightingBrightnessSlider, lightingSinSlider, lightingProgramSelect, lightingUpdatesSlider, lightingReverseSwitch, lightingFireSwitch, lightingLocalDisable, lightingAuto, lightingAutoTime, lightingReverseSecondRow;
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

uint16_t seqBoomAll, seqBoomLeftRight, seqBoomRightLeft;

uint16_t starSeq_SEQ_POOF_END_TO_END, starSeq_SEQ_BOOMER_LEFT_TO_RIGHT, starSeq_SEQ_BOOMER_RIGHT_TO_LEFT, starSeq_SEQ_BOOM_FAST, starSeq_SEQ_BOOM_WAVE_IN, starSeq_SEQ_OFF;
uint16_t starSeq_SEQ_BOOM_POOF;

uint16_t fogOutputOffMinTime, fogOutputOffMaxTime, fogOutputOnMinTime, fogOutputOnMaxTime;

// Define new control IDs for Simona Settings
uint16_t simonaCheatModeSwitch;
uint16_t simonaGameEnabledSwitch;
uint16_t simonaSequenceLocalEchoSwitch;

uint16_t fogPowerManualPanel;

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
            Serial.println("starSeq_SEQ_BOOMER_LEFT_TO_RIGHT UP");
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
    // Add handler for reverse second row toggle
    else if (sender->id == lightingReverseSecondRow)
    {
        lightUtils->setCfgReverseSecondRow(sender->value.toInt());
    }
    // Handle fog power manual toggles
    else if (sender->id >= fogPowerManual[0] && sender->id <= fogPowerManual[11])
    {
        int starIndex = sender->id - fogPowerManual[0];
        star->setFogEnabled(starIndex, sender->value.toInt() == 1);
    }
    else if (sender->id == mainDrunktardSwitch)
    {
        PreferencesManager::setBool("cfgDrunktard", sender->value.toInt() == 1);
        Serial.print("Drunktard Switch Value: ");
        Serial.println(sender->value.toInt());
    }
    else if (sender->id == resetConfigSwitch)
    {
        // TODO:
        //    - Give the user a chance to cancel the config reset.
        if (sender->value.toInt())
        {
            // PreferencesManager::clear();
            // PreferencesManager::save();
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
    // Add handlers for the new Simona Settings switches
    else if (sender->id == simonaCheatModeSwitch)
    {
        SIMONA_CHEAT_MODE = (sender->value == "1");
        PreferencesManager::setBool("simonaCheatMode", SIMONA_CHEAT_MODE);

        // Check if Simona instance exists before calling methods on it
        Simona *simona = Simona::getInstance();
        if (simona)
        {
            simona->setCheatMode(SIMONA_CHEAT_MODE);
        }

        Serial.printf("Cheat mode %s and saved to preferences\n", SIMONA_CHEAT_MODE ? "enabled" : "disabled");
    }
    else if (sender->id == simonaGameEnabledSwitch)
    {
        GAME_ENABLED = (sender->value.toInt() == 1);
        PreferencesManager::setBool("gameEn", GAME_ENABLED); // Shortened from simonaGameEnabled
        Serial.printf("Game %s and saved to preferences\n", GAME_ENABLED ? "enabled" : "disabled");
    }
    else if (sender->id == simonaSequenceLocalEchoSwitch)
    {
        SEQUENCE_LOCAL_ECHO = (sender->value.toInt() == 1);
        PreferencesManager::setBool("simonaSequenceLocalEcho", SEQUENCE_LOCAL_ECHO);

        // Check if Simona instance exists before calling methods on it
        Simona *simona = Simona::getInstance();
        if (simona)
        {
            simona->setSequenceLocalEcho(SEQUENCE_LOCAL_ECHO);
        }

        Serial.printf("Sequence local echo %s and saved to preferences\n", SEQUENCE_LOCAL_ECHO ? "enabled" : "disabled");
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
    // Load saved preferences for Simona settings
    SIMONA_CHEAT_MODE = PreferencesManager::getBool("simonaCheatMode", false);
    GAME_ENABLED = PreferencesManager::getBool("gameEn", true); // Shortened from simonaGameEnabled
    SEQUENCE_LOCAL_ECHO = PreferencesManager::getBool("simonaSequenceLocalEcho", true);

    // Safely check if Simona is initialized before calling methods
    Simona *simona = Simona::getInstance();
    if (simona)
    {
        Serial.println("Initializing Simona with preferences");
        simona->setCheatMode(SIMONA_CHEAT_MODE);
        simona->setSequenceLocalEcho(SEQUENCE_LOCAL_ECHO);
    }
    else
    {
        Serial.println("Warning: Simona not initialized yet");
    }

    // Add tabs
    uint16_t mainTab = ESPUI.addControl(ControlType::Tab, "Main", "Main");
    // uint16_t settingsTab = ESPUI.addControl(ControlType::Tab, "Settings", "Settings");
    uint16_t simonaSettingsTab = ESPUI.addControl(ControlType::Tab, "Simona Settings", "Simona Settings");
    uint16_t manualTab = ESPUI.addControl(ControlType::Tab, "Manual", "Manual");
    uint16_t sequencesTab = ESPUI.addControl(ControlType::Tab, "Sequences", "Sequences");
    uint16_t lightingTab = ESPUI.addControl(ControlType::Tab, "Lighting", "Lighting");
    uint16_t fogTab = ESPUI.addControl(ControlType::Tab, "Fog", "Fog");
    uint16_t sysInfoTab = ESPUI.addControl(ControlType::Tab, "System Info", "System Info");
    uint16_t resetTab = ESPUI.addControl(ControlType::Tab, "Reset", "Reset");

    // Add status label above all tabs
    status = ESPUI.addControl(ControlType::Label, "Status:", "Unknown Status", ControlColor::Turquoise);

    //----- (Main) -----
    // Simona game status labels
    simonaProgressLabel = ESPUI.addControl(ControlType::Label, "Simona Progress:", "0", ControlColor::Emerald, mainTab);
    expectedColorLabel = ESPUI.addControl(ControlType::Label, "Expected Color:", "None", ControlColor::Emerald, mainTab);
    timeRemainingLabel = ESPUI.addControl(ControlType::Label, "Time Remaining:", "0", ControlColor::Emerald, mainTab);

    mainDrunktardSwitch = ESPUI.addControl(ControlType::Switcher, "Drunktard", String(PreferencesManager::getBool("cfgDrunktard", false)), ControlColor::None, mainTab, &switchExample);

    //----- (Simona Settings) -----
    // Add Simona settings to the new tab
    simonaCheatModeSwitch = ESPUI.addControl(
        ControlType::Switcher,
        "Cheat Mode",
        SIMONA_CHEAT_MODE ? "1" : "0",
        ControlColor::Carrot,
        simonaSettingsTab,
        &switchExample);

    // Add tooltip explaining cheat mode
    ESPUI.addControl(
        ControlType::Label,
        "",
        "When enabled, the game sequence will be predictable",
        ControlColor::None,
        simonaCheatModeSwitch);

    // Add game enabled toggle
    simonaGameEnabledSwitch = ESPUI.addControl(
        ControlType::Switcher,
        "Game Enabled",
        GAME_ENABLED ? "1" : "0",
        ControlColor::Peterriver,
        simonaSettingsTab,
        &switchExample);

    // Add tooltip explaining game enabled
    ESPUI.addControl(
        ControlType::Label,
        "",
        "When disabled, game inputs will be ignored",
        ControlColor::None,
        simonaGameEnabledSwitch);

    // Add sequence local echo toggle
    simonaSequenceLocalEchoSwitch = ESPUI.addControl(
        ControlType::Switcher,
        "Sequence Local Echo",
        SEQUENCE_LOCAL_ECHO ? "1" : "0",
        ControlColor::Peterriver,
        simonaSettingsTab,
        &switchExample);

    // Add tooltip explaining sequence local echo
    ESPUI.addControl(
        ControlType::Label,
        "",
        "When disabled, LED sequences will not play locally. (reboot required)",
        ControlColor::None,
        simonaSequenceLocalEchoSwitch);

    // Move uptime to System Info tab
    controlMillis = ESPUI.addControl(ControlType::Label, "Uptime", "0", ControlColor::Emerald, sysInfoTab);
    networkInfo = ESPUI.addControl(ControlType::Label, "Network Info", "", ControlColor::Emerald, sysInfoTab);

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
    if (0)
    {
        ESPUI.addControl(ControlType::Option, "Star 13", "12", ControlColor::Alizarin, starManualSelect);
        ESPUI.addControl(ControlType::Option, "Star 14", "13", ControlColor::Alizarin, starManualSelect);
        ESPUI.addControl(ControlType::Option, "Star 15", "14", ControlColor::Alizarin, starManualSelect);
        ESPUI.addControl(ControlType::Option, "Star 16", "15", ControlColor::Alizarin, starManualSelect);
        ESPUI.addControl(ControlType::Option, "Star 17", "16", ControlColor::Alizarin, starManualSelect);
        ESPUI.addControl(ControlType::Option, "Star 18", "17", ControlColor::Alizarin, starManualSelect);
        ESPUI.addControl(ControlType::Option, "Star 19", "18", ControlColor::Alizarin, starManualSelect);
        ESPUI.addControl(ControlType::Option, "Star 20", "19", ControlColor::Alizarin, starManualSelect);
    }
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

    lightingAuto = ESPUI.addControl(ControlType::Switcher, "Auto Light Program Selection", String(lightUtils->getCfgAuto()), ControlColor::Alizarin, lightingTab, &switchExample);
    lightingAutoTime = ESPUI.addControl(ControlType::Slider, "Auto Time", String(lightUtils->getCfgAutoTime() ? lightUtils->getCfgAutoTime() : 30), ControlColor::Alizarin, lightingAuto, &slider);
    ESPUI.addControl(Min, "", "1", None, fogOutputOffMinTime);
    ESPUI.addControl(Max, "", "3600", None, fogOutputOffMinTime);

    // Add reverse second row toggle
    lightingReverseSecondRow = ESPUI.addControl(ControlType::Switcher, "Reverse Second Row", String(lightUtils->getCfgReverseSecondRow()), ControlColor::Alizarin, lightingTab, &switchExample);

    //--- Fog Tab ---
    if (1)
    {
        // Star Cluster A
        fogPowerClusterA = ESPUI.addControl(ControlType::Label, "Star Cluster - A", "Manual Fog Control", ControlColor::Alizarin, fogTab);
        fogPowerManual[0] = ESPUI.addControl(ControlType::Switcher, "Star 1", star->getFogEnabled(0) ? "1" : "0", ControlColor::Alizarin, fogPowerClusterA, &switchExample);
        fogPowerManual[1] = ESPUI.addControl(ControlType::Switcher, "Star 2", star->getFogEnabled(1) ? "1" : "0", ControlColor::None, fogPowerClusterA, &switchExample);
        fogPowerManual[2] = ESPUI.addControl(ControlType::Switcher, "Star 3", star->getFogEnabled(2) ? "1" : "0", ControlColor::None, fogPowerClusterA, &switchExample);

        // Star Cluster B
        fogPowerClusterB = ESPUI.addControl(ControlType::Label, "Star Cluster - B", "Manual Fog Control", ControlColor::Emerald, fogTab);
        fogPowerManual[3] = ESPUI.addControl(ControlType::Switcher, "Star 4", star->getFogEnabled(3) ? "1" : "0", ControlColor::Emerald, fogPowerClusterB, &switchExample);
        fogPowerManual[4] = ESPUI.addControl(ControlType::Switcher, "Star 5", star->getFogEnabled(4) ? "1" : "0", ControlColor::None, fogPowerClusterB, &switchExample);
        fogPowerManual[5] = ESPUI.addControl(ControlType::Switcher, "Star 6", star->getFogEnabled(5) ? "1" : "0", ControlColor::None, fogPowerClusterB, &switchExample);

        // Star Cluster C
        fogPowerClusterC = ESPUI.addControl(ControlType::Label, "Star Cluster - C", "Manual Fog Control", ControlColor::Peterriver, fogTab);
        fogPowerManual[6] = ESPUI.addControl(ControlType::Switcher, "Star 7", star->getFogEnabled(6) ? "1" : "0", ControlColor::Peterriver, fogPowerClusterC, &switchExample);
        fogPowerManual[7] = ESPUI.addControl(ControlType::Switcher, "Star 8", star->getFogEnabled(7) ? "1" : "0", ControlColor::None, fogPowerClusterC, &switchExample);
        fogPowerManual[8] = ESPUI.addControl(ControlType::Switcher, "Star 9", star->getFogEnabled(8) ? "1" : "0", ControlColor::None, fogPowerClusterC, &switchExample);

        // Star Cluster D
        fogPowerClusterD = ESPUI.addControl(ControlType::Label, "Star Cluster - D", "Manual Fog Control", ControlColor::Carrot, fogTab);
        fogPowerManual[9] = ESPUI.addControl(ControlType::Switcher, "Star 10", star->getFogEnabled(9) ? "1" : "0", ControlColor::Carrot, fogPowerClusterD, &switchExample);
        fogPowerManual[10] = ESPUI.addControl(ControlType::Switcher, "Star 11", star->getFogEnabled(10) ? "1" : "0", ControlColor::None, fogPowerClusterD, &switchExample);
        fogPowerManual[11] = ESPUI.addControl(ControlType::Switcher, "Star 12", star->getFogEnabled(11) ? "1" : "0", ControlColor::None, fogPowerClusterD, &switchExample);
    }

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

    // Reset tab
    ESPUI.addControl(ControlType::Label, "**WARNING**", "Don't even think of doing anything in this tab unless you want to break something!!", ControlColor::Sunflower, resetTab);
    resetConfigSwitch = ESPUI.addControl(ControlType::Switcher, "Reset Configurations", "0", ControlColor::Sunflower, resetTab, &switchExample);
    resetRebootSwitch = ESPUI.addControl(ControlType::Switcher, "Reboot", "0", ControlColor::Sunflower, resetTab, &switchExample);

    // Enable this option if you want sliders to be continuous (update during move) and not discrete (update on stop)
    // ESPUI.sliderContinuous = true;

    // Optionally use HTTP BasicAuth
    // ESPUI.server->addHandler(new CaptiveRequestHandler()).setFilter(ON_AP_FILTER); // only when requested from AP
    // ESPUI->server->begin();

    ESPUI.captivePortal = false; // Disable captive portal

    // ESPUI.list(); // List all files on LittleFS, for info
    ESPUI.begin("NOVA Core");

    // Setup our REST API endpoints
    WebEndpoint::setupApiEndpoints(ESPUI.WebServer());
}

/**
 * Updates the web interface controls every n-second.
 */
ControlColor getColorForName(const char *colorName)
{
    if (!colorName)
        return ControlColor::Dark;

    String color = String(colorName);
    color.toLowerCase();

    if (color == "red")
        return ControlColor::Alizarin; // Red
    if (color == "green")
        return ControlColor::Emerald; // Green
    if (color == "blue")
        return ControlColor::Peterriver; // Blue
    if (color == "yellow")
        return ControlColor::Sunflower; // Yellow
    if (color == "white")
        return ControlColor::Wetasphalt; // White represented as gray

    return ControlColor::Dark;
}

void webLoop()
{
    // Initialize static variables
    static unsigned long oldTime = 0;
    static bool switchState = false;
    static const unsigned long UPDATE_INTERVAL = 1000; // Update every 1 second
    static bool isUpdating = false;                    // Guard against recursion
    static SemaphoreHandle_t webMutex = xSemaphoreCreateMutex();

    // Rate limit updates and prevent recursion
    unsigned long currentMillis = millis();
    if (currentMillis - oldTime < UPDATE_INTERVAL || isUpdating)
    {
        return;
    }

    // Try to take mutex with timeout
    if (xSemaphoreTake(webMutex, (TickType_t)100) != pdTRUE)
    {
        return; // Couldn't get mutex, skip this update
    }

    isUpdating = true;

    // Wrap UI updates in try-catch
    try
    {
        oldTime = currentMillis;

        // Use stack-based string for time formatting
        char timeStr[32];
        unsigned long seconds = (currentMillis / 1000) % 60;
        unsigned long minutes = (currentMillis / (1000 * 60)) % 60;
        unsigned long hours = (currentMillis / (1000 * 60 * 60)) % 24;
        unsigned long days = (currentMillis / (1000 * 60 * 60 * 24));
        snprintf(timeStr, sizeof(timeStr), "%lud %luh %lum %lus", days, hours, minutes, seconds);

        // Update uptime display 
        if (controlMillis && ESPUI.getControl(controlMillis)) {
            ESPUI.updateControlValue(controlMillis, timeStr);
        }

        // Get Simona instance with null check 
        Simona* simona = Simona::getInstance();
        if (simona && simonaProgressLabel && expectedColorLabel && timeRemainingLabel &&
            ESPUI.getControl(simonaProgressLabel) && ESPUI.getControl(expectedColorLabel) && 
            ESPUI.getControl(timeRemainingLabel)) {

            // Update progress directly using the String from getProgress()
            ESPUI.updateControlValue(simonaProgressLabel, simona->getProgress());

            // Update color info
            const char* expectedColor = simona->getExpectedColorName();
            Control* colorControl = ESPUI.getControl(expectedColorLabel);
            if (expectedColor && colorControl) {
                ESPUI.updateControlValue(expectedColorLabel, expectedColor);
                colorControl->color = getColorForName(expectedColor);
                ESPUI.updateControl(colorControl);
            } else if (colorControl) {
                ESPUI.updateControlValue(expectedColorLabel, "None");
            }

            // Update time remaining
            char timeRemStr[16]; 
            snprintf(timeRemStr, sizeof(timeRemStr), "%d", simona->getTimeRemaining());
            ESPUI.updateControlValue(timeRemainingLabel, timeRemStr);
        }

        // Update network info display
        if (networkInfo && ESPUI.getControl(networkInfo)) {
            String networkStatus = "MAC: " + WiFi.macAddress() + "<br>";
            networkStatus += "AP IP: " + WiFi.softAPIP().toString() + "<br>";
            networkStatus += "Client IP: " + WiFi.localIP().toString();
            ESPUI.updateControlValue(networkInfo, networkStatus);
        }

        // Update status message
        Control* statusControl = status ? ESPUI.getControl(status) : nullptr;
        if (statusControl) {
            const char* statusMsg;
            ControlColor statusColor = ControlColor::Emerald;

            if (!GAME_ENABLED) {
                statusMsg = "⚠️ GAME DISABLED - Game inputs ignored";
                statusColor = ControlColor::Alizarin;
            }
            else if (SIMONA_CHEAT_MODE) {
                statusMsg = "⚠️ CHEAT MODE ENABLED - Game sequence predictable ⚠️";
                statusColor = ControlColor::Sunflower;
            }
            else if (enable && enable->isSystemEnabled()) {
                statusMsg = enable->isDrunktard() ? "Drunktard" : "Enabled";
            }
            else {
                statusMsg = enable && enable->isDrunktard() ? "System Disabled - Drunktard" : "System Disabled";
                statusColor = ControlColor::Alizarin;
            }

            ESPUI.updateControlValue(status, statusMsg);
            statusControl->color = statusColor;
            ESPUI.updateControl(statusControl);
        }
    }
    catch (...) {
        Serial.println("Error occurred during webLoop update");
    }

    isUpdating = false;
    xSemaphoreGive(webMutex);
}