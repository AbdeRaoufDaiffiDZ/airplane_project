#include "config.h"
#include "surfaces_control.h"
bool setup_reciver()
{
  // Serial.println("Starting Receiver...");

  // You must use the same name you defined above
  if (!radio.begin())
  {
    // Serial.println("Radio hardware is not responding!!");
    return false;
  }

  // Set the address
  radio.openReadingPipe(0, address);

  // Set the power level
  radio.setPALevel(RF24_PA_MIN);

  // Start listening!
  radio.startListening();
  Serial.println("Listening for messages...");
  return true;
}

// AircraftData recieve_data()
// {
//   // Check if there is any data available to read
//   if (radio.available())
//   {
//     no_data = MAX_RECIVE_TRIES; // to tell when data is lost again
//     // Read the data
//     radio.read(&data, sizeof(data));
//     data.has_payload = true;
//     return data;
//   }
//   else
//   {
//     if (no_data == 0)
//     {

//       no_data = 0; // prevent underflow
//       data.throttle = 0;
//       data.has_payload = false;
//       return data;
//     }
//     else
//     {
//       no_data--;
//     }
//   }
//   return data;
// }

void recive_task(void *parameter)
{
  AircraftData recived_data;
  uint8_t data_lost_count = 0; // Counts consecutive failures

  while (1)
  {
    // 1. Check for success first
    if (radio.available())
    {
      radio.read(&recived_data, sizeof(recived_data));
      recived_data.has_payload = true; // Always true on success
      data_lost_count = 0;             // Reset counter
    }
    // // 2. Handle failure
    else if (data_lost_count < MAX_RECIVE_TRIES)
    {
      data_lost_count++; // Count failure
    }
    // // 3. Handle sustained failure
    else
    {
      // Only update the structure once after MAX_RECIVE_TRIES fail
      recived_data.has_payload = false;
    }
    // 4. Send with a brief timeout
    // Inside recive_task:
    if (xQueueSend(queue_aircraft_data, &recived_data, portMAX_DELAY) != pdTRUE)
    {
      // Log a severe error if the consumer task is stuck/unresponsive for 500ms
      Serial.println("FATAL: Consumer task unresponsive. Dropping data!");
    }
    // 5. Use a larger delay for efficiency
    vTaskDelay(50 / portTICK_PERIOD_MS);
  }
}

void actuators_task(void *parameter)
{
  AircraftData recived_data;
  while (1)
  {
    if (xQueueReceive(queue_aircraft_data, &recived_data, portMAX_DELAY) == pdTRUE)
    {
      if (recived_data.has_payload == false)
      {
        Serial.println("WARNING: Link Lost. Activating Fail-Safe!");
      }
      else
      {
        surface_output(recived_data.aileron, aileron_servo);
        surface_output(recived_data.elevator, elevator_servo);
        surface_output(recived_data.radder, radder_servo);
        control_throttle_out(recived_data.throttle);
      }
    }
  }
}
