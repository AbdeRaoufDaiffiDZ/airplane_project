#include "config.h"

bool setup_sender()
{
  Serial.println("Starting Sender...");

  if (!radio.begin())
  {
    
    Serial.println("Radio hardware is not responding!!");
    return false;
  }
  
  // Set the address
  radio.openWritingPipe(address);

  // Set the power level (RF24_PA_MIN, RF24_PA_LOW, RF24_PA_HIGH, RF24_PA_MAX)
  radio.setPALevel(RF24_PA_MIN);

  // Stop listening, we are the sender
  radio.stopListening(); 
  
  // --- Perform the Handshake Check using Auto-Acknowledge ---
  AircraftData data;
  // Initialize data struct...
  data.has_payload = true; // Use this as the handshake signal

  // The 'radio.write' call will wait for the ACK from the receiver.
  // If it gets an ACK, the receiver is present, and it returns true.
  bool is_connected = radio.write(&data, sizeof(data));

  if (is_connected)
  {
    Serial.println("Sender is ready and connected.");
    return true;
  }
  else
  {
    Serial.println("No ACK from receiver (not connected).");
    return false;
  }
}

void send_message(AircraftData data)
{

  bool tx_ok = radio.write(&data, sizeof(data));

  if (tx_ok)
  {
  }
  else
  {
    Serial.println("Failed");
  }

  delay(10); // Wait a second before sending again
}
