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
    ~Sensor(){;}
    Sensor(int Number,
           int Channel,
           std::string Name,
           std::string NameLog,
           int param);

    int GetValue(){return mValue;}
    std::string GetNameLog(){return mNameLog;}
    int GetParam(){return mParam;}

    void SetValue(int value){mValue = value;}
    void SetNameLog(std::string NameLog){mNameLog = NameLog;}
    void SetParam(int Param){mParam = Param;}
};

#endif // SENSOR_H
