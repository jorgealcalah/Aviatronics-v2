#include <UAVincludes.h>

void IRAM_ATTR onTimer()
{
  portENTER_CRITICAL_ISR(&timerMux);
  interruptFlag = HIGH;
  portEXIT_CRITICAL_ISR(&timerMux);
}
void setup()
{
  communication.begin();
  timer = timerBegin(0, 80, true); //se usa el timer 0 (de 4 disponibles), prescaler de 80 MHz, true para que cuente hacia arriba
  timerAttachInterrupt(timer, &onTimer, true);
  timerAlarmWrite(timer, 1000, true);
  timerAlarmEnable(timer);

  while (!Wire.begin())
  {
    Serial.print("Sensors failed");
    delay(500);
  }
  communication.initializeSensors();
}

void loop()
{
  if (interruptFlag == HIGH)
  {
    portENTER_CRITICAL(&timerMux);
    interruptFlag = LOW;
    portEXIT_CRITICAL(&timerMux);
    communication.sendData();
    //uav.calculateControl();
    //uav.applyControl();
  }
  communication.checkDataIMU();
  communication.displayGPSinfo();
}