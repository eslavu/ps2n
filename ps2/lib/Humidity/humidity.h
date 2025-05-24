#ifndef HUMIDITY_H
#define HUMIDITY_H

#include <Arduino.h>

#define DHT11_DATA 15   // A1

void setup_humidity();
int get_humidity();

#endif