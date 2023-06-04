#ifndef PersistenceManager_h
#define PersistenceManager_h

#pragma once

#include <Arduino.h>
#include <ArduinoJson.h>
#include <LittleFS.h>

#define CONFIG_FILE "/config.json"

struct NestedConfig {
  uint16_t nestedValue1;
  uint16_t nestedValue2;
  uint16_t nestedValue3;
  uint16_t nestedValue4;
};

struct Config {
  uint32_t value1;
  uint32_t value2;
  uint32_t value3;
  uint32_t value4;
  bool masterSwitch;
  NestedConfig nested;
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
