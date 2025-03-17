#ifndef WIFI_CONFIG_H
#define WIFI_CONFIG_H

// WARNING: This is a development/testing configuration.
// DO NOT put real production credentials in this file.
// Instead, copy this file and update with your actual credentials,
// your copy will be ignored by git.

struct WifiNetwork {
    const char* ssid;
    const char* password;
};

// Development networks configuration
// These are dummy values for testing/development
static const WifiNetwork networks[] = {
    {"things", "stuffAndThings!"},
    {"test-network", "test-password"},
};

// Number of networks in the array
static const int NETWORK_COUNT = sizeof(networks) / sizeof(networks[0]);

#endif // WIFI_CONFIG_H