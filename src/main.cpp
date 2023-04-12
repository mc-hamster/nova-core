#include <Arduino.h>
#include <Thread.h>
#include <ThreadController.h>
#include <Wire.h>

#include "OneButton.h"

#include "configuration.h"
#include "modes/Simona.h"
#include "NovaIO.h"
#include "main.h"
#include "Ambient.h"
#include "output/Star.h"
#include "Buttons.h"

void TaskAmbient(void *pvParameters);
void TaskModes(void *pvParameters);
void TaskButtons(void *pvParameters);

void setup()
{
  delay(1000);
  Serial.begin(921600);
  Serial.println("NOVA: CORE");
  Serial.print("setup() is running on core ");
  Serial.println(xPortGetCoreID());

  Serial.setDebugOutput(true);

  Serial.println("Setting up Serial2");
  Serial2.begin(921600, SERIAL_8N1, UART2_RX, UART2_TX);

  Serial.println("Pin Directions");
  pinMode(ENABLE_DEVICE_PIN, INPUT_PULLDOWN);

  pinMode(BUTTON_RED_OUT, OUTPUT);
  pinMode(BUTTON_GREEN_OUT, OUTPUT);
  pinMode(BUTTON_BLUE_OUT, OUTPUT);
  pinMode(BUTTON_YELLOW_OUT, OUTPUT);
  pinMode(BUTTON_WHITE_OUT, OUTPUT);

  Serial.println("Set clock of I2C interface to 400khz");
  Wire.begin();
  Wire.setClock(400000UL);

  Serial.println("new NovaIO");
  novaIO = new NovaIO();

  Serial.println("new Simona");
  simona = new Simona();

  Serial.println("new Ambient");
  ambient = new Ambient();

  Serial.println("new Star");
  star = new Star();

  Serial.println("new Buttons");
  buttons = new Buttons();

  Serial.println("Create TaskAmbient");
  xTaskCreate(&TaskAmbient, "TaskAmbient", 8000, NULL, 5, NULL);
  Serial.println("Create TaskAmbient - Done");

  Serial.println("Create TaskModes");
  xTaskCreate(&TaskModes, "TaskModes", 8000, NULL, 5, NULL);
  Serial.println("Create TaskModes - Done");

  Serial.println("Create TaskButtons");
  xTaskCreate(&TaskButtons, "TaskButtons", 8000, NULL, 5, NULL);
  Serial.println("Create TaskButtons - Done");

  Serial.println("Setup Complete");
}

void loop()
{

  /* Best not to have anything in this loop.
      Everything should be in freeRTOS tasks
  */
}

/*--------------------------------------------------*/
/*---------------------- Tasks ---------------------*/
/*--------------------------------------------------*/

void TaskAmbient(void *pvParameters) // This is a task.
{
  (void)pvParameters;

  Serial.println("TaskAmbient is running");
  while (1) // A Task shall never return or exit.
  {
    ambient->loop();
    yield(); // Should't do anything but it's here incase the watchdog needs it.
    delay(10); 
  }
}

void TaskModes(void *pvParameters) // This is a task.
{
  (void)pvParameters;

  Serial.println("TaskModes is running");

  while (1) // A Task shall never return or exit.
  {
    // Serial.println("in TaskModes while");
    if (ambient->isSystemEnabled())
    {

      // simona->loop();
      star->loop();
    }
    else
    {
      Serial.println("system disabled");
      // Don't run the game.
    }
    yield(); // Should't do anything but it's here incase the watchdog needs it.
    delay(10);
    //  Do something
  }
}

void TaskButtons(void *pvParameters) // This is a task.
{
  (void)pvParameters;

  Serial.println("TaskButtons is running");

  while (1) // A Task shall never return or exit.
  {
    buttons->loop();
    yield();
    delay(10);
  }
}
