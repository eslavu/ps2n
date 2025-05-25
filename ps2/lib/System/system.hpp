#ifndef SYSTEM_H
#define SYSTEM_H

#include <Arduino.h>

enum Flood
{ DRY, MEDIUM, FLOOD };

enum Heat
{ LO, GOOD, HI };

class System
{
private:
    int system_isOn = 0;
    Flood system_flood = FLOOD;
    Heat system_heat = HI;

public:
    System() {}
    void read_serial();

    int get_system_isOn();
    Flood get_system_flood();
    Heat get_system_heat();
};

#endif