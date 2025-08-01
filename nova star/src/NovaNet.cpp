#include <Arduino.h>
#include "NovaNet.h"
#include "main.h"
#include "configuration.h"
#include "pb_arduino.h"
#include "NovaIO.h"
#include "DmxNet.h"
#include "globals.h"
#include "FogMachine.h"
#include "Sensors.h"

#include "messaging.pb.h"

/*

This class is responsible for sending and receiving messages over the NovaNet protocol.

*/

NovaNet::NovaNet() : lastTime(0), count(0)
{
    // messaging_Request request = messaging_Request_init_zero;
    Serial.println("NovaNet setup started");

    // Serial2.begin(NOVANET_BAUD);

    // Set the NovaNet transceiver to receive mode using setStarlink
    novaIO->setStarlink(NovaIO::STARLINK_RECEIVE);

    // Setup goes in here
}

bool NovaNet::readWithTimeout(uint8_t *buffer, size_t size, unsigned long timeout_ms)
{
    unsigned long startTime = millis();
    while (Serial2.available() < size)
    {
        if (millis() - startTime >= timeout_ms)
        {
            Serial.printf("Serial read timeout after %lu ms waiting for %d bytes\n", timeout_ms, size);
            return false;
        }
        vTaskDelay(pdMS_TO_TICKS(1));
    }
    size_t bytesRead = Serial2.readBytes((char *)buffer, size);
    return bytesRead == size;
}

void NovaNet::loop()
{
    unsigned long currentTime = millis();
    unsigned long elapsedTime = currentTime - lastTime;
    uint16_t msg_size = 0;

    // Prepare the header: F0 9F 92 A5 aka "fire" emoji 🔥
    uint8_t header[4] = {0xF0, 0x9F, 0x92, 0xA5};
    uint8_t received_header[4];

    // Read and validate header with timeout
    if (!readWithTimeout(received_header, sizeof(received_header)))
    {
        Serial.println("NovaNet: Timeout waiting for header");
        return;
    }

    if (!validateHeader(received_header))
    {
        //Serial.println("NovaNet: Invalid Header");
        return;
    }

    // Read the CRC of the protobuf with timeout
    uint16_t received_protobuf_crc;
    if (!readWithTimeout((uint8_t *)&received_protobuf_crc, sizeof(received_protobuf_crc)))
    {
        Serial.println("NovaNet: Timeout waiting for CRC");
        return;
    }

    // Read the size of the received protobuf with timeout
    uint16_t received_size;
    if (!readWithTimeout((uint8_t *)&received_size, sizeof(received_size)))
    {
        Serial.println("NovaNet: Timeout waiting for size");
        return;
    }

    // Add size validation
    if (received_size > NOVABUF_MAX || received_size == 0)
    {
        Serial.printf("NovaNet: Invalid message size (%d bytes). Must be between 1 and %d bytes\n", received_size, NOVABUF_MAX);
        return;
    }

    // Read the protobuf data with timeout
    uint8_t received_buffer[NOVABUF_MAX];
    if (!readWithTimeout(received_buffer, received_size))
    {
        Serial.println("NovaNet: Timeout waiting for protobuf data");
        return;
    }

    // Calculate and validate CRC
    uint16_t calculated_protobuf_crc = crc16_ccitt(received_buffer, received_size);
    if (received_protobuf_crc != calculated_protobuf_crc)
    {
        Serial.println("NovaNet: Invalid receive CRC");
        return;
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

    switch (received_msg.which_request_payload)
    {
    case messaging_Request_dmx_request_tag:
    {
        // Handle the DMX request
        messaging_DmxRequest received_dmx_request = received_msg.request_payload.dmx_request;

        if (received_msg.has_configAmnesia)
        {
            if (received_msg.configAmnesia.fogActivateTime)
            {
                Serial.printf("Received Fog activate time: %d\n", received_msg.configAmnesia.fogActivateTime);
                Serial.println("WARNING: fogActivateTime received but this is not implemented");
            }

            bool timingChanged = false;
            if (received_msg.configAmnesia.fogOutputOnMinTime)
            {
                fogMachine->setFogOutputOnMinTime(received_msg.configAmnesia.fogOutputOnMinTime);
                timingChanged = true;
            }
            if (received_msg.configAmnesia.fogOutputOnMaxTime)
            {
                fogMachine->setFogOutputOnMaxTime(received_msg.configAmnesia.fogOutputOnMaxTime);
                timingChanged = true;
            }
            if (received_msg.configAmnesia.fogOutputOffMinTime)
            {
                fogMachine->setFogOutputOffMinTime(received_msg.configAmnesia.fogOutputOffMinTime);
                timingChanged = true;
            }
            if (received_msg.configAmnesia.fogOutputOffMaxTime)
            {
                fogMachine->setFogOutputOffMaxTime(received_msg.configAmnesia.fogOutputOffMaxTime);
                timingChanged = true;
            }

            if (timingChanged)
            {
                // Calculate average ON and OFF times for duty cycle
                float avgOnTime = (received_msg.configAmnesia.fogOutputOnMinTime + received_msg.configAmnesia.fogOutputOnMaxTime) / 2.0f;
                float avgOffTime = (received_msg.configAmnesia.fogOutputOffMinTime + received_msg.configAmnesia.fogOutputOffMaxTime) / 2.0f;
                float dutyCycle = (avgOnTime / (avgOnTime + avgOffTime)) * 100.0f;

                Serial.printf("Received Fog timings - On: %d-%dms, Off: %d-%dms (%.1f%% duty cycle)\n",
                              received_msg.configAmnesia.fogOutputOnMinTime,
                              received_msg.configAmnesia.fogOutputOnMaxTime,
                              received_msg.configAmnesia.fogOutputOffMinTime,
                              received_msg.configAmnesia.fogOutputOffMaxTime,
                              dutyCycle);
            }

            fogMachine->updateLastAmnesiaMessageTime();
            // Serial.println("Received configAmnesia");

            Serial.printf("Received Fog enabled: %d\n", received_msg.configAmnesia.fogEnabled);

            if (received_msg.configAmnesia.fogEnabled)
            {
                bool currentFogEnabled = fogMachine->getFogEnabled();
                if (!currentFogEnabled)
                {
                    Serial.printf("Received Fog enabled: %d\n", received_msg.configAmnesia.fogEnabled);
                    fogMachine->setFogEnabled(true);
                }
            }
            else
            {
                bool currentFogEnabled = fogMachine->getFogEnabled();
                if (currentFogEnabled)
                {
                    Serial.printf("Received Fog enabled: %d\n", received_msg.configAmnesia.fogEnabled);
                    fogMachine->setFogEnabled(false);
                }
            }
        }

        // Send the DMX values to the DMX output
        dmxNet->receiveDMX512(received_dmx_request.values.bytes);
        break;
    }
    case messaging_Request_power_request_tag:
    {
        // Handle the power request
        messaging_PowerRequest received_power_request = received_msg.request_payload.power_request;
        Serial.println("Power request: ???");
        break;
    }
    case messaging_Request_telemetry_request_tag:
    {
        // Handle the telemetry request
        messaging_TelemetryRequest received_telemetry_request = received_msg.request_payload.telemetry_request;
        Serial.println("Received telemetry request, sending response");

        // Send telemetry response
        sendTelemetryResponse();
        break;
    }
    // Add additional cases for other payload types as needed
    default:
        Serial.println("NovaNet: Invalid or unhandled request payload");
        break;
    }

    /*
     * Calculate the frequency of received˝messages
     */
    if (elapsedTime >= 10000)
    {
        float frequency = (float)count / ((float)elapsedTime / 1000.0);
        Serial.print("Received Message Frequency: ");
        Serial.print(frequency);
        Serial.println(" Hz");

        lastTime = currentTime;
        count = 0;
    }
    count++;
}

bool NovaNet::validateHeader(const uint8_t *header)
{
    const uint8_t expected_header[4] = {0xF0, 0x9F, 0x92, 0xA5}; // "fire" emoji
    return memcmp(header, expected_header, 4) == 0;
}

// Helper function for string encoding in nanopb
bool NovaNet::encode_string_callback(pb_ostream_t *stream, const pb_field_t *field, void *const *arg)
{
    const char *str = (const char *)(*arg);
    if (!str)
        return true;

    if (!pb_encode_tag_for_field(stream, field))
        return false;

    return pb_encode_string(stream, (const uint8_t *)str, strlen(str));
}

/**
 * Sends a telemetry response with the current telemetry data.
 * Sets the Starlink to transmit before sending and back to receive afterward.
 */
void NovaNet::sendTelemetryResponse()
{
    // Set the NovaNet transceiver to transmit mode
    novaIO->setStarlink(NovaIO::STARLINK_TRANSMIT);

    // Create a TelemetryResponse object
    messaging_TelemetryResponse telemetryResponse = messaging_TelemetryResponse_init_zero;

    // Fill in telemetry data
    telemetryResponse.temperature = sensors->getTemperature();
    telemetryResponse.humidity = 0.0; // No humidity sensor available

    // Set acceleration data from stored min/max values
    telemetryResponse.accel_min_z = sensors->getMinAccelZ();
    telemetryResponse.accel_max_z = sensors->getMaxAccelZ();
    telemetryResponse.accel_min_z_time = sensors->getTimeSinceBoomForMinAccelZ() / 1000.0f; // Convert ms to seconds
    telemetryResponse.accel_max_z_time = sensors->getTimeSinceBoomForMaxAccelZ() / 1000.0f; // Convert ms to seconds

    // Set chip free heap and sketch size (numeric values)
    //telemetryResponse.chip_free_heap = ESP.getFreeHeap();

    /*
    telemetryResponse.sketch_size = ESP.getSketchSize();

    // For string fields, we need to use callbacks
    // Set up static strings to be used by callbacks
    static const char *chip_model = "ESP32";
    static char chip_revision[8];
    static const char *sdk_version = ESP.getSdkVersion();
    static char sketch_md5[33];
    static char datetime[30];

    // Fill in the static strings
    sprintf(chip_revision, "v%d", ESP.getChipRevision());
    strcpy(sketch_md5, ESP.getSketchMD5().c_str());
    sprintf(datetime, "%s %s", __DATE__, __TIME__);

    // Set up callbacks for string fields
    telemetryResponse.chip_model.funcs.encode = &encode_string_callback;
    telemetryResponse.chip_model.arg = (void *)chip_model;

    telemetryResponse.chip_revision.funcs.encode = &encode_string_callback;
    telemetryResponse.chip_revision.arg = (void *)chip_revision;

    telemetryResponse.sdk_version.funcs.encode = &encode_string_callback;
    telemetryResponse.sdk_version.arg = (void *)sdk_version;

    telemetryResponse.sketch_md5.funcs.encode = &encode_string_callback;
    telemetryResponse.sketch_md5.arg = (void *)sketch_md5;

    telemetryResponse.sketch_compile_datetime.funcs.encode = &encode_string_callback;
    telemetryResponse.sketch_compile_datetime.arg = (void *)datetime;
    */

    // Create a Response object
    messaging_Response response = messaging_Response_init_zero;
    response.type = messaging_ResponseType_RESPONSE_TELEMETRY;
    response.response_payload.telemetry_response = telemetryResponse;
    response.which_response_payload = messaging_Response_telemetry_response_tag;

    // Initialize a buffer stream for the encoded message
    uint8_t buffer[NOVABUF_MAX];
    pb_ostream_t stream = pb_ostream_from_buffer(buffer, sizeof(buffer));

    // Encode the protobuf
    if (!pb_encode(&stream, messaging_Response_fields, &response))
    {
        // Encode error. Maybe the buffer isn't big enough?
        Serial.println("PB_Encode Error!!!");

        // Set the NovaNet transceiver back to receive mode
        novaIO->setStarlink(NovaIO::STARLINK_RECEIVE);
        return;
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

    // Short delay to ensure transmission completes
    delayMicroseconds(8 * (8 + sizeof(msg_size) + msg_size));

    // Wait for serial buffer to empty
    Serial2.flush(true);

    // Set the NovaNet transceiver back to receive mode
    novaIO->setStarlink(NovaIO::STARLINK_RECEIVE);

    // Calculate the total response size: header (4) + CRC (2) + message size field (2) + protobuf body (msg_size)
    size_t totalResponseSize = 4 + sizeof(protobuf_crc) + sizeof(msg_size) + msg_size;
    Serial.printf("Telemetry response sent (Total size: %u bytes, Protobuf: %u bytes)\n",
                  totalResponseSize, msg_size);
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