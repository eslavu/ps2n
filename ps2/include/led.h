#include <Arduino.h>

#include "cloud.h"

#define PORT_LED_ONOFF LED_BUILTIN
#define PORT_LED_FLOOD 2

#define PORT_LED_LOW 5
#define PORT_LED_GOOD 6
#define PORT_LED_HIGH 7

void setup_led()
{
    pinMode(PORT_LED_ONOFF, OUTPUT);
    pinMode(PORT_LED_FLOOD, OUTPUT);
    
    pinMode(PORT_LED_LOW, OUTPUT);
    pinMode(PORT_LED_GOOD, OUTPUT);
    pinMode(PORT_LED_HIGH, OUTPUT);
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
        digitalWrite(PORT_LED_ONOFF, HIGH);
    else
        digitalWrite(PORT_LED_ONOFF, LOW);
}

void led_flood()
{
    switch (system_flood)
    {
        case DRY: // low humidity
            digitalWrite(PORT_LED_FLOOD, LOW);
            break;
        case MEDIUM: // moderate humidity
            digitalWrite(PORT_LED_FLOOD, HIGH);
            delay(2000);
            digitalWrite(PORT_LED_FLOOD, LOW);
            delay(2000);
            break;
        case FLOOD: // high humidity/flood detected
            digitalWrite(PORT_LED_FLOOD, HIGH);
            delay(250);
            digitalWrite(PORT_LED_FLOOD, LOW);
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
            break;
        case GOOD:
            break;
        case HI:
            break;

        default: break;
    }
}