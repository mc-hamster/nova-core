#include "NovaNow.h"
#include <Arduino.h>
#include "../utilities/PreferencesManager.h"
#include "../configuration.h"

static uint32_t currentMessageId = 0;
static bool messageOutput = false;

static void printSimonaMessage(const SimonaMessage &msg) {
    char buffer[256];
    const char* stageName;
    
    switch (msg.stage) {
        case SIMONA_STAGE_WAITING:
            stageName = "SIMONA_STAGE_WAITING";
            break;
        case SIMONA_STAGE_SEQUENCE_GENERATION:
            stageName = "SIMONA_STAGE_SEQUENCE_GENERATION";
            break;
        case SIMONA_STAGE_TRANSITION:
            stageName = "SIMONA_STAGE_TRANSITION";
            break;
        case SIMONA_STAGE_INPUT_COLLECTION:
            stageName = "SIMONA_STAGE_INPUT_COLLECTION";
            break;
        case SIMONA_STAGE_VERIFICATION:
            stageName = "SIMONA_STAGE_VERIFICATION";
            break;
        case SIMONA_STAGE_GAME_LOST:
            stageName = "SIMONA_STAGE_GAME_LOST";
            break;
        case SIMONA_STAGE_GAME_WIN:
            stageName = "SIMONA_STAGE_GAME_WIN";
            break;
        case SIMONA_STAGE_RESET:
            stageName = "SIMONA_STAGE_RESET";
            break;
        case SIMONA_STAGE_ROUND_TRANSITION:
            stageName = "SIMONA_STAGE_ROUND_TRANSITION";
            break;
        default:
            stageName = "UNKNOWN_STAGE";
            break;
    }

    snprintf(buffer, sizeof(buffer),
        "SimonaMessage {\n"
        "  message_id: %d\n"
        "  stage: %s\n"
        "  level: %d\n"
        "  gamePlay: %d\n"
        "  lost: %d\n"
        "  litButton: %d\n"
        "  lastPressedButton: %d\n"
        "  currentRound: %d\n"
        "  maxRounds: %d\n"
        "  levelsInRound: %d\n"
        "}\n",
        msg.message_id,
        stageName,
        msg.level,
        msg.gamePlay,
        msg.lost,
        msg.litButton,
        msg.lastPressedButton,
        msg.currentRound,
        msg.maxRounds,
        msg.levelsInRound);

    Serial.print(buffer);  // Print to debug console
}

void novaNowSetup() {
    messageOutput = PreferencesManager::getBool("messageOutput", true);
    Serial.println("NovaNow initialized");
}

void novaNowLoop() {
    // Process any pending messages in the loop
    // For now this just checks the preferences periodically
    static uint32_t lastPrefsCheck = 0;
    const uint32_t PREFS_CHECK_INTERVAL = 5000; // Check every 5 seconds

    if (millis() - lastPrefsCheck >= PREFS_CHECK_INTERVAL) {
        messageOutput = PreferencesManager::getBool("messageOutput", true);
        lastPrefsCheck = millis();
    }
}

void sendSimonaMessage(const SimonaMessage &simMsg) {
    if (!messageOutput) {
        return;
    }

    currentMessageId++;
    SimonaMessage msgToSend = simMsg;
    msgToSend.message_id = currentMessageId;
    
    printSimonaMessage(msgToSend);
}