#pragma once


#define FOG_STATUS 0 // Expansion A

#define FOG_POWER 1 // Expansion A

#define FOG_ACTIVATE 2 // Expansion A

#define BLOWER_DUTY_PIN 15 // Used to define the duty cycle of the blower to moderate voltage.


#define DMX_DE 4 // Expansion A
#define DMX_RE 5 // Expansion A

#define DMX_RO 2 
#define DMX_DI 4 

#define NOVANET_DE 3 // Expansion A
#define NOVANET_RE 2 // Expansion A

#define UART2_RX 16
#define UART2_TX 17



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