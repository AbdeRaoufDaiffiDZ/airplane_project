#include "config.h"
#include "sender.h"
#include "surfaces_control.h"
void FSM_transmitter()
{

    // Use a static variable to track retries across function calls
    static uint8_t count_send_fails = 0;
    static bool button_state = false;
    switch (current_state_transmitter)
    {
    case AircraftStates_transmitter::INITIALIZING:
        // One-time setup
        current_state_transmitter = AircraftStates_transmitter::CONFIG_SETUP;
        break;

    case AircraftStates_transmitter::CONFIG_SETUP:
        Serial.print("Attempting connection... ");

        if (setup_sender()) // Handshake successful
        {
            count_send_fails = 0; // Reset counter
                                  // Transition to the next safe state
            Serial.println("Transition to IDEAL.");
            current_state_transmitter = AircraftStates_transmitter::TRANSMITTING; //////////////////  you ust change this
        }
        else // Handshake failed
        {
            count_send_fails++;
            Serial.print("Failed (Attempt ");
            Serial.print(count_send_fails);
            Serial.println(")");

            if (count_send_fails >= MAX_SEND_FAILS)
            {
                // Max attempts reached, transition to critical state
                current_state_transmitter = AircraftStates_transmitter::FAILSAFE;
                Serial.println("Max retries reached. Transition to FAILSAFE.");
            }
            // If we still have retries left, stay in CONFIG_SETUP
            // and try again on the next loop iteration.
            delay(100); // Small delay before next retry
        }
        break;

    case AircraftStates_transmitter::IDEAL:
        // Check for the arming condition (e.g., read the SWICTH_PIN)
        Serial.print("Switch State: ");
        Serial.println(digitalRead(SWICTH_PIN));

        if (digitalRead(SWICTH_PIN) == HIGH)
        {
            sleep(10); // Debounce delay
            button_state = !button_state;

            Serial.print("Switch State: ");
            Serial.println(button_state);
        }
        if (button_state)
        {
            Serial.println("Arm switch activated. Transition to READY_TO_ARM.");
            current_state_transmitter = AircraftStates_transmitter::READY_TO_ARM;
        }
        data.has_payload = false; // No actual control data
        data.throttle = analogRead(throttle_controller_pin);     // Set throttle to minimum for safety
        send_message(data);       // Send empty data as heartbeat
        // ... (Keep sending heartbeat or status update here) ...
        break;

    case AircraftStates_transmitter::READY_TO_ARM:
        // Logic to check if sticks are centered (safety check)
        // ...

        // If checks pass, transition to TRANSMITTING
        // current_state_transmitter = AircraftStates_transmitter::TRANSMITTING;
        data.has_payload = false; // No actual control data
        data.throttle = 50;     // Set throttle to minimum for safety
        send_message(data);      // Send empty data as heartbeat

        // If arm switch is turned off, go back to IDEAL
        if (button_state == LOW)
        {
            Serial.println("Arm switch deactivated. Transition to IDEAL.");
            current_state_transmitter = AircraftStates_transmitter::IDEAL;
        }
        break;

    // Add logic for TRANSMITTING and FAILSAFE
    case AircraftStates_transmitter::TRANSMITTING:
        // Read analog sticks and call send_message()
        data = read_controllers_in();
        send_message(data);
        // ...
        break;

    case AircraftStates_transmitter::FAILSAFE:
        // Alert the user (LED/Buzzer) that communication failed
        // ...
        break;
    }
}