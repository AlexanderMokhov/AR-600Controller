#include "FootSensor.h"

FootSensor::FootSensor() : Device()
{
    mUCH0 = 0;
    mUCH1 = 0;
    mUCH2 = 0;
    mUCH3 = 0;
}

FootSensor::~FootSensor()
{

}

FootSensor::FootSensor(unsigned int Number,
                       unsigned int NumberBuffer,
                       string Name,
                       int UCH0,
                       int UCH1,
                       int UCH2,
                       int UCH3) : Device (Number,NumberBuffer,Name)
{
    mUCH0 = UCH0;
    mUCH1 = UCH1;
    mUCH2 = UCH2;
    mUCH3 = UCH3;
}

int FootSensor::GetUCH0()
{
    return mUCH0;
}

int FootSensor::GetUCH1()
{
    return mUCH1;
}

int FootSensor::GetUCH2()
{
    return mUCH2;
}

int FootSensor::GetUCH3()
{
    return mUCH3;
}

void FootSensor::SetUCH0(int UCH)
{
    mUCH0 = UCH;
}

void FootSensor::SetUCH1(int UCH)
{
    mUCH1 = UCH;
}

void FootSensor::SetUCH2(int UCH)
{
    mUCH2 = UCH;
}

void FootSensor::SetUCH3(int UCH)
{
    mUCH3 = UCH;
}

