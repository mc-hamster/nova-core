#ifndef AMBIENT_H
#define AMBIENT_H

#pragma once

#include <Arduino.h>
#include "messaging.pb.h"

bool encode_callback(pb_ostream_t *stream, const pb_field_t *field, void *const *arg);

class Ambient
{
private:
public:
    Ambient();

    void loop();

    void sendProtobuf();

    //bool encode_callback(pb_ostream_t *stream, const pb_field_t *field, void *const *arg);

    uint16_t crc16(const uint8_t* data_p, uint16_t length);

    uint16_t crc16_ccitt(const uint8_t* data, uint16_t length);
};

extern Ambient *ambient;

#endif