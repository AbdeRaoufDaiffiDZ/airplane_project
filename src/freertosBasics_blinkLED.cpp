// #include <Arduino.h>

// #if CONFIG_FREERTOS_UNICORE
// static const BaseType_t app_cpu = 0;
// #else
// static const BaseType_t app_cpu = 1; // BaseType_t means the bus width of the processor
// #endif


// static const int led_pin = BUILTIN_LED;

// void toogleLED(void *parameter)
// {
//     int delay = (int) parameter;
//     while (true)
//     {
//         digitalWrite(led_pin, HIGH);
//         vTaskDelay(delay / portTICK_PERIOD_MS);
//         digitalWrite(led_pin, LOW);
//         vTaskDelay(delay / portTICK_PERIOD_MS); // this function stops the task and not the proccessor
//         // it uses the timer tick to count the delay  using esp32 timer frequency
//     }
// }

// void setup()
// {
//     pinMode(led_pin, OUTPUT);
//     xTaskCreatePinnedToCore(
//         toogleLED,
//         "toggleLED",
//         1024,
//         (void*) 500,
//         1,
//         NULL,
//         app_cpu);

//     xTaskCreate(
//         toogleLED,
//         "toogleLED2",
//         1024,
//         (void*) 100,
//         1,
//         NULL);
// }

// void loop()
// {
// }