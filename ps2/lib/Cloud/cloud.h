#ifndef CLOUD_H
#define CLOUD_H

#include <Arduino.h>

static int system_isOn = 0;

typedef enum Flood
{ DRY, MEDIUM, FLOOD } Flood;
static Flood system_flood = FLOOD;

typedef enum Temperature
{ LO, GOOD, HI } Temperature;
static Temperature system_temperature = HI;

void read_serial();
inline int get_system_isOn();
inline Flood get_system_flood();
inline Temperature get_system_temperature();

#endif