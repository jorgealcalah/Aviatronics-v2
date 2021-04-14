#include <Arduino.h>
#include "UAV.h"
#include "Communications.h"
#include <BluetoothSerial.h>
#include <ImuBNO080.h>
#include <BaroBMP388.h>

UAV uav;
Communications communication;
BluetoothSerial SerialBT;
IMU imu_080;
Baro baro;