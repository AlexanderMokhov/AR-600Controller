#include "SensorListItem.h"

SensorListItem::SensorListItem()
{

}

SensorListItem::~SensorListItem()
{

}

SensorListItem::SensorListItem(unsigned int Number, unsigned int NumberBuffer, string Name): Device(Number,NumberBuffer,Name)
{
    mValue = 0;
}

