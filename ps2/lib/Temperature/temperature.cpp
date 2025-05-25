#include "temperature.hpp"

Temperature::Temperature()
{
    pinMode(this->LM35_VOUT, INPUT);
}

void Temperature::read()
{
    int temp_read = 0;
    float v;

    temp_read = analogRead(LM35_VOUT);
    v = (temp_read * 5) / 1024;
    this->temperature = (v - 0.5) * 100;
}

float Temperature::get()
{ return this->temperature; }