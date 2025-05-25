#include "temperature.hpp"

Temperature::Temperature()
{
    pinMode(this->LM35_VOUT, INPUT);
}

void Temperature::read()
{
    int adc_read = analogRead(LM35_VOUT);

    this->temperature = adc_read * (ADC_VREF / ADC_RESOLUTION);
    this->temperature = sma.next(this->temperature / 100);
}

float Temperature::get()
{ return this->temperature; }