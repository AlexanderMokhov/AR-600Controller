#ifndef SENSOR_H
#define SENSOR_H

#include "Device.h"

class Sensor : public Device
{
private:
    int             mParam;
    int             mValue;
public:
    Sensor();
    ~Sensor();
    Sensor(unsigned int Number,
           unsigned int NumberBuffer,
           std::string Name,
           int param);
    int GetValue();
    void SetValue(int value);
};

#endif // SENSOR_H
