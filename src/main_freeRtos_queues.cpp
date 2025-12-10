// #include <Arduino.h>

// #if CONFIG_FREERTOS_UNICORE
// static const BaseType_t app_cpu = 0;
// #else
// static const BaseType_t app_cpu = 1;
// #endif

// // settings
// static const uint8_t msg_queue_len = 5;

// // Globals
// static QueueHandle_t queue_1 = NULL;
// static QueueHandle_t queue_2 = NULL;
// #define MAX_SERIAL_BUFFER_SIZE 50
// void task_A(void *parameter)
// {
//     char *data_ptr = NULL;
//     char serial_data[MAX_SERIAL_BUFFER_SIZE];
//     uint8_t i = 0;
//     while (1)
//     {
//         if (xQueueReceive(queue_2, &data_ptr, 0) == pdTRUE)
//         {
//             Serial.print("Received in Task A: ");
//             Serial.println(*((uint16_t *)data_ptr));

//             vPortFree(data_ptr);
//             data_ptr = NULL;
//         }
//         while (Serial.available() > 0)
//         {
//             char input = Serial.read();
//             if (input == '\n')
//             {
//                 if (i > 0)
//                 {
//                     serial_data[i] = '\0';
//                 }
//                 Serial.print("User Input: ");
//                 Serial.println(serial_data);
//                 char *msg = (char *)pvPortMalloc(i + 1);
//                 memcpy(msg, serial_data, sizeof(char) * i);
//                 i = 0;

//                 if (xQueueSend(queue_1, &msg, 0) != pdTRUE)
//                 {
//                     vPortFree(msg); // If send fails, free the allocated memory here!
//                 }
//             }
//             else if (i < MAX_SERIAL_BUFFER_SIZE - 1)
//             {
//                 serial_data[i++] = input;
//             }
//         }
//         vTaskDelay(1 / portTICK_PERIOD_MS);
//     }
// }

// void task_B(void *parameter)
// {
//     char *data_ptr = NULL;
//     uint16_t delay = 500; // default delay in ms
//     uint8_t i = 0;
//     while (1)
//     {
//         if (xQueueReceive(queue_1, &data_ptr, 0) == pdTRUE)
//         {
//             delay = atoi(data_ptr);
//             Serial.print("Received in Task B: ");
//             Serial.println(delay);
//             vPortFree(data_ptr);
//             data_ptr = NULL;
//         }
//         else
//         {
//         }
//         digitalWrite(LED_BUILTIN, HIGH);
//         vTaskDelay(delay / portTICK_PERIOD_MS);
//         digitalWrite(LED_BUILTIN, LOW);
//         vTaskDelay(delay / portTICK_PERIOD_MS);
//         if (i >= 100)
//         {
//             char *msg = (char *)pvPortMalloc(sizeof(delay) + 1);
//             memcpy(msg, &delay, sizeof(delay));
//             if (xQueueSend(queue_2, &msg, 0) != pdTRUE)
//             {
//                 vPortFree(msg); // Must free if send fails
//             }
//             i = 0;
//         }
//         i++;
//         vTaskDelay(1 / portTICK_PERIOD_MS);
//     }
// }
// // void printMessages(void *parameter)
// // {
// //     uint8_t item;
// //     while (1)
// //     {
// //         // see if there's a message in the queue
// //         if (xQueueReceive(msg_queue, &item, 0) == pdTRUE)
// //         {
// //             Serial.println(item);
// //         }
// //         vTaskDelay(1000 / portTICK_PERIOD_MS);
// //     }
// // }
// void setup()
// {
//     Serial.begin(115200);
//     pinMode(LED_BUILTIN, OUTPUT);
//     vTaskDelay(1000 / portTICK_PERIOD_MS);
//     Serial.println();
//     Serial.println("Starting Queue Example");
//     while (!Serial)
//         ;
//     // create a queue:
//     queue_1 = xQueueCreate(msg_queue_len, sizeof(char *));
//     queue_2 = xQueueCreate(msg_queue_len, sizeof(char *));
//     xTaskCreatePinnedToCore(
//         task_A,
//         "task_A",
//         1024,
//         NULL,
//         1,
//         NULL,
//         app_cpu);

//     xTaskCreatePinnedToCore(
//         task_B,
//         "task_B",
//         1024,
//         NULL,
//         1,
//         NULL,
//         app_cpu);
// }

// void loop()
// {
//     // static uint8_t num = 0;

//     // try to add item to queue for 10 ticks, fail if queue is full
//     // if(xQueueSend(msg_queue, &num, 0) != pdTRUE)
//     // {
//     //     Serial.println("the queue full !");
//     // }
//     // num++;
//     // vTaskDelay( 500 / portTICK_PERIOD_MS);
// }