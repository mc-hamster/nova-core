#include "NovaNow.h"
#include <Arduino.h>
#include "../utilities/PreferencesManager.h"
#include "../configuration.h"
#include "../output/Star.h"
#include <queue>
#include "../LightUtils.h"

static uint32_t currentMessageId = 0;
static bool messageOutput = false;
static std::queue<SimonaMessage> messageQueue;
static const size_t MAX_QUEUE_SIZE = 10;
static SimonaStage currentSimonaStage = SIMONA_STAGE_WAITING;
static SimonaStage previousStages[2] = {SIMONA_STAGE_WAITING, SIMONA_STAGE_WAITING};
static int currentSequence = 0;
static int currentRoundForMapping = -1;
static bool mappingInitialized = false;
static AnimationState animState;

static void printSimonaMessage(const SimonaMessage &msg)
{
    char buffer[256];
    const char *stageName;

    switch (msg.stage)
    {
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

    Serial.print(buffer); // Print to debug console
}

// Store persistent button-to-LED mapping
static int buttonToLedMapping[12] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1}; // Expanded to 12

// Helper function to map button index to LED position based on round
static int mapButtonToLedPosition(int buttonIndex, int currentRound, bool resetMapping = false)
{
    // Sanity check - button index should be valid
    if (buttonIndex < 1 || buttonIndex > 12)
    {
        Serial.print("ERROR: Invalid button index ");
        Serial.println(buttonIndex);
        return 4; // Default to first LED as fallback
    }

    // Convert from 1-based button index to 0-based array index
    int buttonArrayIndex = buttonIndex - 1;

    // Progressive LED count based on round
    int ledCount = 4; // Default to 4 LEDs
    if (currentRound >= 3 && currentRound <= 4)
    {
        ledCount = 6;
    }
    else if (currentRound >= 5 && currentRound <= 6)
    {
        ledCount = 8;
    }
    else if (currentRound >= 7)
    {
        ledCount = 12;
    }

    // Calculate the center-aligned start position
    int startPos = (12 - ledCount) / 2;

    // Force a reset if round changed or explicitly requested
    if (currentRoundForMapping != currentRound || resetMapping)
    {
        // Initialize random seed each time a new round starts
        // Use multiple sources of entropy
        randomSeed(esp_random());

        // Clear all mappings
        for (int i = 0; i < 12; i++)
        {
            buttonToLedMapping[i] = -1;
        }
        currentRoundForMapping = currentRound;
        mappingInitialized = true;

        Serial.print("New round ");
        Serial.print(currentRound);
        Serial.print(", using ");
        Serial.print(ledCount);
        Serial.print(" LEDs starting at ");
        Serial.println(startPos);
    }

    // Check if we already have a mapping for this button
    if (buttonToLedMapping[buttonArrayIndex] >= 0)
    {
        // Safety check - make sure no other button is using this position
        int position = buttonToLedMapping[buttonArrayIndex];
        bool collision = false;
        for (int i = 0; i < 12; i++)
        {
            if (i != buttonArrayIndex && buttonToLedMapping[i] == position)
            {
                Serial.print("ERROR: Position collision detected! Button ");
                Serial.print(buttonArrayIndex);
                Serial.print(" and Button ");
                Serial.print(i);
                Serial.print(" both mapped to LED position ");
                Serial.println(position);
                collision = true;
                break;
            }
        }

        if (!collision)
        {
            if (0)
            {
                Serial.print("Button ");
                Serial.print(buttonArrayIndex);
                Serial.print(" using existing mapping to LED position ");
                Serial.println(position);
            }
            return position;
        }

        // If there was a collision, we'll need to reassign a position
        Serial.println("Fixing collision by creating new mapping");
        buttonToLedMapping[buttonArrayIndex] = -1;
    }

    // Create an array of available positions within our range
    int availablePositions[12];
    int availableCount = 0;

    // Build a list of positions that aren't already used
    for (int i = startPos; i < startPos + ledCount; i++)
    {
        bool alreadyUsed = false;
        for (int j = 0; j < 12; j++)
        {
            // Check if this position is already assigned to another button
            if (j != buttonArrayIndex && buttonToLedMapping[j] == i)
            {
                alreadyUsed = true;
                break;
            }
        }

        if (!alreadyUsed)
        {
            // This position is available, add it to our list
            availablePositions[availableCount++] = i;
        }
    }

    // Debug: print available positions
    Serial.print("Available positions for button ");
    Serial.print(buttonArrayIndex);
    Serial.print(": ");
    for (int i = 0; i < availableCount; i++)
    {
        Serial.print(availablePositions[i]);
        Serial.print(" ");
    }
    Serial.println();

    int position = -1;

    // If we have available positions, choose one randomly
    if (availableCount > 0)
    {
        // Select a random position from the available ones
        int randomIndex = random(availableCount);
        position = availablePositions[randomIndex];

        Serial.print("Randomly selected position ");
        Serial.print(position);
        Serial.print(" (index ");
        Serial.print(randomIndex);
        Serial.print(" of ");
        Serial.print(availableCount);
        Serial.println(" available)");
    }
    else
    {
        // No available positions - this shouldn't happen with proper management
        Serial.println("WARNING: No available positions found!");

        // Print all current mappings for debugging
        Serial.println("Current mappings:");
        for (int i = 0; i < 12; i++)
        {
            if (buttonToLedMapping[i] >= 0)
            {
                Serial.print("Button ");
                Serial.print(i);
                Serial.print(" -> LED ");
                Serial.println(buttonToLedMapping[i]);
            }
        }

        // Emergency fallback: reset all mappings and try again
        Serial.println("EMERGENCY: Clearing all mappings due to no available positions");
        for (int i = 0; i < 12; i++)
        {
            buttonToLedMapping[i] = -1;
        }

        // Choose a random position within the valid range
        position = startPos + random(ledCount);
        Serial.print("Emergency position assigned: ");
        Serial.println(position);
    }

    // Double check one more time for collisions
    bool finalCollision = false;
    for (int i = 0; i < 12; i++)
    {
        if (i != buttonArrayIndex && buttonToLedMapping[i] == position)
        {
            Serial.print("CRITICAL: Collision detected with button ");
            Serial.print(i);
            Serial.print(" at position ");
            Serial.println(position);
            finalCollision = true;
            break;
        }
    }

    if (finalCollision)
    {
        // As a last resort measure - clear ALL mappings and assign ours first
        Serial.println("CRITICAL ERROR: Clearing all mappings due to unresolvable collision");
        for (int i = 0; i < 12; i++)
        {
            buttonToLedMapping[i] = -1;
        }
    }

    // Assign the position to this button and return it
    buttonToLedMapping[buttonArrayIndex] = position;

    Serial.print("Button ");
    Serial.print(buttonArrayIndex);
    Serial.print(" now assigned to LED position ");
    Serial.println(position);

    return position;
}

// New function to poof all mapped LEDs
void poofAllMappedLeds(int currentRound)
{
    Serial.println("Poofing all mapped LEDs for current round");

    if (star && ledMapper)
    {
        auto mappedLeds = ledMapper->getMappedLeds();
        for (int ledPos : mappedLeds)
        {
            star->poof(ledPos);
        }
    }
    else
    {
        Serial.println("ERROR: Star object is null, cannot poof LEDs");
    }
}

// New function to boom a specified number of mapped LEDs
void boomMappedLeds(int currentRound, int numLedsToBoom)
{
    Serial.print("Booming ");
    Serial.print(numLedsToBoom);
    Serial.println(" mapped LEDs for current round");

    if (star && ledMapper)
    {
        auto mappedLeds = ledMapper->getMappedLeds();
        std::random_shuffle(mappedLeds.begin(), mappedLeds.end());

        int numToTrigger = std::min(numLedsToBoom, (int)mappedLeds.size());
        for (int i = 0; i < numToTrigger; i++)
        {
            star->boom(mappedLeds[i]);
        }
    }
    else
    {
        Serial.println("ERROR: Star object is null, cannot boom LEDs");
    }
}

// Helper function to interpolate between two CRGB colors
static CRGB interpolateColor(const CRGB &start, const CRGB &end, float t)
{
    return CRGB(
        start.r + (end.r - start.r) * t,
        start.g + (end.g - start.g) * t,
        start.b + (end.b - start.b) * t);
}

// Helper function to apply color to LED range with null check
static void safeProtectLedRange(int startLed, int endLed, const CRGB &color)
{
    if (lightUtils)
    {
        lightUtils->protectLedRange(startLed, endLed, color);
    }
}

// Handle waiting stage LED animation
static void updateWaitingAnimation()
{
    const CRGB offWhite(animState.waiting.offVal, animState.waiting.offVal, animState.waiting.offVal);

    // State machine for different animation phases
    switch (animState.waiting.animationPhase)
    {
    case 0: // Initialize
        safeProtectLedRange(0, 11, offWhite);
        animState.waiting.animationPhase = 1;
        animState.waiting.stepIndex = 0;
        return;

    case 1:
    { // Transition from offWhite to 5% base color
        float t = animState.waiting.stepIndex / (float)animState.waiting.steps;
        CRGB newColor = interpolateColor(
            offWhite,
            animState.waiting.colorTransitions[animState.waiting.colorIndex].base,
            t);
        safeProtectLedRange(animState.waiting.ledIndex, animState.waiting.ledIndex, newColor);

        if (++animState.waiting.stepIndex > animState.waiting.steps)
        {
            animState.waiting.stepIndex = 0;
            animState.waiting.animationPhase = 2;
        }
        break;
    }

    case 2:
    { // Ramp up from 5% base color to 100% full color
        float t = animState.waiting.stepIndex / (float)animState.waiting.steps;
        CRGB newColor = interpolateColor(
            animState.waiting.colorTransitions[animState.waiting.colorIndex].base,
            animState.waiting.colorTransitions[animState.waiting.colorIndex].full,
            t);
        safeProtectLedRange(animState.waiting.ledIndex, animState.waiting.ledIndex, newColor);

        if (++animState.waiting.stepIndex > animState.waiting.steps)
        {
            animState.waiting.stepIndex = 0;
            animState.waiting.animationPhase = 3;
        }
        break;
    }

    case 3: // Hold at 100% full color
        safeProtectLedRange(animState.waiting.ledIndex, animState.waiting.ledIndex,
                            animState.waiting.colorTransitions[animState.waiting.colorIndex].full);
        animState.waiting.animationPhase = 4;
        break;

    case 4:
    { // Ramp down from 100% full color to 5% base color
        float t = animState.waiting.stepIndex / (float)animState.waiting.steps;
        CRGB newColor = interpolateColor(
            animState.waiting.colorTransitions[animState.waiting.colorIndex].full,
            animState.waiting.colorTransitions[animState.waiting.colorIndex].base,
            t);
        safeProtectLedRange(animState.waiting.ledIndex, animState.waiting.ledIndex, newColor);

        if (++animState.waiting.stepIndex > animState.waiting.steps)
        {
            animState.waiting.stepIndex = 0;
            animState.waiting.animationPhase = 5;
        }
        break;
    }

    case 5:
    { // Transition from 5% base color back to offWhite
        float t = animState.waiting.stepIndex / (float)animState.waiting.steps;
        CRGB newColor = interpolateColor(
            animState.waiting.colorTransitions[animState.waiting.colorIndex].base,
            offWhite,
            t);
        safeProtectLedRange(animState.waiting.ledIndex, animState.waiting.ledIndex, newColor);

        if (++animState.waiting.stepIndex > animState.waiting.steps)
        {
            animState.waiting.stepIndex = 0;
            animState.waiting.animationPhase = 6;
        }
        break;
    }

    case 6: // Advance to next color or LED
        if (++animState.waiting.colorIndex >= 3)
        {
            animState.waiting.colorIndex = 0;
            if (++animState.waiting.ledIndex >= 12)
            { // Use 12 LEDs instead of 4
                animState.waiting.ledIndex = 0;
            }
        }
        animState.waiting.animationPhase = 1;
        delay(50); // Small delay between cycles
        break;
    }
}

void novaNowSetup()
{
    messageOutput = PreferencesManager::getBool("messageOutput", true);
    ledMapper = new LedMapper();
    Serial.println("NovaNow initialized");
}

SimonaMessage msg;
void novaNowLoop()
{
    // Process any pending messages in the loop
    static uint32_t lastPrefsCheck = 0;
    const uint32_t PREFS_CHECK_INTERVAL = 5000; // Check every 5 seconds

    if (millis() - lastPrefsCheck >= PREFS_CHECK_INTERVAL)
    {
        messageOutput = PreferencesManager::getBool("messageOutput", true);
        lastPrefsCheck = millis();
    }

    // Process one message per cycle to avoid blocking
    if (!messageQueue.empty())
    {
        msg = messageQueue.front();
        messageQueue.pop();

        // Update current stage and button state when processing messages
        currentSimonaStage = msg.stage;
        if (msg.stage == SIMONA_STAGE_SEQUENCE_GENERATION)
        {
            animState.sequenceGen.currentLitButton = msg.litButton;
        }
        else if (msg.stage == SIMONA_STAGE_INPUT_COLLECTION)
        {
            animState.inputCollection.lastPressedButton = msg.lastPressedButton;
        }
    }

    // Update waiting animation if in waiting stage
    if (currentSimonaStage == SIMONA_STAGE_WAITING)
    {
        updateWaitingAnimation();
    }
    // Update sequence generation animation if in sequence generation stage
    else if (currentSimonaStage == SIMONA_STAGE_SEQUENCE_GENERATION)
    {
        // Check for stage change to reset button mappings
        if (previousStages[1] != SIMONA_STAGE_SEQUENCE_GENERATION)
        {
            ledMapper->reset(msg.currentRound);
        }

        static int lastMessageId = -1;
        if (msg.message_id != lastMessageId)
        {
            lastMessageId = msg.message_id;
            // Execute your code here for new message_id changes
            currentSequence++;
        }

        // printSimonaMessage(msg);
        if (lightUtils)
        {
            // Map button to color
            CRGB targetColor;

            switch (animState.sequenceGen.currentLitButton)
            {
            case 0:
                targetColor = CRGB(255, 0, 0); // red
                break;
            case 1:
                targetColor = CRGB(0, 255, 0); // green
                break;
            case 2:
                targetColor = CRGB(0, 0, 255); // blue
                break;
            case 3:
                targetColor = CRGB(255, 255, 0); // yellow
                break;
            default:
                targetColor = CRGB(255, 0, 0); // default red
                break;
            }

            // Map button to LED position based on current round
            int ledIndex = ledMapper->mapButtonToLed(currentSequence, msg.currentRound);
            // Serial.print(">>> currentSequence: ");
            // Serial.print(currentSequence);
            // Serial.println(" <<<");

            // Set all LEDs to dim white
            lightUtils->protectLedRange(0, 11, animState.sequenceGen.offWhite);
            // Light up the target LED
            if (ledIndex >= 0 && ledIndex < 12)
            {
                lightUtils->protectLedRange(ledIndex, ledIndex, targetColor);
            }
        }

        previousStages[1] = SIMONA_STAGE_SEQUENCE_GENERATION;
    }
    // Update input collection animation if in input collection stage
    else if (currentSimonaStage == SIMONA_STAGE_INPUT_COLLECTION)
    {
        // printSimonaMessage(msg);
        currentSequence = 0;
        if (lightUtils)
        {
            // Map button to color
            CRGB targetColor;

            switch (animState.inputCollection.lastPressedButton)
            {
            case 0:
                targetColor = CRGB(255, 0, 0); // red
                break;
            case 1:
                targetColor = CRGB(0, 255, 0); // green
                break;
            case 2:
                targetColor = CRGB(0, 0, 255); // blue
                break;
            case 3:
                targetColor = CRGB(255, 255, 0); // yellow
                break;
            default:
                targetColor = CRGB(255, 0, 0); // default red
                break;
            }

            // Map button to LED position based on current round
            // Mapping gamePlay to LED position based on current round
            int ledIndex = mapButtonToLedPosition(msg.gamePlay, msg.currentRound);
            // Serial.print("==== LED index mapping from gamePlay: ");
            // Serial.print(msg.gamePlay);
            // Serial.println(" ====");

            // Poof that star
            star->poof(ledIndex);

            // Set all LEDs to dim white
            lightUtils->protectLedRange(0, 11, animState.inputCollection.offWhite);
            // Light up the target LED with its color
            if (ledIndex >= 0 && ledIndex < 12)
            {
                lightUtils->protectLedRange(ledIndex, ledIndex, targetColor);
            }
        }
    }
    // Update lost animation if in game lost stage
    else if (currentSimonaStage == SIMONA_STAGE_GAME_LOST)
    {
        if (lightUtils)
        {
            float t = animState.lost.stepIndex / (float)animState.lost.steps;
            uint8_t brightness = animState.lost.startVal - animState.lost.startVal * t;
            CRGB fadeColor = CRGB(brightness, brightness, brightness);
            lightUtils->protectLedRange(0, 11, fadeColor);
            delay(animState.lost.delayMs);

            // Move to next step
            if (++animState.lost.stepIndex > animState.lost.steps)
            {
                animState.lost.stepIndex = 0; // Reset for next fade out cycle
            }
        }
    }
    // Handle verification stage
    else if (currentSimonaStage == SIMONA_STAGE_VERIFICATION)
    {
        if (lightUtils)
        {
            float t = animState.verification.stepIndex / (float)animState.verification.steps;
            uint8_t brightness;

            if (!animState.verification.fadeOut)
            {
                // Fade up: 2% -> 6% (~5 to 15 in 8-bit values)
                brightness = 5 + (uint8_t)(10.0f * t);
            }
            else
            {
                // Fade down: 6% -> 2%
                brightness = 15 - (uint8_t)(10.0f * t);
            }

            CRGB color(brightness, brightness, brightness);
            lightUtils->protectLedRange(0, 11, color);
            delay(30); // Match nova-mini 30ms delay

            if (++animState.verification.stepIndex > animState.verification.steps)
            {
                animState.verification.stepIndex = 0;
                animState.verification.fadeOut = !animState.verification.fadeOut; // Toggle fade direction
            }
        }
    }
    else if (currentSimonaStage == SIMONA_STAGE_TRANSITION)
    {
        if (lightUtils)
        {
            float t = animState.transition.stepIndex / (float)animState.transition.steps;
            uint8_t brightness;

            if (!animState.transition.fadeOut)
            {
                // Fade up: 2% -> 6% (~5 to 15 in 8-bit values)
                brightness = 5 + (uint8_t)(10.0f * t);
            }
            else
            {
                // Fade down: 6% -> 2%
                brightness = 15 - (uint8_t)(10.0f * t);
            }

            CRGB color(brightness, brightness, brightness);
            lightUtils->protectLedRange(0, 11, color);
            delay(30); // Match nova-mini 30ms delay

            if (++animState.transition.stepIndex > animState.transition.steps)
            {
                animState.transition.stepIndex = 0;
                animState.transition.fadeOut = !animState.transition.fadeOut; // Toggle fade direction
            }
        }
    }
    // Handle game win state
    else if (currentSimonaStage == SIMONA_STAGE_GAME_WIN)
    {
        if (lightUtils)
        {
            // Check for stage change to reset button mappings
            if (previousStages[1] != SIMONA_STAGE_GAME_WIN)
            {
                for (int i = 0; i < 12; i++)
                {
                    star->boom(i);
                }
            }

            // Wave inward poof animation 4 times: pair (0,11), (1,10), (2,9), …, (5,6) with 50ms non-blocking pause between pairs.
            static unsigned long lastPoofTime = 0;
            static int poofPairIndex = 0;
            static int poofRepetition = 0;

            if (poofRepetition < 4)
            {
                if (millis() - lastPoofTime >= 50)
                {
                    int led1 = poofPairIndex;
                    int led2 = 11 - poofPairIndex;

                    star->poof(led1);
                    star->poof(led2);

                    lastPoofTime = millis();
                    poofPairIndex++;

                    if (poofPairIndex > 5)
                    {
                        poofPairIndex = 0;
                        poofRepetition++;
                    }
                }
            }
            else
            {
                // Reset for the next time the stage is entered
                poofRepetition = 0;
                poofPairIndex = 0;
            }

            // Calculate sine-based brightness for smooth pulsing
            float fraction = animState.win.stepIndex / (float)animState.win.stepsPerPulse;
            float brightnessFactor = sinf(fraction * 3.14159f);

            // Apply brightness to win color
            CRGB color = CRGB(
                (uint8_t)(animState.win.winColor.r * brightnessFactor),
                (uint8_t)(animState.win.winColor.g * brightnessFactor),
                (uint8_t)(animState.win.winColor.b * brightnessFactor));

            // Apply to all LEDs
            lightUtils->protectLedRange(0, 11, color);
            delay(animState.win.delayMs);

            // Move to next step
            if (++animState.win.stepIndex >= animState.win.stepsPerPulse)
            {
                animState.win.stepIndex = 0;
                if (++animState.win.pulseIndex >= animState.win.pulses)
                {
                    animState.win.pulseIndex = 0;
                }
            }
        }
    }
    // Handle round transition stage
    else if (currentSimonaStage == SIMONA_STAGE_ROUND_TRANSITION)
    {
        // Check if we truly just entered this stage (not just continuing in it)
        if (previousStages[1] != SIMONA_STAGE_ROUND_TRANSITION)
        {
            boomMappedLeds(msg.currentRound, msg.currentRound / 2); // Boom 3 LEDs for round transition
        }

        poofAllMappedLeds(msg.currentRound);

        if (lightUtils)
        {
            switch (animState.roundTransition.animationStep)
            {
            case 0: // Skip relay trigger, move straight to fade in
                animState.roundTransition.currentLED = 0;
                animState.roundTransition.animationStep = 1;
                break;

            case 1:
            {                                                               // Fade in LEDs
                float factor = animState.roundTransition.currentLED / 15.0f; // 15 steps for fade
                for (int i = 0; i < 12; i++)
                {
                    CRGB color = animState.roundTransition.celebrationColors[i % 4];
                    lightUtils->protectLedRange(i, i, CRGB(color.r * factor, color.g * factor, color.b * factor));
                }
                delay(50);

                if (++animState.roundTransition.currentLED > 15)
                {
                    animState.roundTransition.currentLED = 0;
                    animState.roundTransition.animationStep = 2;
                }
                break;
            }

            case 2: // Hold full brightness briefly
                animState.roundTransition.animationStep = 3;
                delay(50);
                break;

            case 3:
            { // Fade out LEDs
                float factor = 1.0f - (animState.roundTransition.currentLED / 15.0f);
                for (int i = 0; i < 12; i++)
                {
                    CRGB color = animState.roundTransition.celebrationColors[i % 4];
                    lightUtils->protectLedRange(i, i, CRGB(color.r * factor, color.g * factor, color.b * factor));
                }
                delay(50);

                if (++animState.roundTransition.currentLED > 15)
                {
                    animState.roundTransition.currentLED = 0;
                    animState.roundTransition.currentPulse++;
                    if (animState.roundTransition.currentPulse >= animState.roundTransition.pulseCount)
                    {
                        animState.roundTransition.animationStep = 4;
                    }
                    else
                    {
                        animState.roundTransition.animationStep = 0; // Loop back for next pulse
                    }
                }
                break;
            }

            case 4:
            { // Set to dim white and finish
                CRGB dimWhite(animState.roundTransition.dimVal, animState.roundTransition.dimVal, animState.roundTransition.dimVal);
                lightUtils->protectLedRange(0, 11, dimWhite);

                // Reset state for next time
                animState.roundTransition.animationStep = 0;
                animState.roundTransition.currentPulse = 0;
                animState.roundTransition.currentLED = 0;
                break;
            }
            }
        }
    }
    // Handle reset stage
    else if (currentSimonaStage == SIMONA_STAGE_RESET)
    {
        if (lightUtils)
        {
            currentSequence = 0;
            switch (animState.reset.animationPhase)
            {
            case 0: // Initialize
                lightUtils->protectLedRange(0, 11, animState.reset.offWhite);
                animState.reset.currentStep = 0;
                animState.reset.currentColor = 0;
                animState.reset.animationPhase = 1;
                break;

            case 1:
            { // Transition from offWhite to 5% base color
                float t = animState.reset.currentStep / (float)animState.reset.steps;
                CRGB newColor = interpolateColor(
                    animState.reset.offWhite,
                    animState.reset.colorTransitions[animState.reset.currentColor].base,
                    t);
                safeProtectLedRange(0, 11, newColor);
                delay(animState.reset.delayMs);

                if (++animState.reset.currentStep > animState.reset.steps)
                {
                    animState.reset.currentStep = 0;
                    animState.reset.animationPhase = 2;
                }
                break;
            }

            case 2:
            { // Ramp up from 5% base color to 100% full color
                float t = animState.reset.currentStep / (float)animState.reset.steps;
                CRGB newColor = interpolateColor(
                    animState.reset.colorTransitions[animState.reset.currentColor].base,
                    animState.reset.colorTransitions[animState.reset.currentColor].full,
                    t);
                safeProtectLedRange(0, 11, newColor);
                delay(animState.reset.delayMs);

                if (++animState.reset.currentStep > animState.reset.steps)
                {
                    animState.reset.currentStep = 0;
                    animState.reset.animationPhase = 3;
                }
                break;
            }

            case 3: // Hold at 100% full color
                safeProtectLedRange(0, 11, animState.reset.colorTransitions[animState.reset.currentColor].full);
                delay(animState.reset.holdDelayMs);
                animState.reset.animationPhase = 4;
                break;

            case 4:
            { // Ramp down from 100% full color to 5% base color
                float t = animState.reset.currentStep / (float)animState.reset.steps;
                CRGB newColor = interpolateColor(
                    animState.reset.colorTransitions[animState.reset.currentColor].full,
                    animState.reset.colorTransitions[animState.reset.currentColor].base,
                    t);
                safeProtectLedRange(0, 11, newColor);
                delay(animState.reset.delayMs);

                if (++animState.reset.currentStep > animState.reset.steps)
                {
                    animState.reset.currentStep = 0;
                    animState.reset.animationPhase = 5;
                }
                break;
            }

            case 5:
            { // Transition from 5% base color back to offWhite
                float t = animState.reset.currentStep / (float)animState.reset.steps;
                CRGB newColor = interpolateColor(
                    animState.reset.colorTransitions[animState.reset.currentColor].base,
                    animState.reset.offWhite,
                    t);
                safeProtectLedRange(0, 11, newColor);
                delay(animState.reset.delayMs);

                if (++animState.reset.currentStep > animState.reset.steps)
                {
                    animState.reset.currentStep = 0;
                    // Move to next color or finish
                    if (++animState.reset.currentColor >= 3)
                    {
                        animState.reset.currentColor = 0;
                        animState.reset.animationPhase = 0; // Back to start for next time
                    }
                    else
                    {
                        animState.reset.animationPhase = 1; // Move to next color
                    }
                }
                break;
            }
            }
        }
    }

    // At the end of novaNowLoop, update stage history
    // Add this just before the closing brace of novaNowLoop()
    previousStages[0] = previousStages[1];
    previousStages[1] = currentSimonaStage;
}

void sendSimonaMessage(const SimonaMessage &simMsg)
{
    currentMessageId++;
    SimonaMessage msgToSend = simMsg;
    msgToSend.message_id = currentMessageId;

    // Add message to queue for processing in novaNowLoop
    if (messageQueue.size() < MAX_QUEUE_SIZE)
    {
        messageQueue.push(msgToSend);
    }
    else
    {
        Serial.println("NovaNow message queue full, dropping message");
    }
}