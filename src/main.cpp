#include "FSM_transmitter.h"
#include "reciver.h"

void setup()
{
  // setup_inputs(); // Setup analog stick pins and the SWICTH_PIN
  // setup_sender();

  Serial.begin(115200);
  // // Add an initial brief printout to show the device is running
  Serial.println("Transmitter Initializing...");
  setup_servos();
  setup_reciver();
}

void loop()
{
  // The FSM_transmitter function will handle reading the switch,
  // checking states, and calling the appropriate functions (like setup_sender/send_message).
  // FSM_transmitter();
  // Serial.print("throtel: ");
  // Serial.println(analogRead(throttle_controller_pin));
  AircraftData data = recieve_data();
  //
  Serial.print("Radder: ");
  Serial.print(data.radder);
  Serial.print(" | Elevator: ");
  Serial.print(data.elevator);
  Serial.print(" | Aileron: ");
  Serial.print(data.aileron);
  Serial.print(" | Throttle_recived: ");
  Serial.print(data.throttle);
  Serial.print(" | Has Payload: ");
  Serial.println(data.has_payload);
  // A small delay helps stabilize the loop and radio operation.
  //
  int throttleValue = map(data.throttle, 0, 255, 1000, 2000);
  aileron_servo.write(map(data.aileron, 0, 255, 0, 180));
  elevator_servo.write(map(data.elevator, 0, 255, 0, 180));
  radder_servo.write(map(data.radder, 0, 255, 0, 180));
  wheels_servo.write(map(data.wheels, 0,  255, 0, 180));
  // Send signal to ESC
  //
  throttle_esc.writeMicroseconds(throttleValue);
  //
  // Debugging
  // Serial.print(" | Throttle_converted: "); Serial.println(throttleValue);

  // delay(20); // Small delay for stability
  delay(10);
}