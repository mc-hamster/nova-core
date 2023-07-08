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