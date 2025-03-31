#include "Screen.h"
#include <WiFi.h>
#include <esp_wifi.h>
#include "Tasks.h"
#include "configuration.h"

Screen* screen = nullptr;

Screen::Screen() : display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET) {
}

bool Screen::begin() {
    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
        Serial.println(F("SSD1306 allocation failed"));
        return false;
    }
    
    display.clearDisplay();
    display.setRotation(2);  // Rotate 180 degrees
    
    // Display NOVA - text size 3 means each character is 6*3=18 pixels wide
    display.setTextSize(3);
    display.setTextColor(SSD1306_WHITE);
    int16_t x1, y1;
    uint16_t w, h;
    display.getTextBounds(F("NOVA"), 0, 0, &x1, &y1, &w, &h);
    int16_t nova_x = (SCREEN_WIDTH - w) / 2;
    int16_t nova_y = (SCREEN_HEIGHT - h) / 2 - 4;  // Shift up slightly to make room for "Core"
    display.setCursor(nova_x, nova_y);
    display.println(F("NOVA"));
    
    // Display Core - increased text size
    display.setTextSize(2);
    display.getTextBounds(F("Core"), 0, 0, &x1, &y1, &w, &h);
    int16_t core_x = (SCREEN_WIDTH - w) / 2;
    int16_t core_y = nova_y + h + 12;
    display.setCursor(core_x, core_y);
    display.println(F("Core"));
    
    display.display();
    return true;
}

void Screen::clear() {
    display.clearDisplay();
    display.display();
}

void Screen::displayMessage(const char* message) {
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.println(message);
    display.display();
}

void Screen::updateNetworkInfo(const String& apIP, const String& clientIP) {
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    
    // Display MAC Address
    display.setCursor(0, 0);
    display.print(F("MAC "));
    display.println(WiFi.macAddress());
    
    // Display AP IP
    display.setCursor(0, 10);
    display.print(F("AP "));
    display.println(apIP);
    
    // Display Client IP
    display.setCursor(0, 20);
    display.print(F("IP "));
    display.println(clientIP);
    
    display.display();
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
        
        vTaskDelay(pdMS_TO_TICKS(5000));
    }
}