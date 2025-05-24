#include "cloud.h"

static char serial_input;

void read_serial()
{
    // if (Serial.available())
    // {
    //     String command = Serial.readStringUntil('\n');
    //     if (command == "ON")
    //         system_isOn = 1;
    //     else if (command == "OFF")
    //         system_isOn = 0;
    // }
    if (Serial.available())
        serial_input = Serial.read();

    switch (serial_input)
    {
        case '0':
            system_isOn = 0;
            break;
        case '1':
            system_isOn = 1;
            break;

        break;
    }
}