#include "system.hpp"

void System::read_serial()
{
    if (Serial.available())
    {
        String command = Serial.readStringUntil('\n');
        if (command == "ON")
            system_isOn = true;
        else if (command == "OFF")
            system_isOn = false;
    }
    // char serial_input;
    // if (Serial.available())
    // {
    //     serial_input = Serial.read();
    //     switch (serial_input)
    //     {
    //         case '0':
    //             Serial.println("sistem oprit!");
    //             this->system_isOn = false;
    //             break;
    //         case '1':
    //             Serial.println("sistem pornit!");
    //             this->system_isOn = true;
    //             break;

    //         default: break;
    //     }
    // }
}

int System::get_system_isOn()
{ return this->system_isOn; }

Flood System::get_system_flood()
{ return this->system_flood; }

Heat System::get_system_heat()
{ return this->system_heat; }