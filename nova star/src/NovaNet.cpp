#include <Arduino.h>
#include "NovaNet.h"
#include "main.h"
#include "configuration.h"
#include "pb_arduino.h"
#include "NovaIO.h"
#include "DmxNet.h"
#include "globals.h"
#include "FogMachine.h"

#include "messaging.pb.h"

/*

This class is responsible for sending and receiving messages over the NovaNet protocol.

*/

NovaNet *novaNet = NULL;

unsigned long lastTime = 0;
unsigned int count = 0;

NovaNet::NovaNet()
{

    messaging_Request request = messaging_Request_init_zero;
    Serial.println("NovaNet setup started");

    // Serial2.begin(NOVANET_BAUD);

    // Set the NovaNet pins to receive
    novaIO->mcp_digitalWrite(NOVANET_RE, LOW, 0);
    novaIO->mcp_digitalWrite(NOVANET_DE, HIGH, 0);

    // Setup goes in here
}

void NovaNet::loop()
{
    // Serial.println("NovaNet loop");
    receiveProtobuf();
    // delay(1000);
}

void NovaNet::receiveProtobuf()
{
    unsigned long currentTime = millis();
    unsigned long elapsedTime = currentTime - lastTime;

    uint16_t msg_size = 0;

    // Prepare the header: F0 9F 92 A5 followed by the CRC and the size of the protobuf
    // aka "fire" emoji 🔥
    uint8_t header[4] = {0xF0, 0x9F, 0x92, 0xA5};

    // Serial.println("receiving");
    //  Read and check the header
    uint8_t received_header[4];

    while (Serial2.available() < sizeof(received_header))
    {
        // Wait until the header has been received
        delay(1);
    }

    Serial2.readBytes((char *)received_header, sizeof(received_header));

    if (memcmp(received_header, header, sizeof(header)) != 0)
    {
        // Handle the error: invalid header
        Serial.println("NovaNet: Invalid Header");
        return;
    }

    // Read the CRC of the protobuf
    uint16_t received_protobuf_crc;
    while (Serial2.available() < sizeof(received_protobuf_crc))
    {
        // Wait until the CRC has been received
        yield();
    }
    Serial2.readBytes((char *)&received_protobuf_crc, sizeof(received_protobuf_crc));

    // Read the size of the received protobuf
    while (Serial2.available() < sizeof(msg_size))
    {
        // Wait until the size has been received
        yield();
    }
    uint16_t received_size;
    Serial2.readBytes((char *)&received_size, sizeof(received_size));

    // Wait until the entire protobuf has been received
    while (Serial2.available() < received_size)
    {
        // Wait
        yield();
    }

    // Now read the protobuf
    uint8_t received_buffer[NOVABUF_MAX];
    Serial2.readBytes((char *)received_buffer, received_size);

    // Calculate the CRC of the received protobuf
    uint16_t calculated_protobuf_crc = crc16_ccitt(received_buffer, received_size);
    if (received_protobuf_crc != calculated_protobuf_crc)
    {
        // Handle the error: invalid CRC
        Serial.println("NovaNet: Invalid receive CRC");
        return;
    }
    else
    {
        // Serial.println("NovaNet: CRC OK");
    }

    // Initialize a protobuf input stream
    pb_istream_t pb_istream = pb_istream_from_buffer(received_buffer, received_size);

    // Decode the received protobuf
    messaging_Request received_msg = messaging_Request_init_zero;
    if (!pb_decode(&pb_istream, messaging_Request_fields, &received_msg))
    {
        // Handle the decoding error
        Serial.println("NovaNet: Decode Error");
    }

    if (received_msg.which_request_payload == messaging_Request_dmx_request_tag)
    {
        // Handle the DMX request
        messaging_DmxRequest received_dmx_request = received_msg.request_payload.dmx_request;

        if (received_msg.configAmnesia.fogActivateTime)
        {
            Serial.printf("Received Fog activate time: %d\n", received_msg.configAmnesia.fogActivateTime);
            // fogActivateTime = received_msg.configAmnesia.fogActivateTime;
            Serial.println("WARNING: fogActivateTime received but this is not implemented");
        }

        if (received_msg.configAmnesia.fogOutputOnMinTime)
        {
            Serial.printf("Received Fog output on min time: %d\n", received_msg.configAmnesia.fogOutputOnMinTime);
            fogMachine->setFogOutputOnMinTime(received_msg.configAmnesia.fogOutputOnMinTime);
        }

        if (received_msg.configAmnesia.fogOutputOnMaxTime)
        {
            Serial.printf("Received Fog output on max time: %d\n", received_msg.configAmnesia.fogOutputOnMaxTime);
            fogMachine->setFogOutputOnMaxTime(received_msg.configAmnesia.fogOutputOnMaxTime);
        }

        if (received_msg.configAmnesia.fogOutputOffMinTime)
        {
            Serial.printf("Received Fog output off min time: %d\n", received_msg.configAmnesia.fogOutputOffMinTime);
            fogMachine->setFogOutputOffMinTime(received_msg.configAmnesia.fogOutputOffMinTime);
        }

        if (received_msg.configAmnesia.fogOutputOffMaxTime)
        {
            Serial.printf("Received Fog output off max time: %d\n", received_msg.configAmnesia.fogOutputOffMaxTime);
            fogMachine->setFogOutputOffMaxTime(received_msg.configAmnesia.fogOutputOffMaxTime);
        }

        if (0)
        {
            Serial.print("R: ");
            // Print the received DMX values
            for (int i = 0; i < received_dmx_request.values.size; i++)
            {
                Serial.print(received_dmx_request.values.bytes[i], HEX);
                Serial.print(" ");
            }
            Serial.println();
        }

        // Send the DMX values to the DMX output
        dmxNet->receiveDMX512(received_dmx_request.values.bytes);
    }
    else if (received_msg.which_request_payload == messaging_Request_power_request_tag)
    {
        // Handle the power request
        messaging_PowerRequest received_power_request = received_msg.request_payload.power_request;

        // Print the received power request
        Serial.println("Power request: ???");
        // Serial.println(received_power_request.power);
    }
    else
    {
        Serial.println("NovaNet: Invalid request payload");
        // Handle the error: invalid request payload
    }

    /*
     * Calculate the frequency of received messages
     */
    if (elapsedTime >= 10000)
    {
        float frequency = (float)count / ((float)elapsedTime / 10000.0);
        Serial.print("Received Message Frequency: ");
        Serial.print(frequency);
        Serial.println(" Hz");

        lastTime = currentTime;
        count = 0;
    }
    count++;
}

// CRC-16-CCITT function
uint16_t NovaNet::crc16_ccitt(const uint8_t *data, uint16_t length)
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