#include <Arduino.h>
#include "UAV.h"
#include "Communications.h"
#include <BluetoothSerial.h>
#include <PID_controller.h>
#include <RefRead.h>
#include <ESP32_PWM.h>

//PID variables
#define pitch_Kp 0.6
#define Pitch_Ki 0.4
#define pitch_Kd 0.0
#define roll_Kp 0.6
#define roll_ki 0.3
#define roll_kd 0.0
#define sampleTime 0.038
#define PWMPitchPin 27
#define PWMRollPin 26
float pitchOut;
float rollOut;
float pitchRef;
float rollRef;
float pitchU;
float rollU;
//PID_controller pitchValue;

//Interrupt Variables
int totalInterruptCounter;
volatile bool interruptFlag = LOW;
hw_timer_t *timer = NULL;
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;

//Control objects
PID_controller PID;
PID_controller PID2;
RefRead Reference;
PWM pwm1;
PWM pwm2;

//class definitions
UAV uav; //not used
Communications communication;
BluetoothSerial BT;

//polling variables (not used)
uint16_t dt_n = 100;
uint16_t blink_period = 20;
ulong previous_millis, current_millis;