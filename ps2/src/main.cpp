#include <Arduino.h>

#include "led.h"
#include "cloud.h"

#include "temperature.h"
#include "humidity.h"

void setup()
{
  Serial.begin(9600);
  Serial.println("ready");
}

void loop()
{
  led();
}