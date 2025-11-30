#include "config.h"
void control_aileron_out(uint8_t angle)
{
    aileron_servo.write(angle);
}
void control_elevator_out(uint8_t angle)
{
    elevator_servo.write(angle);
}
void control_radder_out(uint8_t angle)
{
    radder_servo.write(angle);
}
void control_wheels_out(uint8_t angle)
{
    wheels_servo.write(angle);
}
void control_throttle_out(uint8_t angle)
{
    int microseconds = map(angle, 0, 255, 0, 180);
    throttle_esc.writeMicroseconds(microseconds);
}

AircraftData read_controllers_in()
{
    AircraftData data;
    data.aileron = analogRead(aileron_controller_pin) / 16; // Scale 0-1023 to 0-255
    data.elevator = analogRead(elevator_controller_pin) / 16;
    data.radder = analogRead(radder_controller_pin) / 16;
    data.throttle = analogRead(throttle_controller_pin) / 16;
    data.wheels = analogRead(wheels_controller_pin) / 16;
    data.has_payload = true;
    return data;
}
