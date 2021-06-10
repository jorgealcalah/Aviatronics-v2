#include <UAVincludes.h>

void IRAM_ATTR onTimer() //rutina de atención de timer interrupt
{
  portENTER_CRITICAL_ISR(&timerMux);
  interruptFlag = HIGH;
  portEXIT_CRITICAL_ISR(&timerMux);
}
void setup()
{

  pwm1.setup(PWMPitchPin, 1, 250); //configuración de señales PWM para controlar pitch y roll
  pwm2.setup(PWMRollPin, 2, 250);
  communication.begin();                       //incializa baud rate y conexión BT con la ESP32
  timer = timerBegin(0, 80, true);             //se usa el timer 0 (de 4 disponibles), prescaler de 80 MHz, true para que cuente hacia arriba
  timerAttachInterrupt(timer, &onTimer, true); //se inicializa interrupt
  timerAlarmWrite(timer, 1000, true);          // se establecen 1000 microsegundos (1 milisegundo) para el timer. Más info en https://techtutorialsx.com/2017/10/07/esp32-arduino-timer-interrupts/#:~:text=The%20prescaler%20is%20used%20to,a%20lot%20of%20configuration%20freedom.
  timerAlarmEnable(timer);                     //se habilita el timer

  while (!Wire.begin())
  {
    Serial.print("Sensors failed");
    delay(500);
  }
  communication.initializeSensors(); //inicializa IMU, barómetro, GPS y el bus I2C
}

void loop()
{
  if (interruptFlag == HIGH) //rutina de interrupción de timer
  {
    portENTER_CRITICAL(&timerMux);
    interruptFlag = LOW;
    portEXIT_CRITICAL(&timerMux);
    communication.sendData(pitchRef, rollRef); //manda las referencias de pitch y roll y las imprime con los otros datos
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