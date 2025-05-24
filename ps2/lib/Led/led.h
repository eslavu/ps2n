#ifndef LED_H
#define LED_H

#include <Arduino.h>
#include "cloud.h"

#define LED_ONOFF LED_BUILTIN
#define LED_FLOOD 2

#define LED_LOW 5
#define LED_GOOD 6
#define LED_HIGH 7

static int temp[3];

void setup_led();
void led();

void led_onoff();
void led_flood();
void led_temperature();

#endif