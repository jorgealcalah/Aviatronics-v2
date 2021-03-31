#ifndef _MESSAGEUTILITIES_h
#define _MESSAGEUTILITIES_h

#include <Arduino.h>

template <typename data>
void parseString(String string_in, char *delimiter, data output_array[])
{
    char str[sizeof(string_in) * 8];               //Create an array to store the input string
    string_in.toCharArray(str, (sizeof(str) * 8)); //Convert the input data to CharArray
    char *pch;                                     //create buffer
    pch = strtok(str, delimiter);                  //begin parsing the values
    byte i = 0;
    while (pch != NULL)
    {
        output_array[i] = atof(pch);
        pch = strtok(NULL, delimiter);
        i++;
    }
}

template <typename data>
String buildString(data data_to_string[], const char delimiter[], byte decimals = 3)
{
    String payload = "";
    byte number_of_elements = sizeof(data_to_string) / sizeof(data_to_string[0]);
    byte i;
    for (i = 0; i < number_of_elements; i++)
    {
        payload += String(data_to_string[i], decimals);
        if (i < number_of_elements)
            payload += delimiter;
    }
    return payload;
}

#endif
