#include "surfaces_control.h"
#define MIN_ANGLE 0
#define CENTER_ANGLE 128
#define MAX_ANGLE 255


void test_servos()
{
    surface_output(MIN_ANGLE, aileron_servo);
    delay(1000);
    surface_output(CENTER_ANGLE, aileron_servo);
    delay(1000);
    surface_output(MAX_ANGLE, aileron_servo);
    delay(1000);

    surface_output(MIN_ANGLE, elevator_servo);
    delay(1000);
    surface_output(CENTER_ANGLE, elevator_servo);
    delay(1000);
    surface_output(MAX_ANGLE, elevator_servo);
    delay(1000);
    surface_output(MIN_ANGLE, radder_servo);

    delay(1000);
    surface_output(CENTER_ANGLE, radder_servo);

    delay(1000);
    surface_output(MAX_ANGLE, radder_servo);
    delay(1000);
}

void test_throttle()
{
    for (uint8_t speed = MIN_THROTTLE_US; speed <= MAX_THROTTLE_US; speed += 5)
    {
        control_throttle_out(speed);
        delay(200);
    }
    for (uint8_t speed = MAX_THROTTLE_US; speed >= MIN_THROTTLE_US; speed -= 5)
    {
        control_throttle_out(speed);
        delay(200);
    }
}