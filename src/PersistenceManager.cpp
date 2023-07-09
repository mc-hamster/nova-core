#include "PersistenceManager.h"

#define CONFIG_FILE "/config.json"

PersistenceManager::PersistenceManager(const char *filename)
{
    _filename = filename;
}

// read the configuration from the file system
Config PersistenceManager::readConfig()
{
    Config cfg;
    if (LittleFS.exists(_filename))
    {
        File file = LittleFS.open(_filename, "r");
        StaticJsonDocument<200> doc;
        deserializeJson(doc, file);
        cfg.value1 = doc["value1"];
        cfg.value2 = doc["value2"];
        cfg.value3 = doc["value3"];
        cfg.value4 = doc["value4"];
        cfg.masterSwitch = doc["masterSwitch"];

        cfg.lightConfig.brightness = doc["lightConfig"]["brightness"];
        cfg.lightConfig.program = doc["lightConfig"]["program"];
        cfg.lightConfig.sin = doc["lightConfig"]["sin"];
        cfg.lightConfig.reverse = doc["lightConfig"]["reverse"];
        cfg.lightConfig.fire = doc["lightConfig"]["fire"];
        cfg.lightConfig.updatesPerSecond = doc["lightConfig"]["updatesPerSecond"];

        file.close();
    }
    return cfg;
}

// write the configuration to the file system
void PersistenceManager::writeConfig(Config cfg)
{
    LittleFS.remove(_filename);
    File file = LittleFS.open(_filename, "w");
    StaticJsonDocument<200> doc;
    doc["value1"] = cfg.value1;
    doc["value2"] = cfg.value2;
    doc["value3"] = cfg.value3;
    doc["value4"] = cfg.value4;
    doc["masterSwitch"] = cfg.masterSwitch;
    doc["lightConfig"]["brightness"] = cfg.lightConfig.brightness;
    doc["lightConfig"]["program"] = cfg.lightConfig.program;
    doc["lightConfig"]["sin"] = cfg.lightConfig.sin;
    doc["lightConfig"]["reverse"] = cfg.lightConfig.reverse;
    doc["lightConfig"]["fire"] = cfg.lightConfig.fire;
    doc["lightConfig"]["updatesPerSecond"] = cfg.lightConfig.updatesPerSecond;

    serializeJson(doc, file);
    file.close();
}

void PersistenceManager::begin()
{

    /*
    if (!LittleFS.begin())
    {
        Serial.println("An Error has occurred while mounting LittleFS");
        return;
    }
    */

    // write a test configuration if the file doesn't exist yet
    if (!LittleFS.exists(_filename))
    {
        static Config cfg;

        cfg.value1 = 10;
        cfg.value2 = 20;
        cfg.value3 = 30;
        cfg.value4 = 40;
        cfg.masterSwitch = true;

        cfg.lightConfig.brightness = 255;
        cfg.lightConfig.program = 1;
        cfg.lightConfig.sin = 0;
        cfg.lightConfig.reverse = 0;
        cfg.lightConfig.fire = 0;
        cfg.lightConfig.updatesPerSecond = 100;

        writeConfig(cfg);
        Serial.println("Configuration written.");
    }
    else
    {
        Serial.println("Configuration file already exists. Skipping write.");
    }
}