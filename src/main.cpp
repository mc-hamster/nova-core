#include <Arduino.h>
// #include <Thread.h>
// #include <ThreadController.h>
#include <Wire.h>
#include <WiFi.h>
#include <LittleFS.h>
#include "FS.h"

#include "OneButton.h"

#include <DNSServer.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include "ESPAsyncWebServer.h"
#include <ESPUI.h>

#include "configuration.h"
#include "modes/Simona.h"
#include "NovaIO.h"
#include "main.h"
#include "Enable.h"
#include "Ambient.h"
#include "LightUtils.h"
#include "output/Star.h"
#include "Buttons.h"
#include "Web.h"
#include "PersistenceManager.h"
#include "fileSystemHelper.h"
#include "Ambient.h"

#define FORMAT_LITTLEFS_IF_FAILED true

#define CONFIG_FILE "/config.json"

PersistenceManager persistenceManager(CONFIG_FILE);


void TaskLightUtils(void *pvParameters);
void TaskAmbient(void *pvParameters);
void TaskEnable(void *pvParameters);
void TaskMDNS(void *pvParameters);
void TaskModes(void *pvParameters);
void TaskButtons(void *pvParameters);
void TaskWeb(void *pvParameters);

DNSServer dnsServer;
AsyncWebServer webServer(80);

void setup()
{
  delay(500);
  Serial.begin(921600);
  Serial.println("NOVA: CORE");
  Serial.print("setup() is running on core ");
  Serial.println(xPortGetCoreID());

  Serial.setDebugOutput(true);

  if (!LittleFS.begin(FORMAT_LITTLEFS_IF_FAILED))
  {
    Serial.println("LITTLEFS Mount Failed");
    return;
  }
  else
  {
    Serial.println("LITTLEFS Mount Success");

    listDir(LittleFS, "/", 0);
  }

  persistenceManager.begin();

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

  Serial.println("new Enable");
  enable = new Enable();

  Serial.println("new Star");
  star = new Star();

  Serial.println("new Ambient");
  ambient = new Ambient();

  Serial.println("new LightUtils");
  lightUtils = new LightUtils();

  Serial.println("new Buttons");
  buttons = new Buttons();

  // your other setup stuff...
  WiFi.softAP("NOVA", "scubadandy");
  WiFi.setSleep(false); // Disable power saving on the wifi interface.

  dnsServer.start(53, "*", WiFi.softAPIP());
  // webServer.addHandler(new CaptiveRequestHandler()).setFilter(ON_AP_FILTER); // only when requested from AP
  //  more handlers...
  //  webServer.begin();

  Serial.println("Setting up Webserver");
  webSetup();
  Serial.println("Setting up Webserver - Done");

  Serial.println("Create TaskEnable");
  xTaskCreate(&TaskEnable, "TaskEnable", 2048, NULL, 5, NULL);
  Serial.println("Create TaskEnable - Done");

  Serial.println("Create TaskWeb");
  xTaskCreate(&TaskWeb, "TaskWeb", 4096, NULL, 5, NULL);
  Serial.println("Create TaskWeb - Done");

  Serial.println("Create TaskModes");
  xTaskCreate(&TaskModes, "TaskModes", 4096, NULL, 5, NULL);
  Serial.println("Create TaskModes - Done");

  Serial.println("Create TaskButtons");
  xTaskCreate(&TaskButtons, "TaskButtons", 4096, NULL, 5, NULL);
  Serial.println("Create TaskButtons - Done");

  Serial.println("Create TaskMDNS");
  xTaskCreate(&TaskMDNS, "TaskMDNS", 4098, NULL, 5, NULL);
  Serial.println("Create TaskMDNS - Done");

  Serial.println("Create TaskAmbient");
  xTaskCreate(&TaskAmbient, "TaskAmbient", 6 * 1024, NULL, 5, NULL);
  Serial.println("Create TaskAmbient - Done");

  Serial.println("Create LightUtils");
  xTaskCreate(&TaskLightUtils, "LightUtils", 6 * 4096, NULL, 5, NULL);
  Serial.println("Create LightUtils - Done");

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
  UBaseType_t uxHighWaterMark;

  Serial.println("TaskAmbient is running");
  while (1) // A Task shall never return or exit.
  {
    ambient->loop();
    yield(); // Should't do anything but it's here incase the watchdog needs it.
    delay(1);

    // Set this to 'true' to print stack high watermark
    if (0)
    {
      /* Calling the function will have used some stack space, we would
          therefore now expect uxTaskGetStackHighWaterMark() to return a
          value lower than when it was called on entering the task. */
      uxHighWaterMark = uxTaskGetStackHighWaterMark(NULL);
      Serial.print("TaskAmbient stack free - ");
      Serial.println(uxHighWaterMark);
    }
  }
}

void TaskLightUtils(void *pvParameters) // This is a task.
{
  (void)pvParameters;
  UBaseType_t uxHighWaterMark;

  Serial.println("TaskLightUtils is running");
  while (1) // A Task shall never return or exit.
  {
    lightUtils->loop();
    yield(); // Should't do anything but it's here incase the watchdog needs it.
    yield(); // Should't do anything but it's here incase the watchdog needs it.
    //delay(1);

    // Set this to 'true' to print stack high watermark
    if (0)
    {
      /* Calling the function will have used some stack space, we would
          therefore now expect uxTaskGetStackHighWaterMark() to return a
          value lower than when it was called on entering the task. */
      uxHighWaterMark = uxTaskGetStackHighWaterMark(NULL);
      Serial.print("TaskLightUtils stack free - ");
      Serial.println(uxHighWaterMark);
    }
  }
}


void TaskEnable(void *pvParameters) // This is a task.
{
  (void)pvParameters;

  Serial.println("TaskEnable is running");
  while (1) // A Task shall never return or exit.
  {
    enable->loop();
    yield(); // Should't do anything but it's here incase the watchdog needs it.
    delay(5);
  }
}

void TaskWeb(void *pvParameters) // This is a task.
{
  (void)pvParameters;

  Serial.println("TaskWeb is running");
  while (1) // A Task shall never return or exit.
  {
    webLoop();
    yield(); // Should't do anything but it's here incase the watchdog needs it.
    delay(5);
  }
}

void TaskMDNS(void *pvParameters) // This is a task.
{
  (void)pvParameters;

  Serial.println("TaskMDNS is running");
  while (1) // A Task shall never return or exit.
  {
    dnsServer.processNextRequest();
    yield(); // Should't do anything but it's here incase the watchdog needs it.
    delay(5);
  }
}

void TaskModes(void *pvParameters) // This is a task.
{
  (void)pvParameters;

  Serial.println("TaskModes is running");

  while (1) // A Task shall never return or exit.
  {
    // Serial.println("in TaskModes while");
    if (enable->isSystemEnabled())
    {

      // simona->loop();
      star->loop();
    }
    else
    {
      Serial.println("system disabled");
      delay(1000);
      // Don't run the game.
    }
    yield(); // Should't do anything but it's here incase the watchdog needs it.
    delay(5);
    //  Do something
  }
}

void TaskButtons(void *pvParameters) // This is a task.
{
  (void)pvParameters;

  Serial.println("TaskButtons is running");

  while (1) // A Task shall never return or exit.
  {
    if (enable->isSystemEnabled())
    {
      buttons->loop();
      yield(); // Should't do anything but it's here incase the watchdog needs it.
      delay(5);
    }
    else
    {
      // If system is disabled, wait a long time before checking buttons again.
      delay(100);
    }
  }
}
