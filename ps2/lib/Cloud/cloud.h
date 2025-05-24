#ifndef CLOUD_H
#define CLOUD_H

#include <Arduino.h>

static int system_isOn = 0;

typedef enum Flood
{ DRY, MEDIUM, FLOOD };
static Flood system_flood = DRY;

typedef enum Temperature
{ LO, GOOD, HI };
static Temperature system_temperature = GOOD;

void read_serial();

#endif