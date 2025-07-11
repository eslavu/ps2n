#include <string.h>
#include "system.hpp"

void System::save_alert(unsigned long timestamp)
{
    this->alerts[this->alertIndex].timestamp = timestamp;

    int baseAddr = 20 + this->alertIndex * 4;
    for (int i = 0; i < 4; i++)
        EEPROM.write(baseAddr + i, (timestamp >> (8 * i)) & 0xFF);

    this->alertIndex = (this->alertIndex + 1) % MAX_FLOOD_ALERTS;
}

void System::log()
{
    Serial.print("%\n");
    for (StatusMessage message : this->status)
    {
        Serial.print(message.temperature);
        Serial.print(",");
        Serial.print(message.humidity);
        Serial.print("\n");
    }
    Serial.print("%\n");
    for (FloodAlert message : this->alerts)
    {
        Serial.print(message.timestamp);
        Serial.print("\n");
    }
    Serial.print("%\n");
}

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
        else if (command == "LOG")
            this->log();

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

void System::save_status(float temperature, int humidity)
{
    this->status[this->statusIndex].temperature = temperature;
    this->status[this->statusIndex].humidity = humidity;

    int addr = this->statusIndex * 2;
    EEPROM.write(addr, temperature);
    EEPROM.write(addr + 1, humidity);

    this->statusIndex = (this->statusIndex + 1) % MAX_STATUS_MESSAGES;

    if(this->system_flood == FLOOD)
    {
        unsigned long now = millis();
        if(now - this->last_alert >= FLOOD_ALERT_COOLDOWN)
        {
            this->save_alert(now);
            this->last_alert = now;
        }
    }
}

void System::load_EEPROM()
{
    for (int i = 0; i < MAX_STATUS_MESSAGES; i++)
    {
        int addr = i * 2;
        this->status[i].temperature = EEPROM.read(addr);
        this->status[i].humidity = EEPROM.read(addr + 1);
    }
    for (int i = 0; i < MAX_FLOOD_ALERTS; i++)
    {
        int baseAddr = 20 + i * 4;

        unsigned long ts = 0;
        for (int j = 0; j < 4; j++)
            ts |= ((unsigned long)EEPROM.read(baseAddr + j)) << (8 * j);
        this->alerts[i].timestamp = ts;
    }
}

void System::clear_EEPROM()
{
    int addr, i, j;
    this->statusIndex = 0;
    this->alertIndex = 0;

    for (i = 0; i < MAX_STATUS_MESSAGES; i++)
    {
        addr = i * 2;
        EEPROM.write(addr, 0);
        EEPROM.write(addr + 1, 0);
    }
    for (i = 0; i < MAX_FLOOD_ALERTS; i++)
    {
        addr = 20 + i * 4;
        for (j = 0; j < 4; j++)
            EEPROM.write(addr + j, (0 >> (8 * i)) & 0xFF);
    }
}