#include <Arduino.h>
#include "UAV.h"
#include "Communications.h"
#include <BluetoothSerial.h>


//#define ADDR_PIN 17

UAV uav;
Communications communication;
//BluetoothSerial SerialBT;
//IMU imu_080;
//Baro baro;


//const byte LED_PIN = 15;
uint16_t dt_n = 100;
uint16_t blink_period = 20;
ulong previous_millis, current_millis;
/*float imu_measurements[6];
float baro_measurements[1];
char imu_string[48];
char baro_string[16];
*/
//bool imu_data[] = {false, true, true, false, false, false};
//bool baro_data[] = {false, true, false};