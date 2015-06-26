#ifndef SENSORLISTITEM_H
#define SENSORLISTITEM_H

#include "Device.h"

class SensorListItem : public Device
{
public:
    int             mValue;
    string          mNameLog;
public:
    SensorListItem();
    ~SensorListItem();
    SensorListItem(unsigned int Number,
           unsigned int NumberBuffer,
           std::string Name,
           std::string NameLog);
};

#endif // SENSORLISTITEM_H
