#include "GyroscopeSensor.h"

GyroscopeSensor::GyroscopeSensor():Device()
{
    mYAW = 0;
    mPITCH = 0;
    mROLL = 0;
}

GyroscopeSensor::~GyroscopeSensor()
{

}

int GyroscopeSensor::GetYAW()
{
    return mYAW;
}

int GyroscopeSensor::GetPITCH()
{
    return mPITCH;
}

int GyroscopeSensor::GetROLL()
{
    return mROLL;
}

void GyroscopeSensor::SetYAW(int YAW)
{
    mYAW = YAW;
}

void GyroscopeSensor::SetPITH(int PITCH)
{
    mPITCH = PITCH;
}

void GyroscopeSensor::SetROLL(int ROLL)
{
    mROLL = ROLL;
}

