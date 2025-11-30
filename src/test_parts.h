#include "surfaces_control.h"

#define MIN_ANGLE 0
#define CENTER_ANGLE 128
#define MAX_ANGLE 255
void test_servos()
{
    control_aileron_out(MIN_ANGLE);
    delay(1000);
    control_aileron_out(CENTER_ANGLE);
    delay(1000);
    control_aileron_out(MAX_ANGLE);
    delay(1000);

    control_elevator_out(MIN_ANGLE);
    delay(1000);
    control_elevator_out(CENTER_ANGLE);
    delay(1000);
    control_elevator_out(MAX_ANGLE);
    delay(1000);
    control_radder_out(MIN_ANGLE);
    delay(1000);
    control_radder_out(CENTER_ANGLE);
    delay(1000);
    control_radder_out(MAX_ANGLE);
    delay(1000);
}

void test_throttle()
{
    for (uint8_t angle = MIN_ANGLE; angle <= CENTER_ANGLE; angle += 5)
    {
        control_throttle_out(angle);
        delay(200);
    }
    for (uint8_t angle = CENTER_ANGLE; angle >= MIN_ANGLE; angle -= 5)
    {
        control_throttle_out(angle);
        delay(200);
    }
}