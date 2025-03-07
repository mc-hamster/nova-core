#include "utilities.h"
#include <WiFi.h>
#include "../configuration.h"

String getLastFourOfMac() {
    String mac = WiFi.macAddress();
    String lastPart = mac.substring(mac.length() - 5);  // Get last 5 chars including colon
    lastPart.replace(":", "");  // Remove the colon
    return lastPart;
}

void setLedBrightness(uint8_t led, bool isOn) {
    uint8_t channel;
    switch(led) {
      case BUTTON_RED_OUT: channel = LEDC_CHANNEL_RED; break;
      case BUTTON_GREEN_OUT: channel = LEDC_CHANNEL_GREEN; break;
      case BUTTON_BLUE_OUT: channel = LEDC_CHANNEL_BLUE; break;
      case BUTTON_YELLOW_OUT: channel = LEDC_CHANNEL_YELLOW; break;
      case BUTTON_WHITE_OUT: channel = LEDC_CHANNEL_RESET; break;
      default: return;
    }
    ledcWrite(channel, isOn ? LEDC_FULL_DUTY : LEDC_DIM_DUTY);
}
