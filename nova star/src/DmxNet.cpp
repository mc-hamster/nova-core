#include <Arduino.h>
#include "DmxNet.h"
#include "configuration.h"
#include "esp_dmx.h"
#include <FastLED.h>

/*

This class is responsible for sending and receiving messages over the NovaNet protocol.

*/

DmxNet *dmxNet = NULL;

dmx_port_t dmxPort = 1;

unsigned long lastUpdate = millis();

#define NUM_LEDS 4
CRGBArray<NUM_LEDS> leds;
uint8_t hue = 0;

DmxNet::DmxNet()
{

  Serial.println("DmxNet setup started");

  /* Set the DMX hardware pins to the pins that we want to use. */
  dmx_set_pin(dmxPort, DMX_DI, DMX_RO, 0);

  /* Now we can install the DMX driver! We'll tell it which DMX port to use and
    which interrupt priority it should have. If you aren't sure which interrupt
    priority to use, you can use the macro `DMX_DEFAULT_INTR_FLAG` to set the
    interrupt to its default settings.*/
  dmx_driver_install(dmxPort, DMX_DEFAULT_INTR_FLAGS);
  // Setup goes in here
}

void DmxNet::loop()
{
  static uint8_t hue;

  /* Get the current time since boot in milliseconds so that we can find out how
   long it has been since we last updated data and printed to the Serial
   Monitor. */
  unsigned long now = millis();

  if (millis() - lastReceivededPacketTime < 5 * 1000)
  {
    // Serial.println("Received packet less than 5 seconds ago");
    //  Do something if the last packet was received less than 10 seconds ago
    dmx_write(dmxPort, data, DMX_PACKET_SIZE);

    if (0)
    {
      Serial.print("D: ");
      for (int i = 0; i < 21; i++)
      {
        Serial.print(data[i], HEX);
        Serial.print(" ");
      }
      Serial.println();
    }
  }
  else if (now - lastUpdate >= 70)
  {
    Serial.println("No novanet data received in 5 seconds, sending test data");

    /* Increment every byte in our packet. Notice we don't increment the zeroeth
      byte, since that is our DMX start code. Then we must write our changes to
      the DMX packet. Maximum is kept in DMX_PACKET_SIZE */
    data[0] = 0x00; // Start code byte.

    for (int i = 0; i < NUM_LEDS; i++)
    {
      // let's set an led value
      leds[i] = CHSV(hue + (i * 127), 255, 255);
    }

    data[1] = 0xff; // Brightness
    data[2] = leds[0].r;
    data[3] = leds[0].g;
    data[4] = leds[0].b;

    data[8] = 0xff; // Brightness
    data[9] = leds[1].r;
    data[10] = leds[1].g;
    data[11] = leds[1].b;

    data[15] = 0xff; // Brightness
    data[16] = leds[2].r;
    data[17] = leds[2].g;
    data[18] = leds[2].b;

    data[22] = 0xff; // Brightness
    data[23] = leds[3].r;
    data[24] = leds[3].g;
    data[25] = leds[3].b;

    hue++;

    dmx_write(dmxPort, data, DMX_PACKET_SIZE);

    lastUpdate = now;
  }

  /* Now we can transmit the DMX packet! */
  dmx_send(dmxPort, DMX_PACKET_SIZE);

  /* If we have no more work to do, we will wait until we are done sending our
    DMX packet. */
  if (!dmx_wait_sent(dmxPort, DMX_TIMEOUT_TICK))
  {
    /* If we get here, it means that we timed out waiting for the DMX packet to
      send. */
    Serial.println("DMX: Timed out waiting for DMX packet to send.");
  }
}

/**
 * @brief Receives DMX512 data and copies it into the data buffer.
 * 
 * When DMX512 data is received, the function sets the time that the DMX packet was received and copies the received data into the data buffer.
 * 
 * @param receivedData Pointer to the received DMX512 data.
 */
void DmxNet::receiveDMX512(const uint8_t *receivedData)
{
  /*
   When we receive DMX512:
     - Set the time that the DMX packet was received.
     - Copy the received DMX512 data into the data buffer.
  */

  lastReceivededPacketTime = millis();

  // Copy the received data into the data buffer
  memcpy(data, receivedData, DMX_PACKET_SIZE);

  // Print the received data to the Serial Monitor (optional)
  if (false)
  {
    Serial.print("R: ");
    for (int i = 0; i < DMX_PACKET_SIZE; i++)
    {
      Serial.print(receivedData[i], HEX);
      Serial.print(" ");
    }
    Serial.println();
  }

  // Print the copied data to the Serial Monitor (optional)
  if (false)
  {
    Serial.print("D: ");
    for (int i = 0; i < DMX_PACKET_SIZE; i++)
    {
      Serial.print(data[i], HEX);
      Serial.print(" ");
    }
    Serial.println();
  }
}