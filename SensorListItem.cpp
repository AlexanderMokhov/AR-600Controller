#include "SensorListItem.h"

SensorListItem::SensorListItem()
{

}

SensorListItem::~SensorListItem()
{

}

SensorListItem::SensorListItem(unsigned int Number, unsigned int NumberBuffer, string Name, string NameLog): Device(Number,NumberBuffer,Name)
{
    mValue = 0;
    mNameLog = NameLog;
}

