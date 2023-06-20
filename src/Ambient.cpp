#include <Arduino.h>
#include "Ambient.h"
#include "configuration.h"
#include "NovaIO.h"
#include "SerialProto.h"
#include "main.h"

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

    // Setup goes in here
}

void Ambient::loop()
{
}

void Ambient::sendProtobuf()
{
 /*
    // Create a DmxRequest object
    messaging_DmxRequest dmxRequest = {};
    // Fill in values for DmxRequest
    dmxRequest.ack = true;
    // For simplicity, let's say we just want to send a sequence of values from 1 to 10
    for (int i = 0; i < 10; i++)
    {
        dmxRequest.values[i] = i + 1;
    }
    dmxRequest.values_count = 10; // Don't forget to set the count

    // Create a Request object and set its type to DMX_REQUEST
    messaging_Request request = {};
    request.which_request_payload = Request_dmx_request_tag;
    request.request_payload.dmx_request = dmxRequest;

    uint8_t buffer[512]; // adjust buffer size if necessary
    pb_ostream_t stream = pb_ostream_from_buffer(buffer, sizeof(buffer));

    if (!pb_encode(&stream, Request_fields, &request))
    {
        // Handle the error...
    }
    Serial2.write(buffer, stream.bytes_written);
    */
}

