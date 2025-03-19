#include <Arduino.h>
#include "Ambient.h"
#include "configuration.h"
#include "NovaIO.h"
// #include "SerialProto.h"
#include "main.h"
#include "pb_arduino.h"
#include "output/Star.h"
#include "LightUtils.h"
#include "utilities/PreferencesManager.h"

#include "messaging.pb.h"

/*

This class manages the background tasks that control:
  - Lighting
  - Power management

*/

Ambient *ambient = NULL;

Ambient::Ambient()
{

    messaging_Request request = messaging_Request_init_zero;
    Serial.println("Ambient setup started");

    Serial2.begin(NOVANET_BAUD);

    // Setup goes in here
}

void Ambient::loop()
{
    uint32_t currentTime = millis();
    static uint32_t amnesiaLastTime = 0;
    bool sendAmnesia = false;

    if (currentTime - amnesiaLastTime >= 5 * 1000)
    {
        sendAmnesia = true;
        amnesiaLastTime = currentTime;
    }
    else
    {
        sendAmnesia = false;
    }

    // Serial.println("Ambient loop");
    // sendProtobuf();

    CRGB *leds = lightUtils->getLeds();

    uint32_t frameTime = micros();

    uint8_t lightsPre = 3;
    uint8_t lightsPost = 3;

    for (int starIndex = 0; starIndex < 12; starIndex++)
    {
        uint8_t dmxValues[DMX512_MAX] = {};

        // Set the selected star to transmit.
        star->netOut(starIndex);

        if (starIndex == 0) // First Star
        {

            uint8_t dmxFixture = 0;
            dmxValues[0] = 0x00; // Always 0x00 (other values are reserved)
            // for (int lightsPreIndex = 0; lightsPreIndex < lightsPre; lightsPreIndex++)
            for (int lightsPreIndex = lightsPre; lightsPreIndex >= 0; lightsPreIndex--)
            {

                dmxValues[1 + (7 * lightsPreIndex)] = 0xff;              // Brightness
                dmxValues[2 + (7 * lightsPreIndex)] = leds[starIndex].r; // red
                dmxValues[3 + (7 * lightsPreIndex)] = leds[starIndex].g; // green
                dmxValues[4 + (7 * lightsPreIndex)] = leds[starIndex].b; // blue
                dmxValues[5 + (7 * lightsPreIndex)] = 0x00;              // null
                dmxValues[6 + (7 * lightsPreIndex)] = 0x00;              // null
                dmxValues[7 + (7 * lightsPreIndex)] = 0x00;              // null

                dmxValues[8 + (7 * lightsPreIndex)] = 0xff;                                 // Brightness
                dmxValues[9 + (7 * lightsPreIndex)] = leds[starIndex + dmxFixture + 15].r;  // red
                dmxValues[10 + (7 * lightsPreIndex)] = leds[starIndex + dmxFixture + 15].g; // green
                dmxValues[11 + (7 * lightsPreIndex)] = leds[starIndex + dmxFixture + 15].b; // blue
                dmxValues[12] = 0x00;                                                       // null
                dmxValues[13] = 0x00;                                                       // null
                dmxValues[14] = 0x00;                                                       // null

                dmxFixture++;
            }
        }
        else if (starIndex == 11) // Last Star
        {
            uint8_t dmxFixture = 0;
            dmxValues[0] = 0x00; // Always 0x00 (other values are reserved)
            for (int lightsPostIndex = 0; lightsPostIndex <= lightsPost; lightsPostIndex++)
            // for (int lightsPostIndex = lightsPost - 1; lightsPostIndex >= 0; lightsPostIndex--)
            {
                dmxValues[1 + (7 * lightsPostIndex)] = 0xff;              // Brightness
                dmxValues[2 + (7 * lightsPostIndex)] = leds[starIndex].r; // red
                dmxValues[3 + (7 * lightsPostIndex)] = leds[starIndex].g; // green
                dmxValues[4 + (7 * lightsPostIndex)] = leds[starIndex].b; // blue
                dmxValues[5 + (7 * lightsPostIndex)] = 0x00;              // null
                dmxValues[6 + (7 * lightsPostIndex)] = 0x00;              // null
                dmxValues[7 + (7 * lightsPostIndex)] = 0x00;              // null

                dmxValues[8 + (7 * lightsPostIndex)] = 0xff;                                 // Brightness
                dmxValues[9 + (7 * lightsPostIndex)] = leds[starIndex + dmxFixture + 15].r;  // red
                dmxValues[10 + (7 * lightsPostIndex)] = leds[starIndex + dmxFixture + 15].g; // green
                dmxValues[11 + (7 * lightsPostIndex)] = leds[starIndex + dmxFixture + 15].b; // blue
                dmxValues[12] = 0x00;                                                       // null
                dmxValues[13] = 0x00;                                                       // null
                dmxValues[14] = 0x00;                                                       // null

                dmxFixture++;
                // Serial.println("dmxFixture");
            }
        }
        else
        {

            dmxValues[0] = 0x00; // Always 0x00 (other values are reserved)

            dmxValues[1] = 0xff;              // Brightness
            dmxValues[2] = leds[starIndex].r; // red
            dmxValues[3] = leds[starIndex].g; // green
            dmxValues[4] = leds[starIndex].b; // blue
            dmxValues[5] = 0x00;              // null
            dmxValues[6] = 0x00;              // null
            dmxValues[7] = 0x00;              // null

            dmxValues[8] = 0xff;                    // Brightness
            dmxValues[9] = leds[starIndex + 15].r;  // red
            dmxValues[10] = leds[starIndex + 15].g; // green
            dmxValues[11] = leds[starIndex + 15].b; // blue
            dmxValues[12] = 0x00;                   // null
            dmxValues[13] = 0x00;                   // null
            dmxValues[14] = 0x00;                   // null
        }

        sendDmxMessage(dmxValues, DMX512_MAX, sendAmnesia);
    }

    if (currentTime - lastExecutionTime >= 120 * 1000)
    {
        // Calculate average frame time
        unsigned long avgFrameTime = totalFrameTime / numFrames;

        // Print statistics
        Serial.printf("Average network frame time: %d (milliseconds) %d (fps) \n", avgFrameTime / 1000, 1000 / (avgFrameTime / 1000));

        // Reset statistics
        totalFrameTime = 0;
        numFrames = 0;

        // Update last execution time
        lastExecutionTime = currentTime;
    }

    totalFrameTime += micros() - frameTime;
    numFrames++;
}

/**
 * Sends a DMX message with the given DMX values over NovaNet.
 *
 * Think of this as the display driver. It takes the DMX values
 * and sends them to the display.
 *
 * @param dmxValues The DMX values to send.
 * @param dmxValuesSize The size of the DMX values array.
 */
void Ambient::sendDmxMessage(uint8_t *dmxValues, size_t dmxValuesSize, bool sendAmnesia)
{

    uint8_t newDmxValues[dmxValuesSize] = {};
    memcpy(newDmxValues, dmxValues, dmxValuesSize - 1);

    // Create a DmxRequest object
    messaging_DmxRequest dmxRequest = messaging_DmxRequest_init_zero;

    memcpy(dmxRequest.values.bytes, newDmxValues, dmxValuesSize);

    // Find the last index with data
    int lastIndexWithData = 0;
    for (int i = DMX512_MAX - 1; i >= 0; i--)
    {
        if (newDmxValues[i] != 0)
        {
            lastIndexWithData = i + 1;
            break;
        }
    }

    dmxRequest.values.size = lastIndexWithData;

    dmxRequest.ack = false; // Request acknoledgement

    // Create a Request object and set its type to DMX_REQUEST
    messaging_Request request = messaging_Request_init_zero;
    // request.type = messaging_RequestType_REQUEST_DMX;
    request.request_payload.dmx_request = dmxRequest;
    request.which_request_payload = messaging_Request_dmx_request_tag;

    // TODO: This shouldn't be here. Needs to be higher up in the stack.
    if (sendAmnesia)
    {
        runAmnesiaCode(request);
    }

    // Initialize a buffer stream for the encoded message
    uint8_t buffer[NOVABUF_MAX];
    pb_ostream_t stream = pb_ostream_from_buffer(buffer, sizeof(buffer));

    // Encode the protobuf
    if (!pb_encode(&stream, messaging_Request_fields, &request))
    {
        // Encode error. Maybe the buffer isn't big enough?
        Serial.println("PB_Encode Error!!!");
    }

    // Calculate the CRC of the protobuf
    uint16_t protobuf_crc = crc16_ccitt(buffer, stream.bytes_written);

    // Prepare the header: F0 9F 92 A5 followed by the CRC and the size of the protobuf
    uint8_t header[4] = {0xF0, 0x9F, 0x92, 0xA5};
    uint16_t msg_size = stream.bytes_written;

    // Send the header
    Serial2.write(header, sizeof(header));

    // Send the CRC of the protobuf
    Serial2.write((uint8_t *)&protobuf_crc, sizeof(protobuf_crc));

    // Send the size of the protobuf
    Serial2.write((uint8_t *)&msg_size, sizeof(msg_size));

    // Then send the protobuf
    Serial2.write(buffer, msg_size);

    // TODO: Cleanup the magic numbers.
    //  8 microseconds for each byte
    //
    //  8 bytes in the header before the message
    //  sizeof(msg_size) for the message.
    delayMicroseconds(8 * (8 + sizeof(msg_size)));

    // Wait for to make sure that the serial buffer is empty
    Serial2.flush(true);

    return;
}

/**
 * Calculates the CRC-16-CCITT checksum for the given data.
 *
 * This function calculates the CRC-16-CCITT checksum for the given data using the polynomial x^16 + x^12 + x^5 + 1.
 *
 * @param data The data to calculate the checksum for.
 * @param length The length of the data in bytes.
 * @return The calculated CRC-16-CCITT checksum.
 */
// CRC-16-CCITT function
uint16_t Ambient::crc16_ccitt(const uint8_t *data, uint16_t length)
{
    uint16_t crc = 0xFFFF; // Initialize CRC to 0xFFFF

    // Iterate over the data
    for (uint16_t i = 0; i < length; i++)
    {
        crc ^= data[i] << 8; // XOR the current byte with the CRC

        // Iterate over the bits in the byte
        for (uint16_t j = 0; j < 8; j++)
        {
            // If the MSB of the CRC is 1, XOR with the polynomial
            if (crc & 0x8000)
            {
                crc = (crc << 1) ^ 0x1021; // Polynomial: x^16 + x^12 + x^5 + 1
            }
            else // Otherwise, shift the CRC left by 1 bit
            {
                crc <<= 1;
            }
        }
    }

    return crc; // Return the final CRC value
}

/**
 * Runs the amnesia code for the given messaging request.
 *
 * @param request The messaging request to run the amnesia code for.
 *
 * TODO: This needs to run for the entire frame, not just every 200ms.
 *
 */
void Ambient::runAmnesiaCode(messaging_Request &request)
{
    uint32_t currentTime = millis();

    // Run this every 200ms
    request.has_configAmnesia = true;

    // Important: Ensure the min is not greater than max
    uint32_t fogOffMin = getFogOutputOffMinTime() ? getFogOutputOffMinTime() : 5000;
    uint32_t fogOffMax = getFogOutputOffMaxTime() ? getFogOutputOffMaxTime() : 20000;
    uint32_t fogOnMin = getFogOutputOnMinTime() ? getFogOutputOnMinTime() : 200;
    uint32_t fogOnMax = getFogOutputOnMaxTime() ? getFogOutputOnMaxTime() : 1000;

    // Safety
    if (fogOffMax < fogOffMin)
    {
        fogOffMax = fogOffMin;
    }

    if (fogOnMax < fogOnMin)
    {
        fogOnMax = fogOnMin;
    }

    request.configAmnesia.fogOutputOffMinTime = fogOffMin;
    request.configAmnesia.fogOutputOffMaxTime = fogOffMax;

    request.configAmnesia.fogOutputOnMinTime = fogOnMin;
    request.configAmnesia.fogOutputOnMaxTime = fogOnMax;
}

bool Ambient::setFogOutputOffMinTime(uint32_t time)
{
    PreferencesManager::setInt("fogOffMin", time);
    return true;
}

bool Ambient::setFogOutputOffMaxTime(uint32_t time)
{
    PreferencesManager::setInt("fogOffMax", time);
    return true;
}

bool Ambient::setFogOutputOnMinTime(uint32_t time)
{
    PreferencesManager::setInt("fogOnMin", time);
    return true;
}

bool Ambient::setFogOutputOnMaxTime(uint32_t time)
{
    PreferencesManager::setInt("fogOnMax", time);
    return true;
}

uint32_t Ambient::getFogOutputOffMinTime(void)
{
    return PreferencesManager::getInt("fogOffMin", 5000);
}

uint32_t Ambient::getFogOutputOffMaxTime(void)
{
    return PreferencesManager::getInt("fogOffMax", 20000);
}

uint32_t Ambient::getFogOutputOnMinTime(void)
{
    return PreferencesManager::getInt("fogOnMin", 200);
}

uint32_t Ambient::getFogOutputOnMaxTime(void)
{
    return PreferencesManager::getInt("fogOnMax", 1000);
}