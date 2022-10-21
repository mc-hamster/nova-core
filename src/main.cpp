#include <Arduino.h>

TaskHandle_t Task1;
TaskHandle_t Task2;

const int led_1 = 32;
const int led_2 = 25;

void Task1code(void *parameter)
{
    Serial.print("Task1 is running on core ");
    Serial.println(xPortGetCoreID());

    for (;;)
    {
        digitalWrite(led_1, HIGH);
        delay(500);
        digitalWrite(led_1, LOW);
        delay(500);
    }
}

void Task2code(void *parameter)
{
    Serial.print("Task2 is running on core ");
    Serial.println(xPortGetCoreID());

    for (;;)
    {
        digitalWrite(led_2, HIGH);
        delay(1000);
        digitalWrite(led_2, LOW);
        delay(1000);
    }
}

void setup()
{
    Serial.begin(115200);
    Serial.print("setup() is running on core ");
    Serial.println(xPortGetCoreID());

    pinMode(led_1, OUTPUT);
    pinMode(led_2, OUTPUT);

    /*
        core1 - main program code
        core0 - esp32 network stack
    */

    xTaskCreatePinnedToCore(Task1code, "Task1", 10000, NULL, 1, &Task1, 0);
    delay(500);

    xTaskCreatePinnedToCore(Task2code, "Task2", 10000, NULL, 1, &Task2, 1);
    delay(500);
}

void loop()
{
    Serial.print("loop() is running on core ");
    Serial.println(xPortGetCoreID());
}