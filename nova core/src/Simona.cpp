#include "Simona.h"
#include "midi/MIDIControl.hpp" // Updated path to MIDI module
#include "SimonaMessage.h"
#include "configuration.h"
#include <Preferences.h>
#include "utilities/PreferencesManager.h" // Updated path
#include "main.h"                         // Added for setLedBrightness
#include "Web.h"
#include "output/NovaNow.h" // Updated path to output directory

/*
  Based on:
    https://github.com/embeddedlab786/Simon_Memory_Game

  Described in the YoutubeVideo:
    https://www.youtube.com/watch?v=8ORj7vU1hU0


Definitions:
  Sequence: The sequence of LEDs that the player must remember and repeat.
  Level: The current level of the game. The level increases as the player progresses.
  levelsInGame: The total number of levels in the game.


*/

Simona *Simona::instance = nullptr;

void Simona::initInstance(uint8_t *buttons, uint8_t *leds, const char **buttonColors, const char **ledColors,
                          LedControlCallback ledControl, ButtonReadCallback buttonRead)
{
  if (!instance)
  {
    instance = new Simona(buttons, leds, buttonColors, ledColors, ledControl, buttonRead);
    instance->loadPreferences();
  }
}

Simona::Simona(uint8_t *buttons, uint8_t *leds, const char **buttonColors, const char **ledColors, LedControlCallback ledControl, ButtonReadCallback buttonRead)
    : buttons(buttons), leds(leds), buttonColors(buttonColors), ledColors(ledColors), lost(false), game_play(1), level(1), stage(SIMONA_STAGE_WAITING), ledControl(ledControl), buttonRead(buttonRead)
{
  for (uint8_t i = 0; i < 4; i++)
  {
    button[i] = false;
  }
  
  // Initialize the sequence arrays
  for (uint8_t i = 0; i < 100; i++)
  {
    led_simonSaid[i] = 0;
    bt_simonSaid[i] = 0;
  }
}

void Simona::controlLed(uint8_t led, bool state)
{
  if (ledControl)
  {
    ledControl(led, !state); // Keep the inversion logic
  }
  else
  {
    setLedBrightness(led, !state); // Using the new PWM function, keep inversion logic
  }
}

bool Simona::readButton(uint8_t button)
{
  if (buttonRead)
  {
    return buttonRead(button);
  }
  else
  {
    return novaIO->expansionDigitalRead(button) == LOW;
  }
}

/**
 * @brief Updates the provided SimonaMessage object with the current state of the Simona instance
 *        and prepares it for sending.
 *
 * This function updates the fields of the given SimonaMessage object with the current values
 * of the Simona instance's stage, level, game play status, lost status, current round, maximum
 * rounds, and levels in the current round. The updated message is then ready to be sent.
 *
 * @param simMsg A reference to the SimonaMessage object that will be updated with the current state.
 */
void Simona::updateAndSendSimMsg(SimonaMessage &simMsg)
{
  simMsg.stage = stage;
  simMsg.level = level;
  simMsg.gamePlay = game_play;
  simMsg.lost = lost;
  simMsg.currentRound = m_currentRound;
  simMsg.maxRounds = MAX_ROUNDS;
  simMsg.levelsInRound = m_levelsInRound;
  sendSimonaMessage(simMsg);
}

void Simona::loadPreferences()
{
  m_sequenceLocalEcho = PreferencesManager::getBool("simonaSequenceLocalEcho", true); // Use correct preference key
}

void Simona::runGameTask()
{
  // Remove this line - we're using the class member instead
  // static uint32_t inputStart = 0;

  static SimonaMessage simMsg = {};

  // while (true)
  //{
  switch (stage)
  {
  case SIMONA_STAGE_WAITING:
    Serial.println("Press White Button for Start Game");
    updateAndSendSimMsg(simMsg);
    inputStart = 0; // Reset timer when waiting
    while (stage == SIMONA_STAGE_WAITING)
    {
      vTaskDelay(10 / portTICK_PERIOD_MS);
    }
    break;

  case SIMONA_STAGE_SEQUENCE_GENERATION: // 1
    Serial.println();
    Serial.print("Level: ");
    Serial.print((level / 10) % 10);
    Serial.println(level % 10);
    Serial.print("Round: ");
    Serial.print(m_currentRound);
    Serial.print("/");
    Serial.print(MAX_ROUNDS);
    Serial.print(" (");
    Serial.print(m_levelsInRound);
    Serial.println(" levels)");
    Serial.println(" -- SIMONA_STAGE_SEQUENCE_GENERATION -- ");

    {
      // Update cheat mode from global setting
      m_cheatMode = SIMONA_CHEAT_MODE;

      if (m_cheatMode)
      {
        // In cheat mode, sequence is always RED->GREEN->YELLOW->BLUE
        const uint8_t cheatSequence[] = {0, 1, 3, 2}; // RED=0, GREEN=1, YELLOW=3, BLUE=2
        led_simonSaid[level] = cheatSequence[(level - 1) % 4];
      }
      else
      {
        uint8_t maxSameAllowed = 2;
        if (level == 1)
        {
          led_simonSaid[level] = random(0, 4);
        }
        else
        {
          uint8_t newColor;
          uint8_t count;
          do
          {
            newColor = random(0, 4);
            count = 1;
            for (int j = level - 1; j >= 1; j--)
            {
              if (led_simonSaid[j] == newColor)
                count++;
              else
                break;
            }
          } while (count >= maxSameAllowed);
          led_simonSaid[level] = newColor;
        }
      }
    }

    Serial.print("Full Sequence: ");
    for (uint8_t i = 1; i <= level; i++)
    {
      Serial.print(ledColors[led_simonSaid[i]]);
      Serial.print(" ");
    }
    Serial.println();

    vTaskDelay(200 / portTICK_PERIOD_MS); // Replaced delay(200)
    Serial.print("Sequence: ");
    for (uint8_t i = 1; i <= level; i++)
    {
      // Only control LEDs if sequence local echo is enabled
      if (m_sequenceLocalEcho)
      {
        controlLed(leds[led_simonSaid[i]], true);
      }

      simMsg.litButton = led_simonSaid[i];
      Serial.print(" ");

      updateAndSendSimMsg(simMsg);

      playBuzzer(60 + (led_simonSaid[i] - 7));
      vTaskDelay(50 / portTICK_PERIOD_MS); // Replaced delay(50)

      // Only control LEDs if sequence local echo is enabled
      if (m_sequenceLocalEcho)
      {
        controlLed(leds[led_simonSaid[i]], false);
      }
    }
    Serial.println();
    inputStart = millis(); // Reset timer at start of new sequence
    Serial.println("Timer reset: New sequence");
    stage = SIMONA_STAGE_TRANSITION;

    break;

  case SIMONA_STAGE_TRANSITION: // 2
    // Transition to input collection.
    updateAndSendSimMsg(simMsg);
    stage = SIMONA_STAGE_INPUT_COLLECTION;
    Serial.println("   -- SIMONA_STAGE_TRANSITION --   ");
    break;

  case SIMONA_STAGE_INPUT_COLLECTION: // 3
  {
    // Remove any local declarations of inputStart
    if (inputStart == 0)
    {
      inputStart = millis();
      Serial.println("Timer reset: Input collection start");
    }

    uint32_t elapsed = millis() - inputStart;
    uint32_t remaining = (SIMONA_INPUT_TIMEOUT_SECONDS * 1000UL) - elapsed;

#if SIMONA_DEBUG_TIMEOUT
    // Only print every 1000ms to avoid console spam
    static uint32_t lastDebugPrint = 0;
    if (millis() - lastDebugPrint >= 1000)
    {
      Serial.print("Time remaining: ");
      Serial.print(remaining / 1000);
      Serial.println(" seconds");
      lastDebugPrint = millis();
    }
#endif

    if (elapsed > SIMONA_INPUT_TIMEOUT_SECONDS * 1000UL)
    { // Use configuration timeout in seconds.
      Serial.print("Input timeout after ");
      Serial.print(elapsed / 1000);
      Serial.println(" seconds");
      lost = 1;
      stage = SIMONA_STAGE_GAME_LOST;
      inputStart = 0;
      break;
    }

    // Only process button inputs if game is enabled
    if (GAME_ENABLED)
    {
      // Collect player's input and update lastPressedButton on button press.
      for (uint8_t i = 0; i <= 3; i++)
      {
        button[i] = readButton(buttons[i]);
        if (button[i])
        {
          // Only reset timer if the input was correct
          if (bt_simonSaid[game_play] == led_simonSaid[game_play])
          {
            inputStart = millis();
            Serial.println("Timer reset: Valid input");
          }
          // Reset timer on any button press.
          inputStart = millis();
          // Update lastPressedButton immediately.
          simMsg.lastPressedButton = i;
          bt_simonSaid[game_play] = i;

          updateAndSendSimMsg(simMsg);

          controlLed(leds[i], true);
          Serial.print("Button Pressed: ");
          Serial.println(buttonColors[i]);
          playBuzzer(60 + (i - 7));
          if (bt_simonSaid[game_play] != led_simonSaid[game_play])
          {
            Serial.println("Incorrect button! Ending game play.");
            lost = 1;
            stage = SIMONA_STAGE_GAME_LOST;

            while (readButton(buttons[i]))
            {
              vTaskDelay(10 / portTICK_PERIOD_MS);
            }
            controlLed(leds[i], false);
            break;
          }
          while (readButton(buttons[i]))
          {
            vTaskDelay(10 / portTICK_PERIOD_MS);
          }
          vTaskDelay(10 / portTICK_PERIOD_MS); // Replaced delay(10)
          controlLed(leds[i], false);
          Serial.print("LED OFF: ");
          Serial.println(ledColors[i]);
          game_play++;
          if (game_play - 1 == level)
          {
            game_play = 1;
            stage = SIMONA_STAGE_VERIFICATION;
            break;
          }
        }
      }
    }
    else
    {
      // Game input disabled, but still send updates
      simMsg.lastPressedButton = -1; // No button pressed
      updateAndSendSimMsg(simMsg);
    }

    vTaskDelay(10 / portTICK_PERIOD_MS);
    break;
  }

  case SIMONA_STAGE_VERIFICATION: // 4
    // Verify player's sequence.
    Serial.println("   -- Verification --   ");
    for (uint8_t i = 1; i <= level; i++)
    {
      if (led_simonSaid[i] != bt_simonSaid[i])
      {
        lost = 1;
        break;
      }
    }
    updateAndSendSimMsg(simMsg);

    vTaskDelay(400 / portTICK_PERIOD_MS); // Replaced delay(400)

    if (!lost)
    {
      inputStart = millis();
      Serial.println("Timer reset: Sequence verified");
    }

    stage = (lost == 1) ? SIMONA_STAGE_GAME_LOST : SIMONA_STAGE_GAME_WIN;
    break;

  case SIMONA_STAGE_GAME_LOST: // 5
    // Handle game lost.
    Serial.println(" !! You Lost !! ");

    updateAndSendSimMsg(simMsg);

    playLost();
    for (uint8_t i = 0; i <= 3; i++)
    {
      controlLed(leds[i], true);
    }
    for (uint8_t i = 0; i <= 3; i++)
    {
      controlLed(leds[i], false);
    }
    level = 1;
    stage = SIMONA_STAGE_WAITING;
    lost = 0;

    break;

  case SIMONA_STAGE_GAME_WIN: // 6
    Serial.println(" ** You Win ** ");
    if (level == m_levelsInRound)
    {
      if (m_currentRound == MAX_ROUNDS)
      {
        Serial.println("Congratulations!!! You have completed ALL rounds of the game!");
        updateAndSendSimMsg(simMsg);

        controlLed(BUTTON_RED_OUT, true);
        controlLed(BUTTON_GREEN_OUT, true);
        controlLed(BUTTON_BLUE_OUT, true);
        controlLed(BUTTON_YELLOW_OUT, true);
        playWin();
        controlLed(BUTTON_RED_OUT, false);
        controlLed(BUTTON_GREEN_OUT, false);
        controlLed(BUTTON_BLUE_OUT, false);
        controlLed(BUTTON_YELLOW_OUT, false);

        // Reset everything for a new game
        level = 1;
        m_currentRound = 1;
        m_levelsInRound = LEVELS_PER_ROUND_DEFAULT; // Use constant instead of literal 3.
        stage = SIMONA_STAGE_WAITING;
      }
      else
      {
        Serial.println("Round complete - transitioning to next round");
        level = 1; // Explicitly reset level here
        stage = SIMONA_STAGE_ROUND_TRANSITION;
      }
    }
    else
    {
      Serial.println(" Level Complete");
      Serial.print("Current level: ");
      Serial.print(level);
      Serial.print("/");
      Serial.println(m_levelsInRound);
      if (level < m_levelsInRound)
        level++;
      stage = SIMONA_STAGE_SEQUENCE_GENERATION;
    }
    break;

  case SIMONA_STAGE_RESET: // 7
    Serial.println("Resetting game...");
    updateAndSendSimMsg(simMsg);

    playGameIntro();
    // controlLed(LED_RESET, true);
    // vTaskDelay(500 / portTICK_PERIOD_MS);  // Replaced delay(500)
    // controlLed(LED_RESET, false);
    level = 1;
    game_play = 1;
    lost = 0;
    m_currentRound = 1;                         // Reset round count
    m_levelsInRound = LEVELS_PER_ROUND_DEFAULT; // Reset levels per round using the constant.
    stage = SIMONA_STAGE_SEQUENCE_GENERATION;
    break;

  case SIMONA_STAGE_ROUND_TRANSITION: // 8
  {
    Serial.println("   -- SIMONA_STAGE_ROUND_TRANSITION --   ");
    Serial.println("Round Complete! Starting next round with more levels!");
    updateAndSendSimMsg(simMsg);

    // Play round transition music before visual feedback
    playRoundTransitionMusic(m_currentRound);

    // Flash LEDs in sequence 20 times
    const uint8_t allLeds[] = {BUTTON_RED_OUT, BUTTON_GREEN_OUT, BUTTON_BLUE_OUT, BUTTON_YELLOW_OUT};
    for (int j = 0; j < 4; j++)
    {
      for (int i = 0; i < 4; i++)
      {
        controlLed(allLeds[i], true);
        vTaskDelay(50 / portTICK_PERIOD_MS); // Replaced delay(50)
        controlLed(allLeds[i], false);
      }
    }

    // Increment round and increase levels per round
    m_currentRound++;
    m_levelsInRound++; // Increase levels instead of resetting to DEFAULT_LEVELS_PER_ROUND.
    level = 1;         // Ensure level is reset to 1
    Serial.print("New round started. Round: ");
    Serial.print(m_currentRound);
    Serial.print(", Levels in round: ");
    Serial.print(m_levelsInRound);
    Serial.print(", Starting at level: ");
    Serial.println(level);
    inputStart = millis();
    Serial.println("Timer reset: Round transition");
    stage = SIMONA_STAGE_SEQUENCE_GENERATION;
    break;
  }

  default:
    break;
  }
  //  vTaskDelay(10 / portTICK_PERIOD_MS);
  //}
}

// In runTaskButton, change reset handling to trigger the reset stage.
void Simona::runTaskButton()
{
  // while (true)
  //{
  //  Only process button presses if game is enabled
  if (GAME_ENABLED)
  {
    // Take 5 readings and verify they're all LOW
    const int requiredReadings = 2;
    bool allLow = true;

    for (int i = 0; i < requiredReadings; i++)
    {
      uint8_t buttonState = novaIO->expansionDigitalRead(BUTTON_WHITE_IN);

      //Serial.printf("BUTTON_WHITE_IN value: %d\n", buttonState);

      if (buttonState)
      {
        allLow = false;
        break;
      }
      vTaskDelay(1 / portTICK_PERIOD_MS); // Small delay between readings
    }

    if (allLow) // Only proceed if all readings were LOW
    {
      Serial.println("White button pressed - resetting game... runTaskButton()");
      stage = SIMONA_STAGE_RESET; // Set the new reset stage.
      while (novaIO->expansionDigitalRead(BUTTON_WHITE_IN) == LOW)
      {
        controlLed(BUTTON_WHITE_OUT, true);  // Turn on the reset LED.
        vTaskDelay(10 / portTICK_PERIOD_MS); // wait for button release.
      }
      controlLed(BUTTON_WHITE_OUT, false); // Turn on the reset LED.
    }
  }
  // ...existing code...
  //  vTaskDelay(10 / portTICK_PERIOD_MS);
  //}
}
