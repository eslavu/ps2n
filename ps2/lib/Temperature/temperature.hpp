#ifndef TEMPERATURE_H
#define TEMPERATURE_H

#include <Arduino.h>
#include "MovingAverage.hpp"

#define ADC_VREF 5000.0
#define ADC_RESOLUTION 1024.0

class Temperature
{
private:
    const uint8_t LM35_VOUT = A0;
    MovingAverage sma = MovingAverage(5);

    float temperature = 0;

public:
    Temperature();

    void read();
    float get();
};

#endif