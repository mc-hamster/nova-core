#include "Screen.h"
#include <WiFi.h>
#include <esp_wifi.h>
#include "Tasks.h"
#include "configuration.h"
#include "NovaIO.h"

Screen* screen = nullptr;
extern NovaIO* novaIO;

Screen::Screen() : display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET) {
}

bool Screen::begin() {
    if (xSemaphoreTake(novaIO->mutex_i2c, BLOCK_TIME) != pdTRUE) {
        Serial.println(F("Failed to take I2C mutex for screen initialization"));
        return false;
    }
    
    bool result = false;
    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
        Serial.println(F("SSD1306 allocation failed"));
    } else {
        display.clearDisplay();
        display.setRotation(2);  // Rotate 180 degrees
        
        // Calculate total height of both text elements
        int16_t x1, y1;
        uint16_t w_nova, h_nova, w_core, h_core;
        
        // Get bounds for NOVA text (size 3)
        display.setTextSize(3);
        display.getTextBounds(F("NOVA"), 0, 0, &x1, &y1, &w_nova, &h_nova);
        
        // Get bounds for Core text (size 2)
        display.setTextSize(2);
        display.getTextBounds(F("Core"), 0, 0, &x1, &y1, &w_core, &h_core);
        
        // Calculate spacing between texts
        int16_t spacing = 6;
        int16_t total_height = h_nova + spacing + h_core;
        
        // Calculate starting Y position to center both texts vertically
        int16_t start_y = (SCREEN_HEIGHT - total_height) / 2;
        
        // Display NOVA - centered horizontally
        display.setTextSize(3);
        display.setTextColor(SSD1306_WHITE);
        int16_t nova_x = (SCREEN_WIDTH - w_nova) / 2;
        int16_t nova_y = start_y;
        display.setCursor(nova_x, nova_y);
        display.println(F("NOVA"));
        
        // Display Core - centered horizontally
        display.setTextSize(2);
        int16_t core_x = (SCREEN_WIDTH - w_core) / 2;
        int16_t core_y = nova_y + h_nova + spacing;
        display.setCursor(core_x, core_y);
        display.println(F("Core"));
        
        display.display();
        result = true;
    }
    
    xSemaphoreGive(novaIO->mutex_i2c);
    return result;
}

void Screen::clear() {
    if (xSemaphoreTake(novaIO->mutex_i2c, BLOCK_TIME) == pdTRUE) {
        display.clearDisplay();
        display.display();
        xSemaphoreGive(novaIO->mutex_i2c);
    } else {
        Serial.println(F("Failed to take I2C mutex for screen clear"));
    }
}

void Screen::displayMessage(const char* message) {
    if (xSemaphoreTake(novaIO->mutex_i2c, BLOCK_TIME) == pdTRUE) {
        display.clearDisplay();
        display.setTextSize(1);
        display.setTextColor(SSD1306_WHITE);
        display.setCursor(0, 0);
        display.println(message);
        display.display();
        xSemaphoreGive(novaIO->mutex_i2c);
    } else {
        Serial.println(F("Failed to take I2C mutex for display message"));
    }
}

void Screen::updateNetworkInfo(const String& apIP, const String& clientIP) {
    // Get current MAC address
    String macAddress = WiFi.macAddress();
    
    // Check if any of the network info has changed
    if (macAddress != prevMacAddress || apIP != prevApIP || clientIP != prevClientIP) {
        // Update the stored values
        prevMacAddress = macAddress;
        prevApIP = apIP;
        prevClientIP = clientIP;
        
        // Take the mutex and update the display
        if (xSemaphoreTake(novaIO->mutex_i2c, BLOCK_TIME) == pdTRUE) {
            display.clearDisplay();
            display.setTextSize(1);
            display.setTextColor(SSD1306_WHITE);
            
            // Display MAC Address
            display.setCursor(0, 0);
            display.print(F("MAC "));
            display.println(macAddress);
            
            // Display AP IP
            display.setCursor(0, 10);
            display.print(F("AP "));
            display.println(apIP);
            
            // Display Client IP
            display.setCursor(0, 20);
            display.print(F("IP "));
            display.println(clientIP);
            
            display.display();
            xSemaphoreGive(novaIO->mutex_i2c);
        } else {
            Serial.println(F("Failed to take I2C mutex for network info update"));
        }
    }
}

void TaskScreen(void* pvParameters) {
    UBaseType_t uxHighWaterMark;
    TaskHandle_t xTaskHandle = xTaskGetCurrentTaskHandle();
    const char* pcTaskName = pcTaskGetName(xTaskHandle);
    uint32_t lastExecutionTime = 0;
    
    Serial.println("Screen Task Started");
    
    // Add initial delay to keep NOVA text visible
    vTaskDelay(pdMS_TO_TICKS(5000));
    
    while (1) {
        if (screen != nullptr) {
            IPAddress apIP = WiFi.softAPIP();
            IPAddress clientIP = WiFi.localIP();
            screen->updateNetworkInfo(apIP.toString(), clientIP.toString());
        }

        if (millis() - lastExecutionTime >= REPORT_TASK_INTERVAL) {
            uxHighWaterMark = uxTaskGetStackHighWaterMark(NULL);
            updateTaskStats(pcTaskName, uxHighWaterMark, xPortGetCoreID());
            lastExecutionTime = millis();
        }
        
        vTaskDelay(pdMS_TO_TICKS(250));
    }
}