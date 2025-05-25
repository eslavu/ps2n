#ifndef HUMIDITY_H
#define HUMIDITY_H

#include <Arduino.h>

class Humidity
{
private:
    const uint8_t DHT11_DATA = 15; // A1
    int humidity = 0;

    void setup();

public:
    void read();
    int get();
};

#endif