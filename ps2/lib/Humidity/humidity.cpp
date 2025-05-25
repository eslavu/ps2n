#include "humidity.hpp"

Humidity::Humidity()
{
    dht = DHT(this->DHT11_DATA, TYPE);
    dht.begin();

    values = (int*)calloc(2, sizeof(int));
}

void Humidity::read()
{
    float h = dht.readHumidity();
    this->humidity = sma.next((int)h);

    this->temperature = dht.readTemperature();
}

int* Humidity::get()
{
    values[0] = this->humidity; values[1] = this->temperature;
    return values;
}

Humidity::~Humidity()
{ free(values); }