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
    MovingAverage sma = MovingAverage(5);

    int humidity = 0;

public:
    Humidity();

    void read();
    int get();
};

#endif