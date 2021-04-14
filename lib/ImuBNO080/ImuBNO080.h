#ifndef _IMUBNO080_h
#define _IMUBNO080_h

#include <Arduino.h>
#include <SparkFun_BNO080_Arduino_Library.h>

#define IMU_ADDR1 0x4B
#define IMU_ADDR2 0x4A

#define QUATERNION _imu_data[0]
#define EULER_ANG _imu_data[1]
#define LINEAR_ACCEL _imu_data[2]
#define ACCELEROMETER _imu_data[3]
#define GYROSCOPE _imu_data[4]
#define MAGNETOMETER _imu_data[5]

class IMU
{
public:
	IMU();
	~IMU();
	BNO080 bno;
	void begin(uint8_t address, uint16_t dt, bool imu_data[6]);
	void setSensors(bool imu_data[6]);
	bool dataAvailable();
	void readSensors(float measurements[]);

private:
	uint16_t _dt;
	float _quat[4];
	bool *_imu_data;
};

void quaternion2euler(float quaternion[], float euler[]);

#endif