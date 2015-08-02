#include "Sensor.h"

Sensor::Sensor()
{
    mValue = 0;
}

Sensor::Sensor(int Number,
               int Channel,
               string Name,
               string NameLog,
               int param): Device(Number,Channel,Name)
{
    mParam = param;
    mValue = 0;
    mNameLog = NameLog;
}
