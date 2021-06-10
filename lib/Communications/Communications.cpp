#include "Communications.h"
#include "MessageUtilities.h"

#define ADDR_PIN 17
const byte LED_PIN = 15;
BluetoothSerial SerialBT;
bool imu_data[] = {false, true, true, false, false, false};
bool baro_data[] = {false, true, false};
uint16_t dt = 100;
double pitchread;

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
    if (myI2CGPS.begin() == false)
    {
        Serial.println("Module failed to respond. Please check wiring.");
        while (1)
            ; //Freeze!
    }
    Serial.println("GPS module found!");
}
void Communications::sendData(float _pitchRef,float _rollRef)
{
    baro.readSensors(baro_measurements);
    buildString(baro_measurements, sizeof(baro_measurements) / sizeof(baro_measurements[0]), baro_string, "%.2f,");
    buildString(imu_measurements, sizeof(imu_measurements) / sizeof(imu_measurements[0]), imu_string, "%.2f, ");
    buildString(gps_measurements, sizeof(gps_measurements) / sizeof(gps_measurements[0]), gps_string, "%.6f, ");
    Serial.printf("%lu, %s%s%s\n", millis(), imu_string, baro_string, gps_string);
    SerialBT.printf("%lu, %s%s%s%.2f%s%.2f\n", millis(), imu_string, baro_string, gps_string,_pitchRef,",",_rollRef);
}
float Communications::checkDataIMU()
{
    if (imu_080.dataAvailable())
    {
        imu_080.readSensors(imu_measurements);
        return imu_measurements[1];
    }
}

float Communications::checkRoll(){
    return imu_measurements[0];
}


float Communications::checkPitch(){
    return imu_measurements[1];
}

float Communications::checkYaw(){
    return imu_measurements[2];
}
void Communications::displayGPSinfo()
{
    
    while (myI2CGPS.available()) //available() returns the number of new bytes available from the GPS module
    {
        gps.encode(myI2CGPS.read()); //Feed the GPS parser
    }

    if (gps.time.isUpdated()) //Check to see if new GPS info is available
    {
        if (gps.location.isValid())
        {
            byte index_gps = 0;
            gps_measurements[index_gps++] = gps.location.lat();
            gps_measurements[index_gps++] = gps.location.lng();
            gps_measurements[index_gps++] = gps.speed.mps();
            //Serial.printf("%.6f, %.6f\n", gps_measurements[0], gps_measurements[1]);
        }
    }
}
bool Communications::available()
{
}