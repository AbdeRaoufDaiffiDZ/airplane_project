#include "FSM_transmitter.h"
// #include "reciver.h"
// #include "config.h"
Servo servo;
void setup()
{

    Serial.begin(115200);
    // // Add an initial brief printout to show the device is running
    setup_inputs();

    //////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////

    // while (!setup_reciver())
    //     ;
    // setup_servos();
    // queue_aircraft_data = xQueueCreate(1, sizeof(AircraftData));
    // xTaskCreatePinnedToCore(
    //     recive_task,
    //     "recive_task",
    //     2048,
    //     NULL,
    //     1,
    //     NULL,
    //     app_cpu_0);

    // xTaskCreatePinnedToCore(
    //     actuators_task,
    //     "actuators_task",
    //     2048,
    //     NULL,
    //     1,
    //     NULL,
    //     app_cpu_1);
}

void loop()
{
    // The FSM_transmitter function will handle reading the switch,
    FSM_transmitter();
}