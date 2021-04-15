#include "Communications.h"
#include "MessageUtilities.h"
#include <ImuBNO080.h>
#include <BaroBMP388.h>
#include <BluetoothSerial.h>

#define ADDR_PIN 17
const byte LED_PIN = 15;
BluetoothSerial SerialBT;
Communications::Communications()
{
}

Communications::~Communications()
{
}

void Communications::begin()
{
    Serial.begin(115200);
    SerialBT.begin("Nimu");
    pinMode(ADDR_PIN, OUTPUT);
    digitalWrite(ADDR_PIN, HIGH);
    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, LOW);
}

void Communications::sendData(double data[], uint8_t decimals)
{
    //String payload = buildString(data,",",decimals);
    //preguntar cuantos decimales (8)
    Serial.printf("%.8f,%.8f,%.2f\n",data[0],data[1],data[2]);
}

bool Communications::available() 
{
    
}