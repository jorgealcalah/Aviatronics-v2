#include "ImuBNO080.h"

IMU::IMU()
{
}

IMU::~IMU()
{
}

void IMU::begin(uint8_t address, uint16_t dt, bool imu_data[6]) //Quat, Euler, Linear accel, Accel, Gyro, Magneto
{
	_dt = dt;
	while (!bno.begin(address))
	{
		Serial.printf("The IMU with address %x was not detected\n", address);
		delay(1000);
	}
	Serial.printf("IMU with address %x initialized\n", address);
	setSensors(imu_data);
	delay(50);
}

bool IMU::dataAvailable()
{
	return bno.dataAvailable();
}

void IMU::setSensors(bool imu_data[])
{
	_imu_data = imu_data;
	if (QUATERNION || EULER_ANG)
		bno.enableRotationVector(_dt);
	if (LINEAR_ACCEL)
		bno.enableLinearAccelerometer(_dt);
	if (ACCELEROMETER)
		bno.enableAccelerometer(_dt);
	if (GYROSCOPE)
		bno.enableGyro(_dt);
	if (MAGNETOMETER)
		bno.enableMagnetometer(_dt);
	delay(100);
}

void IMU::readSensors(float measurements[])
{
	byte i = 0;
	byte index = 0;
	if (QUATERNION || EULER_ANG)
	{
		_quat[0] = bno.getQuatReal();
		_quat[1] = bno.getQuatI();
		_quat[2] = bno.getQuatJ();
		_quat[3] = bno.getQuatK();
		if (QUATERNION)
		{
			for (i = index; i < index + 4; i++)
				measurements[i] = _quat[i];
			index = i;
		}
		if (EULER_ANG)
		{
			float euler[3];
			euler[0] = RAD_TO_DEG * bno.getRoll();
			euler[1] = RAD_TO_DEG * bno.getPitch();
			euler[2] = RAD_TO_DEG * bno.getYaw();
			for (i = index; i < index + 3; i++)
				measurements[i] = euler[i];
			index = i;
		}
	}
	if (LINEAR_ACCEL)
	{
		measurements[index++] = bno.getLinAccelX();
		measurements[index++] = bno.getLinAccelY();
		measurements[index++] = bno.getLinAccelZ();
	}
	if (ACCELEROMETER)
	{
		measurements[index++] = bno.getAccelX();
		measurements[index++] = bno.getAccelY();
		measurements[index++] = bno.getAccelZ();
	}
	if (GYROSCOPE)
	{
		measurements[index++] = bno.getGyroX();
		measurements[index++] = bno.getGyroY();
		measurements[index++] = bno.getGyroZ();
	}
	if (MAGNETOMETER)
	{
		measurements[index++] = bno.getMagX();
		measurements[index++] = bno.getMagY();
		measurements[index++] = bno.getMagZ();
	}
}

void quaternion2euler(float quaternion[], float euler[])
{
	float R11, R21, R31, R32, R33;
	float q0 = quaternion[0];
	float q1 = quaternion[1];
	float q2 = quaternion[2];
	float q3 = quaternion[3];
	R11 = 1.0f - 2.0f * (q2 * q2 + q3 * q3);
	R21 = 2.0f * (q1 * q2 + q0 * q3);
	R31 = 2.0f * (q1 * q3 - q2 * q0);
	R32 = 2.0f * (q2 * q3 + q0 * q1);
	R33 = 1.0f - 2.0f * (q1 * q1 + q2 * q2);
	euler[1] = RAD_TO_DEG * atan2(-R31, sqrt(R11 * R11 + R21 * R21));
	euler[0] = RAD_TO_DEG * atan2(R21, R11);
	euler[2] = RAD_TO_DEG * atan2(R32, R33);
}
