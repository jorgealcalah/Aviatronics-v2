#include "RefRead.h"
#define Pitch_in 32
#define Roll_in 33
#define Pitch_out 25
#define Roll_out 26
#define K_p 1
uint32_t _now, _tsubida, _dt, _now1, _tsubida1, _dt1;

void IRAM_ATTR isr()
{
  _now = micros();
  if (digitalRead(Pitch_in) == 1)
  {
    _tsubida = _now;
  }
  else
    _dt = _now - _tsubida;
}

void IRAM_ATTR isr1()
{
  _now1 = micros();
  if (digitalRead(Roll_in) == 1)
  {
    _tsubida1 = _now1;
  }
  else
    _dt1 = _now1 - _tsubida1;
}

RefRead::RefRead()
{
  pinMode(Pitch_in, INPUT);
  pinMode(Roll_in, INPUT);
  attachInterrupt(Pitch_in, isr, CHANGE);
  attachInterrupt(Roll_in, isr1, CHANGE);
}
RefRead::~RefRead()
{
}

double RefRead::readRefPitch()
{

  //_pwmValue=pulseIn(Pitch_in,HIGH);
  double dt = _dt;
  _PitchAngle = ((dt-1500)/500)*30;
  return (_PitchAngle);
}

double RefRead::readRefRoll(){
  double dt1 = _dt1;
  _RollAngle = ((dt1-1500)/500)*30;
  return (_RollAngle);
}

uint32_t RefRead::Time()
{
  return (_dt);
}