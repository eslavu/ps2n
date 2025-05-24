#include "cloud.h" 

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
    char serial_input;
    if (Serial.available())
    {
        serial_input = Serial.read();
        switch (serial_input)
        {
            case '0':
                system_isOn = 0;
                break;
            case '1':
                system_isOn = 1;
                break;

            default: break;
        }
    }
}

inline int get_system_isOn()
{ return system_isOn; }

inline Flood get_system_flood()
{ return system_flood; }

inline Temperature get_system_temperature()
{ return system_temperature; }