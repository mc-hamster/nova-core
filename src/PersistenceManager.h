#ifndef PersistenceManager_h
#define PersistenceManager_h

#pragma once

#include <Arduino.h>
#include <ArduinoJson.h>
#include <LittleFS.h>

#define CONFIG_FILE "/config.json"

struct LightConfig {
  uint16_t brightness;
  uint16_t program;
  uint16_t sin;
  uint16_t updatesPerSecond;
  bool reverse;
  bool fire;
  bool localDisable;
};

struct Config {
  uint32_t value1;
  uint32_t value2;
  uint32_t value3;
  uint32_t value4;
  bool masterSwitch;
  LightConfig lightConfig;
};

class PersistenceManager {
  public:
    PersistenceManager(const char* filename);
    void begin();
    Config readConfig();
    void writeConfig(Config cfg);

  private:
    const char* _filename;
};


#endif
