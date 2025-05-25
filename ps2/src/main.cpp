#include <Arduino.h>
#include "MovingAverage.hpp"

#include "led.hpp"
#include "system.hpp"

#include "temperature.hpp"
#include "humidity.hpp"

static int timeStart, timeStop;
static System sys;

static Led led;
static Temperature LM35;
static Humidity DHT;

static int system_isOn;
static float system_temperature;
static int system_humidity;

void setup()
{
  Serial.begin(9600);
  Serial.println("ready");

  timeStart = millis();
}

// sudo chmod a+rw /dev/ttyACM0
void loop()
{
  sys.read_serial();
  system_isOn = sys.get_system_isOn();
  
  led.led(system_isOn, sys.get_system_flood(), sys.get_system_heat());
  LM35.read();
  DHT.read();
  
  if (system_isOn)
  {
    system_temperature = LM35.get();
    system_humidity = DHT.get();

    timeStop = millis();
    if (timeStop - timeStart >= 2000)
    {
      Serial.print("temperatura: ");  Serial.print(system_temperature);  Serial.println("C");
      Serial.print("umiditate: ");  Serial.print(system_humidity);  Serial.println("%");
      Serial.println();

      timeStart = millis();
    }
  }
}