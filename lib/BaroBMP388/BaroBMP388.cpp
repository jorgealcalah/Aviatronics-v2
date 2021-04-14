#include "BaroBMP388.h"

Baro::Baro()
{
}

Baro::~Baro()
{
}

void Baro::begin(uint8_t address, bool baro_data[3])
{
    while (!bmp.begin_I2C(address))
    {
        Serial.printf("The barometer with address %x not detected\n", address);
        delay(1000);
    }
    Serial.printf("Barometer with address %x initialized\n", address);
    bmp.setIIRFilterCoeff(BMP3_IIR_FILTER_COEFF_15);
    bmp.setOutputDataRate(BMP3_ODR_100_HZ);
    setSensors(baro_data);
}

void Baro::setSensors(bool baro_data[3])
{
    _baro_data = baro_data;
}

void Baro::readSensors(float measurements[])
{
    byte index = 0;
    if (PRESSURE)
        measurements[index++] = bmp.readPressure();
    if (ALTITUDE)
        measurements[index++] = bmp.readAltitude(SEALEVELPRESSURE_HPA);
    if (TEMPERATURE)
        measurements[index++] = bmp.readTemperature();
}