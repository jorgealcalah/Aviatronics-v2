#include "Communications.h"
#include "MessageUtilities.h"
#define ADDR_PIN 17
const byte LED_PIN = 15;
BluetoothSerial SerialBT;
bool imu_data[] = {false, true, true, false, false, false};
bool baro_data[] = {false, true, false};
uint16_t dt = 100;

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

void Communications::initializeSensors()
{
    imu_080.begin(IMU_ADDR1, dt, imu_data);
    baro.begin(BARO_ADDR2, baro_data);
    Wire.setClock(400000);
}
void Communications::sendData()
{
    //String payload = buildString(data,",",decimals); CÓDIGO ANTIGUO
    //preguntar cuantos decimales (8)
    //Serial.printf("%.8f,%.8f,%.2f\n", data[0], data[1], data[2]);

    baro.readSensors(baro_measurements);
    buildString(baro_measurements, sizeof(baro_measurements) / sizeof(baro_measurements[0]), baro_string, "%.2f,");
    buildString(imu_measurements, sizeof(imu_measurements) / sizeof(imu_measurements[0]), imu_string, "%.2f, ");
    Serial.printf("%lu, %s%s\n", millis(), imu_string, baro_string);
}
void Communications::checkDataIMU()
{
    if (imu_080.dataAvailable())
    {
        imu_080.readSensors(imu_measurements);
    }
}
bool Communications::available()
{
}