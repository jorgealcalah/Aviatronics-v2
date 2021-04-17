#include "UAV.h"

UAV::UAV()
{
}
UAV::~UAV()
{
}

bool UAV::begin()
{
    Wire.begin(21, 22);
    Serial.println("Comenzando");
    delay(500);
    if (!bno.begin()) // && bno.begin() == false)
        return false;
    // cambiar a or para saber qué cosa falló
    else
        return true;
}

void UAV::read_Sensors()
{
    while (i2cgps.available())
    {
        gps.encode(i2cgps.read());
    }
    if (gps.time.isUpdated())
    {
        gps_data[0] = gps.location.lat();
        gps_data[1] = gps.location.lng();
        gps_data[2] = gps.speed.mps();
    }

    sensors_event_t event;
    bno.getEvent(&event);
    imu::Vector<3> euler = bno.getVector(Adafruit_BNO055::VECTOR_EULER);
    imu::Vector<3> lin_acc = bno.getVector(Adafruit_BNO055::VECTOR_LINEARACCEL);
    //checar unidades y hacer conversion si es necesario
    imu_data[0] = euler.x();
    imu_data[1] = euler.y();
    imu_data[2] = euler.z();
    imu_data[3] = lin_acc.x();
    imu_data[4] = lin_acc.y();
    imu_data[5] = lin_acc.z();
}

void UAV::calculateControl()
{
}

void UAV::applyControl()
{
}

void UAV::updateParameters(float updated_parameters[])
{
}