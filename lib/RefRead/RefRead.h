#include <Arduino.h>
#ifndef ImuBNO080_h
#include <ImuBNO080.h>
#endif
class RefRead

{
public:
    double readRefPitch();
    double readRefRoll();
    RefRead();
    ~RefRead();
    uint32_t Time();
    IMU _IMUout;
    double _PitchAngle;
    double _RollAngle;
    float imu_meas[6];
private:
int _pitchPinIn=33;
int _pitchPinOut=32;
int _rollPinIn=25;
float _angle;
};