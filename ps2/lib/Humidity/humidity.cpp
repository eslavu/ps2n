#include "humidity.h"

void setup_humidity()
{
    pinMode(DHT11_DATA, OUTPUT);
    digitalWrite(DHT11_DATA, LOW);
    delay(18);

    digitalWrite(DHT11_DATA, HIGH);
    pinMode(DHT11_DATA, INPUT_PULLUP);
}

int get_humidity()
{
    unsigned long timeOn, timeOff;
    unsigned char dataBit, counterBit,
        dataByte[5], checkByte;

    int humidity = 0;

    setup_humidity();
    timeOff = pulseIn(DHT11_DATA, LOW);

    if (timeOff <= 84 && timeOff >= 76)
    {
        while (1)
        {
            timeOn = pulseIn(DHT11_DATA, HIGH);
            if (timeOn <= 28 && timeOn >= 20)
                dataBit = 0;
            else if (timeOn <= 74 && timeOn >= 65)
                dataBit = 1;
            else if (counterBit == 40)
                break;
                
            dataByte[counterBit / 8] |= dataBit << (7 - (counterBit % 8));
            counterBit++;
        }
    }
    checkByte = dataByte[0] + dataByte[1] + dataByte[2] + dataByte[3];

    if (checkByte == dataByte[4] && checkByte != 0)
        humidity = (int)dataByte[0];

    counterBit = 0;
    for (int i = 0; i < 5; i++)
        dataByte[i] = 0;

    return humidity;
}