/**
 * @file LedMapper.cpp
 * @brief Maps game buttons to LED positions with dynamic round-based positioning
 * 
 * This file implements the LED mapping logic for the Simona game, handling the 
 * progressive increase in LED count and positions as rounds advance. It maintains
 * consistent button-to-LED mappings within each round while ensuring random but
 * fair distribution of LEDs.
 */

#include "NovaNow.h"
#include <Arduino.h>

// Global instance of LedMapper accessible to other components
LedMapper* ledMapper = nullptr;

/**
 * @brief Calculate number of active LEDs for the current round
 * 
 * Progressive LED count scaling:
 * - Rounds 1-2: 4 LEDs
 * - Rounds 3-4: 6 LEDs
 * - Rounds 5-6: 8 LEDs
 * - Rounds 7+:  12 LEDs
 * 
 * @param round Current game round number
 * @return Number of LEDs to use for this round
 */
int LedMapper::calculateLedCount(int round) const {
    if (round >= 7) return 12;
    if (round >= 5) return 8;
    if (round >= 3) return 6;
    return 4;
}

/**
 * @brief Calculate starting LED position to center the active LEDs
 * 
 * Centers the active LEDs within the available 12 LED positions.
 * For example, with 4 LEDs, starts at position 4 to center them.
 * 
 * @param ledCount Number of LEDs being used in current round
 * @return Starting position for LED placement
 */
int LedMapper::calculateStartPosition(int ledCount) const {
    return (MAX_LEDS - ledCount) / 2;
}

/**
 * @brief Reset mapping state for a new round
 * 
 * Clears existing mappings and initializes state for a new round.
 * Uses hardware random number generator for better randomization.
 * 
 * @param round New round number to initialize for
 */
void LedMapper::reset(int round) {
    randomSeed(esp_random());  // Use hardware RNG for better randomization
    currentRound = round;
    isInitialized = true;
    for (int i = 0; i < MAX_LEDS; i++) {
        buttonToLedMapping[i] = -1;
    }
}

/**
 * @brief Map a button press to an LED position
 * 
 * Core mapping function that:
 * 1. Validates input and handles edge cases
 * 2. Maintains consistent mappings within a round
 * 3. Creates new random mappings as needed
 * 4. Ensures fair LED distribution
 * 
 * @param buttonIndex Button that was pressed (1-based index)
 * @param round Current game round
 * @return Mapped LED position (0-based index)
 */
int LedMapper::mapButtonToLed(int buttonIndex, int round) {
    // Input validation
    if (buttonIndex < 1 || buttonIndex > MAX_LEDS) {
        Serial.printf("Invalid button index %d\n", buttonIndex);
        return 4;  // Default fallback position
    }

    // Reset mapping if round changed
    if (currentRound != round || !isInitialized) {
        reset(round);
    }

    int buttonArrayIndex = buttonIndex - 1;
    
    // Return existing mapping if available
    if (buttonToLedMapping[buttonArrayIndex] >= 0) {
        return buttonToLedMapping[buttonArrayIndex];
    }

    // Calculate new mapping parameters
    int ledCount = calculateLedCount(round);
    int startPos = calculateStartPosition(ledCount);

    // Find available LED positions
    std::vector<int> availablePositions;
    for (int i = startPos; i < startPos + ledCount; i++) {
        bool isUsed = false;
        for (int j = 0; j < MAX_LEDS; j++) {
            if (buttonToLedMapping[j] == i) {
                isUsed = true;
                break;
            }
        }
        if (!isUsed) {
            availablePositions.push_back(i);
        }
    }

    // Assign new random position from available ones
    if (!availablePositions.empty()) {
        int randomIndex = random(availablePositions.size());
        buttonToLedMapping[buttonArrayIndex] = availablePositions[randomIndex];
        return buttonToLedMapping[buttonArrayIndex];
    }

    // Emergency fallback - should rarely occur
    Serial.println("No available positions, using emergency fallback");
    buttonToLedMapping[buttonArrayIndex] = startPos + random(ledCount);
    return buttonToLedMapping[buttonArrayIndex];
}

/**
 * @brief Get list of currently mapped LED positions
 * 
 * Used for special effects like poofing or booming multiple LEDs.
 * Only returns positions that have been mapped to buttons.
 * 
 * @return Vector of currently mapped LED positions
 */
std::vector<int> LedMapper::getMappedLeds() const {
    std::vector<int> mappedLeds;
    for (int i = 0; i < MAX_LEDS; i++) {
        if (buttonToLedMapping[i] >= 0) {
            mappedLeds.push_back(buttonToLedMapping[i]);
        }
    }
    return mappedLeds;
}