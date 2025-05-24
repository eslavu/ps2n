#include <Arduino.h>

#include "led.h"
#include "cloud.h"

void setup()
{
  Serial.begin(9600);
  Serial.print("ready");
}

void loop()
{
  led();
}