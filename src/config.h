#pragma once // Prevents this file from being included multiple times

#include <Arduino.h>
#include <SPI.h>
#include <RF24.h>
#include <ESP32Servo.h>
// Define the pins NRF24L01+ connected to
#define CE_PIN 4
#define CSN_PIN 5
#define MAX_SEND_FAILS 10

////////////////////////////////////////////////// transmitter config //////////////////////////////////////////////////
// inputs controllers for aircraft config
#define aileron_controller_pin 33
#define elevator_controller_pin 25
#define radder_controller_pin 26
#define wheels_controller_pin 27
#define throttle_controller_pin 32
#define SWICTH_PIN 2

enum class AircraftStates_transmitter
{
    INITIALIZING,
    CONFIG_SETUP,
    IDEAL,
    READY_TO_ARM,
    TRANSMITTING,
    FAILSAFE
};
AircraftStates_transmitter current_state_transmitter = AircraftStates_transmitter::INITIALIZING;

RF24 radio(CE_PIN, CSN_PIN);
const byte address[6] = "00001";

struct AircraftData
{
    uint8_t radder;
    uint8_t elevator;
    uint8_t aileron;
    uint8_t throttle;
    bool has_payload;
};
AircraftData data = {0, 0, 0, 0, false};

void setup_inputs()
{
    pinMode(aileron_controller_pin, INPUT);
    pinMode(elevator_controller_pin, INPUT);
    pinMode(radder_controller_pin, INPUT);
    pinMode(wheels_controller_pin, INPUT);
    pinMode(throttle_controller_pin, INPUT);
    pinMode(SWICTH_PIN, INPUT);
}

////////////////////////////////////////////////// reciver config //////////////////////////////////////////////////

// outputs to actutators for aircraft config
#define aileron_servo_pin 33
#define elevator_servo_pin 25
#define radder_servo_pin 26
#define wheels_servo_pin 27
#define throttle_esc_pin 32
// ESC throttle limits in microseconds
#define MIN_THROTTLE_US 1000
#define MAX_THROTTLE_US 2000

// Maximum number of consecutive failed receive attempts before considering data lost
#define MAX_RECIVE_TRIES 5 // parashot

// DEFINE the servo objects
Servo aileron_servo, elevator_servo, radder_servo, throttle_esc;

// DEFINE the radio object and address *once*

// VARUABLES to hold received data
uint8_t no_data = MAX_RECIVE_TRIES; // Counter for lost data packets
void setup_servos()
{
    aileron_servo.attach(aileron_servo_pin);
    elevator_servo.attach(elevator_servo_pin);
    radder_servo.attach(radder_servo_pin);
    // wheels_servo.attach(wheels_servo_pin);
    throttle_esc.attach(throttle_esc_pin, MIN_THROTTLE_US, MAX_THROTTLE_US);

    // Calibrate ESC by sending max throttle signal for 4 seconds
    throttle_esc.writeMicroseconds(MAX_THROTTLE_US);
    delay(4000); // Wait for 4 seconds
    // Initialize throttle to minimum
    throttle_esc.writeMicroseconds(MIN_THROTTLE_US);
    delay(3000);
}
