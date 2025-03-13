#include "NovaNow.h"
#include <Arduino.h>
#include "../utilities/PreferencesManager.h"
#include "../configuration.h"
#include <queue>
#include "../LightUtils.h" // Include LightUtils for LED control

static uint32_t currentMessageId = 0;
static bool messageOutput = false;

// Message queue for non-blocking processing
static std::queue<SimonaMessage> messageQueue;
static const size_t MAX_QUEUE_SIZE = 10; // Maximum number of messages to queue

// Track the current Simona stage to maintain LED state
static SimonaStage currentSimonaStage = SIMONA_STAGE_WAITING;

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

// Add LED sequence generation animation to match nova-mini implementation but without relay triggering
static struct {
    const uint8_t offVal = 8; // 3% of 255 for dim white
    CRGB offWhite = CRGB(offVal, offVal, offVal);
} sequenceGenAnimation;

// Track previous stage to detect stage changes
static SimonaStage previousStage = SIMONA_STAGE_WAITING;

// Track animation state for lost mode
static struct {
    int stepIndex = 0;
    const uint8_t startVal = 5; // 5% brightness
    const int steps = 20;
    const int delayMs = 30;
} lostAnimation;

// Process a message based on its stage
static void processMessage(const SimonaMessage &msg) {
    // Print the message if output is enabled
    if (messageOutput) {
        printSimonaMessage(msg);
    }
    
    // Check if stage has changed
    if (msg.stage != currentSimonaStage) {
        // Log stage change
        Serial.print("Simona stage changed from ");
        Serial.print(previousStage);
        Serial.print(" to ");
        Serial.println(msg.stage);
        
        // Handle LED state based on stage transition
        if (lightUtils) {
            // If entering WAITING stage, protect LEDs 1-12 and set them to dim white (5% brightness)
            if (msg.stage == SIMONA_STAGE_WAITING) {
                // Create dim white color (5% of full white)
                CRGB dimWhite = CRGB(13, 13, 13); // 13 is ~5% of 255
                lightUtils->protectLedRange(0, 11, dimWhite); // 0-11 are LEDs 1-12
                Serial.println("LEDs 1-12 protected and set to 5% white for WAITING stage");
            } 
            // If exiting WAITING stage, unprotect all LEDs
            else if (previousStage == SIMONA_STAGE_WAITING) {
                lightUtils->unprotectAllLeds();
                Serial.println("Unprotected all LEDs for non-WAITING stage");
            }
        }

        // Update stage tracking
        previousStage = currentSimonaStage;
        currentSimonaStage = msg.stage;
    }

    // Handle different stages with non-blocking actions
    switch (msg.stage) {
        case SIMONA_STAGE_WAITING:
            // LED update will happen in loop to maintain state
            break;
        case SIMONA_STAGE_SEQUENCE_GENERATION:
            if (lightUtils) {
                // Protect all LEDs and set them to dim white first
                lightUtils->protectLedRange(0, 11, sequenceGenAnimation.offWhite);
                
                // Map button number to color and light up corresponding LED
                CRGB targetColor;
                switch (msg.litButton) {
                    case 0:
                        targetColor = CRGB(255, 0, 0); // Red
                        break;
                    case 1:
                        targetColor = CRGB(0, 255, 0); // Green
                        break;
                    case 2:
                        targetColor = CRGB(0, 0, 255); // Blue
                        break;
                    case 3:
                        targetColor = CRGB(255, 255, 0); // Yellow
                        break;
                    default:
                        targetColor = sequenceGenAnimation.offWhite;
                        break;
                }
                
                if (msg.litButton >= 0 && msg.litButton < 4) {
                    // Update just the one LED's color through the protected range
                    lightUtils->protectLedRange(msg.litButton, msg.litButton, targetColor);
                    delay(500); // Brief flash
                    lightUtils->protectLedRange(msg.litButton, msg.litButton, sequenceGenAnimation.offWhite);
                }
            }
            break;
        case SIMONA_STAGE_TRANSITION:
            // If coming from waiting stage, the default handler will handle LED reset
            break;
        case SIMONA_STAGE_INPUT_COLLECTION:
            if (lightUtils) {
                // Default dim white state for all LEDs (3% brightness)
                CRGB offWhite = CRGB(8, 8, 8); // 3% of 255 ≈ 8
                lightUtils->protectLedRange(0, 11, offWhite);

                // If a button was pressed, light up its corresponding LED
                if (msg.lastPressedButton >= 0 && msg.lastPressedButton < 4) {
                    // Map button number to color
                    CRGB targetColor;
                    switch (msg.lastPressedButton) {
                        case 0:
                            targetColor = CRGB(255, 0, 0); // Red
                            break;
                        case 1:
                            targetColor = CRGB(0, 255, 0); // Green
                            break;
                        case 2:
                            targetColor = CRGB(0, 0, 255); // Blue
                            break;
                        case 3:
                            targetColor = CRGB(255, 255, 0); // Yellow
                            break;
                        default:
                            targetColor = offWhite;
                            break;
                    }
                    
                    if (msg.litButton >= 0 && msg.litButton < 4) {
                        // Update just the one LED's color through the protected range
                        lightUtils->protectLedRange(msg.lastPressedButton, msg.lastPressedButton, targetColor);
                        delay(500); // Brief flash
                        lightUtils->protectLedRange(msg.lastPressedButton, msg.lastPressedButton, sequenceGenAnimation.offWhite);
                    }
    
                }
            }
            break;
        case SIMONA_STAGE_VERIFICATION:
            // If coming from waiting stage, the default handler will handle LED reset
            break;
        case SIMONA_STAGE_GAME_LOST:
            if (lightUtils) {
                // Start with white at 5% brightness
                CRGB startColor = CRGB(lostAnimation.startVal, lostAnimation.startVal, lostAnimation.startVal);
                lightUtils->protectLedRange(0, 11, startColor);
                
                // Reset animation state
                lostAnimation.stepIndex = 0;
            }
            break;
        case SIMONA_STAGE_GAME_WIN:
            // If coming from waiting stage, the default handler will handle LED reset
            break;
        case SIMONA_STAGE_RESET:
            // If coming from waiting stage, the default handler will handle LED reset
            break;
        case SIMONA_STAGE_ROUND_TRANSITION:
            // If coming from waiting stage, the default handler will handle LED reset
            break;
        default:
            break;
    }
}

// Track animation state for waiting mode
static struct {
    int ledIndex = 0;
    int colorIndex = 0;
    int stepIndex = 0;
    int animationPhase = 0;
    const int steps = 10;
    const uint8_t offVal = 8; // 3% of 255
    struct ColorTransition {
        CRGB base;
        CRGB full;
    } colorTransitions[3] = {
        {CRGB(8, 0, 0), CRGB(255, 0, 0)},   // Red
        {CRGB(0, 8, 0), CRGB(0, 255, 0)},   // Green
        {CRGB(0, 0, 8), CRGB(0, 0, 255)}    // Blue
    };
} waitingAnimation;

// Handle waiting stage LED animation
static void updateWaitingAnimation() {
    const CRGB offWhite(waitingAnimation.offVal, waitingAnimation.offVal, waitingAnimation.offVal);

    // State machine for different animation phases
    switch (waitingAnimation.animationPhase) {
        case 0: // Initialize
            if (lightUtils) {
                // Protect and set all LEDs to dim white
                lightUtils->protectLedRange(0, 11, offWhite);
            }
            waitingAnimation.animationPhase = 1;
            waitingAnimation.stepIndex = 0;
            return;

        case 1: { // Transition from offWhite to 5% base color
            float t = waitingAnimation.stepIndex / (float)waitingAnimation.steps;
            if (lightUtils) {
                CRGB newColor;
                newColor.r = offWhite.r + (waitingAnimation.colorTransitions[waitingAnimation.colorIndex].base.r - offWhite.r) * t;
                newColor.g = offWhite.g + (waitingAnimation.colorTransitions[waitingAnimation.colorIndex].base.g - offWhite.g) * t;
                newColor.b = offWhite.b + (waitingAnimation.colorTransitions[waitingAnimation.colorIndex].base.b - offWhite.b) * t;
                lightUtils->protectLedRange(waitingAnimation.ledIndex, waitingAnimation.ledIndex, newColor);
            }

            if (++waitingAnimation.stepIndex > waitingAnimation.steps) {
                waitingAnimation.stepIndex = 0;
                waitingAnimation.animationPhase = 2;
            }
            break;
        }

        case 2: { // Ramp up from 5% base color to 100% full color
            float t = waitingAnimation.stepIndex / (float)waitingAnimation.steps;
            if (lightUtils) {
                CRGB newColor;
                newColor.r = waitingAnimation.colorTransitions[waitingAnimation.colorIndex].base.r + 
                            (waitingAnimation.colorTransitions[waitingAnimation.colorIndex].full.r - waitingAnimation.colorTransitions[waitingAnimation.colorIndex].base.r) * t;
                newColor.g = waitingAnimation.colorTransitions[waitingAnimation.colorIndex].base.g + 
                            (waitingAnimation.colorTransitions[waitingAnimation.colorIndex].full.g - waitingAnimation.colorTransitions[waitingAnimation.colorIndex].base.g) * t;
                newColor.b = waitingAnimation.colorTransitions[waitingAnimation.colorIndex].base.b + 
                            (waitingAnimation.colorTransitions[waitingAnimation.colorIndex].full.b - waitingAnimation.colorTransitions[waitingAnimation.colorIndex].base.b) * t;
                lightUtils->protectLedRange(waitingAnimation.ledIndex, waitingAnimation.ledIndex, newColor);
            }

            if (++waitingAnimation.stepIndex > waitingAnimation.steps) {
                waitingAnimation.stepIndex = 0;
                waitingAnimation.animationPhase = 3;
            }
            break;
        }

        case 3: // Hold at 100% full color
            if (lightUtils) {
                lightUtils->protectLedRange(waitingAnimation.ledIndex, waitingAnimation.ledIndex, 
                    waitingAnimation.colorTransitions[waitingAnimation.colorIndex].full);
            }
            waitingAnimation.animationPhase = 4;
            break;

        case 4: { // Ramp down from 100% full color to 5% base color
            float t = waitingAnimation.stepIndex / (float)waitingAnimation.steps;
            if (lightUtils) {
                CRGB newColor;
                newColor.r = waitingAnimation.colorTransitions[waitingAnimation.colorIndex].full.r - 
                            (waitingAnimation.colorTransitions[waitingAnimation.colorIndex].full.r - waitingAnimation.colorTransitions[waitingAnimation.colorIndex].base.r) * t;
                newColor.g = waitingAnimation.colorTransitions[waitingAnimation.colorIndex].full.g - 
                            (waitingAnimation.colorTransitions[waitingAnimation.colorIndex].full.g - waitingAnimation.colorTransitions[waitingAnimation.colorIndex].base.g) * t;
                newColor.b = waitingAnimation.colorTransitions[waitingAnimation.colorIndex].full.b - 
                            (waitingAnimation.colorTransitions[waitingAnimation.colorIndex].full.b - waitingAnimation.colorTransitions[waitingAnimation.colorIndex].base.b) * t;
                lightUtils->protectLedRange(waitingAnimation.ledIndex, waitingAnimation.ledIndex, newColor);
            }

            if (++waitingAnimation.stepIndex > waitingAnimation.steps) {
                waitingAnimation.stepIndex = 0;
                waitingAnimation.animationPhase = 5;
            }
            break;
        }

        case 5: { // Transition from 5% base color back to offWhite
            float t = waitingAnimation.stepIndex / (float)waitingAnimation.steps;
            if (lightUtils) {
                CRGB newColor;
                newColor.r = waitingAnimation.colorTransitions[waitingAnimation.colorIndex].base.r + (offWhite.r - waitingAnimation.colorTransitions[waitingAnimation.colorIndex].base.r) * t;
                newColor.g = waitingAnimation.colorTransitions[waitingAnimation.colorIndex].base.g + (offWhite.g - waitingAnimation.colorTransitions[waitingAnimation.colorIndex].base.g) * t;
                newColor.b = waitingAnimation.colorTransitions[waitingAnimation.colorIndex].base.b + (offWhite.b - waitingAnimation.colorTransitions[waitingAnimation.colorIndex].base.b) * t;
                lightUtils->protectLedRange(waitingAnimation.ledIndex, waitingAnimation.ledIndex, newColor);
            }

            if (++waitingAnimation.stepIndex > waitingAnimation.steps) {
                waitingAnimation.stepIndex = 0;
                waitingAnimation.animationPhase = 6;
            }
            break;
        }

        case 6: // Advance to next color or LED
            if (++waitingAnimation.colorIndex >= 3) {
                waitingAnimation.colorIndex = 0;
                if (++waitingAnimation.ledIndex >= 12) { // Use 12 LEDs instead of 4
                    waitingAnimation.ledIndex = 0;
                }
            }
            waitingAnimation.animationPhase = 1;
            delay(50); // Small delay between cycles
            break;
    }
}

void novaNowSetup() {
    messageOutput = PreferencesManager::getBool("messageOutput", true);
    Serial.println("NovaNow initialized");
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

    // Update waiting animation if in waiting stage
    if (currentSimonaStage == SIMONA_STAGE_WAITING) {
        updateWaitingAnimation();
    }
    // Update lost animation if in game lost stage
    else if (currentSimonaStage == SIMONA_STAGE_GAME_LOST) {
        if (lightUtils) {
            float t = lostAnimation.stepIndex / (float)lostAnimation.steps;
            uint8_t brightness = lostAnimation.startVal - lostAnimation.startVal * t;
            CRGB fadeColor = CRGB(brightness, brightness, brightness);
            lightUtils->protectLedRange(0, 11, fadeColor);
            delay(lostAnimation.delayMs);
            
            // Move to next step 
            if (++lostAnimation.stepIndex > lostAnimation.steps) {
                lostAnimation.stepIndex = 0; // Reset for next fade out cycle
            }
        }
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