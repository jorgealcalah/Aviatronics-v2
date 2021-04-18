#include <SparkFun_I2C_GPS_Arduino_Library.h>
#include <Adafruit_BNO055.h>
#include <TinyGPS++.h>
#include <Wire.h>


class UAV
{
public:
    UAV();
    ~UAV();

    I2CGPS i2cgps;
    TinyGPSPlus gps;
    Adafruit_BNO055 bno = Adafruit_BNO055(55, 0x28);
    bool begin();

    void read_Sensors();

    //double gps_data[3];
    //double imu_data[6];
    void calculateControl();
    void applyControl();
    void updateParameters(float updated_parameters[]);

private:
};