#ifndef AMBIENT_H
#define AMBIENT_H

#pragma once

#include <Arduino.h>
#include "messaging.pb.h"
#include "configuration.h"

bool encode_callback(pb_ostream_t *stream, const pb_field_t *field, void *const *arg);

class Ambient
{
private:
    uint32_t lastExecutionTime = 0;
    uint32_t totalFrameTime = 0;
    uint32_t numFrames = 0;

public:
    Ambient();

    void loop();

    void sendDmxMessage(uint8_t* dmxValues, size_t dmxValuesSize);

    // bool encode_callback(pb_ostream_t *stream, const pb_field_t *field, void *const *arg);

    uint16_t crc16_ccitt(const uint8_t *data, uint16_t length);
};

extern Ambient *ambient;

#endif