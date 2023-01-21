#include <Arduino.h>

#include <Thread.h>
#include <ThreadController.h>

#include "configuration.h"

#include "Simona.h"
#include "NovaIO.h"

//    novaIO->digitalWrite(expA, 1, 1);

Thread threadSimona = Thread();
Thread threadAmbient = Thread();

// callback for myThread
void callbackSimona()
{
  Serial.print("callbackSimona! I'm running on: ");
  Serial.println(millis());

  if (!novaIO->mcp_h.digitalRead(BUTTON_GREEN_IN_PIN))
  {
    Serial.println("Button Pressed!");
    digitalWrite(23, true);
    digitalWrite(BUTTON_GREEN_OUT_PIN, true);
    digitalWrite(26, true);
    digitalWrite(27, true);
    digitalWrite(32, true);

    delay(100);
  }
  digitalWrite(23, false);
  digitalWrite(BUTTON_GREEN_OUT_PIN, false);
  digitalWrite(26, false);
  digitalWrite(27, false);
  digitalWrite(32, false);
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
  Serial.begin(921600);
  Serial.print("setup() is running on core ");
  Serial.println(xPortGetCoreID());

  Serial.setDebugOutput(true);

  novaIO = new NovaIO();

  pinMode(ENABLE_DEVICE_PIN, INPUT);

  pinMode(23, OUTPUT);
  pinMode(BUTTON_GREEN_OUT_PIN, OUTPUT);
  pinMode(26, OUTPUT);
  pinMode(27, OUTPUT);
  pinMode(32, OUTPUT);

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
