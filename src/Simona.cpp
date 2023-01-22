#include <Arduino.h>
#include "Simona.h"
#include "configuration.h"
#include "NovaIO.h"

// Original Source: https://github.com/printnplay/SimpleSimon/blob/main/simon.ino
// THANK YOU JAMES!

//*****************************************

/*
int LENGTH = 400; // Length of time to play the main notes

int gamepattern[20]; // Array to store game pattern in during play

int difficulty = 1;
*/
//*****************************************

Simona *simona = NULL;

Simona::Simona()
{

  // Setup goes in here
}

void Simona::loop()
{
  // generate_game(); // Was used for testing a single-game mode before main menu was implimented
  main_menu();
}

void Simona::main_menu()
{
  Serial.println("main_menu()");
  while (1 == 1)
  {

    if (novaIO->expansionDigitalRead(BUTTON_RED_IN) == LOW)
    {
      Serial.println("Difficulty 1");
      difficulty = 1;
      generate_game();
      play_game();
    }
    if (novaIO->expansionDigitalRead(BUTTON_GREEN_IN) == LOW)
    {
      Serial.println("Difficulty 2");
      difficulty = 2;
      generate_game();
      play_game();
    }
    if (novaIO->expansionDigitalRead(BUTTON_BLUE_IN) == LOW)
    {
      Serial.println("Difficulty 3");
      difficulty = 3;
      generate_game();
      play_game();
    }
    if (novaIO->expansionDigitalRead(BUTTON_YELLOW_IN) == LOW)
    {
      Serial.println("Difficulty 4");
      difficulty = 4;
      generate_game();
      play_game();
    }
    yield();
  }
}

void Simona::play_game()
{

  Serial.println("play_game()");
  int roundCount = 0;
  int playerTurn = 1;
  bool buttonPress = false;
  int currentNote;
  int userInput = 0;
  bool loss = false;
  play_note(1, 100);
  play_note(2, 100);
  play_note(3, 100);
  play_note(4, 100);
  delay(1000);
  for (int currentRound = 1; (currentRound - 1) <= (difficulty * 5); currentRound++) // Number of rounds to play
  {
    roundCount += 1;
    playerTurn = 1;
    buttonPress = false;
    userInput = 0;
    for (int j = 1; j != currentRound; j++)
    {
      play_note(gamepattern[j - 1], LENGTH); // Play current round note(s)
    }
    while (playerTurn < currentRound)
    {
      currentNote = gamepattern[playerTurn - 1];
      Serial.println(currentNote);
      while (buttonPress == false)
      {
        /*        */

        if (novaIO->expansionDigitalRead(BUTTON_RED_IN) == LOW) // Button 1 Pressed
        {
          buttonPress = true;
          userInput = 1;
        }
        if (novaIO->expansionDigitalRead(BUTTON_GREEN_IN) == LOW) // Button 2 Pressed
        {
          buttonPress = true;
          userInput = 2;
        }
        if (novaIO->expansionDigitalRead(BUTTON_BLUE_IN) == LOW) // Button 3 Pressed
        {
          buttonPress = true;
          userInput = 3;
        }
        if (novaIO->expansionDigitalRead(BUTTON_YELLOW_IN) == LOW) // Button 4 Pressed
        {
          buttonPress = true;
          userInput = 4;
        }
        if (buttonPress == true) // A button was Pressed
        {
          play_note(userInput, LENGTH); // Play the note pushed
          if (currentNote == userInput) // You pushed the right one!
          {
            playerTurn++;
          }
          else // You pushed the wrong one! :(
          {
            game_over(false);
          }
        }
        yield();
      }
      buttonPress = false;
      yield();
    }
  }
  if (loss == false)
  {
    Serial.println("You Win!");
    game_over(true);
  }
}

void Simona::generate_game()
{
  Serial.println("generate_game()");
  randomSeed(esp_random());
  for (int i = 0; i < (difficulty * 5); i++) // For each level of difficulty, add 5 more turns to the game
  {
    gamepattern[i] = random(1, 5);
  }

  Serial.println("Game pattern: ");
  for (int i = 0; i < (difficulty * 5); i++) // For each level of difficulty, add 5 more turns to the game
  {
    Serial.print(gamepattern[i]);
    Serial.print(" ");
  }
  Serial.println(" ");
}

void Simona::play_note(int index, int notespeed)
{
  Serial.println("play_note()");
  if (index == 1)
  {
    digitalWrite(BUTTON_RED_OUT, HIGH);
  }
  else if (index == 2)
  {
    digitalWrite(BUTTON_GREEN_OUT, HIGH);
  }
  else if (index == 3)
  {
    digitalWrite(BUTTON_BLUE_OUT, HIGH);
  }
  else if (index == 4)
  {
    digitalWrite(BUTTON_YELLOW_OUT, HIGH);
  }

  delay(notespeed * 2);

  if (index == 1)
  {
    digitalWrite(BUTTON_RED_OUT, LOW);
  }
  else if (index == 2)
  {
    digitalWrite(BUTTON_GREEN_OUT, LOW);
  }
  else if (index == 3)
  {
    digitalWrite(BUTTON_BLUE_OUT, LOW);
  }
  else if (index == 4)
  {
    digitalWrite(BUTTON_YELLOW_OUT, LOW);
  }

  delay(notespeed * 2);
}

void Simona::game_over(bool win)
{
  Serial.println("game_over()");
  if (win)
  {
    Serial.println("You Win!");
    for (int i = 0; i < 10; i++)
    {
      play_note(1, 50);
      play_note(2, 50);
      play_note(3, 50);
      play_note(4, 50);
    }
  }

  else
  {
    Serial.println("You Lose!");
    for (int i = 0; i < 6; i++)
    {
      play_note(4, 100);
      play_note(3, 100);
      play_note(2, 100);
      play_note(1, 100);
    }
  }
  Serial.println("Game over");
  main_menu();
}
