#ifndef HUMIDITY_H
#define HUMIDITY_H

#include <Arduino.h>
#include <DHT.h>
#include "MovingAverage.hpp"

#define TYPE DHT11
static DHT dht(0, TYPE);

class Humidity
{
private:
    const uint8_t DHT11_DATA = 15; // A1
    MovingAverage sma = MovingAverage(3);

    int *values;
    int humidity = 0;
    int temperature = 0;

public:
    Humidity();

    void read();
    int* get();

    ~Humidity();
};

#endif