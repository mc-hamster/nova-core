#include "NovaNow.h"
#include <Arduino.h>
#include "../utilities/PreferencesManager.h"
#include "../configuration.h"
#include <queue>

static uint32_t currentMessageId = 0;
static bool messageOutput = false;

// Message queue for non-blocking processing
static std::queue<SimonaMessage> messageQueue;
static const size_t MAX_QUEUE_SIZE = 10; // Maximum number of messages to queue

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

// Process a message based on its stage
static void processMessage(const SimonaMessage &msg) {
    // Print the message if output is enabled
    if (messageOutput) {
        printSimonaMessage(msg);
    }

    // Handle different stages with non-blocking actions
    switch (msg.stage) {
        case SIMONA_STAGE_WAITING:
            // Actions for waiting stage
            break;
        case SIMONA_STAGE_SEQUENCE_GENERATION:
            // Actions for sequence generation stage
            break;
        case SIMONA_STAGE_TRANSITION:
            // Actions for transition stage
            break;
        case SIMONA_STAGE_INPUT_COLLECTION:
            // Actions for input collection stage
            break;
        case SIMONA_STAGE_VERIFICATION:
            // Actions for verification stage
            break;
        case SIMONA_STAGE_GAME_LOST:
            // Actions for game lost stage
            break;
        case SIMONA_STAGE_GAME_WIN:
            // Actions for game win stage
            break;
        case SIMONA_STAGE_RESET:
            // Actions for reset stage
            break;
        case SIMONA_STAGE_ROUND_TRANSITION:
            // Actions for round transition stage
            break;
        default:
            // Unknown stage
            break;
    }
}

void novaNowLoop() {
    // Process any pending messages in the loop
    static uint32_t lastPrefsCheck = 0;
    const uint32_t PREFS_CHECK_INTERVAL = 5000; // Check every 5 seconds

    if (millis() - lastPrefsCheck >= PREFS_CHECK_INTERVAL) {
        messageOutput = PreferencesManager::getBool("messageOutput", true);
        lastPrefsCheck = millis();
    }

    // Process one message per loop cycle to avoid blocking for too long
    if (!messageQueue.empty()) {
        SimonaMessage msg = messageQueue.front();
        messageQueue.pop();
        processMessage(msg);
    }
}

void sendSimonaMessage(const SimonaMessage &simMsg) {
    currentMessageId++;
    SimonaMessage msgToSend = simMsg;
    msgToSend.message_id = currentMessageId;

    // Add message to queue for processing in novaNowLoop
    if (messageQueue.size() < MAX_QUEUE_SIZE) {
        messageQueue.push(msgToSend);
    } else {
        Serial.println("NovaNow message queue full, dropping message");
    }
}