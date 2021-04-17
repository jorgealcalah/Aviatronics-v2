#include "Communications.h"
#include "MessageUtilities.h"

#define ADDR_PIN 17
const byte LED_PIN = 15;
BluetoothSerial SerialBT;
//IMU imu_080;
//Baro baro;
bool imu_data[] = {false, true, true, false, false, false};
bool baro_data[] = {false, true, false};
uint16_t dt = 20;

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

void Communications::initializeIMU()
{
    imu_080.begin(IMU_ADDR1, dt, imu_data);
    baro.begin(BARO_ADDR2, baro_data);
    Wire.setClock(400000);
}
void Communications::sendData(double data[], uint8_t decimals)
{
    //String payload = buildString(data,",",decimals);
    //preguntar cuantos decimales (8)
    Serial.printf("%.8f,%.8f,%.2f\n", data[0], data[1], data[2]);
}

bool Communications::available()
{
}