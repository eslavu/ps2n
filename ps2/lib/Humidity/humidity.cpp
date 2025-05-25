#include "humidity.hpp"

Humidity::Humidity()
{
    dht = DHT(this->DHT11_DATA, TYPE);
    dht.begin();
}

void Humidity::read()
{
    float h = 0;
    
    h = dht.readHumidity();
    this->humidity = sma.next((int)this->humidity);
}

int Humidity::get()
{ return this->humidity; }