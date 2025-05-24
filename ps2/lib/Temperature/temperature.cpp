#include "temperature.h"

void setup_temperature()
{
    pinMode(LM35_VOUT, INPUT);
}

float get_temperature()
{
    int temp_read = 0;
    float v, temperature;

    temp_read = analogRead(LM35_VOUT);
    v = (temp_read * 5) / 1024;
    temperature = (v - 0.5) * 100;

    return temperature;
}