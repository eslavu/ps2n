#include <Arduino.h>

#include "led.h"
#include "cloud.h"

#include "temperature.h"
#include "humidity.h"

static int timeStart, timeStop;

void setup()
{
  Serial.begin(9600);
  Serial.println("ready");
  
  setup_led();
  setup_temperature();

  timeStart = millis();
}

void loop()
{
  read_serial();
  led();

  if (get_system_isOn())
  {
    timeStop = millis();
    if (timeStop - timeStart >= 2000)
    {
      Serial.print("temperatura: ");  Serial.print(get_temperature());  Serial.println("C");
      Serial.print("umiditate: ");  Serial.print(get_humidity());  Serial.println("%");
      Serial.println();

      timeStart = millis();
    }
  }
}