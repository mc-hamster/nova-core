// SerialProto.cpp
#include "SerialProto.h"

SerialProto::SerialProto(HardwareSerial &serial) : _serial(serial) {}

bool SerialProto::send(const pb_msgdesc_t *fields, const void *src_struct)
{
    pb_ostream_t stream = {SerialProto::encode_callback, &_serial, SIZE_MAX, 0, NULL};
    return pb_encode(&stream, fields, src_struct);
}

bool SerialProto::receive(const pb_msgdesc_t *fields, void *dst_struct)
{
    pb_istream_t stream = {SerialProto::decode_callback, &_serial, _serial.available(), 0};
    return pb_decode(&stream, fields, dst_struct);
}

bool SerialProto::encode_callback(pb_ostream_t *stream, const uint8_t *buf, size_t count)
{
    HardwareSerial *serial = reinterpret_cast<HardwareSerial *>(stream->state);
    serial->write(buf, count);
    return true;
}

bool SerialProto::decode_callback(pb_istream_t *stream, uint8_t *buf, size_t count)
{
    HardwareSerial *serial = reinterpret_cast<HardwareSerial *>(stream->state);
    if (serial->available() < count)
    {
        return false;
    }
    serial->readBytes(buf, count);
    return true;
}