#include "surfaces_control.h"
void createFreeRtosTask()
{

    xTaskCreatePinnedToCore(
        surface_task_output,
        "AileronSurfaceTask",
        2048,
        (void *)&aileron_servo,
        1,
        NULL,
        app_cpu);
    xTaskCreatePinnedToCore(
        surface_task_output,
        "ElevatorSurfaceTask",
        2048,
        (void *)&elevator_servo,
        1,
        NULL,
        app_cpu);
    xTaskCreatePinnedToCore(
        surface_task_output,
        "RadderSurfaceTask",
        2048,
        (void *)&radder_servo,
        1,
        NULL,
        app_cpu);

    xTaskCreatePinnedToCore(
        control_throttle_out,
        "thrustleControlTask",
        2048,
        (void *)&throttle_esc,
        1,
        NULL,
        app_cpu);
}