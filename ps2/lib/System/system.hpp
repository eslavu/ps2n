#ifndef SYSTEM_H
#define SYSTEM_H

#include <stdio.h>
#include <Arduino.h>
#include <EEPROM.h>

#define MAX_STATUS_MESSAGES 10
#define MAX_FLOOD_ALERTS 10
#define FLOOD_ALERT_COOLDOWN 300000UL

struct StatusMessage
{
    byte temperature = 0;
    byte humidity = 0;
};

struct FloodAlert
{
    unsigned long timestamp = 0;
};

enum Flood
{ DRY, MEDIUM, FLOOD };

enum Heat
{ LO, GOOD, HI };

class System
{
private:
    const uint8_t VCC = 12;

    bool system_isOn = false;
    Flood system_flood = DRY;
    Heat system_heat = LO;

    StatusMessage status[MAX_STATUS_MESSAGES];
    FloodAlert alerts[MAX_FLOOD_ALERTS];

    int statusIndex = 0,
        alertIndex = 0;
    unsigned long last_alert = 0;

    void save_alert(unsigned long);

public:
    System() {}
    void read_serial();

    int get_system_isOn();
    Flood get_system_flood();
    Heat get_system_heat();

    void log();
    void save_status(float, int);
    void load_EEPROM();
    void clear_EEPROM();
};

#endif