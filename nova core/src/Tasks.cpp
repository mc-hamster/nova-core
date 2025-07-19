#include "Tasks.h"
#include "Ambient.h"
#include "LightUtils.h"
#include "Enable.h"
#include "output/StarSequence.h"
#include "Web.h"
#include <WiFi.h>
#include <WiFiMulti.h>
#include "output/Star.h"
#include "Simona.h"
#include "NovaIO.h"
#include "output/NovaNow.h"
#include <esp_heap_caps.h>

// Using REPORT_TASK_INTERVAL from configuration.h
#define TASK_STALL_TIMEOUT 10000 // Consider a task stalled if no update in 10 seconds

// Declare external WiFiMulti object
extern WiFiMulti wifiMulti;

struct TaskStats
{
    const char *name;
    UBaseType_t stackHighWaterMark;
    UBaseType_t initialStackSize;
    BaseType_t coreId;
    uint32_t lastUpdateTime;
    uint32_t lastCPUMark;  // Time marker for CPU estimation
    uint32_t prevIdleTime; // Previous idle time for CPU estimation
    float cpuUsage;        // CPU usage as percentage
};

#define MAX_MONITORED_TASKS 15
static TaskStats taskStats[MAX_MONITORED_TASKS];
static uint8_t numMonitoredTasks = 0;

void registerTaskForMonitoring(const char *name, UBaseType_t watermark, BaseType_t coreId, UBaseType_t initialStackSize)
{
    if (numMonitoredTasks < MAX_MONITORED_TASKS)
    {
        Serial.printf("Registering task for monitoring: '%s' (Initial Stack: %d bytes)\n", name, initialStackSize);
        taskStats[numMonitoredTasks].name = name;
        taskStats[numMonitoredTasks].stackHighWaterMark = watermark;
        taskStats[numMonitoredTasks].initialStackSize = initialStackSize;
        taskStats[numMonitoredTasks].coreId = coreId;
        taskStats[numMonitoredTasks].lastUpdateTime = millis();
        taskStats[numMonitoredTasks].lastCPUMark = millis();
        taskStats[numMonitoredTasks].prevIdleTime = 0;
        taskStats[numMonitoredTasks].cpuUsage = 0;
        numMonitoredTasks++;
    }
}

void updateTaskStats(const char *name, UBaseType_t watermark, BaseType_t coreId)
{
    for (uint8_t i = 0; i < numMonitoredTasks; i++)
    {
        if (strcmp(taskStats[i].name, name) == 0)
        {
            taskStats[i].stackHighWaterMark = watermark;
            taskStats[i].coreId = coreId;
            taskStats[i].lastUpdateTime = millis();
            return;
        }
    }

    // If task not found, try to determine its initial stack size
    UBaseType_t initialStack = 4096; // Default size
    if (strcmp(name, "TaskWeb") == 0)
        initialStack = 8 * 1024;
    else if (strcmp(name, "TaskStars") == 0)
        initialStack = 6 * 1024;
    else if (strcmp(name, "TaskAmbient") == 0)
        initialStack = 8 * 1024;
    else if (strcmp(name, "LightUtils") == 0)
        initialStack = 3 * 1024;
    else if (strcmp(name, "StarSequence") == 0)
        initialStack = 3 * 1024;
    else if (strcmp(name, "TaskEnable") == 0)
        initialStack = 3 * 1024;
    else if (strcmp(name, "gameTask") == 0)
        initialStack = 8 * 1024;
    else if (strcmp(name, "taskButton") == 0)
        initialStack = 3 * 1024;
    else if (strcmp(name, "I2CMonitor") == 0)
        initialStack = 3 * 1024; // Updated to match new size
    else if (strcmp(name, "NovaNow") == 0)
        initialStack = 4 * 1024;
    else if (strcmp(name, "TaskMonitor") == 0)
        initialStack = 4096;
    else if (strcmp(name, "TaskWiFiConnect") == 0)
        initialStack = 5 * 1024;
    else
    {
        Serial.printf("updateTaskStats: Unknown task '%s' encountered\n", name);
    }

    registerTaskForMonitoring(name, watermark, coreId, initialStack);
}

void TaskMonitor(void *pvParameters)
{
    UBaseType_t uxHighWaterMark;
    TaskHandle_t xTaskHandle = xTaskGetCurrentTaskHandle();
    const char *pcTaskName = pcTaskGetName(xTaskHandle);

    Serial.println("TaskMonitor is running");

    while (1)
    {
        Serial.println("\n=== Task Monitor Report ===");
        Serial.println("Task Name          Stack Size  Free    Used%  Core  Status");
        Serial.println("---------------    ----------  ------  -----  ----  ------");
        uint32_t currentTime = millis();

        // Get heap statistics
        multi_heap_info_t heapInfo;
        heap_caps_get_info(&heapInfo, MALLOC_CAP_DEFAULT);

        for (uint8_t i = 0; i < numMonitoredTasks; i++)
        {
            bool taskStalled = (currentTime - taskStats[i].lastUpdateTime) > TASK_STALL_TIMEOUT;

            // Calculate stack usage percentage
            float stackUsedPercent = 100.0 * ((taskStats[i].initialStackSize - taskStats[i].stackHighWaterMark) / (float)taskStats[i].initialStackSize);

            Serial.printf("%-16s  %6d B   %5d B  %3.0f%%    %d    %s\n",
                          taskStats[i].name,
                          taskStats[i].initialStackSize,
                          taskStats[i].stackHighWaterMark,
                          stackUsedPercent,
                          taskStats[i].coreId,
                          taskStalled ? "STALLED!" : "OK");
        }

        // Print memory statistics
        Serial.println("\n=== Memory Statistics ===");
        Serial.printf("Total Free Heap: %u bytes\n", heap_caps_get_free_size(MALLOC_CAP_DEFAULT));
        Serial.printf("Total Heap Size: %u bytes\n", heap_caps_get_total_size(MALLOC_CAP_DEFAULT));
        Serial.printf("Minimum Free Heap: %u bytes\n", heap_caps_get_minimum_free_size(MALLOC_CAP_DEFAULT));

        // Calculate heap fragmentation as ratio of largest free block to total free heap
        float fragmentation = 100.0f * (1.0f - (float)heapInfo.largest_free_block / heapInfo.total_free_bytes);
        Serial.printf("Heap Fragmentation: %.2f%%\n", fragmentation);

        // Monitor our own stack
        uxHighWaterMark = uxTaskGetStackHighWaterMark(NULL);
        updateTaskStats(pcTaskName, uxHighWaterMark, xPortGetCoreID());

        vTaskDelay(pdMS_TO_TICKS(REPORT_TASK_INTERVAL));
    }
}

extern Ambient *ambient;
extern LightUtils *lightUtils;
extern Enable *enable;
extern StarSequence *starSequence;
extern Star *star;
extern NovaIO *novaIO;

void TaskAmbient(void *pvParameters)
{
    (void)pvParameters;
    UBaseType_t uxHighWaterMark;
    TaskHandle_t xTaskHandle = xTaskGetCurrentTaskHandle();
    const char *pcTaskName = pcTaskGetName(xTaskHandle);
    uint32_t lastExecutionTime = 0;

    Serial.println("TaskAmbient is running");
    while (1)
    {
        ambient->loop();
        vTaskDelay(pdMS_TO_TICKS(2));

        if (millis() - lastExecutionTime >= REPORT_TASK_INTERVAL)
        {
            uxHighWaterMark = uxTaskGetStackHighWaterMark(NULL);
            updateTaskStats(pcTaskName, uxHighWaterMark, xPortGetCoreID());
            lastExecutionTime = millis();
        }
    }
}

void TaskLightUtils(void *pvParameters)
{
    (void)pvParameters;
    UBaseType_t uxHighWaterMark;
    TaskHandle_t xTaskHandle = xTaskGetCurrentTaskHandle();
    const char *pcTaskName = pcTaskGetName(xTaskHandle);
    uint32_t lastExecutionTime = 0;

    Serial.println("TaskLightUtils is running");
    while (1)
    {
        lightUtils->loop();
        vTaskDelay(pdMS_TO_TICKS(3));

        if (millis() - lastExecutionTime >= REPORT_TASK_INTERVAL)
        {
            uxHighWaterMark = uxTaskGetStackHighWaterMark(NULL);
            updateTaskStats(pcTaskName, uxHighWaterMark, xPortGetCoreID());
            lastExecutionTime = millis();
        }
    }
}

void TaskEnable(void *pvParameters)
{
    (void)pvParameters;
    UBaseType_t uxHighWaterMark;
    TaskHandle_t xTaskHandle = xTaskGetCurrentTaskHandle();
    const char *pcTaskName = pcTaskGetName(xTaskHandle);
    uint32_t lastExecutionTime = 0;

    Serial.println("TaskEnable is running");
    while (1)
    {
        enable->loop();
        vTaskDelay(pdMS_TO_TICKS(50));

        if (millis() - lastExecutionTime >= REPORT_TASK_INTERVAL)
        {
            uxHighWaterMark = uxTaskGetStackHighWaterMark(NULL);
            updateTaskStats(pcTaskName, uxHighWaterMark, xPortGetCoreID());
            lastExecutionTime = millis();
        }
    }
}

void TaskWeb(void *pvParameters)
{
    (void)pvParameters;
    UBaseType_t uxHighWaterMark;
    TaskHandle_t xTaskHandle = xTaskGetCurrentTaskHandle();
    const char *pcTaskName = pcTaskGetName(xTaskHandle);
    uint32_t lastExecutionTime = 0;

    // Log the task handle to identify it in memory dumps
    uint32_t taskAddress = (uint32_t)xTaskHandle;
    Serial.printf("TaskWeb is running on core %d with handle 0x%08x\n", xPortGetCoreID(), taskAddress);

    while (1)
    {
        // Check stack watermark before UI operations
        uxHighWaterMark = uxTaskGetStackHighWaterMark(NULL);
        if (uxHighWaterMark < 1000)
        {
            Serial.printf("WARNING: Low stack in TaskWeb before webLoop: %u bytes\n", uxHighWaterMark * 4);
        }

        webLoop();

        // Increased delay to give more time for network stack processing
        vTaskDelay(pdMS_TO_TICKS(20));

        if (millis() - lastExecutionTime >= REPORT_TASK_INTERVAL)
        {
            uxHighWaterMark = uxTaskGetStackHighWaterMark(NULL);
            updateTaskStats(pcTaskName, uxHighWaterMark, xPortGetCoreID());
            lastExecutionTime = millis();
        }
    }
}

void TaskStars(void *pvParameters)
{
    (void)pvParameters;
    UBaseType_t uxHighWaterMark;
    TaskHandle_t xTaskHandle = xTaskGetCurrentTaskHandle();
    const char *pcTaskName = pcTaskGetName(xTaskHandle);
    Serial.println("TaskStars is running");

    // Add counter and timing variables
    uint32_t loopCounter = 0;
    uint32_t lastPrintTime = millis();
    uint32_t delayCounter = 0;
    uint32_t lastExecutionTime = 0;

    while (1)
    {

        if (enable->isSystemEnabled())
        {
            star->loop();
        }
        else
        {
            Serial.println("system disabled - TaskStars");
            delay(1000);
        }

        // Delay once ever 3 loops to allow other tasks to run
        delayCounter++;
        if (delayCounter >= 3)
        {
            delayCounter = 0;
            vTaskDelay(pdMS_TO_TICKS(1));
            // yield();
        }
        else
        {
            yield();
        }

        if (millis() - lastExecutionTime >= REPORT_TASK_INTERVAL)
        {
            uxHighWaterMark = uxTaskGetStackHighWaterMark(NULL);
            updateTaskStats(pcTaskName, uxHighWaterMark, xPortGetCoreID());
            lastExecutionTime = millis();
        }
    }
}

void TaskStarSequence(void *pvParameters)
{
    (void)pvParameters;
    UBaseType_t uxHighWaterMark;
    TaskHandle_t xTaskHandle = xTaskGetCurrentTaskHandle();
    const char *pcTaskName = pcTaskGetName(xTaskHandle);
    Serial.println("TaskStarSequence is running");
    uint32_t lastExecutionTime = 0;

    while (1)
    {
        if (enable->isSystemEnabled())
        {
            starSequence->loop();
            vTaskDelay(pdMS_TO_TICKS(3));
        }
        else
        {
            vTaskDelay(pdMS_TO_TICKS(10));
        }

        if (millis() - lastExecutionTime >= REPORT_TASK_INTERVAL)
        {
            uxHighWaterMark = uxTaskGetStackHighWaterMark(NULL);
            updateTaskStats(pcTaskName, uxHighWaterMark, xPortGetCoreID());
            lastExecutionTime = millis();
        }
    }
}

void TaskWiFiConnection(void *pvParameters)
{
    UBaseType_t uxHighWaterMark;
    TaskHandle_t xTaskHandle = xTaskGetCurrentTaskHandle();
    const char *pcTaskName = pcTaskGetName(xTaskHandle);
    uint32_t lastExecutionTime = 0;

    Serial.println("TaskWiFiConnection is running");

    while (1)
    {
        if (WiFi.status() != WL_CONNECTED)
        {
            Serial.println("WiFi connection lost, attempting to reconnect...");
            if (wifiMulti.run(5000) == WL_CONNECTED)
            {
                Serial.println("WiFi reconnected");
                Serial.print("IP address: ");
                Serial.println(WiFi.localIP());
            }
        }

        if (millis() - lastExecutionTime >= REPORT_TASK_INTERVAL)
        {
            uxHighWaterMark = uxTaskGetStackHighWaterMark(NULL);
            updateTaskStats(pcTaskName, uxHighWaterMark, xPortGetCoreID());
            lastExecutionTime = millis();
        }

        vTaskDelay(pdMS_TO_TICKS(2000)); // Check connection every 2 seconds
    }
}

// Task definitions
void taskSetup()
{
    Serial.println("Create TaskEnable");
    xTaskCreate(&TaskEnable, "TaskEnable", 3 * 1024, NULL, 1, NULL);
    Serial.println("Create TaskEnable - Done");

    Serial.println("Create gameTask");
    xTaskCreate(gameTask, "gameTask", 8 * 1024, NULL, 4, NULL);
    Serial.println("Create gameTask - Done");

    Serial.println("Create taskButton");
    xTaskCreate(taskButton, "taskButton", 3 * 1024, NULL, 3, NULL);
    Serial.println("Create taskButton - Done");

    Serial.println("Create TaskWeb");
    xTaskCreate(&TaskWeb, "TaskWeb", 8 * 1024, NULL, 1, NULL);
    Serial.println("Create TaskWeb - Done");

    Serial.println("Create TaskStars");
    xTaskCreate(&TaskStars, "TaskStars", 6 * 1024, NULL, 4, NULL);
    Serial.println("Create TaskStars - Done");

    Serial.println("Create TaskAmbient");
    xTaskCreate(&TaskAmbient, "TaskAmbient", 8 * 1024, NULL, 4, NULL);
    Serial.println("Create TaskAmbient - Done");

    Serial.println("Create LightUtils");
    xTaskCreate(&TaskLightUtils, "LightUtils", 3 * 1024, NULL, 3, NULL);
    Serial.println("Create LightUtils - Done");

    Serial.println("Create StarSequence");
    xTaskCreate(&TaskStarSequence, "StarSequence", 3 * 1024, NULL, 3, NULL);
    Serial.println("Create StarSequence - Done");

    Serial.println("Create TaskI2CMonitor");
    xTaskCreate(&TaskI2CMonitor, "I2CMonitor", 3 * 1024, NULL, 1, NULL);
    Serial.println("Create TaskI2CMonitor - Done");

    Serial.println("Create TaskNovaNow");
    xTaskCreate(&TaskNovaNow, "NovaNow", 4 * 1024, NULL, 1, NULL);
    Serial.println("Create TaskNovaNow - Done");

    Serial.println("Create TaskMonitor");
    xTaskCreate(&TaskMonitor, "TaskMonitor", 4096, NULL, 1, NULL);
    Serial.println("Create TaskMonitor - Done");

    // Increase WiFi Connection task stack size for better stability
    Serial.println("Create TaskWiFiConnection");
    xTaskCreate(&TaskWiFiConnection, "TaskWiFiConnection", 5 * 1024, NULL, 1, NULL);
    Serial.println("Create TaskWiFiConnection - Done");

    Serial.println("Create TaskScreen");
    xTaskCreate(&TaskScreen, "TaskScreen", 4 * 1024, NULL, 1, NULL);
    Serial.println("Create TaskScreen - Done");
}

void gameTask(void *pvParameters)
{
    UBaseType_t uxHighWaterMark;
    TaskHandle_t xTaskHandle = xTaskGetCurrentTaskHandle();
    const char *pcTaskName = pcTaskGetName(xTaskHandle);
    uint32_t lastExecutionTime = 0; // Moved outside the loop

    Serial.println("Game task is running");

    while (true)
    {
        Simona::getInstance()->runGameTask();
        uint32_t currentTime = millis();
        if (currentTime - lastExecutionTime >= REPORT_TASK_INTERVAL)
        {
            uxHighWaterMark = uxTaskGetStackHighWaterMark(NULL);
            updateTaskStats(pcTaskName, uxHighWaterMark, xPortGetCoreID());
            lastExecutionTime = currentTime;
        }
        vTaskDelay(pdMS_TO_TICKS(5));
    }
}

void taskButton(void *pvParameters)
{
    UBaseType_t uxHighWaterMark;
    TaskHandle_t xTaskHandle = xTaskGetCurrentTaskHandle();
    const char *pcTaskName = pcTaskGetName(xTaskHandle);
    uint32_t lastExecutionTime = 0; // Moved outside the loop

    Serial.println("Button task is running");

    while (true)
    {
        Simona::getInstance()->runTaskButton();
        uint32_t currentTime = millis();
        if (currentTime - lastExecutionTime >= REPORT_TASK_INTERVAL)
        {
            uxHighWaterMark = uxTaskGetStackHighWaterMark(NULL);
            updateTaskStats(pcTaskName, uxHighWaterMark, xPortGetCoreID());
            lastExecutionTime = currentTime;
        }
        vTaskDelay(pdMS_TO_TICKS(20));
    }
}

void TaskI2CMonitor(void *pvParameters)
{
    UBaseType_t uxHighWaterMark;
    TaskHandle_t xTaskHandle = xTaskGetCurrentTaskHandle();
    const char *pcTaskName = pcTaskGetName(xTaskHandle);
    uint32_t lastExecutionTime = 0;

    Serial.println("TaskI2CMonitor is running");
    while (1)
    {
        novaIO->updateI2CStats();

        // I2C Bus Statistics
        float utilization = novaIO->getI2CUtilization();
        Serial.println("\n=== I2C Health Report ===");
        Serial.printf("I2C Bus Utilization: %.2f%%\n", utilization);

        // Cache Performance
        float cacheHitRatio = novaIO->getCacheHitRatio();
        Serial.printf("Cache Hit Ratio: %.2f%%\n", cacheHitRatio * 100.0f);

        // Operation Timing
        float avgOpTime = novaIO->getAverageOperationTime();
        Serial.printf("Average Operation Time: %.2fms\n", avgOpTime);

        // Error Statistics
        Serial.printf("Total Transaction Errors: %lu\n", novaIO->getTransactionErrors());
        Serial.printf("Mutex Contentions: %lu\n", novaIO->getMutexContentionCount());

        // Consecutive Errors Per Expander
        Serial.println("\nExpander Error Status:");
        for (uint8_t i = 0; i < 8; i++)
        {
            unsigned long errors = novaIO->getConsecutiveErrors(i);
            if (errors > 0)
            {
                Serial.printf("  Expander %d: %lu consecutive errors\n", i, errors);
            }
        }

        // Health Assessment
        Serial.println("\nHealth Assessment:");
        if (utilization > 80.0f)
        {
            Serial.println("  [WARNING] High I2C bus utilization");
        }
        if (cacheHitRatio < 0.5f)
        {
            Serial.println("  [WARNING] Low cache hit ratio");
        }
        if (avgOpTime > 10.0f)
        {
            Serial.println("  [WARNING] High average operation time");
        }
        for (uint8_t i = 0; i < 8; i++)
        {
            if (novaIO->getConsecutiveErrors(i) > 5)
            {
                Serial.printf("  [CRITICAL] Expander %d showing repeated failures\n", i);
            }
        }
        Serial.println("=====================\n");

        if (millis() - lastExecutionTime >= REPORT_TASK_INTERVAL)
        {
            uxHighWaterMark = uxTaskGetStackHighWaterMark(NULL);
            updateTaskStats(pcTaskName, uxHighWaterMark, xPortGetCoreID());
            lastExecutionTime = millis();
        }

        // Run health check every 2 minutes
        vTaskDelay(pdMS_TO_TICKS(120000));
    }
}

void TaskNovaNow(void *pvParameters)
{
    UBaseType_t uxHighWaterMark;
    TaskHandle_t xTaskHandle = xTaskGetCurrentTaskHandle();
    const char *pcTaskName = pcTaskGetName(xTaskHandle);
    uint32_t lastExecutionTime = 0;

    Serial.println("TaskNovaNow is running");

    while (1)
    {
        novaNowLoop();
        vTaskDelay(pdMS_TO_TICKS(5));

        if (millis() - lastExecutionTime >= REPORT_TASK_INTERVAL)
        {
            uxHighWaterMark = uxTaskGetStackHighWaterMark(NULL);
            updateTaskStats(pcTaskName, uxHighWaterMark, xPortGetCoreID());
            lastExecutionTime = millis();
        }
    }
}