#include <UAVincludes.h>

void IRAM_ATTR onTimer()
{
  portENTER_CRITICAL_ISR(&timerMux);
  interruptFlag = HIGH;
  portEXIT_CRITICAL_ISR(&timerMux);
}
void setup()
{
  pwm1.setup(PWMPitchPin, 1, 250);
  pwm2.setup(PWMRollPin, 2, 250);
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
    communication.sendData(pitchRef, rollRef);
  }
  communication.checkDataIMU();
  communication.displayGPSinfo();
  pitchOut = communication.checkPitch();
  pitchRef = Reference.readRefPitch();
  pitchU = PID.PIDloop(pitchRef, pitchOut, pitch_Kp, Pitch_Ki, pitch_Kd, sampleTime);
  pwm1.setDuty(pitchU / 4000 * 100);
  rollOut = communication.checkRoll();
  rollRef = -(Reference.readRefRoll());
  rollU = PID.PIDloopRoll(rollRef, rollOut, roll_Kp, roll_ki, roll_kd, sampleTime);
  pwm2.setDuty((rollU - 200) / 4000 * 100);
  //Serial.println(pitchU);
  //BT.println(rollOut);
}