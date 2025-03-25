#ifndef NOVANET_H
#define NOVANET_H

#pragma once

#include <Arduino.h>
#include "messaging.pb.h"

class NovaNet
{
public:
    NovaNet();
    void loop();
    void receiveProtobuf();

    // Testing methods - only compiled in test builds
    #ifdef UNIT_TESTING
    uint16_t crc16_ccitt(const uint8_t* data, uint16_t length);
    bool validateHeader(const uint8_t* header);
    #endif

private:
    #ifndef UNIT_TESTING
    uint16_t crc16_ccitt(const uint8_t* data, uint16_t length);
    #endif
    bool readWithTimeout(uint8_t* buffer, size_t size, unsigned long timeout_ms = 1000);
    bool validateHeader(const uint8_t* header);
    static const unsigned long SERIAL_READ_TIMEOUT_MS = 1000; // 1 second timeout
};

extern NovaNet *novaNet;

#endif