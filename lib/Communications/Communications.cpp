#include "Communications.h"
#include "MessageUtilities.h"
Communications::Communications()
{
}

Communications::~Communications()
{
}

void Communications::begin()
{
    Serial.begin(115200);
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