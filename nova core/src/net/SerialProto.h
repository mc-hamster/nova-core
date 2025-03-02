// SerialProto.h
#include <Arduino.h>
#include <pb_encode.h>
#include <pb_decode.h>
#include <HardwareSerial.h>

#include "messaging.pb.h"


class SerialProto
{
public:
    SerialProto(HardwareSerial &serial);
    bool send(const pb_msgdesc_t *fields, const void *src_struct);
    bool receive(const pb_msgdesc_t *fields, void *dst_struct);

private:
    HardwareSerial &_serial;

    static bool encode_callback(pb_ostream_t *stream, const uint8_t *buf, size_t count);
    static bool decode_callback(pb_istream_t *stream, uint8_t *buf, size_t count);
};