#include "Sensor.h"

Sensor::Sensor()
{
    m_value = 0;
}

Sensor::Sensor(int number,
               int channel,
               string name,
               string nameLog,
               int param): Device(number, channel, name)
{
    m_param = param;
    m_value = 0;
    m_nameLog = nameLog;
}
