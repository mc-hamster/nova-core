#include <Arduino.h>
#include "main.h"
#include "configuration.h"
#include "NovaNet.h"
#include "NovaIO.h"
#include "DmxNet.h"
#include "globals.h"
#include "FogMachine.h"

void TaskNovaNet(void *pvParameters);
void TaskDmxNet(void *pvParameters);
void TaskFogMachine(void *pvParameters);


void setup()
{
  Serial.begin(921600);
  delay(500); // Give time for the serial monitor to connect
  Serial.println("NOVA: STARBASE");

  pinMode(BLOWER_DUTY_PIN, OUTPUT);

  Serial.println("Setting up Serial2");
  Serial2.begin(921600, SERIAL_8N1, UART2_RX, UART2_TX);

  Serial.println("Set clock of I2C interface to 400khz");
  Wire.begin();
  Wire.setClock(400000UL);

  Serial.println("new NovaIO");
  novaIO = new NovaIO();

  uint8_t blowerDuty = 255;
  float blowerVolt = ((blowerDuty / 255.0) * 24.0);

  Serial.print("Blower: Setting up Blower Duty Pin (Max is 255) @ ");
  Serial.print(blowerDuty);
  Serial.print(" or  ");
  Serial.print(blowerVolt);
  Serial.println(" volts DC");

  Serial.println("new NovaNet");
  novaNet = new NovaNet();

  Serial.println("new DmxNet");
  dmxNet = new DmxNet();

  Serial.println("new FogMachine");
  fogMachine = new FogMachine();

  analogWrite(BLOWER_DUTY_PIN, blowerDuty); // Note: Best not to use blower below ~130 (~12.2v)

  Serial.println("DMX: Setting Pin States.");
  novaIO->mcp_a.pinMode(DMX_DE, OUTPUT);
  novaIO->mcp_a.pinMode(DMX_RE, OUTPUT);

  novaIO->mcpA_digitalWrite(DMX_DE, HIGH);
  novaIO->mcpA_digitalWrite(DMX_RE, HIGH);

  Serial.println("Fog Machine: Setting Pin States.");

  novaIO->mcp_a.pinMode(FOG_STATUS, INPUT);
  novaIO->mcp_a.pinMode(FOG_POWER, OUTPUT);
  novaIO->mcp_a.pinMode(FOG_ACTIVATE, OUTPUT);

  Serial.println("Fog Machine: Turning on power to the Fog Machine.");
  novaIO->mcp_a.digitalWrite(FOG_POWER, HIGH);

  Serial.println("Fog Machine: Ensuring the machine is not currently active.");
  novaIO->mcp_a.digitalWrite(FOG_ACTIVATE, LOW);

  Serial.println("Create TaskNovaNet");
  xTaskCreate(&TaskNovaNet, "TaskNovaNet", 6 * 1024, NULL, 6, NULL);
  Serial.println("Create TaskNovaNet - Done");

  Serial.println("Create TaskDmxNet");
  xTaskCreate(&TaskDmxNet, "TaskDmxNet", 6 * 1024, NULL, 5, NULL);
  Serial.println("Create TaskDmxNet - Done");

  Serial.println("Create TaskFogMachine");
  xTaskCreate(&TaskFogMachine, "TaskFogMachine", 6 * 1024, NULL, 4, NULL);
  Serial.println("Create TaskFogMachine - Done");

  
}

void loop()
{
  /* Best not to have anything in this loop.
    Everything should be in freeRTOS tasks
  */
}

void TaskNovaNet(void *pvParameters) // This is a task.
{
  (void)pvParameters;

  Serial.println("TaskNovaNet is running");
  while (1) // A Task shall never return or exit.
  {
    novaNet->loop();
    // yield(); // Should't do anything but it's here incase the watchdog needs it.
    delayMicroseconds(250);
  }
}

void TaskDmxNet(void *pvParameters) // This is a task.
{
  (void)pvParameters;

  Serial.println("TaskDmxNet is running");
  while (1) // A Task shall never return or exit.
  {
    dmxNet->loop();
    // yield(); // Should't do anything but it's here incase the watchdog needs it.
    delay(1);
  }
}

void TaskFogMachine(void *pvParameters) // This is a task.
{
  (void)pvParameters;

  Serial.println("TaskFogMachine is running");
  while (1) // A Task shall never return or exit.
  {
    fogMachine->loop();
    // yield(); // Should't do anything but it's here incase the watchdog needs it.
    delay(10);
  }
}
