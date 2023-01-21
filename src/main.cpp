#include <Arduino.h>

#include <Thread.h>
#include <ThreadController.h>
#include <Wire.h>

#include "configuration.h"

#include "Simona.h"
#include "NovaIO.h"

//    novaIO->digitalWrite(expA, 1, 1);

Thread threadSimona = Thread();
Thread threadAmbient = Thread();

// callback for myThread
void callbackSimona()
{
  // Serial.print("callbackSimona! I'm running on: ");
  // Serial.println(millis());
  // Serial.println("Button Pressed!");

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

// callback for myThread
void callbackAmbient()
{
  if (digitalRead(ENABLE_DEVICE_PIN))
  {
    delay(10);

    novaIO->mcp_a.writeGPIOAB(0b1111111111111111);
    novaIO->mcp_b.writeGPIOAB(0b1111111111111111);
    novaIO->mcp_c.writeGPIOAB(0b1111111111111111);
    novaIO->mcp_d.writeGPIOAB(0b1111111111111111);
    novaIO->mcp_e.writeGPIOAB(0b1111111111111111);

    delay(10);

    novaIO->mcp_a.writeGPIOAB(0b0000000000000000);
    novaIO->mcp_b.writeGPIOAB(0b0000000000000000);
    novaIO->mcp_c.writeGPIOAB(0b0000000000000000);
    novaIO->mcp_d.writeGPIOAB(0b0000000000000000);
    novaIO->mcp_e.writeGPIOAB(0b0000000000000000);
  }
  else
  {
    novaIO->mcp_a.writeGPIOAB(0b0000000000000000);
    novaIO->mcp_b.writeGPIOAB(0b0000000000000000);
    novaIO->mcp_c.writeGPIOAB(0b0000000000000000);
    novaIO->mcp_d.writeGPIOAB(0b0000000000000000);
    novaIO->mcp_e.writeGPIOAB(0b0000000000000000);
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

  novaIO = new NovaIO();

  pinMode(ENABLE_DEVICE_PIN, INPUT);

  pinMode(BUTTON_RED_OUT, OUTPUT);
  pinMode(BUTTON_GREEN_OUT, OUTPUT);
  pinMode(BUTTON_BLUE_OUT, OUTPUT);
  pinMode(BUTTON_YELLOW_OUT, OUTPUT);
  pinMode(BUTTON_WHITE_OUT, OUTPUT);

  threadSimona.onRun(callbackSimona);
  threadSimona.setInterval(10);

  threadAmbient.onRun(callbackAmbient);
  threadAmbient.setInterval(500);
}

void loop()
{

  if (threadSimona.shouldRun())
    threadSimona.run();

  if (threadAmbient.shouldRun())
    threadAmbient.run();
}
