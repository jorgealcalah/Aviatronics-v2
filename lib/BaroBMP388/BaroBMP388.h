#ifndef _BAROBMP388_h
#define _BAROBMP388_h

#include <Arduino.h>
#include <Adafruit_BMP3XX.h>

#define SEALEVELPRESSURE_HPA (1013.25f)
#define BARO_ADDR1 0x77
#define BARO_ADDR2 0x76

#define PRESSURE _baro_data[0]
#define ALTITUDE _baro_data[1]
#define TEMPERATURE _baro_data[2]

class Baro
{
public:
    Baro();
    ~Baro();
    Adafruit_BMP3XX bmp;
    void begin(uint8_t address, bool baro_data[3]);
    void setSensors(bool baro_data[3]);
    void readSensors(float measurements[]);

private:
    bool *_baro_data;
};

#endif