#include "sender.h"
#include "reciver.h"
#include "surfaces_control.h"

static uint16_t counter = 0;

void read_and_send()
{
    //read controllers and control surfaces and send data through NRF24L01
  AircraftData controller_data = read_controllers_in();
  send_message(controller_data);
}

void send_only()
{
    //send only counter data through NRF24L01
  AircraftData data;
  data.aileron = counter % 256;
  data.elevator = (counter + 1) % 256;
  data.throttle = (counter + 2) % 256;
  data.radder = (counter + 3) % 256;
  data.wheels = (counter + 4) % 256;
  send_message(data);
  counter++;
}


void recive_and_control()
{
  
    //recive data through NRF24L01 and control surfaces
  AircraftData received_data = recieve_data();
  if (received_data.has_payload)
  { // Check if we received valid data
    control_aileron_out(received_data.aileron);
    control_elevator_out(received_data.elevator);
    control_throttle_out(received_data.throttle);
    control_radder_out(received_data.radder);
    control_wheels_out(received_data.wheels);
  }
}

void recive_only()
{
    //recive data through NRF24L01 only
  AircraftData received_data = recieve_data();
  if (received_data.has_payload)
  { // Check if we received valid data
    Serial.print("aileron: ");
    Serial.print(received_data.aileron);
    Serial.print(" elevator: ");
    Serial.print(received_data.elevator);
    Serial.print(" throttle: ");
    Serial.print(received_data.throttle);
    Serial.print(" radder: ");
    Serial.print(received_data.radder);
    Serial.print(" wheels: ");
    Serial.println(received_data.wheels);
    Serial.println("-----");
  }
}

void time_count(){
    unsigned long timeMillis = millis();

// Convert milliseconds to total seconds
unsigned long totalSeconds = timeMillis / 1000;

// Calculate hours
int hours = totalSeconds / 3600;

// Calculate remaining seconds after subtracting hours
int remainingSeconds = totalSeconds % 3600;

// Calculate minutes from the remaining seconds
int minutes = remainingSeconds / 60;

// Calculate final seconds
int seconds = remainingSeconds % 60;

// Print the formatted time
Serial.print("time: ");
Serial.print(hours);
Serial.print("h ");
Serial.print(minutes);
Serial.print("m ");
Serial.print(seconds);
Serial.println("s");
}