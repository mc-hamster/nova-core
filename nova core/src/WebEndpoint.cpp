/**
 * NOVA Core REST API Documentation
 * ================================
 * 
 * This file implements the REST API endpoints for the NOVA Core system.
 * All endpoints are under /api/* and return JSON responses.
 * 
 * API Endpoints:
 * -------------
 * 
 * 1. GET /api/status
 *    Returns system status including uptime, emergency stop state, lighting settings, fog settings, etc.
 *    Response example:
 *    {
 *      "success": true,
 *      "status": {
 *        "uptime": 123456,
 *        "emergency_stop": false,
 *        "drunktard_mode": false
 *      },
 *      "simona": {
 *        "game_enabled": true,
 *        "cheat_mode": false,
 *        "sequence_local_echo": true,
 *        "progress": "3/8",
 *        "expected_color": "red",
 *        "time_remaining": 10
 *      },
 *      "fog_enabled": [true, false, true, ...],
 *      "fog_settings": {
 *        "off_min_time": 5000,
 *        "off_max_time": 20000,
 *        "on_min_time": 200,
 *        "on_max_time": 1000
 *      }
 *    }
 * 
 * 2. POST /api/command
 *    Unified endpoint for all write operations. Requires a "command" field to determine the operation.
 *    
 *    Request body structure:
 *    {
 *      "command": "[command-type]",  // Required: simona, star, sequence, lighting, fog, system
 *      // Additional parameters specific to the command type
 *    }
 *    
 *    Command Types and Parameters:
 *    ----------------------------
 *    
 *    a. "simona" - Configure Simona game settings
 *       {
 *         "command": "simona",
 *         "cheat_mode": true|false,        // Enable/disable cheat mode (predictable sequence)
 *         "game_enabled": true|false,      // Enable/disable the game
 *         "sequence_local_echo": true|false // Enable/disable local LED sequence display
 *       }
 * 
 *    b. "star" - Control individual stars
 *       Examples:
 *       - Poof a specific star:
 *         {
 *           "command": "star",
 *           "poof": 5  // Trigger poof effect on star index 5
 *         }
 *       - Boom a specific star:
 *         {
 *           "command": "star",
 *           "boom": 5  // Trigger boom effect on star index 5
 *         }
 *       - Set fog state:
 *         {
 *           "command": "star",
 *           "fog_enabled": {
 *             "0": true,
 *             "1": false,
 *             "2": true,
 *             ...
 *           }
 *         }
 *       - Manual control:
 *         {
 *           "command": "star",
 *           "manual": true,
 *           "star_index": 5,
 *           "action": "poof"|"blow"|"blow_fuel"|"fuel"|"zap",
 *           "state": true|false
 *         }
 * 
 *    c. "sequence" - Control star sequences
 *       - Set sequence:
 *         {
 *           "command": "sequence",
 *           "sequence": "POOF_END_TO_END"|"BOOMER_LEFT_TO_RIGHT"|"BOOMER_RIGHT_TO_LEFT"|
 *                       "BOOM_FAST"|"BOOM_WAVE_IN"|"BOOM_POOF"|"OFF",
 *           "activate": true|false  // Optional, defaults to true
 *         }
 *       - Quick sequence:
 *         {
 *           "command": "sequence",
 *           "quick_sequence": "BOOM_ALL"|"BOOM_LEFT_RIGHT"|"BOOM_RIGHT_LEFT"
 *         }
 * 
 *    d. "lighting" - Configure lighting settings
 *       {
 *         "command": "lighting",
 *         // All fields below are optional
 *         "brightness": 0-255,
 *         "program": 1-50,
 *         "sin": 0-32,
 *         "updates": 1-255,
 *         "reverse": true|false,
 *         "fire": true|false,
 *         "local_disable": true|false,
 *         "auto": true|false,
 *         "auto_time": 1-3600,
 *         "reverse_second_row": true|false
 *       }
 * 
 *    e. "fog" - Configure fog timing settings
 *       {
 *         "command": "fog",
 *         // All fields below are optional
 *         "off_min_time": 2000-60000,  // Min time fog is off (ms)
 *         "off_max_time": 2000-60000,  // Max time fog is off (ms)
 *         "on_min_time": 200-2000,     // Min time fog is on (ms)
 *         "on_max_time": 200-2000      // Max time fog is on (ms)
 *       }
 * 
 *    f. "system" - System control commands
 *       - Set drunktard mode:
 *         {
 *           "command": "system",
 *           "drunktard": true|false
 *         }
 *       - Reset configuration:
 *         {
 *           "command": "system",
 *           "reset_config": true
 *         }
 *       - Reboot system:
 *         {
 *           "command": "system",
 *           "reboot": true
 *         }
 * 
 * All API endpoints return JSON responses with at least a "success" field.
 * On error, endpoints return a JSON object: { "success": false, "error": "Error message" }
 * 
 * NOTE: This API is optimized for the free version of FlutterFlow, which allows only two endpoints.
 */

#include "WebEndpoint.h"
#include <WiFi.h>
#include <AsyncTCP.h>
#include "ESPAsyncWebServer.h"
#include <AsyncJson.h>  // Add this include for AsyncJsonWebHandler
#include "main.h"
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
#include <ArduinoJson.h>
#include "Web.h"  // For external variables

// Remove the global apiMutex - we'll use the one from Web.cpp
// SemaphoreHandle_t apiMutex = NULL;

namespace WebEndpoint {

// Define a local apiMutex for this namespace
SemaphoreHandle_t endpointApiMutex = NULL;

// API response helpers
void sendJsonResponseEndpoint(AsyncWebServerRequest *request, const JsonDocument &doc) {
    AsyncResponseStream *response = request->beginResponseStream("application/json");
    serializeJson(doc, *response);
    request->send(response);
}

void sendErrorResponseEndpoint(AsyncWebServerRequest *request, int code, const String &message) {
    AsyncResponseStream *response = request->beginResponseStream("application/json");
    JsonDocument doc;
    doc["success"] = false;
    doc["error"] = message;
    serializeJson(doc, *response);
    request->send(response);
}

// API route handlers
void handleStatusRequest(AsyncWebServerRequest *request) {
    // Use the endpointApiMutex instead
    if (xSemaphoreTake(endpointApiMutex, (TickType_t)1000) != pdTRUE) {
        sendErrorResponseEndpoint(request, 503, "Server busy");
        return;
    }
    
    JsonDocument doc;
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
    
    // Fog settings - using JsonArray correctly
    JsonArray fogArray = doc["fog_enabled"].to<JsonArray>();
    for (int i = 0; i < 12; i++) {
        fogArray.add(star->getFogEnabled(i));
    }
    
    doc["fog_settings"]["off_min_time"] = ambient->getFogOutputOffMinTime();
    doc["fog_settings"]["off_max_time"] = ambient->getFogOutputOffMaxTime();
    doc["fog_settings"]["on_min_time"] = ambient->getFogOutputOnMinTime();
    doc["fog_settings"]["on_max_time"] = ambient->getFogOutputOnMaxTime();
    
    sendJsonResponseEndpoint(request, doc);
    xSemaphoreGive(endpointApiMutex);
}

// Unified command handler that processes all commands based on the command type
void handleCommand(AsyncWebServerRequest *request) {
    // Use the endpointApiMutex for all command operations
    if (xSemaphoreTake(endpointApiMutex, (TickType_t)1000) != pdTRUE) {
        sendErrorResponseEndpoint(request, 503, "Server busy");
        return;
    }

    // Check content type
    if (request->contentType() != "application/json") {
        sendErrorResponseEndpoint(request, 415, "Unsupported Media Type");
        xSemaphoreGive(endpointApiMutex);
        return;
    }
    
    // Debug output
    Serial.println("Command received");
    
    // Check if there's any body content
    if (!request->hasParam("plain", true)) {
        Serial.println("No request body found");
        sendErrorResponseEndpoint(request, 400, "Missing request body");
        xSemaphoreGive(endpointApiMutex);
        return;
    }
    
    // Get the body content
    String bodyContent = request->getParam("plain", true)->value();
    
    // Debug the received JSON
    Serial.print("Received JSON: ");
    Serial.println(bodyContent);
    
    // Check if body is empty
    if (bodyContent.length() == 0) {
        Serial.println("Empty request body");
        sendErrorResponseEndpoint(request, 400, "Empty request body");
        xSemaphoreGive(endpointApiMutex);
        return;
    }
    
    // Parse the JSON from the request body
    JsonDocument jsonDoc;
    DeserializationError error = deserializeJson(jsonDoc, bodyContent);
    if (error) {
        Serial.print("JSON parsing error: ");
        Serial.println(error.c_str());
        sendErrorResponseEndpoint(request, 400, String("JSON parsing error: ") + error.c_str());
        xSemaphoreGive(endpointApiMutex);
        return;
    }
    
    // Debug - Print the parsed JSON
    Serial.println("JSON parsed successfully");
    
    JsonDocument response;
    response["success"] = true;
    
    // Determine the command type and call the appropriate handler function
    if (!jsonDoc["command"].is<String>()) {
        sendErrorResponseEndpoint(request, 400, "Missing or invalid 'command' field");
        xSemaphoreGive(endpointApiMutex);
        return;
    }

    String command = jsonDoc["command"].as<String>();
    
    // Route the command to the appropriate handler based on the command type
    if (command == "simona") {
        // Handle Simona game settings
        bool updated = false;
        
        if (jsonDoc["cheat_mode"].is<bool>()) {
            SIMONA_CHEAT_MODE = jsonDoc["cheat_mode"].as<bool>();
            PreferencesManager::setBool("simonaCheatMode", SIMONA_CHEAT_MODE);
            Simona *simona = Simona::getInstance();
            if (simona) {
                simona->setCheatMode(SIMONA_CHEAT_MODE);
            }
            updated = true;
        }
        
        if (jsonDoc["game_enabled"].is<bool>()) {
            GAME_ENABLED = jsonDoc["game_enabled"].as<bool>();
            PreferencesManager::setBool("gameEn", GAME_ENABLED);
            updated = true;
        }
        
        if (jsonDoc["sequence_local_echo"].is<bool>()) {
            SEQUENCE_LOCAL_ECHO = jsonDoc["sequence_local_echo"].as<bool>();
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
    }
    else if (command == "star") {
        // Handle star commands
        if (jsonDoc["poof"].is<int>()) {
            int starIndex = jsonDoc["poof"].as<int>();
            if (starIndex >= 0 && starIndex < 12) {
                star->poof(starIndex);
                response["message"] = "Poof command sent to star " + String(starIndex);
            } else {
                response["success"] = false;
                response["error"] = "Invalid star index (must be 0-11)";
            }
        } 
        else if (jsonDoc["boom"].is<int>()) {
            int starIndex = jsonDoc["boom"].as<int>();
            if (starIndex >= 0 && starIndex < 12) {
                star->boom(starIndex);
                response["message"] = "Boom command sent to star " + String(starIndex);
            } else {
                response["success"] = false;
                response["error"] = "Invalid star index (must be 0-11)";
            }
        }
        else if (jsonDoc["fog_enabled"].is<JsonObject>()) {
            JsonObject fogSettings = jsonDoc["fog_enabled"].as<JsonObject>();
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
        else if (jsonDoc["manual"].is<bool>()) {
            int starIndex = jsonDoc["star_index"].as<int>();
            String action = jsonDoc["action"].as<String>();
            bool state = jsonDoc["state"].as<bool>();
            
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
            response["error"] = "No valid star command specified";
        }
    }
    else if (command == "sequence") {
        // Handle sequence commands
        if (jsonDoc["quick_sequence"].is<String>()) {
            String quickSeq = jsonDoc["quick_sequence"].as<String>();
            
            if (quickSeq == "BOOM_ALL") {
                for (int i = 0; i < 12; i++) {
                    star->boom(i);
                }
                response["message"] = "All boomers triggered";
            }
            else if (quickSeq == "BOOM_LEFT_RIGHT") {
                // Start from the left side (stars 0-5)
                for(int i = 0; i < 6; i++) {
                    star->boom(i);
                    delay(100);
                }
                // Then the right side (stars 6-11)
                for(int i = 6; i < 12; i++) {
                    star->boom(i);
                    delay(100);
                }
                response["message"] = "Left to right boom sequence triggered";
            }
            else if (quickSeq == "BOOM_RIGHT_LEFT") {
                // Start from right side (stars 11-6)
                for(int i = 11; i >= 6; i--) {
                    star->boom(i);
                    delay(100);
                }
                // Then the left side (stars 5-0)
                for(int i = 5; i >= 0; i--) {
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
        else if (jsonDoc["sequence"].is<String>()) {
            String seqName = jsonDoc["sequence"].as<String>();
            
            // Get the activate flag, default to true if not present
            bool activate = true;
            if (jsonDoc["activate"].is<bool>()) {
                activate = jsonDoc["activate"].as<bool>();
            }

            StarSequence::sequences sequenceType = StarSequence::SEQ_OFF;
            
            if (seqName == "POOF_END_TO_END") {
                sequenceType = StarSequence::SEQ_POOF_END_TO_END;
            }
            else if (seqName == "BOOMER_LEFT_TO_RIGHT") {
                sequenceType = StarSequence::SEQ_BOOMER_LEFT_TO_RIGHT;
            }
            else if (seqName == "BOOMER_RIGHT_TO_LEFT") {
                sequenceType = StarSequence::SEQ_BOOMER_RIGHT_TO_LEFT;
            }
            else if (seqName == "BOOM_FAST") {
                sequenceType = StarSequence::SEQ_BOOM_FAST;
            }
            else if (seqName == "BOOM_WAVE_IN") {
                sequenceType = StarSequence::SEQ_BOOM_WAVE_IN;
            }
            else if (seqName == "BOOM_POOF") {
                sequenceType = StarSequence::SEQ_BOOM_POOF;
            }
            else if (seqName == "OFF") {
                sequenceType = StarSequence::SEQ_OFF;
            }
            else {
                response["success"] = false;
                response["error"] = "Unknown sequence type: " + seqName;
                sendJsonResponseEndpoint(request, response);
                xSemaphoreGive(endpointApiMutex);
                return;
            }
            
            // Set the sequence
            if (activate) {
                starSequence->setSequence(sequenceType);
                response["message"] = "Sequence " + seqName + " activated";
            } else {
                starSequence->setSequence(StarSequence::SEQ_OFF);
                response["message"] = "Sequence deactivated";
            }
        }
        else {
            response["success"] = false;
            response["error"] = "No sequence specified";
        }
    }
    else if (command == "lighting") {
        // Handle lighting commands
        bool updated = false;
        
        if (jsonDoc["brightness"].is<int>()) {
            int value = jsonDoc["brightness"].as<int>();
            if (value >= 0 && value <= 255) {
                lightUtils->setCfgBrightness(value);
                updated = true;
                response["brightness"] = value;
            }
        }
        
        if (jsonDoc["program"].is<int>()) {
            int value = jsonDoc["program"].as<int>();
            if (value >= 1 && value <= 50) {
                lightUtils->setCfgProgram(value);
                updated = true;
                response["program"] = value;
            }
        }
        
        if (jsonDoc["sin"].is<int>()) {
            int value = jsonDoc["sin"].as<int>();
            if (value >= 0 && value <= 32) {
                lightUtils->setCfgSin(value);
                updated = true;
                response["sin"] = value;
            }
        }
        
        if (jsonDoc["updates"].is<int>()) {
            int value = jsonDoc["updates"].as<int>();
            if (value >= 1 && value <= 255) {
                lightUtils->setCfgUpdates(value);
                updated = true;
                response["updates"] = value;
            }
        }
        
        if (jsonDoc["reverse"].is<bool>()) {
            bool value = jsonDoc["reverse"].as<bool>();
            lightUtils->setCfgReverse(value ? 1 : 0);
            updated = true;
            response["reverse"] = value;
        }
        
        if (jsonDoc["fire"].is<bool>()) {
            bool value = jsonDoc["fire"].as<bool>();
            lightUtils->setCfgFire(value ? 1 : 0);
            updated = true;
            response["fire"] = value;
        }
        
        if (jsonDoc["local_disable"].is<bool>()) {
            bool value = jsonDoc["local_disable"].as<bool>();
            lightUtils->setCfgLocalDisable(value ? 1 : 0);
            updated = true;
            response["local_disable"] = value;
        }
        
        if (jsonDoc["auto"].is<bool>()) {
            bool value = jsonDoc["auto"].as<bool>();
            lightUtils->setCfgAuto(value ? 1 : 0);
            updated = true;
            response["auto"] = value;
        }
        
        if (jsonDoc["auto_time"].is<int>()) {
            int value = jsonDoc["auto_time"].as<int>();
            if (value >= 1 && value <= 3600) {
                lightUtils->setCfgAutoTime(value);
                updated = true;
                response["auto_time"] = value;
            }
        }
        
        if (jsonDoc["reverse_second_row"].is<bool>()) {
            bool value = jsonDoc["reverse_second_row"].as<bool>();
            lightUtils->setCfgReverseSecondRow(value ? 1 : 0);
            updated = true;
            response["reverse_second_row"] = value;
        }
        
        if (updated) {
            response["message"] = "Lighting settings updated";
        } else {
            response["message"] = "No settings changed";
        }
    }
    else if (command == "fog") {
        // Handle fog settings commands
        bool updated = false;
        
        if (jsonDoc["off_min_time"].is<int>()) {
            int value = jsonDoc["off_min_time"].as<int>();
            if (value >= 2000 && value <= 60000) {
                ambient->setFogOutputOffMinTime(value);
                updated = true;
                response["off_min_time"] = value;
            }
        }
        
        if (jsonDoc["off_max_time"].is<int>()) {
            int value = jsonDoc["off_max_time"].as<int>();
            if (value >= 2000 && value <= 60000) {
                ambient->setFogOutputOffMaxTime(value);
                updated = true;
                response["off_max_time"] = value;
            }
        }
        
        if (jsonDoc["on_min_time"].is<int>()) {
            int value = jsonDoc["on_min_time"].as<int>();
            if (value >= 200 && value <= 2000) {
                ambient->setFogOutputOnMinTime(value);
                updated = true;
                response["on_min_time"] = value;
            }
        }
        
        if (jsonDoc["on_max_time"].is<int>()) {
            int value = jsonDoc["on_max_time"].as<int>();
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
    }
    else if (command == "system") {
        // Handle system commands
        if (jsonDoc["drunktard"].is<bool>()) {
            bool value = jsonDoc["drunktard"].as<bool>();
            PreferencesManager::setBool("cfgDrunktard", value);
            response["message"] = "Drunktard mode " + String(value ? "enabled" : "disabled");
        }
        else if (jsonDoc["reset_config"].is<bool>() && jsonDoc["reset_config"].as<bool>()) {
            // PreferencesManager::clear();
            // PreferencesManager::save();
            response["message"] = "Config reset requested. Device will reboot.";
            
            // Schedule a reboot after response is sent
            xSemaphoreGive(endpointApiMutex);  // Release mutex before reboot
            request->onDisconnect([](){
                delay(100);
                ESP.restart();
            });
            sendJsonResponseEndpoint(request, response);
            return;
        }
        else if (jsonDoc["reboot"].is<bool>() && jsonDoc["reboot"].as<bool>()) {
            response["message"] = "System reboot requested";
            
            // Schedule a reboot after response is sent
            xSemaphoreGive(endpointApiMutex);  // Release mutex before reboot
            request->onDisconnect([](){
                delay(100);
                ESP.restart();
            });
            sendJsonResponseEndpoint(request, response);
            return;
        }
        else {
            response["success"] = false;
            response["error"] = "No valid system command specified";
        }
    }
    else {
        response["success"] = false;
        response["error"] = "Unknown command type: " + command;
    }
    
    sendJsonResponseEndpoint(request, response);
    xSemaphoreGive(endpointApiMutex);
}

void setupApiEndpoints(AsyncWebServer *server) {
    // Initialize API mutex
    if (endpointApiMutex == NULL) {
        endpointApiMutex = xSemaphoreCreateMutex();
    }

    // Define the two API endpoints for FlutterFlow's free version
    server->on("/api/status", HTTP_GET, handleStatusRequest);
    server->on("/api/command", HTTP_POST, handleCommand);

    Serial.println("API endpoints for FlutterFlow registered (2 endpoints total)");
}

}