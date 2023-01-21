#pragma once


#define ENABLE_DEVICE_PIN 13 // This is the "emergency stop" button. 

#define BUTTON_GREEN_IN_PIN 9 // On expansion H
#define BUTTON_GREEN_OUT_PIN 25 // On esp32


#define DEBUG_MSG(...) printf(__VA_ARGS__)
#define LOG_DEBUG(...) printf(__VA_ARGS__)
