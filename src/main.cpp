#include <Arduino.h>
#include "configuration.h"

#include "Simona.h"
#include "NovaIO.h"

// SKETCH BEGIN
TaskHandle_t Task1;
TaskHandle_t Task2;

#define BUTTON_GREEN_PIN 9

void Task1code(void *parameter)
{
  Serial.print("Task1 is running on core ");
  Serial.println(xPortGetCoreID());
  for (;;)
  {
    // Task shall never exit
    novaIO->digitalWrite(expA, 1, 1);
  }

    //uint8_t i;

    /*
        for (i = 0; i <= 1; ++i)
        {
          mcp_a.writeGPIOAB(0b0000000000000001);
          delay(100);
          mcp_a.writeGPIOAB(0b0000000000000000);
          delay(100);

          mcp_a.writeGPIOAB(0b0000000000000010);
          delay(100);
          mcp_a.writeGPIOAB(0b0000000000000000);
          delay(100);

          mcp_a.writeGPIOAB(0b0000000000000100);
          delay(100);
          mcp_a.writeGPIOAB(0b0000000000000000);
          delay(100);

          mcp_a.writeGPIOAB(0b0000000000001000);
          delay(100);
          mcp_a.writeGPIOAB(0b0000000000000000);
          delay(100);

          mcp_a.writeGPIOAB(0b0000000000010000);
          delay(100);
          mcp_a.writeGPIOAB(0b0000000000000000);
          delay(100);

          mcp_a.writeGPIOAB(0b0000000000100000);
          delay(100);
          mcp_a.writeGPIOAB(0b0000000000000000);
          delay(100);
        }
    */
    /*
        Serial.println("mcp_a");
        for (i = 0; i <= 15; ++i)
        {
          mcp_a.digitalWrite(i, HIGH);
          delay(100);
          mcp_a.digitalWrite(i, LOW);
          delay(100);
        }


        Serial.println("mcp_b");
        for (i = 0; i <= 15; ++i)
        {
          mcp_b.digitalWrite(i, HIGH);
          delay(100);
          mcp_b.digitalWrite(i, LOW);
          delay(100);
        }

        Serial.println("mcp_c");
        for (i = 0; i <= 15; ++i)
        {
          mcp_c.digitalWrite(i, HIGH);
          delay(100);
          mcp_c.digitalWrite(i, LOW);
          delay(100);
        }

        Serial.println("mcp_d");
        for (i = 0; i <= 15; ++i)
        {
          mcp_d.digitalWrite(i, HIGH);
          delay(100);
          mcp_d.digitalWrite(i, LOW);
          delay(100);
        }
        Serial.println("mcp_e");
        for (i = 0; i <= 15; ++i)
        {
          mcp_e.digitalWrite(i, HIGH);
          delay(100);
          mcp_e.digitalWrite(i, LOW);
          delay(100);
        }

    */
}

void Task2code(void *parameter)
{
  Serial.print("Task2 is running on core ");
  Serial.println(xPortGetCoreID());
  for (;;)
  {
    /*
    digitalWrite(led_2, HIGH);
    delay(1000);
    digitalWrite(led_2, LOW);
    delay(1000);
    */
  }
}

void setup()
{
  Serial.begin(921600);
  Serial.print("setup() is running on core ");
  Serial.println(xPortGetCoreID());

  Serial.setDebugOutput(true);

  novaIO = new NovaIO();

  pinMode(BUTTON_GREEN_LED, OUTPUT);

  Serial.println("MCP23xxx Blink Test!");

  /*
      core1 - main program code
      core0 - esp32 network stack
  */
  xTaskCreatePinnedToCore(Task1code, "Task1", 10000, NULL, 1, &Task1, 0);
  delay(500);
  xTaskCreatePinnedToCore(Task2code, "Task2", 10000, NULL, 1, &Task2, 1);
  delay(500);
}

void loop()
{
  // Serial.print("loop() is running on core ");
  //  Serial.println(xPortGetCoreID());
  if (novaIO->digitalRead(expH, BUTTON_GREEN_PIN))
  {
    Serial.println("Button Pressed!");
    //digitalWrite(BUTTON_GREEN_LED, true);
    delay(100);
    //digitalWrite(BUTTON_GREEN_LED, false);
  }
/*
*/
}
