#include <Arduino.h>
#include "MovingAverage.hpp"

#include "led.hpp"
#include "system.hpp"

#include "temperature.hpp"
#include "humidity.hpp"

static System sys;

static Led led;
static Humidity DHT;
static Temperature LM35;

static char message[100];
static bool system_isOn;
static int system_humidity;
static float system_temperature;

void setup()
{
  Serial.begin(9600);
  sys.load_EEPROM();
  sys.log();
}

// sudo chmod a+rw /dev/ttyACM0
void loop()
{
  sys.read_serial();
  system_isOn = sys.get_system_isOn();
  
  led.led(system_isOn, sys.get_system_flood(), sys.get_system_heat());
  DHT.read();
  system_humidity = DHT.get()[0];

  LM35.read();
  system_temperature = LM35.get(DHT.get()[1]);
  
  if (system_isOn)
  {
    Serial.print("temp:");
    Serial.print(system_temperature);
    Serial.print(",hum:");
    Serial.print(system_humidity);
    Serial.print('\n');

    sys.save_status(system_temperature, system_humidity);
  }
}