#include "PersistenceManager.h"

#define CONFIG_FILE "/config.json"

PersistenceManager::PersistenceManager(const char *filename)
{
    _filename = filename;
}

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
        cfg.nested.nestedValue1 = doc["nested"]["nestedValue1"];
        cfg.nested.nestedValue2 = doc["nested"]["nestedValue2"];
        cfg.nested.nestedValue3 = doc["nested"]["nestedValue3"];
        cfg.nested.nestedValue4 = doc["nested"]["nestedValue4"];
        file.close();
    }
    return cfg;
}

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
    doc["nested"]["nestedValue1"] = cfg.nested.nestedValue1;
    doc["nested"]["nestedValue2"] = cfg.nested.nestedValue2;
    doc["nested"]["nestedValue3"] = cfg.nested.nestedValue3;
    doc["nested"]["nestedValue4"] = cfg.nested.nestedValue4;
    serializeJson(doc, file);
    file.close();
}

void PersistenceManager::begin()
{
    if (!LittleFS.begin())
    {
        Serial.println("An Error has occurred while mounting LittleFS");
        return;
    }

    // write a test configuration if the file doesn't exist yet
    if (!LittleFS.exists(_filename))
    {
        Config cfg;

        cfg.value1 = 10;
        cfg.value2 = 20;
        cfg.value3 = 30;
        cfg.value4 = 40;
        cfg.masterSwitch = true;

        cfg.nested.nestedValue1 = 100;
        cfg.nested.nestedValue2 = 200;
        cfg.nested.nestedValue3 = 300;
        cfg.nested.nestedValue4 = 400;

        writeConfig(cfg);
        Serial.println("Configuration written.");
    }
    else
    {
        Serial.println("Configuration file already exists. Skipping write.");
    }
}