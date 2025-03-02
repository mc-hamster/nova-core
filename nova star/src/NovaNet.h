#ifndef NOVANET_H
#define NOVANET_H

#pragma once

#include <Arduino.h>
#include "messaging.pb.h"
//#include "main.h"

//bool encode_callback(pb_ostream_t *stream, const pb_field_t *field, void *const *arg);





class NovaNet
{
private:
public:
    NovaNet();

    void loop();

    void receiveProtobuf();

    uint16_t crc16_ccitt(const uint8_t* data, uint16_t length);
};

extern NovaNet *novaNet;

#endif