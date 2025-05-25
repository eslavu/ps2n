#ifndef LED_H
#define LED_H

#include <Arduino.h>
#include "system.hpp"

class Led
{
private:
    const uint8_t LED_ONOFF = LED_BUILTIN;
    const uint8_t LED_FLOOD = 2;

    const uint8_t LED_LOW = 5;
    const uint8_t LED_GOOD = 6;
    const uint8_t LED_HIGH = 7;
    
    int heat[3];
    int system_isOn;
    Flood system_flood;
    Heat system_heat;

    void led_onoff();
    void led_flood();
    void led_heat();
    void reset_heat();

public:
    Led();
    void led(int, Flood, Heat);
};

#endif