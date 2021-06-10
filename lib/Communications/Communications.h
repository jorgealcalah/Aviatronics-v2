#ifndef Arduino_h
#include <Arduino.h>
#endif
#ifndef ImuBNO080_h
#include <ImuBNO080.h>
#endif
#ifndef BaroBMP388_h
#include <BaroBMP388.h>
#endif
#ifndef BluetoothSerial_h
#include <BluetoothSerial.h>
#endif
#ifndef SparkFun_I2C_GPS_Arduino_Library_h
#include <SparkFun_I2C_GPS_Arduino_Library.h>
#endif
#ifndef TinyGPS++ _h
#include <TinyGPS++.h>
#endif

class Communications
{
public:
    Communications();
    ~Communications();
    IMU imu_080;
    Baro baro;
    I2CGPS myI2CGPS;
    TinyGPSPlus gps;
    void begin();
    void initializeSensors();
    void sendData(float _rollRef, float _pitchRef);
    float checkDataIMU();
    float checkRoll();
    float checkPitch();
    float checkYaw();
    void displayGPSinfo();
    bool available();

    float imu_measurements[6];
    float baro_measurements[1];
    float gps_measurements[3];
    char imu_string[48];
    char baro_string[16];
    char gps_string[40];
    float updated_parameters[4];
};