#ifndef TEMPERATURE_H
#define TEMPERATURE_H

#include <Arduino.h>

#define LM35_VOUT 14    // A0

void setup_temperature();
float get_temperature();

#endif