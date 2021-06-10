#include <Arduino.h>

class PID_controller

{
public:
    PID_controller();
    ~PID_controller();
double PIDloop(float _reference,float _output, float _Kp, float _Ki, float _kd, float _ts);
double PIDloopRoll(float _referencer,float _outputr, float _Kpr, float _Kir, float _kdr, float _tsr);
void PWM_build();
void BTsetup();
float pastPitch;
float pastRoll;
float pastTimePitch;
float pastTimeRoll;
private:
};