#include "Tasks.h"
#include "Ambient.h"
#include "LightUtils.h"
#include "Enable.h"
#include "modes/Buttons.h"
#include "output/StarSequence.h"
#include "Web.h"
#include <DNSServer.h>
#include "output/Star.h"

extern Ambient *ambient;
extern LightUtils *lightUtils;
extern Enable *enable;
extern Buttons *buttons;
extern StarSequence *starSequence;
extern DNSServer dnsServer;
extern Star *star;

void TaskAmbient(void *pvParameters) // This is a task.
{
  (void)pvParameters;
  UBaseType_t uxHighWaterMark;
  TaskHandle_t xTaskHandle = xTaskGetCurrentTaskHandle();
  const char *pcTaskName = pcTaskGetName(xTaskHandle);

  Serial.println("TaskAmbient is running");
  while (1) // A Task shall never return or exit.
  {
    ambient->loop();
    delay(1);

    static uint32_t lastExecutionTime = 0;
    if (millis() - lastExecutionTime >= REPORT_TASK_INTERVAL)
    {
      uxHighWaterMark = uxTaskGetStackHighWaterMark(NULL);
      Serial.printf("%s stack free - %d running on core %d\n", pcTaskName, uxHighWaterMark, xPortGetCoreID());
      lastExecutionTime = millis();
    }
  }
}

void TaskLightUtils(void *pvParameters) // This is a task.
{
  (void)pvParameters;
  UBaseType_t uxHighWaterMark;
  TaskHandle_t xTaskHandle = xTaskGetCurrentTaskHandle();
  const char *pcTaskName = pcTaskGetName(xTaskHandle);

  Serial.println("TaskLightUtils is running");
  while (1) // A Task shall never return or exit.
  {
    lightUtils->loop();
    yield();
    delay(10);

    static uint32_t lastExecutionTime = 0;
    if (millis() - lastExecutionTime >= REPORT_TASK_INTERVAL)
    {
      uxHighWaterMark = uxTaskGetStackHighWaterMark(NULL);
      Serial.printf("%s stack free - %d running on core %d\n", pcTaskName, uxHighWaterMark, xPortGetCoreID());
      lastExecutionTime = millis();
    }
  }
}

void TaskEnable(void *pvParameters) // This is a task.
{
  (void)pvParameters;
  UBaseType_t uxHighWaterMark;
  TaskHandle_t xTaskHandle = xTaskGetCurrentTaskHandle();
  const char *pcTaskName = pcTaskGetName(xTaskHandle);

  Serial.println("TaskEnable is running");
  while (1) // A Task shall never return or exit.
  {
    enable->loop();
    yield();
    delay(50);

    static uint32_t lastExecutionTime = 0;
    if (millis() - lastExecutionTime >= REPORT_TASK_INTERVAL)
    {
      uxHighWaterMark = uxTaskGetStackHighWaterMark(NULL);
      Serial.printf("%s stack free - %d running on core %d\n", pcTaskName, uxHighWaterMark, xPortGetCoreID());
      lastExecutionTime = millis();
    }
  }
}

void TaskWeb(void *pvParameters) // This is a task.
{
  (void)pvParameters;
  UBaseType_t uxHighWaterMark;
  TaskHandle_t xTaskHandle = xTaskGetCurrentTaskHandle();
  const char *pcTaskName = pcTaskGetName(xTaskHandle);

  Serial.println("TaskWeb is running");
  while (1) // A Task shall never return or exit.
  {
    webLoop();
    yield();
    delay(1);

    static uint32_t lastExecutionTime = 0;
    if (millis() - lastExecutionTime >= REPORT_TASK_INTERVAL)
    {
      uxHighWaterMark = uxTaskGetStackHighWaterMark(NULL);
      Serial.printf("%s stack free - %d running on core %d\n", pcTaskName, uxHighWaterMark, xPortGetCoreID());
      lastExecutionTime = millis();
    }
  }
}

void TaskMDNS(void *pvParameters) // This is a task.
{
  (void)pvParameters;
  UBaseType_t uxHighWaterMark;
  TaskHandle_t xTaskHandle = xTaskGetCurrentTaskHandle();
  const char *pcTaskName = pcTaskGetName(xTaskHandle);

  Serial.println("TaskMDNS is running");
  while (1) // A Task shall never return or exit.
  {
    dnsServer.processNextRequest();
    yield();
    delay(10);

    static uint32_t lastExecutionTime = 0;
    if (millis() - lastExecutionTime >= REPORT_TASK_INTERVAL)
    {
      uxHighWaterMark = uxTaskGetStackHighWaterMark(NULL);
      Serial.printf("%s stack free - %d running on core %d\n", pcTaskName, uxHighWaterMark, xPortGetCoreID());
      lastExecutionTime = millis();
    }
  }
}

void TaskModes(void *pvParameters) // This is a task.
{
  (void)pvParameters;
  UBaseType_t uxHighWaterMark;
  TaskHandle_t xTaskHandle = xTaskGetCurrentTaskHandle();
  const char *pcTaskName = pcTaskGetName(xTaskHandle);
  Serial.println("TaskModes is running");

  while (1) // A Task shall never return or exit.
  {
    if (enable->isSystemEnabled())
    {
      star->loop();
    }
    else
    {
      Serial.println("system disabled");
      delay(1000);
    }
    yield();
    delay(5);

    static uint32_t lastExecutionTime = 0;
    if (millis() - lastExecutionTime >= REPORT_TASK_INTERVAL)
    {
      uxHighWaterMark = uxTaskGetStackHighWaterMark(NULL);
      Serial.printf("%s stack free - %d running on core %d\n", pcTaskName, uxHighWaterMark, xPortGetCoreID());
      lastExecutionTime = millis();
    }
  }
}

void TaskButtons(void *pvParameters) // This is a task.
{
  (void)pvParameters;
  UBaseType_t uxHighWaterMark;
  TaskHandle_t xTaskHandle = xTaskGetCurrentTaskHandle();
  const char *pcTaskName = pcTaskGetName(xTaskHandle);
  Serial.println("TaskButtons is running");

  while (1) // A Task shall never return or exit.
  {
    if (enable->isSystemEnabled())
    {
      buttons->loop();
      delay(2);
    }
    else
    {
      delay(100);
    }

    static uint32_t lastExecutionTime = 0;
    if (millis() - lastExecutionTime >= REPORT_TASK_INTERVAL)
    {
      uxHighWaterMark = uxTaskGetStackHighWaterMark(NULL);
      Serial.printf("%s stack free - %d running on core %d\n", pcTaskName, uxHighWaterMark, xPortGetCoreID());
      lastExecutionTime = millis();
    }
  }
}

void TaskStarSequence(void *pvParameters) // This is a task.
{
  (void)pvParameters;
  UBaseType_t uxHighWaterMark;
  TaskHandle_t xTaskHandle = xTaskGetCurrentTaskHandle();
  const char *pcTaskName = pcTaskGetName(xTaskHandle);
  Serial.println("TaskStarSequence is running");

  while (1) // A Task shall never return or exit.
  {
    if (enable->isSystemEnabled())
    {
      starSequence->loop();
      delay(2);
    }
    else
    {
      delay(10);
    }

    static uint32_t lastExecutionTime = 0;
    if (millis() - lastExecutionTime >= REPORT_TASK_INTERVAL)
    {
      uxHighWaterMark = uxTaskGetStackHighWaterMark(NULL);
      Serial.printf("%s stack free - %d running on core %d\n", pcTaskName, uxHighWaterMark, xPortGetCoreID());
      lastExecutionTime = millis();
    }
  }
}
