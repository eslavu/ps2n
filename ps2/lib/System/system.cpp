#include <string.h>
#include "system.hpp"

void System::read_serial()
{
    if (Serial.available())
    {
        int index;
        String command = Serial.readStringUntil('\n');
        if (command == "ON")
            system_isOn = true;
        else if (command == "OFF")
            system_isOn = false;

        else
        {
            index = command.indexOf(',');
            if (index != -1)
            {
                system_flood = (Flood)command.substring(0, index).toInt();
                system_heat = (Heat)command.substring(index + 1).toInt();
            }
        }
    }
}

int System::get_system_isOn()
{ return this->system_isOn; }

Flood System::get_system_flood()
{ return this->system_flood; }

Heat System::get_system_heat()
{ return this->system_heat; }