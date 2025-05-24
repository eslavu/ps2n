#include "led.h"

void setup_led()
{
    pinMode(LED_ONOFF, OUTPUT);
    pinMode(LED_FLOOD, OUTPUT);
    
    pinMode(LED_LOW, OUTPUT);
    pinMode(LED_GOOD, OUTPUT);
    pinMode(LED_HIGH, OUTPUT);
    for (int i = 0; i < 3; i++)
        temp[i] = 0;
}

void led()
{
    led_onoff();
    led_flood();
    led_temperature();
}

void led_onoff()
{
    if (system_isOn)
        digitalWrite(LED_ONOFF, HIGH);
    else
        digitalWrite(LED_ONOFF, LOW);
}

void led_flood()
{
    switch (system_flood)
    {
        case DRY: // low humidity
            digitalWrite(LED_FLOOD, LOW);
            break;
        case MEDIUM: // moderate humidity
            digitalWrite(LED_FLOOD, HIGH);
            delay(2000);
            digitalWrite(LED_FLOOD, LOW);
            delay(2000);
            break;
        case FLOOD: // high humidity/flood detected
            digitalWrite(LED_FLOOD, HIGH);
            delay(250);
            digitalWrite(LED_FLOOD, LOW);
            delay(250);
            break;

        default: break;
    }
}

void led_temperature()
{
    switch (system_temperature)
    {
        case LO:
            temp[0] = HIGH;  temp[1] = LOW; temp[2] = LOW;
            break;
        case GOOD:
            temp[0] = LOW;  temp[1] = HIGH; temp[2] = LOW;
            break;
        case HI:
            temp[0] = LOW;  temp[1] = LOW; temp[2] = HIGH;
            break;

        default: break;
    }

    digitalWrite(LED_LOW, temp[0]);
    digitalWrite(LED_GOOD, temp[1]);
    digitalWrite(LED_HIGH, temp[2]);
}