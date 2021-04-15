#include <UAVincludes.h>

//cambiar a interrupciones, en vez de hacer poleo de tiempo
ulong previous_time;
uint32_t elapsed_time;

void setup()
{
  communication.begin();
  while (!Wire.begin())
  {
    Serial.print("Sensors failed");
    delay(500);
  }
  communication.initializeIMU();
  previous_time = millis();
}
//comentario prueba
void loop()
{
  elapsed_time = millis() - previous_time;
  if (elapsed_time > dt_n) //cambiar esta variable de dt_n
  {
    previous_time = millis();
    uav.readSensors();
    communication.sendData(uav.gps_data, 8);
    // communication.sendData(uav.imu_data, 3);
    uav.calculateControl();
    uav.applyControl();
  }
  if (communication.available())
    uav.updateParameters(communication.updated_parameters);
}