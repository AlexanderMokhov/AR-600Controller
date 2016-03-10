#include "Device.h"

Device::Device()
{
    m_number = 0;
    m_channel = 0;
    m_name = "";
}

Device::~Device()
{

}

Device::Device(int number, int channel, string name)
{
    m_number = number;
    m_channel = channel;
    m_name = name;
}

int Device::getNumber()
{
    return m_number;
}

int Device::getChannel()
{
    return m_channel;
}

string Device::getName()
{
    return m_name;
}

void Device::setNumber(int number)
{
    m_number = number;
}

void Device::setChannel(int channel)
{
    m_channel = channel;
}

void Device::setName(string name)
{
    m_name = name;
}

