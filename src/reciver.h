#include "config.h"

bool setup_reciver()
{
  Serial.println("Starting Receiver...");

  // You must use the same name you defined above
  if (!radio.begin())
  { // <-- FIX: Was "radio"
    Serial.println("Radio hardware is not responding!!");
    while (1)
    {
    } // Freeze
  }

  // Set the address
  radio.openReadingPipe(0, address); // <-- FIX: Was "radio"

  // Set the power level
  radio.setPALevel(RF24_PA_MIN); // <-- FIX: Was "radio"

  // Start listening!
  radio.startListening(); // <-- FIX: Was "radio"
  Serial.println("Listening for messages...");
  return true;
}

AircraftData recieve_data()
{
  // Check if there is any data available to read
  if (radio.available())
  {                             // <-- FIX: Was "radio"
    no_data = MAX_RECIVE_TRIES; // to tell when data is lost again
    // Read the data
    radio.read(&data, sizeof(data)); // <-- FIX: Was "radio"
    data.has_payload = true;
    return data;
  }
  else
  {
    // Serial.print("no_data counter: ");
    // Serial.print(no_data);
    // Serial.print(" | ");
    if (no_data == 0)
    {

      no_data = 0; // prevent underflow
      data.throttle = 0;
      data.has_payload = false;
      return data;
    }
    else
    {
      no_data--;
    }
  }

  // FIX: Return a default value if no data is available.
  // 0 is a common choice, or you could use a special value
  // like UINT16_MAX (65535) to indicate "no new data".
  // AircraftData empty_data;
  // empty_data.has_payload = false;
  return data;
}