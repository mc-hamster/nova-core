#pragma once

#define UART2_RX 16
#define UART2_TX 17

#define APA102_CLOCK 18
#define APA102_DATA 4

#define ENABLE_DEVICE_PIN 13 // This is the "emergency stop" button. 

#define BUTTON_RED_IN 8 // On expansion H
#define BUTTON_RED_OUT 23 // On esp32

#define BUTTON_GREEN_IN 9 // On expansion H
#define BUTTON_GREEN_OUT 25 // On esp32

#define BUTTON_BLUE_IN 10 // On expansion H
#define BUTTON_BLUE_OUT 26 // On esp32

#define BUTTON_YELLOW_IN 11 // On expansion H
#define BUTTON_YELLOW_OUT 27 // On esp32

#define BUTTON_WHITE_IN 12 // On expansion H
#define BUTTON_WHITE_OUT 32 // On esp32

#define DMX512_MAX 512 // Maximum number of channels on a DMX512 universe.

#define NOVABUF_MAX 1024 // Maximum size of the protocol buffer

#define REPORT_TASK_INTERVAL 120 * 1000 // How often to report task status in milliseconds

/*
    Options include:
        9600
        19200
        28800
        38400
        57600
        76800
        115200
        230400
        460800
        576000
        921600
*/

#define NOVANET_BAUD 921600

// Game configuration constants
#define SIMONA_INPUT_TIMEOUT_SECONDS 30
#define SIMONA_DEBUG_TIMEOUT 0  // Set to 1 to enable timeout debug messages
#define LEVELS_PER_ROUND_DEFAULT 1
#define SIMONA_MAX_ROUNDS 8

// LEDC (PWM) Configuration
#define LEDC_FREQ_HZ      5000
#define LEDC_RESOLUTION   8       // 8-bit resolution (0-255)
#define LEDC_FULL_DUTY    255     // Full brightness duty cycle
#define LEDC_DIM_DUTY     3      // 10% brightness duty cycle (255 * 0.10)

#define LEDC_CHANNEL_RED      0
#define LEDC_CHANNEL_GREEN    1
#define LEDC_CHANNEL_BLUE     2
#define LEDC_CHANNEL_YELLOW   3
#define LEDC_CHANNEL_RESET     4

// RMT MIDI Output Configuration
#define RMT_BIT_DURATION_TICKS 2560  // Nova core-specific MIDI timing

// Debug configurations
#define DEBUG_STARS_ENABLED 0  // Set to 0 to disable Star debug messages in serial console
