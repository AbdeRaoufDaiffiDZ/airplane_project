// #include <Arduino.h>

// #if CONFIG_FREERTOS_UNICORE
// static const BaseType_t app_cpu = 0;
// #else
// static const BaseType_t app_cpu = 1;
// #endif

// const char msg[] = "FreeRTOS Basic Example";
// int serialData = 0;
// // static TaskHandle_t task_1 = NULL;
// // static TaskHandle_t task_2 = NULL;

// // void startTask1(void *parameter)
// // {

// //     int msg_ln = strlen(msg);

// //     while (1)
// //     {
// //         for (int i = 0; i < msg_ln; i++)
// //             Serial.print(msg[i]);
// //         Serial.println();
// //         vTaskDelay(1000 / portTICK_RATE_MS);
// //     }
// // }

// // void startTask2(void *parameter)
// // {
// //     while (1)
// //     {
// //         Serial.print('*');
// //         vTaskDelay(100 / portTICK_RATE_MS);
// //     }
// // }

// void serialRead_task(void *parameter)
// {
//     while (1)
//     {
//         if (Serial.available() > 0)
//         {
//             serialData = Serial.read();
//             vTaskDelay( 100 / portTICK_PERIOD_MS );
//         }
//     }
// }

// void ledBlink_task(void *parameter){
//     while(1){
//         int delay = (int) parameter;
//         digitalWrite(LED_BUILTIN, HIGH);
//         vTaskDelay(delay / portTICK_PERIOD_MS);
//         digitalWrite(LED_BUILTIN, LOW);
//         vTaskDelay(delay / portTICK_PERIOD_MS);
//     }
// }
// void setup()
// {
//     // Serial.begin(300); // you have to set your Serial Monitor to 300 baud rate

//     // vTaskDelay(100 / portTICK_PERIOD_MS);
//     // Serial.println();
//     // Serial.print("Starting FreeRTOS tasks...");

//     // Serial.print("Setup and loop task running core: ");
//     // Serial.println(xPortGetCoreID());
//     // Serial.print(" with periority: ");
//     // Serial.println(uxTaskPriorityGet(NULL));

//     // // --------------------------------------------------------------------

//     // xTaskCreatePinnedToCore(
//     //     startTask1,
//     //     "task_1",
//     //     1024,
//     //     NULL,
//     //     1,
//     //     &task_1,
//     //     app_cpu);

//     // xTaskCreatePinnedToCore(
//     //     startTask2,
//     //     "task_2",
//     //     1024,
//     //     NULL,
//     //     2,
//     //     &task_2,
//     //     app_cpu);

//     xTaskCreatePinnedToCore(
//         serialRead_task,
//         "serialRead_task",
//         1024,
//         (void*) serialData,
//         2,
//         NULL,
//         app_cpu);
    
//     xTaskCreatePinnedToCore(
//         ledBlink_task,
//         "ledBlink_task",
//         1024,
//         (void*) serialData,
//         3,
//         NULL,
//         app_cpu);
// }

// void loop()
// {

//     // for (int i = 0; i < 3; i++)
//     // {
//     //     vTaskSuspend(task_1);
//     //     vTaskDelay(2000 / portTICK_RATE_MS);
//     //     vTaskResume(task_1);
//     //     vTaskDelay(2000 / portTICK_PERIOD_MS);
//     // }

//     // if (task_1 != NULL)
//     // {
//     //     vTaskDelete(task_1);
//     //     task_1 = NULL;
//     // }
// }