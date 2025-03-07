#ifndef TASKS_H
#define TASKS_H

#include <Arduino.h>

// Task function declarations
void TaskLightUtils(void *pvParameters);
void TaskAmbient(void *pvParameters);
void TaskEnable(void *pvParameters);
void TaskMDNS(void *pvParameters);
void TaskModes(void *pvParameters);
void TaskButtons(void *pvParameters);
void TaskWeb(void *pvParameters);
void TaskStarSequence(void *pvParameters);

void gameTask(void *pvParameters);
void buttonTask(void *pvParameters);

#endif // TASKS_H
