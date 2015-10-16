#include "Device.h"

Device::Device()
{
    mNumber = 0;
    mChannel = 0;
    mName = "";
}

Device::~Device()
{

}

Device::Device(int Number, int Channel, string Name)
{
    mNumber = Number;
    mChannel = Channel;
    mName = Name;
}

int Device::GetNumber()
{
    return mNumber;
}

int Device::GetChannel()
{
    return mChannel;
}

string Device::GetName()
{
    return mName;
}

void Device::SetNumber(int Number)
{
    mNumber = Number;
}

void Device::SetChannel(int Channel)
{
    mChannel = Channel;
}

void Device::SetName(string Name)
{
    mName = Name;
}

