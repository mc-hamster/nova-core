#include <Arduino.h>

#include <Thread.h>
#include <ThreadController.h>
#include <Wire.h>

#include "configuration.h"

#include "modes/Simona.h"
#include "NovaIO.h"
#include "main.h"
#include "Ambient.h"

#include "output/Star.h"

Thread threadSimona = Thread();

void TaskAmbient(void *pvParameters);
void TaskModes(void *pvParameters);
void Task3(void *pvParameters);

void setup()
{
  delay(1000);
  Serial.begin(921600);
  Serial.println("NOVA: CORE");
  Serial.print("setup() is running on core ");
  Serial.println(xPortGetCoreID());

  Serial.setDebugOutput(true);

  Serial2.begin(921600, SERIAL_8N1, UART2_RX, UART2_TX);

  Wire.begin();
  Wire.setClock(400000UL);

  Serial.println("new NovaIO");
  novaIO = new NovaIO();

  Serial.println("new Simona");
  simona = new Simona();

  Serial.println("new Ambient");
  ambient = new Ambient();

  pinMode(ENABLE_DEVICE_PIN, INPUT_PULLDOWN);

  pinMode(BUTTON_RED_OUT, OUTPUT);
  pinMode(BUTTON_GREEN_OUT, OUTPUT);
  pinMode(BUTTON_BLUE_OUT, OUTPUT);
  pinMode(BUTTON_YELLOW_OUT, OUTPUT);
  pinMode(BUTTON_WHITE_OUT, OUTPUT);

  /*
    Priorities:
      0 = Lowest
      configMAX_PRIORITIES = highest
  */
  Serial.println("Create TaskAmbient");
  xTaskCreate(&TaskAmbient, "TaskAmbient", 2048, NULL, 5, NULL);

  Serial.println("Create TaskModes");
  xTaskCreate(&TaskModes, "TasTaskModes", 2048, NULL, 5, NULL);

  /*
    Serial.println("Create Task3");
    xTaskCreate(
        Task3, "Task3" // A name just for humans
        ,
        1024 // This stack size can be checked & adjusted by reading the Stack Highwater
        ,
        NULL, 2 // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
        ,
        NULL);

        */
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
    // delay(50);
  }
}

void TaskModes(void *pvParameters) // This is a task.
{
  (void)pvParameters;
  Serial.println("TaskSimona is running");

  while (1) // A Task shall never return or exit.
  {
    // Serial.println("in TaskSimona while");
    if (ambient->isSystemEnabled())
    {

      simona->loop();
    }
    else
    {
      Serial.println("system disabled");
      // Don't run the game.
    }
    // Serial.println("in TaskSimona while 2");
    yield(); // Should't do anything but it's here incase the watchdog needs it.
    delay(10);
    //  Do something
  }
}

void Task3(void *pvParameters) // This is a task.
{
  (void)pvParameters;
  Serial.println("Task3 is running");

  while (1) // A Task shall never return or exit.
  {
    delay(10);
    // Do something
  }
}