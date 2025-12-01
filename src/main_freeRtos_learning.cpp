// #include <Arduino.h>

// #if CONFIG_FREERTOS_UNICORE
// static const BaseType_t app_cpu = 0;
// #else
// static const BaseType_t app_cpu = 1;
// #endif

// // settings
// static const uint8_t msg_queue_len = 5;

// // Globals
// static QueueHandle_t msg_queue = NULL;

// void printMessages(void *parameter)
// {
//     uint8_t item;
//     while (1)
//     {
//         // see if there's a message in the queue
//         if (xQueueReceive(msg_queue, (void *)item, 0) == pdTRUE)
//         {
//             Serial.println(item);
//         }
//         vTaskDelay(1000 / portTICK_PERIOD_MS);
//     }
// }
// void setup()
// {
//     Serial.begin(115200);

//     vTaskDelay(1000 / portTICK_PERIOD_MS);
//     Serial.println();
//     Serial.println("Starting Queue Example");

//     // create a queue:
//     msg_queue = xQueueCreate(msg_queue_len, sizeof(int));

//     xTaskCreatePinnedToCore(
//         printMessages,
//         "PrintMessages",
//         4096,
//         NULL,
//         1,
//         NULL,
//         app_cpu);
// }

// void loop() {
//     static uint8_t num = 0;

//     // try to add item to queue for 10 ticks, fail if queue is full
//     if(xQueueSend(msg_queue, (void *)num, 0) != pdTRUE)
//     {
//         Serial.println("the queue full !");
//     }
//     num++;
//     vTaskDelay( 1000 / portTICK_PERIOD_MS);
// }