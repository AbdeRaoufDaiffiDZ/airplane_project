// #include "FSM_transmitter.h"
#include "reciver.h"
#include "config.h"
Servo servo;
void setup()
{

    Serial.begin(115200);
    // // Add an initial brief printout to show the device is running
    // setup_inputs();
    setup_servos();
    setup_reciver();

    xTaskCreatePinnedToCore(
        recive_task,
        "recive_task",
        1024,
        NULL,
        1,
        NULL,
        1);
    xTaskCreatePinnedToCore(
        actuators_task,
        "actuators_task",
        1024,
        NULL,
        1,
        NULL,
        1);
}

void loop()
{
    // The FSM_transmitter function will handle reading the switch,
    // checking states, and calling the appropriate functions (like setup_sender/send_message).
    // FSM_transmitter();
    // Serial.print("throtel: ");
    // Serial.println(analogRead(throttle_controller_pin));
    // recieve_data();
    //
    //   Serial.print("Radder: ");
    //   Serial.print(data.radder);
    //   Serial.print(" | Elevator: ");
    //   Serial.print(data.elevator);
    //   Serial.print(" | Aileron: ");
    //   Serial.print(data.aileron);
    //   Serial.print(" | Throttle_recived: ");
    //   Serial.print(data.throttle);
    //   Serial.print(" | Has Payload: ");
    //   Serial.println(data.has_payload);
    // A small delay helps stabilize the loop and radio operation.
    //

    // surface_output(data.aileron, aileron_servo);
    // surface_output(data.elevator, elevator_servo);
    // surface_output(data.radder, radder_servo);
    // control_throttle_out(data.throttle);

    // Debugging
    // Serial.print(" | Throttle_converted: "); Serial.println(throttleValue);
    // test_servos();

    // for (int i = 90; i < 180; i++)
    // {
    //     elevator_servo.write(i);
    //     delay(10);
    // }
    // for (int i = 180; i > 90; i--)
    // {
    //     elevator_servo.write(i);
    //     delay(10);
    // }

    // Small delay for stability
    // delay(10);
}