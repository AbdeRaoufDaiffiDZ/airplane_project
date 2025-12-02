#include <Arduino.h>

#if CONFIG_FREERTOS_UNICORE
static const BaseType_t app_cpu = 0;
#else
static const BaseType_t app_cpu = 1;
#endif

// settings
static const uint8_t msg_queue_len = 5;

// Globals
static QueueHandle_t queue_1 = NULL;
static QueueHandle_t queue_2 = NULL;

void task_A(void *parameter)
{
    while(1){
        
    }
}

// void printMessages(void *parameter)
// {
//     uint8_t item;
//     while (1)
//     {
//         // see if there's a message in the queue
//         if (xQueueReceive(msg_queue, &item, 0) == pdTRUE)
//         {
//             Serial.println(item);
//         }
//         vTaskDelay(1000 / portTICK_PERIOD_MS);
//     }
// }
void setup()
{
    Serial.begin(115200);

    vTaskDelay(1000 / portTICK_PERIOD_MS);
    Serial.println();
    Serial.println("Starting Queue Example");

    // create a queue:
    queue_1 = xQueueCreate(msg_queue_len, sizeof(int));

    xTaskCreatePinnedToCore(
        task_A,
        "task_A",
        1024,
        NULL,
        1,
        NULL,
        app_cpu);
}

void loop()
{
    // static uint8_t num = 0;

    // try to add item to queue for 10 ticks, fail if queue is full
    // if(xQueueSend(msg_queue, &num, 0) != pdTRUE)
    // {
    //     Serial.println("the queue full !");
    // }
    // num++;
    // vTaskDelay( 500 / portTICK_PERIOD_MS);
}