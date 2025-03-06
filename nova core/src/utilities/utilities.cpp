#include "utilities.h"
#include <WiFi.h>

String getLastFourOfMac() {
    String mac = WiFi.macAddress();
    String lastPart = mac.substring(mac.length() - 5);  // Get last 5 chars including colon
    lastPart.replace(":", "");  // Remove the colon
    return lastPart;
}
