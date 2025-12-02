#include "config.h"

////////////////////////////////////////////////// surfaces control transmitter ////////////////////////////////////////////////


void read_controllers_in()
{
    data.aileron = analogRead(aileron_controller_pin) / 16; // Scale 0-1023 to 0-255
    data.elevator = analogRead(elevator_controller_pin) / 16;
    data.radder = analogRead(radder_controller_pin) / 16;
    data.throttle = analogRead(throttle_controller_pin) / 16;
    data.has_payload = true;
}

////////////////////////////////////////////////// surfaces control reciver //////////////////////////////////////////////////

void surface_output(uint8_t angle, Servo servo)
{
    servo.write(map(angle, 0, 255, 0, 180));
}
void control_throttle_out(uint8_t speed)
{
    throttle_esc.writeMicroseconds(map(speed, 0, 255, MIN_THROTTLE_US, MAX_THROTTLE_US));
}

