#include <Arduino.h>

#include <Thread.h>
#include <ThreadController.h>
#include <Wire.h>

#include "configuration.h"

#include "Simona.h"
#include "NovaIO.h"
#include "main.h"

Thread threadSimona = Thread();

void TaskAmbient(void *pvParameters);
void TaskSimona(void *pvParameters);
void Task3(void *pvParameters);

// callback for myThread
void callbackSimona()
{
  // Serial.print("callbackSimona! I'm running on: ");
  // Serial.println(millis());
  // Serial.println("Button Pressed!");

  simona->loop();

  return;
  if (!novaIO->mcp_h.digitalRead(BUTTON_RED_IN))
  {
    digitalWrite(BUTTON_RED_OUT, true);
    delay(100);
  }
  else
  {
    digitalWrite(BUTTON_RED_OUT, false);
  }

  if (!novaIO->mcp_h.digitalRead(BUTTON_GREEN_IN))
  {
    digitalWrite(BUTTON_GREEN_OUT, true);
    delay(100);
  }
  else
  {
    digitalWrite(BUTTON_GREEN_OUT, false);
  }

  if (!novaIO->mcp_h.digitalRead(BUTTON_BLUE_IN))
  {
    digitalWrite(BUTTON_BLUE_OUT, true);
    delay(100);
  }
  else
  {
    digitalWrite(BUTTON_BLUE_OUT, false);
  }

  if (!novaIO->mcp_h.digitalRead(BUTTON_YELLOW_IN))
  {
    digitalWrite(BUTTON_YELLOW_OUT, true);
    delay(100);
  }
  else
  {
    digitalWrite(BUTTON_YELLOW_OUT, false);
  }

  if (!novaIO->mcp_h.digitalRead(BUTTON_WHITE_IN))
  {
    digitalWrite(BUTTON_WHITE_OUT, true);
    delay(100);
  }
  else
  {
    digitalWrite(BUTTON_WHITE_OUT, false);
  }
}

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

  pinMode(ENABLE_DEVICE_PIN, INPUT_PULLDOWN);

  pinMode(BUTTON_RED_OUT, OUTPUT);
  pinMode(BUTTON_GREEN_OUT, OUTPUT);
  pinMode(BUTTON_BLUE_OUT, OUTPUT);
  pinMode(BUTTON_YELLOW_OUT, OUTPUT);
  pinMode(BUTTON_WHITE_OUT, OUTPUT);

  // threadSimona.onRun(callbackSimona);
  // threadSimona.setInterval(10);

  /*
    Priorities:
      0 = Lowest
      configMAX_PRIORITIES = highest
  */
  Serial.println("Create TaskAmbient");
  xTaskCreate(&TaskAmbient, "TaskAmbient", 2048, NULL, 5, NULL);

  Serial.println("Create TaskSimona");
  xTaskCreate(&TaskSimona, "TasTaskSimonak2", 2048, NULL, 5, NULL);

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
    if (digitalRead(ENABLE_DEVICE_PIN))
    {
      novaIO->mcpA_writeGPIOAB(0b1111111111111111);
      novaIO->mcpB_writeGPIOAB(0b1111111111111111);
      novaIO->mcpC_writeGPIOAB(0b1111111111111111);
      novaIO->mcpD_writeGPIOAB(0b1111111111111111);
      novaIO->mcpE_writeGPIOAB(0b1111111111111111);
    delay(100);

      novaIO->mcpA_writeGPIOAB(0b0000000000000000);
      novaIO->mcpB_writeGPIOAB(0b0000000000000000);
      novaIO->mcpC_writeGPIOAB(0b0000000000000000);
      novaIO->mcpD_writeGPIOAB(0b0000000000000000);
      novaIO->mcpE_writeGPIOAB(0b0000000000000000);
    }
    else
    {
      novaIO->mcpA_writeGPIOAB(0b0000000000000000);
      novaIO->mcpB_writeGPIOAB(0b0000000000000000);
      novaIO->mcpC_writeGPIOAB(0b0000000000000000);
      novaIO->mcpD_writeGPIOAB(0b0000000000000000);
      novaIO->mcpE_writeGPIOAB(0b0000000000000000);
    }

    yield(); // Should't do anything but it's here incase the watchdog needs it.
    delay(100);
  }
}

void TaskSimona(void *pvParameters) // This is a task.
{
  (void)pvParameters;
  Serial.println("TaskSimona is running");

  while (1) // A Task shall never return or exit.
  {
    Serial.println("in TaskSimona while");
    simona->loop();
    Serial.println("in TaskSimona while 2");
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