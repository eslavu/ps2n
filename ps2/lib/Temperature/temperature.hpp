#ifndef TEMPERATURE_H
#define TEMPERATURE_H

#include <Arduino.h>

#define LM35_VOUT A0

class Temperature
{
private:
    const uint8_t LM35_VOUT = A0;

    float temperature = 0;

public:
    Temperature();

    void read();
    float get();
};

#endif