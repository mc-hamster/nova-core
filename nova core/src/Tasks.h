#ifndef TASKS_H
#define TASKS_H

#include <Arduino.h>

// Task function declarations
void TaskLightUtils(void *pvParameters);
void TaskAmbient(void *pvParameters);
void TaskEnable(void *pvParameters);
void TaskMDNS(void *pvParameters);
void TaskModes(void *pvParameters);
void TaskWeb(void *pvParameters);
void TaskStarSequence(void *pvParameters);
void TaskI2CMonitor(void *pvParameters); // Added I2C monitoring task

void gameTask(void *pvParameters);
void buttonTask(void *pvParameters);

#endif // TASKS_H
