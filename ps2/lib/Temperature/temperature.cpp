#include "temperature.hpp"

Temperature::Temperature()
{
    pinMode(this->LM35_VOUT, INPUT);

    this->scaling = ADC_AMP;
}

void Temperature::read()
{
    if (CALIBRATE_DHT)
        this->calibrate_dht();
    this->adc = analogRead(this->LM35_VOUT);

    this->temperature = this->adc * (ADC_VREF / ADC_RESOLUTION);
    this->temperature = sma.next(this->temperature / (10 * this->scaling));
}

float Temperature::get(float dht_temp)
{
    this->dht_temp = dht_temp;
    return this->temperature;
}

float Temperature::calibrate_dht()
{
    if (this->dht_temp > 0)
        this->scaling = (this->temperature * 10) / this->dht_temp;
}