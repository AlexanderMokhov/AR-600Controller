#ifndef SENSOR_H
#define SENSOR_H

#include "Device.h"

class Sensor : public Device
{
private:
    std::string     mNameLog;
    int             mParam;
    int             mValue;
public:
    Sensor();
    ~Sensor();
    Sensor(unsigned int Number,
           unsigned int NumberBuffer,
           std::string Name,
           std::string NameLog,
           int param);
    int GetValue();
    void SetValue(int value);
    std::string GetNameLog();
    void SetNameLog(std::string NameLog);
    int GetParam();
    void SetParam(int Param);
};

#endif // SENSOR_H
