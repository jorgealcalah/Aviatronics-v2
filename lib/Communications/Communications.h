#include <Arduino.h>
#include <ImuBNO080.h>
#include <BaroBMP388.h>
#include <BluetoothSerial.h>
class Communications
{
public:
    Communications();
    ~Communications();
    void begin();
    void initializeIMU();
    void sendData(double data[], uint8_t decimals);
    bool available();
    float updated_parameters[4];
};