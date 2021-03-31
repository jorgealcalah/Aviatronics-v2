#include <Arduino.h>

class Communications
{
public:
    Communications();
    ~Communications();
    void begin();
    void sendData(double data[], uint8_t decimals);
    bool available();
    float updated_parameters[4];
};