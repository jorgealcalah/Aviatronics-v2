#include "PID_controller.h"

#define K_p 0.5
#define PWMPitchpin 27

float _Poutput;
float _Ioutput;
float _Doutput;
float _Poutputr;
float _Ioutputr = 0;
float _Doutputr;
float _error;
float _errorr;
float _pastErrorr = 0; 
float _pastError = 0;
float _PitchOut;

PID_controller::PID_controller()
{
 
}
PID_controller::~PID_controller()
{
}
double PID_controller::PIDloop(float _reference,float _output, float _Kp, float _Ki, float _kd, float _ts){
  _error = _reference+_output;
  int f=_output;
  if (abs(f)<180)
  {
    _Poutput=_Kp*_error;
    _Doutput=-_kd*(_output-pastPitch)/_ts;
    _Ioutput=_Ioutput+_Ki*((_pastError+_error)*_ts/2);
    _pastError= _error;
    pastPitch=_output;
    if(abs(_Ioutput)>15){
      if(_Ioutput>0){
      _Ioutput=15;
      }else{
        _Ioutput=-15;
      }
    }
  }
  float _usignal=_Poutput+_Ioutput+_Doutput;
  _usignal=(_usignal/30)*500+1500; 
  if (_usignal>2000)
  {
    _usignal=2000;
  }
  else if (_usignal<1000)
  {
    _usignal=1000;
  }
 
  return _usignal;        
}

double PID_controller::PIDloopRoll(float _referencer,float _outputr, float _Kpr, float _Kir, float _kdr, float _tsr){
  _errorr = _referencer-_outputr;
  int fr=_outputr;
  if (abs(fr)<180)
  {
    _Poutputr=_Kpr*_errorr;
    _Doutputr=-_kdr*(_outputr-pastRoll)/_tsr;
    _Ioutputr=_Ioutputr+_Kir*(_pastErrorr+_errorr)*_tsr/2;
    pastRoll=_outputr;
    if(abs(_Ioutputr)>15){
      if(_Ioutputr>0){
      _Ioutputr=20;
      }else{
        _Ioutput=-20;
      }
    }
    _pastErrorr= _errorr;
  }
  float _usignalr=_Poutputr+_Ioutputr+_Doutputr;
  _usignalr=(-_usignalr/30)*500+1500; 
  if (_usignalr>1800)
  {
    _usignalr=1800;
  }
  else if (_usignalr<1150)
  {
    _usignalr=1150;
  }
 
  return _usignalr;    
}

void PID_controller::BTsetup(){
  
}