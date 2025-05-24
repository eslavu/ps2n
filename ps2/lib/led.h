#include <Arduino.h>

#define PORT_LED_ONOFF LED_BUILTIN

void setup_led()
{
    pinMode(PORT_LED_ONOFF, OUTPUT);
}