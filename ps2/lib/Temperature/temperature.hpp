#ifndef TEMPERATURE_H
#define TEMPERATURE_H

#include <Arduino.h>
#include "MovingAverage.hpp"

#define ADC_VREF 5000.0
#define ADC_RESOLUTION 1024.0
#define ADC_AMP 7.73

#define CALIBRATE_DHT true

class Temperature
{
private:
    const uint8_t LM35_VOUT = A0;
    MovingAverage sma = MovingAverage(3);

    float scaling;
    float temperature = 0;
    int adc = 0;

    float dht_temp = 0;
    float calibrate_dht();

public:
    Temperature();

    void read();
    float get(float);
    int get_adc(){return this->adc;}
};

#endif