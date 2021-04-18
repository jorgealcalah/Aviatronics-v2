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

class Communications
{
public:
    Communications();
    ~Communications();
    IMU imu_080;
    Baro baro;
    void begin();
    void initializeSensors();
    void sendData(double data[], uint8_t decimals);
    bool available();
    float imu_measurements[6];
    float baro_measurements[1];
    char imu_string[48];
    char baro_string[16];
    float updated_parameters[4];
};