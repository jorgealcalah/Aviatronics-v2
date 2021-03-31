#include <UAVincludes.h>

uint32_t dt = 100000;

//cambiar a interrupciones, en vez de hacer poleo de tiempo
ulong previous_time;
uint32_t elapsed_time;

void setup()
{
  communication.begin();
  while (!uav.begin())
  {
    Serial.print("Sensors failed");
    delay(500);
  }

  previous_time = micros();
}

void loop()
{
  elapsed_time = micros() - previous_time;
  if (elapsed_time > dt)
  {
    previous_time = micros();
    uav.readSensors();
    communication.sendData(uav.gps_data, 8);
    // communication.sendData(uav.imu_data, 3);
    uav.calculateControl();
    uav.applyControl();
  }
  if (communication.available())
    uav.updateParameters(communication.updated_parameters);
}