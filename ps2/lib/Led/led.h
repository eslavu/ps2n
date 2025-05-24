#ifndef LED_H
#define LED_H

#include <Arduino.h>
#include "cloud.h"

#define PORT_LED_ONOFF LED_BUILTIN
#define PORT_LED_FLOOD 2

#define PORT_LED_LOW 5
#define PORT_LED_GOOD 6
#define PORT_LED_HIGH 7

static int temp[3];

void setup_led();
void led();

void led_onoff();
void led_flood();
void led_temperature();

#endif