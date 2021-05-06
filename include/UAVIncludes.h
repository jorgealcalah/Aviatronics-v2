#include <Arduino.h>
#include "UAV.h"
#include "Communications.h"
#include <BluetoothSerial.h>

//Interrupt Variables
int totalInterruptCounter;
volatile bool interruptFlag = LOW;
hw_timer_t *timer = NULL;
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;

//Object definitions
UAV uav;
Communications communication;

//polling variables (not used)
uint16_t dt_n = 100;
uint16_t blink_period = 20;
ulong previous_millis, current_millis;