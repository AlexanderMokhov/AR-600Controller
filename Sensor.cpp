#include "Sensor.h"

Sensor::Sensor()
{
    mValue = 0;
}

Sensor::~Sensor()
{

}

Sensor::Sensor(unsigned int Number,
               unsigned int NumberBuffer,
               string Name,
               string NameLog,
               int param): Device(Number,NumberBuffer,Name)
{
    mParam = param;
    mValue = 0;
    mNameLog = NameLog;
}

int Sensor::GetValue()
{
    return mValue;
}

void Sensor::SetValue(int value)
{
    mValue = value;
}

string Sensor::GetNameLog()
{
    return mNameLog;
}

void Sensor::SetNameLog(string NameLog)
{
    mNameLog = NameLog;
}

int Sensor::GetParam()
{
    return mParam;
}

void Sensor::SetParam(int Param)
{
    mParam = Param;
}

