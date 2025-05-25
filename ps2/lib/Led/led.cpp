#include "led.hpp"

Led::Led()
{
    pinMode(this->LED_ONOFF, OUTPUT);
    pinMode(this->LED_FLOOD, OUTPUT);
    
    pinMode(this->LED_LOW, OUTPUT);
    pinMode(this->LED_GOOD, OUTPUT);
    pinMode(this->LED_HIGH, OUTPUT);
    
    this->reset_heat();
}

void Led::led(int system_isOn, Flood system_flood, Heat system_heat)
{
    this->system_isOn = system_isOn;
    this->system_flood = system_flood;
    this->system_heat = system_heat;

    this->led_onoff();
    this->led_flood();
    this->led_heat();
}

void Led::led_onoff()
{
    if (this->system_isOn)
        digitalWrite(this->LED_ONOFF, HIGH);
    else
        digitalWrite(this->LED_ONOFF, LOW);
}

void Led::led_flood()
{
    if (!this->system_isOn)
        digitalWrite(this->LED_FLOOD, LOW);

    else
        switch (this->system_flood)
        {
            case DRY:
                digitalWrite(this->LED_FLOOD, LOW);
                break;
            case MEDIUM:
                digitalWrite(this->LED_FLOOD, HIGH);
                delay(2000);
                digitalWrite(this->LED_FLOOD, LOW);
                delay(2000);
                break;
            case FLOOD:
                digitalWrite(this->LED_FLOOD, HIGH);
                delay(250);
                digitalWrite(this->LED_FLOOD, LOW);
                delay(250);
                break;

            default: break;
        }
}

void Led::led_heat()
{
    if (this->system_isOn)
        switch (this->system_heat)
        {
            case LO:
                this->heat[0] = HIGH;  this->heat[1] = LOW; this->heat[2] = LOW;
                break;
            case GOOD:
                this->heat[0] = LOW;  this->heat[1] = HIGH; this->heat[2] = LOW;
                break;
            case HI:
                this->heat[0] = LOW;  this->heat[1] = LOW; this->heat[2] = HIGH;
                break;

            default: break;
        }
    else
        this->reset_heat();

    digitalWrite(this->LED_LOW, this->heat[0]);
    digitalWrite(this->LED_GOOD, this->heat[1]);
    digitalWrite(this->LED_HIGH, this->heat[2]);
}

void Led::reset_heat()
{
    for (int i = 0; i < 3; i++)
        this->heat[i] = 0;
}