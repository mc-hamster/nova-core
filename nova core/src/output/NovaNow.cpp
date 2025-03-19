#include "NovaNow.h"
#include <Arduino.h>
#include "../utilities/PreferencesManager.h"
#include "../configuration.h"
#include "../output/Star.h" // Add Star.h include
#include <queue>
#include "../LightUtils.h" // Include LightUtils for LED control

static uint32_t currentMessageId = 0;
static bool messageOutput = false;

// Message queue for non-blocking processing
static std::queue<SimonaMessage> messageQueue;
static const size_t MAX_QUEUE_SIZE = 10; // Maximum number of messages to queue

// Track the current Simona stage to maintain LED state
static SimonaStage currentSimonaStage = SIMONA_STAGE_WAITING;

// Add near the top with other static variables
static SimonaStage previousStages[2] = {SIMONA_STAGE_WAITING, SIMONA_STAGE_WAITING}; // Track last 2 stages

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

// Track animation state for sequence generation
static struct
{
    int currentLitButton = 0;
    const uint8_t offVal = 8; // 3% of 255 for dim white
    CRGB offWhite = CRGB(offVal, offVal, offVal);
} sequenceGenAnimation;

// Track animation state for input collection
static struct
{
    int lastPressedButton = 0;
    const uint8_t offVal = 8; // 3% of 255 for dim white
    CRGB offWhite = CRGB(offVal, offVal, offVal);
} inputCollectionAnimation;

// Track previous stage to detect stage changes
static SimonaStage previousStage = SIMONA_STAGE_WAITING;

// Track animation state for lost mode
static struct
{
    int stepIndex = 0;
    const uint8_t startVal = 5; // 5% brightness
    const int steps = 20;
    const int delayMs = 30;
} lostAnimation;

// Add transition animation state
static struct
{
    int stepIndex = 0;
    const int steps = 20;
    const uint8_t lowVal = 5;   // ~2% brightness
    const uint8_t highVal = 15; // ~6% brightness
    bool fadeOut = false;
    const int delayMs = 30;
} transitionAnimation;

// Track animation state for waiting mode
static struct
{
    int ledIndex = 0;
    int colorIndex = 0;
    int stepIndex = 0;
    int animationPhase = 0;
    const int steps = 10;
    const uint8_t offVal = 8; // 3% of 255
    struct ColorTransition
    {
        CRGB base;
        CRGB full;
    } colorTransitions[3] = {
        {CRGB(8, 0, 0), CRGB(255, 0, 0)}, // Red
        {CRGB(0, 8, 0), CRGB(0, 255, 0)}, // Green
        {CRGB(0, 0, 8), CRGB(0, 0, 255)}  // Blue
    };
} waitingAnimation;

// Add win animation state struct
static struct
{
    int stepIndex = 0;
    int pulseIndex = 0;
    const int pulses = 4;
    const int stepsPerPulse = 10;
    const int delayMs = 50;
    const CRGB winColor = CRGB(255, 100, 255); // Purple color for win animation
} winAnimation;

// Add round transition animation state
static struct
{
    int currentLED = 0;
    int animationStep = 0;
    int currentPulse = 0;
    const int pulseCount = 3;
    const uint8_t dimVal = 8; // 3% brightness
    // Celebration colors - complementary colors for interesting effect
    const CRGB celebrationColors[4] = {
        CRGB(255, 50, 50), // Red-orange
        CRGB(50, 255, 50), // Green
        CRGB(50, 50, 255), // Blue
        CRGB(255, 255, 50) // Yellow
    };
} roundTransitionAnimation;

// Add reset animation state

int currentSequence = 0;

static struct
{
    int currentStep = 0;
    int currentColor = 0;
    int animationPhase = 0;
    const int steps = 10;
    const uint8_t offVal = 8; // 3% brightness
    const int delayMs = 50 / steps;
    const int holdDelayMs = 150;
    CRGB offWhite = CRGB(offVal, offVal, offVal);
    struct ColorTransition
    {
        CRGB base;
        CRGB full;
    } colorTransitions[3] = {
        {CRGB(offVal, 0, 0), CRGB(255, 0, 0)}, // Red
        {CRGB(0, offVal, 0), CRGB(0, 255, 0)}, // Green
        {CRGB(0, 0, offVal), CRGB(0, 0, 255)}  // Blue
    };
} resetAnimation;

// Add verification animation state
static struct
{
    int stepIndex = 0;
    const int steps = 20;
    const uint8_t lowVal = 5;   // ~2% brightness
    const uint8_t highVal = 15; // ~6% brightness
    bool fadeOut = false;
    const int delayMs = 30;
} verificationAnimation;

// Store persistent button-to-LED mapping
static int buttonToLedMapping[12] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1}; // Expanded to 12
static int currentRoundForMapping = -1;
static bool mappingInitialized = false;

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
    //Serial.println("Poofing all mapped LEDs for current round");

    if (star)
    {
        // Calculate number of LEDs used in current round
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

        // First, check the button-to-LED mapping array
        for (int i = 0; i < 12; i++)
        {
            if (buttonToLedMapping[i] >= 0)
            {
                //Serial.print("Poofing mapped LED at position ");
                //Serial.println(buttonToLedMapping[i]);

                star->poof(buttonToLedMapping[i]); // Call poof on this mapped LED
                // delay(50);                         // Small delay between poofs for visual effect
            }
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

    if (star)
    {
        // Calculate number of LEDs used in current round
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

        // Collect all mapped LEDs
        std::vector<int> mappedLeds;
        for (int i = 0; i < 12; i++)
        {
            if (buttonToLedMapping[i] >= 0)
            {
                mappedLeds.push_back(buttonToLedMapping[i]);
            }
        }

        // Shuffle the mapped LEDs to randomize selection
        std::random_shuffle(mappedLeds.begin(), mappedLeds.end());

        // Boom the specified number of LEDs
        for (int i = 0; i < numLedsToBoom && i < mappedLeds.size(); i++)
        {
            Serial.print("Booming mapped LED at position ");
            Serial.println(mappedLeds[i]);

            star->boom(mappedLeds[i]); // Call boom on this mapped LED
        }
    }
    else
    {
        Serial.println("ERROR: Star object is null, cannot boom LEDs");
    }
}

// Handle waiting stage LED animation
static void updateWaitingAnimation()
{
    const CRGB offWhite(waitingAnimation.offVal, waitingAnimation.offVal, waitingAnimation.offVal);

    // State machine for different animation phases
    switch (waitingAnimation.animationPhase)
    {
    case 0: // Initialize
        if (lightUtils)
        {
            // Protect and set all LEDs to dim white
            lightUtils->protectLedRange(0, 11, offWhite);
        }
        waitingAnimation.animationPhase = 1;
        waitingAnimation.stepIndex = 0;
        return;

    case 1:
    { // Transition from offWhite to 5% base color
        float t = waitingAnimation.stepIndex / (float)waitingAnimation.steps;
        if (lightUtils)
        {
            CRGB newColor;
            newColor.r = offWhite.r + (waitingAnimation.colorTransitions[waitingAnimation.colorIndex].base.r - offWhite.r) * t;
            newColor.g = offWhite.g + (waitingAnimation.colorTransitions[waitingAnimation.colorIndex].base.g - offWhite.g) * t;
            newColor.b = offWhite.b + (waitingAnimation.colorTransitions[waitingAnimation.colorIndex].base.b - offWhite.b) * t;
            lightUtils->protectLedRange(waitingAnimation.ledIndex, waitingAnimation.ledIndex, newColor);
        }

        if (++waitingAnimation.stepIndex > waitingAnimation.steps)
        {
            waitingAnimation.stepIndex = 0;
            waitingAnimation.animationPhase = 2;
        }
        break;
    }

    case 2:
    { // Ramp up from 5% base color to 100% full color
        float t = waitingAnimation.stepIndex / (float)waitingAnimation.steps;
        if (lightUtils)
        {
            CRGB newColor;
            newColor.r = waitingAnimation.colorTransitions[waitingAnimation.colorIndex].base.r +
                         (waitingAnimation.colorTransitions[waitingAnimation.colorIndex].full.r - waitingAnimation.colorTransitions[waitingAnimation.colorIndex].base.r) * t;
            newColor.g = waitingAnimation.colorTransitions[waitingAnimation.colorIndex].base.g +
                         (waitingAnimation.colorTransitions[waitingAnimation.colorIndex].full.g - waitingAnimation.colorTransitions[waitingAnimation.colorIndex].base.g) * t;
            newColor.b = waitingAnimation.colorTransitions[waitingAnimation.colorIndex].base.b +
                         (waitingAnimation.colorTransitions[waitingAnimation.colorIndex].full.b - waitingAnimation.colorTransitions[waitingAnimation.colorIndex].base.b) * t;
            lightUtils->protectLedRange(waitingAnimation.ledIndex, waitingAnimation.ledIndex, newColor);
        }

        if (++waitingAnimation.stepIndex > waitingAnimation.steps)
        {
            waitingAnimation.stepIndex = 0;
            waitingAnimation.animationPhase = 3;
        }
        break;
    }

    case 3: // Hold at 100% full color
        if (lightUtils)
        {
            lightUtils->protectLedRange(waitingAnimation.ledIndex, waitingAnimation.ledIndex,
                                        waitingAnimation.colorTransitions[waitingAnimation.colorIndex].full);
        }
        waitingAnimation.animationPhase = 4;
        break;

    case 4:
    { // Ramp down from 100% full color to 5% base color
        float t = waitingAnimation.stepIndex / (float)waitingAnimation.steps;
        if (lightUtils)
        {
            CRGB newColor;
            newColor.r = waitingAnimation.colorTransitions[waitingAnimation.colorIndex].full.r -
                         (waitingAnimation.colorTransitions[waitingAnimation.colorIndex].full.r - waitingAnimation.colorTransitions[waitingAnimation.colorIndex].base.r) * t;
            newColor.g = waitingAnimation.colorTransitions[waitingAnimation.colorIndex].full.g -
                         (waitingAnimation.colorTransitions[waitingAnimation.colorIndex].full.g - waitingAnimation.colorTransitions[waitingAnimation.colorIndex].base.g) * t;
            newColor.b = waitingAnimation.colorTransitions[waitingAnimation.colorIndex].full.b -
                         (waitingAnimation.colorTransitions[waitingAnimation.colorIndex].full.b - waitingAnimation.colorTransitions[waitingAnimation.colorIndex].base.b) * t;
            lightUtils->protectLedRange(waitingAnimation.ledIndex, waitingAnimation.ledIndex, newColor);
        }

        if (++waitingAnimation.stepIndex > waitingAnimation.steps)
        {
            waitingAnimation.stepIndex = 0;
            waitingAnimation.animationPhase = 5;
        }
        break;
    }

    case 5:
    { // Transition from 5% base color back to offWhite
        float t = waitingAnimation.stepIndex / (float)waitingAnimation.steps;
        if (lightUtils)
        {
            CRGB newColor;
            newColor.r = waitingAnimation.colorTransitions[waitingAnimation.colorIndex].base.r + (offWhite.r - waitingAnimation.colorTransitions[waitingAnimation.colorIndex].base.r) * t;
            newColor.g = waitingAnimation.colorTransitions[waitingAnimation.colorIndex].base.g + (offWhite.g - waitingAnimation.colorTransitions[waitingAnimation.colorIndex].base.g) * t;
            newColor.b = waitingAnimation.colorTransitions[waitingAnimation.colorIndex].base.b + (offWhite.b - waitingAnimation.colorTransitions[waitingAnimation.colorIndex].base.b) * t;
            lightUtils->protectLedRange(waitingAnimation.ledIndex, waitingAnimation.ledIndex, newColor);
        }

        if (++waitingAnimation.stepIndex > waitingAnimation.steps)
        {
            waitingAnimation.stepIndex = 0;
            waitingAnimation.animationPhase = 6;
        }
        break;
    }

    case 6: // Advance to next color or LED
        if (++waitingAnimation.colorIndex >= 3)
        {
            waitingAnimation.colorIndex = 0;
            if (++waitingAnimation.ledIndex >= 12)
            { // Use 12 LEDs instead of 4
                waitingAnimation.ledIndex = 0;
            }
        }
        waitingAnimation.animationPhase = 1;
        delay(50); // Small delay between cycles
        break;
    }
}

void novaNowSetup()
{
    messageOutput = PreferencesManager::getBool("messageOutput", true);
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
            sequenceGenAnimation.currentLitButton = msg.litButton;
        }
        else if (msg.stage == SIMONA_STAGE_INPUT_COLLECTION)
        {
            inputCollectionAnimation.lastPressedButton = msg.lastPressedButton;
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
        if (previousStage != SIMONA_STAGE_SEQUENCE_GENERATION)
        {
            mapButtonToLedPosition(0, msg.currentRound, true); // Reset mappings on stage change
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

            switch (sequenceGenAnimation.currentLitButton)
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
            int ledIndex = mapButtonToLedPosition(currentSequence, msg.currentRound);
            // Serial.print(">>> currentSequence: ");
            // Serial.print(currentSequence);
            // Serial.println(" <<<");

            // Set all LEDs to dim white
            lightUtils->protectLedRange(0, 11, sequenceGenAnimation.offWhite);
            // Light up the target LED
            if (ledIndex >= 0 && ledIndex < 12)
            {
                lightUtils->protectLedRange(ledIndex, ledIndex, targetColor);
            }
        }

        previousStage = SIMONA_STAGE_SEQUENCE_GENERATION;
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

            switch (inputCollectionAnimation.lastPressedButton)
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
            lightUtils->protectLedRange(0, 11, inputCollectionAnimation.offWhite);
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
            float t = lostAnimation.stepIndex / (float)lostAnimation.steps;
            uint8_t brightness = lostAnimation.startVal - lostAnimation.startVal * t;
            CRGB fadeColor = CRGB(brightness, brightness, brightness);
            lightUtils->protectLedRange(0, 11, fadeColor);
            delay(lostAnimation.delayMs);

            // Move to next step
            if (++lostAnimation.stepIndex > lostAnimation.steps)
            {
                lostAnimation.stepIndex = 0; // Reset for next fade out cycle
            }
        }
    }
    // Handle verification stage
    else if (currentSimonaStage == SIMONA_STAGE_VERIFICATION)
    {
        if (lightUtils)
        {
            float t = verificationAnimation.stepIndex / (float)verificationAnimation.steps;
            uint8_t brightness;

            if (!verificationAnimation.fadeOut)
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

            if (++verificationAnimation.stepIndex > verificationAnimation.steps)
            {
                verificationAnimation.stepIndex = 0;
                verificationAnimation.fadeOut = !verificationAnimation.fadeOut; // Toggle fade direction
            }
        }
    }
    else if (currentSimonaStage == SIMONA_STAGE_TRANSITION)
    {
        if (lightUtils)
        {
            float t = transitionAnimation.stepIndex / (float)transitionAnimation.steps;
            uint8_t brightness;

            if (!transitionAnimation.fadeOut)
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

            if (++transitionAnimation.stepIndex > transitionAnimation.steps)
            {
                transitionAnimation.stepIndex = 0;
                transitionAnimation.fadeOut = !transitionAnimation.fadeOut; // Toggle fade direction
            }
        }
    }
    // Handle game win state
    else if (currentSimonaStage == SIMONA_STAGE_GAME_WIN)
    {
        if (lightUtils)
        {
            // Check for stage change to reset button mappings
            if (previousStage != SIMONA_STAGE_GAME_WIN)
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

            if (poofRepetition < 4) {
                if (millis() - lastPoofTime >= 50) {
                    int led1 = poofPairIndex;
                    int led2 = 11 - poofPairIndex;

                    star->poof(led1);
                    star->poof(led2);

                    lastPoofTime = millis();
                    poofPairIndex++;

                    if (poofPairIndex > 5) {
                        poofPairIndex = 0;
                        poofRepetition++;
                    }
                }
            } else {
                // Reset for the next time the stage is entered
                poofRepetition = 0;
                poofPairIndex = 0;
            }

            // Calculate sine-based brightness for smooth pulsing
            float fraction = winAnimation.stepIndex / (float)winAnimation.stepsPerPulse;
            float brightnessFactor = sinf(fraction * 3.14159f);

            // Apply brightness to win color
            CRGB color = CRGB(
                (uint8_t)(winAnimation.winColor.r * brightnessFactor),
                (uint8_t)(winAnimation.winColor.g * brightnessFactor),
                (uint8_t)(winAnimation.winColor.b * brightnessFactor));

            // Apply to all LEDs
            lightUtils->protectLedRange(0, 11, color);
            delay(winAnimation.delayMs);

            // Move to next step
            if (++winAnimation.stepIndex >= winAnimation.stepsPerPulse)
            {
                winAnimation.stepIndex = 0;
                if (++winAnimation.pulseIndex >= winAnimation.pulses)
                {
                    winAnimation.pulseIndex = 0;
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
            switch (roundTransitionAnimation.animationStep)
            {
            case 0: // Skip relay trigger, move straight to fade in
                roundTransitionAnimation.currentLED = 0;
                roundTransitionAnimation.animationStep = 1;
                break;

            case 1:
            {                                                               // Fade in LEDs
                float factor = roundTransitionAnimation.currentLED / 15.0f; // 15 steps for fade
                for (int i = 0; i < 12; i++)
                {
                    CRGB color = roundTransitionAnimation.celebrationColors[i % 4];
                    lightUtils->protectLedRange(i, i, CRGB(color.r * factor, color.g * factor, color.b * factor));
                }
                delay(50);

                if (++roundTransitionAnimation.currentLED > 15)
                {
                    roundTransitionAnimation.currentLED = 0;
                    roundTransitionAnimation.animationStep = 2;
                }
                break;
            }

            case 2: // Hold full brightness briefly
                roundTransitionAnimation.animationStep = 3;
                delay(50);
                break;

            case 3:
            { // Fade out LEDs
                float factor = 1.0f - (roundTransitionAnimation.currentLED / 15.0f);
                for (int i = 0; i < 12; i++)
                {
                    CRGB color = roundTransitionAnimation.celebrationColors[i % 4];
                    lightUtils->protectLedRange(i, i, CRGB(color.r * factor, color.g * factor, color.b * factor));
                }
                delay(50);

                if (++roundTransitionAnimation.currentLED > 15)
                {
                    roundTransitionAnimation.currentLED = 0;
                    roundTransitionAnimation.currentPulse++;
                    if (roundTransitionAnimation.currentPulse >= roundTransitionAnimation.pulseCount)
                    {
                        roundTransitionAnimation.animationStep = 4;
                    }
                    else
                    {
                        roundTransitionAnimation.animationStep = 0; // Loop back for next pulse
                    }
                }
                break;
            }

            case 4:
            { // Set to dim white and finish
                CRGB dimWhite(roundTransitionAnimation.dimVal, roundTransitionAnimation.dimVal, roundTransitionAnimation.dimVal);
                lightUtils->protectLedRange(0, 11, dimWhite);

                // Reset state for next time
                roundTransitionAnimation.animationStep = 0;
                roundTransitionAnimation.currentPulse = 0;
                roundTransitionAnimation.currentLED = 0;
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
            switch (resetAnimation.animationPhase)
            {
            case 0: // Initialize
                lightUtils->protectLedRange(0, 11, resetAnimation.offWhite);
                resetAnimation.currentStep = 0;
                resetAnimation.currentColor = 0;
                resetAnimation.animationPhase = 1;
                break;

            case 1:
            { // Transition from offWhite to 5% base color
                float t = resetAnimation.currentStep / (float)resetAnimation.steps;
                CRGB newColor;
                newColor.r = resetAnimation.offWhite.r + (resetAnimation.colorTransitions[resetAnimation.currentColor].base.r - resetAnimation.offWhite.r) * t;
                newColor.g = resetAnimation.offWhite.g + (resetAnimation.colorTransitions[resetAnimation.currentColor].base.g - resetAnimation.offWhite.g) * t;
                newColor.b = resetAnimation.offWhite.b + (resetAnimation.colorTransitions[resetAnimation.currentColor].base.b - resetAnimation.offWhite.b) * t;
                lightUtils->protectLedRange(0, 11, newColor);
                delay(resetAnimation.delayMs);

                if (++resetAnimation.currentStep > resetAnimation.steps)
                {
                    resetAnimation.currentStep = 0;
                    resetAnimation.animationPhase = 2;
                }
                break;
            }

            case 2:
            { // Ramp up from 5% base color to 100% full color
                float t = resetAnimation.currentStep / (float)resetAnimation.steps;
                CRGB newColor;
                newColor.r = resetAnimation.colorTransitions[resetAnimation.currentColor].base.r +
                             (resetAnimation.colorTransitions[resetAnimation.currentColor].full.r - resetAnimation.colorTransitions[resetAnimation.currentColor].base.r) * t;
                newColor.g = resetAnimation.colorTransitions[resetAnimation.currentColor].base.g +
                             (resetAnimation.colorTransitions[resetAnimation.currentColor].full.g - resetAnimation.colorTransitions[resetAnimation.currentColor].base.g) * t;
                newColor.b = resetAnimation.colorTransitions[resetAnimation.currentColor].base.b +
                             (resetAnimation.colorTransitions[resetAnimation.currentColor].full.b - resetAnimation.colorTransitions[resetAnimation.currentColor].base.b) * t;
                lightUtils->protectLedRange(0, 11, newColor);
                delay(resetAnimation.delayMs);

                if (++resetAnimation.currentStep > resetAnimation.steps)
                {
                    resetAnimation.currentStep = 0;
                    resetAnimation.animationPhase = 3;
                }
                break;
            }

            case 3: // Hold at 100% full color
                lightUtils->protectLedRange(0, 11, resetAnimation.colorTransitions[resetAnimation.currentColor].full);
                delay(resetAnimation.holdDelayMs);
                resetAnimation.animationPhase = 4;
                break;

            case 4:
            { // Ramp down from 100% full color to 5% base color
                float t = resetAnimation.currentStep / (float)resetAnimation.steps;
                CRGB newColor;
                newColor.r = resetAnimation.colorTransitions[resetAnimation.currentColor].full.r -
                             (resetAnimation.colorTransitions[resetAnimation.currentColor].full.r - resetAnimation.colorTransitions[resetAnimation.currentColor].base.r) * t;
                newColor.g = resetAnimation.colorTransitions[resetAnimation.currentColor].full.g -
                             (resetAnimation.colorTransitions[resetAnimation.currentColor].full.g - resetAnimation.colorTransitions[resetAnimation.currentColor].base.g) * t;
                newColor.b = resetAnimation.colorTransitions[resetAnimation.currentColor].full.b -
                             (resetAnimation.colorTransitions[resetAnimation.currentColor].full.b - resetAnimation.colorTransitions[resetAnimation.currentColor].base.b) * t;
                lightUtils->protectLedRange(0, 11, newColor);
                delay(resetAnimation.delayMs);

                if (++resetAnimation.currentStep > resetAnimation.steps)
                {
                    resetAnimation.currentStep = 0;
                    resetAnimation.animationPhase = 5;
                }
                break;
            }

            case 5:
            { // Transition from 5% base color back to offWhite
                float t = resetAnimation.currentStep / (float)resetAnimation.steps;
                CRGB newColor;
                newColor.r = resetAnimation.colorTransitions[resetAnimation.currentColor].base.r +
                             (resetAnimation.offWhite.r - resetAnimation.colorTransitions[resetAnimation.currentColor].base.r) * t;
                newColor.g = resetAnimation.colorTransitions[resetAnimation.currentColor].base.g +
                             (resetAnimation.offWhite.g - resetAnimation.colorTransitions[resetAnimation.currentColor].base.g) * t;
                newColor.b = resetAnimation.colorTransitions[resetAnimation.currentColor].base.b +
                             (resetAnimation.offWhite.b - resetAnimation.colorTransitions[resetAnimation.currentColor].base.b) * t;
                lightUtils->protectLedRange(0, 11, newColor);
                delay(resetAnimation.delayMs);

                if (++resetAnimation.currentStep > resetAnimation.steps)
                {
                    resetAnimation.currentStep = 0;
                    // Move to next color or finish
                    if (++resetAnimation.currentColor >= 3)
                    {
                        resetAnimation.currentColor = 0;
                        resetAnimation.animationPhase = 0; // Back to start for next time
                    }
                    else
                    {
                        resetAnimation.animationPhase = 1; // Move to next color
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