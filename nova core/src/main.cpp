#include <Arduino.h>
#include <Wire.h>
#include <WiFi.h>
#include <WiFiMulti.h>
#include <LittleFS.h>
#include "FS.h"

// #include "OneButton.h"

#include <DNSServer.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include "ESPAsyncWebServer.h"
#include <ESPUI.h>

#include "configuration.h"
#include "NovaIO.h"
#include "main.h"
#include "Enable.h"
#include "Ambient.h"
#include "LightUtils.h"
#include "output/Star.h"
#include "output/StarSequence.h"
#include "output/NovaNow.h" // Updated path
#include "Web.h"
#include "utilities/PreferencesManager.h"
#include "fileSystemHelper.h"
#include "Ambient.h"
#include "Tasks.h"
#include "utilities/utilities.h"

#include "Simona.h"
#include "midi/MIDIControl.hpp" // Updated path to MIDI module
#include <MIDI.h>
#include "wifi_config.h"

#define FORMAT_LITTLEFS_IF_FAILED true

#define CONFIG_FILE "/config.json"

uint8_t buttons[4] = {BUTTON_RED_IN, BUTTON_GREEN_IN, BUTTON_BLUE_IN, BUTTON_YELLOW_IN};
uint8_t leds[4] = {BUTTON_RED_OUT, BUTTON_GREEN_OUT, BUTTON_BLUE_OUT, BUTTON_YELLOW_OUT};
const char *buttonColors[4] = {"RED", "GREEN", "BLUE", "YELLOW"};
const char *ledColors[4] = {"RED", "GREEN", "BLUE", "YELLOW"};

void TaskLightUtils(void *pvParameters);
void TaskAmbient(void *pvParameters);
void TaskEnable(void *pvParameters);
void TaskMDNS(void *pvParameters);
void TaskModes(void *pvParameters);
void TaskWeb(void *pvParameters);
void TaskStarSequence(void *pvParameters);
void TaskI2CMonitor(void *pvParameters);

DNSServer dnsServer;
AsyncWebServer webServer(80);

WiFiMulti wifiMulti;

// Add WiFi event handler function
void WiFiEvent(WiFiEvent_t event)
{
    Serial.printf("[WiFi-event] event: %d\n", event);

    switch (event)
    {
    case SYSTEM_EVENT_WIFI_READY:
        Serial.println("WiFi interface ready");
        break;
    case SYSTEM_EVENT_SCAN_DONE:
        Serial.println("Completed scan for access points");
        break;
    case SYSTEM_EVENT_STA_START:
        Serial.println("WiFi client started");
        break;
    case SYSTEM_EVENT_AP_START:
        Serial.println("WiFi AP started");
        Serial.print("AP IP address: ");
        Serial.println(WiFi.softAPIP());
        Serial.print("AP MAC address: ");
        Serial.println(WiFi.softAPmacAddress());
        break;
    case SYSTEM_EVENT_AP_STOP:
        Serial.println("WiFi AP stopped");
        break;
    case SYSTEM_EVENT_AP_STACONNECTED:
        Serial.println("Client connected");
        break;
    case SYSTEM_EVENT_AP_STADISCONNECTED:
        Serial.println("Client disconnected");
        break;
    case SYSTEM_EVENT_STA_CONNECTED:
        Serial.println("Connected to access point");
        break;
    case SYSTEM_EVENT_STA_DISCONNECTED:
        Serial.println("Disconnected from access point");
        break;
    case SYSTEM_EVENT_STA_GOT_IP:
        Serial.println("Got IP address as station");
        Serial.print("Station IP: ");
        Serial.println(WiFi.localIP());
        break;
    }
}

// Function to initialize LED with PWM
void initLedPWM(uint8_t pin, uint8_t channel)
{
    ledcSetup(channel, LEDC_FREQ_HZ, LEDC_RESOLUTION);
    ledcAttachPin(pin, channel);
    ledcWrite(channel, LEDC_FULL_DUTY); // Initialize to full brightness (on state)
}

// Global game objects
Simona *simona = nullptr;

void setup()
{
    Serial.begin(921600);
    delay(2000); // Give serial interface time to connect
    Serial.println("");
    Serial.println("NOVA: CORE");
    Serial.print("setup() is running on core ");
    Serial.println(xPortGetCoreID());

    Serial.setDebugOutput(true);

    PreferencesManager::begin(); // Move this to the start

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

    Serial.println("Setting up Serial2");
    Serial2.begin(921600, SERIAL_8N1, UART2_RX, UART2_TX);

    Serial.println("Pin Directions");
    pinMode(ENABLE_DEVICE_PIN, INPUT_PULLDOWN);

    pinMode(BUTTON_RED_OUT, OUTPUT);
    pinMode(BUTTON_GREEN_OUT, OUTPUT);
    pinMode(BUTTON_BLUE_OUT, OUTPUT);
    pinMode(BUTTON_YELLOW_OUT, OUTPUT);
    pinMode(BUTTON_WHITE_OUT, OUTPUT);

    initLedPWM(BUTTON_RED_OUT, LEDC_CHANNEL_RED);
    initLedPWM(BUTTON_GREEN_OUT, LEDC_CHANNEL_GREEN);
    initLedPWM(BUTTON_BLUE_OUT, LEDC_CHANNEL_BLUE);
    initLedPWM(BUTTON_YELLOW_OUT, LEDC_CHANNEL_YELLOW);
    initLedPWM(BUTTON_WHITE_OUT, LEDC_CHANNEL_RESET);

    randomSeed(esp_random()); // Seed the random number generator with more entropy

    initializeMIDI();

    Serial.println("Set clock of I2C interface to 0.4mhz");
    Wire.begin();

    Wire.setClock(400000UL); // 400khz

    Serial.println("new NovaIO");
    novaIO = new NovaIO();

    Serial.println("new Enable");
    enable = new Enable();

    Serial.println("new Star");
    star = new Star();

    Serial.println("new Ambient");
    ambient = new Ambient();

    Serial.println("new LightUtils");
    lightUtils = new LightUtils();

    Serial.println("new Star Sequence");
    starSequence = new StarSequence();

    String apName = "NovaCore_" + getLastFourOfMac();

    // Set WiFi mode to WIFI_AP_STA for simultaneous AP and STA mode
    WiFi.mode(WIFI_AP_STA);

    WiFi.softAP(apName.c_str(), "scubadandy");
    WiFi.setSleep(false); // Disable power saving on the wifi interface.

    WiFi.onEvent(WiFiEvent);

    // Initialize WiFiMulti and add access points from config
    for (int i = 0; i < NETWORK_COUNT; i++)
    {
        wifiMulti.addAP(networks[i].ssid, networks[i].password);
    }

    if (0) // We don't need this at startup. We have a task that will turn it on.
    {
        // Attempt to connect to one of the networks
        Serial.println("Connecting to WiFi...");
        if (wifiMulti.run() == WL_CONNECTED)
        {
            Serial.println("WiFi connected");
            Serial.println("IP address: ");
            Serial.println(WiFi.localIP());
        }
    }

    // Print network information
    Serial.println("Device Information:");
    Serial.print("MAC Address: ");
    Serial.println(WiFi.macAddress());
    Serial.print("AP Name: ");
    Serial.println(apName);
    Serial.print("AP IP Address: ");
    Serial.println(WiFi.softAPIP());
    Serial.print("STA IP Address: ");
    Serial.println(WiFi.localIP());
    Serial.print("Free Heap: ");
    Serial.println(ESP.getFreeHeap());
    Serial.print("CPU Frequency (MHz): ");
    Serial.println(ESP.getCpuFreqMHz());
    Serial.print("SDK Version: ");
    Serial.println(ESP.getSdkVersion());

    dnsServer.start(53, "*", WiFi.softAPIP());

    // Initialize Simona singleton
    Simona::initInstance(buttons, leds, buttonColors, ledColors);

    // Initialize NovaNow for message handling
    novaNowSetup();

    Serial.println("Setting up Webserver");
    webSetup();
    Serial.println("Setting up Webserver - Done");

    // Create all tasks
    taskSetup();

    Serial.println("Setup Complete");

    playStartupMusic(); // New: play startup music (short, under 1.5 seconds)
}

void loop()
{
    /* Best not to have anything in this loop.
        Everything should be in freeRTOS tasks
    */
    delay(1);
}