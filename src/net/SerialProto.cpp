// SerialProto.cpp
#include "SerialProto.h"

SerialProto::SerialProto(HardwareSerial &serial) : _serial(serial) {}

bool SerialProto::send(const pb_msgdesc_t *fields, const void *src_struct)
{
    pb_ostream_t stream = {SerialProto::encode_callback, &_serial, SIZE_MAX, 0, NULL};
    bool status = pb_encode(&stream, fields, src_struct);

    if (status)
    {
        Serial.print("Successfully sent message with size: ");
        Serial.println(stream.bytes_written);
    }

    return status;
}

bool SerialProto::receive(const pb_msgdesc_t *fields, void *dst_struct) {
  pb_istream_t stream = {SerialProto::decode_callback, &_serial, (size_t)_serial.available(), 0};
  size_t bytes_before = stream.bytes_left;
  bool status = pb_decode(&stream, fields, dst_struct);
  
  if (status) {
    size_t bytes_read = bytes_before - stream.bytes_left;
    Serial.print("Successfully received message with size: ");
    Serial.println(bytes_read);
  }
  
  return status;
}

bool SerialProto::encode_callback(pb_ostream_t *stream, const uint8_t *buf, size_t count)
{
    HardwareSerial *serial = reinterpret_cast<HardwareSerial *>(stream->state);
    serial->write(buf, count);
    //Serial.println(count);
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