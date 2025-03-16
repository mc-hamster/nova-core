#ifndef NOVANOW_H
#define NOVANOW_H

#include "../SimonaMessage.h"
#include <FastLED.h>
#include <vector>

/**
 * @brief Manages dynamic LED mapping for the Simona game
 * 
 * The LedMapper class handles the complex task of mapping button presses
 * to LED positions as the game progresses through rounds. It provides:
 * - Progressive scaling of active LED count
 * - Consistent button-to-LED mapping within rounds
 * - Random but fair LED distribution
 * - Center-aligned LED positioning
 */
class LedMapper {
private:
    /** Maximum number of LEDs/buttons in the system */
    static const int MAX_LEDS = 12;
    /** Array storing current button-to-LED mappings (-1 = unmapped) */
    int buttonToLedMapping[MAX_LEDS];
    /** Current game round being mapped */
    int currentRound;
    /** Flag indicating if mapping has been initialized */
    bool isInitialized;

    /**
     * @brief Calculate number of LEDs to use for current round
     * @param round Current game round
     * @return Number of active LEDs for this round
     */
    int calculateLedCount(int round) const;

    /**
     * @brief Calculate starting LED position to center the active range
     * @param ledCount Number of LEDs being used
     * @return Starting LED position
     */
    int calculateStartPosition(int ledCount) const;

public:
    /** 
     * @brief Construct a new LedMapper
     * 
     * Initializes mapping array to all unmapped (-1) and sets initial state
     */
    LedMapper() : currentRound(-1), isInitialized(false) {
        for (int i = 0; i < MAX_LEDS; i++) {
            buttonToLedMapping[i] = -1;
        }
    }

    /**
     * @brief Reset mapping state for a new round
     * @param round New round number
     */
    void reset(int round);

    /**
     * @brief Map a button to an LED position
     * @param buttonIndex Button that was pressed (1-based)
     * @param round Current game round
     * @return Mapped LED position (0-based)
     */
    int mapButtonToLed(int buttonIndex, int round);

    /**
     * @brief Get all currently mapped LED positions
     * @return Vector of active LED positions
     */
    std::vector<int> getMappedLeds() const;
};

// Animation state management class
class AnimationState {
public:
    struct WaitingAnimation {
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
            {CRGB(8, 0, 0), CRGB(255, 0, 0)}, // Red
            {CRGB(0, 8, 0), CRGB(0, 255, 0)}, // Green
            {CRGB(0, 0, 8), CRGB(0, 0, 255)}  // Blue
        };
    };

    struct SequenceGeneration {
        int currentLitButton = 0;
        const uint8_t offVal = 8;
        CRGB offWhite = CRGB(offVal, offVal, offVal);
    };

    struct InputCollection {
        int lastPressedButton = 0;
        const uint8_t offVal = 8;
        CRGB offWhite = CRGB(offVal, offVal, offVal);
    };

    struct LostAnimation {
        int stepIndex = 0;
        const uint8_t startVal = 5;
        const int steps = 20;
        const int delayMs = 30;
    };

    struct TransitionAnimation {
        int stepIndex = 0;
        const int steps = 20;
        const uint8_t lowVal = 5;
        const uint8_t highVal = 15;
        bool fadeOut = false;
        const int delayMs = 30;
    };

    struct WinAnimation {
        int stepIndex = 0;
        int pulseIndex = 0;
        const int pulses = 4;
        const int stepsPerPulse = 10;
        const int delayMs = 50;
        const CRGB winColor = CRGB(255, 100, 255);
    };

    struct RoundTransitionAnimation {
        int currentLED = 0;
        int animationStep = 0;
        int currentPulse = 0;
        const int pulseCount = 3;
        const uint8_t dimVal = 8;
        const CRGB celebrationColors[4] = {
            CRGB(255, 50, 50), // Red-orange
            CRGB(50, 255, 50), // Green
            CRGB(50, 50, 255), // Blue
            CRGB(255, 255, 50) // Yellow
        };
    };

    struct ResetAnimation {
        int currentStep = 0;
        int currentColor = 0;
        int animationPhase = 0;
        const int steps = 10;
        const uint8_t offVal = 8;
        const int delayMs = 50 / steps;
        const int holdDelayMs = 150;
        CRGB offWhite = CRGB(offVal, offVal, offVal);
        struct ColorTransition {
            CRGB base;
            CRGB full;
        } colorTransitions[3] = {
            {CRGB(offVal, 0, 0), CRGB(255, 0, 0)}, // Red
            {CRGB(0, offVal, 0), CRGB(0, 255, 0)}, // Green
            {CRGB(0, 0, offVal), CRGB(0, 0, 255)}  // Blue
        };
    };

    struct VerificationAnimation {
        int stepIndex = 0;
        const int steps = 20;
        const uint8_t lowVal = 5;
        const uint8_t highVal = 15;
        bool fadeOut = false;
        const int delayMs = 30;
    };

    WaitingAnimation waiting;
    SequenceGeneration sequenceGen;
    InputCollection inputCollection;
    LostAnimation lost;
    TransitionAnimation transition;
    WinAnimation win;
    RoundTransitionAnimation roundTransition;
    ResetAnimation reset;
    VerificationAnimation verification;
};

// Global state management
extern LedMapper* ledMapper;

/**
 * @brief Initialize the NovaNow module
 * 
 * Sets up the initial state and preferences for the NovaNow LED control system.
 * Should be called once during system startup before using other functions.
 */
void novaNowSetup();

/**
 * @brief Main processing loop for NovaNow
 * 
 * Handles message queue processing and updates LED animations based on the current
 * Simona game state. This should be called regularly in the main loop.
 */
void novaNowLoop();

/**
 * @brief Send a Simona game message to be processed by NovaNow
 * 
 * Queues a SimonaMessage for processing by the NovaNow system. The message will be
 * processed in the next call to novaNowLoop() and may trigger LED animations based
 * on the game state contained in the message.
 * 
 * @param simMsg Reference to the SimonaMessage to be sent
 */
void sendSimonaMessage(const SimonaMessage &simMsg);

#endif // NOVANOW_H