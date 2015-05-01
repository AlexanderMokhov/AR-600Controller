#include "Driver.h"

Driver::Driver() : Device()
{
    mMinPos =       0;
    mMaxPos =       0;
    mReverce =      false;
    mStiff =        0;//KP
    mDump =         0;//KI
    mTorque =       0;//KD
    mCalibration =  0;
    mEnable =       false;
}

Driver::~Driver()
{

}

Driver::Driver(unsigned int Number,
               unsigned int NumberBuffer,
               string Name, int MinPos,
               int MaxPos, bool Reverce,
               int Stiff,
               int Dump,
               int Torque,
               int Calibration,
               bool Enable) : Device(Number,NumberBuffer,Name)
{
    mMinPos = MinPos;
    mMaxPos = MaxPos;
    mReverce = Reverce;
    mStiff = Stiff;
    mDump = Dump;
    mTorque = Torque;
    mCalibration = Calibration;
    mEnable = Enable;
}

int Driver::GetMinPos()
{
    return mMinPos;
}

int Driver::GetMaxPos()
{
    return mMaxPos;
}

bool Driver::GetReverce()
{
    return mReverce;
}

int Driver::GetStiff()
{
    return mStiff;
}

int Driver::GetDump()
{
    return mDump;
}

int Driver::GetTorque()
{
    return mTorque;
}

int Driver::GetCalibration()
{
    return mCalibration;
}

bool Driver::GetEnable()
{
    return mEnable;
}

void Driver::SetCalibration(int Calibration)
{
    mCalibration = Calibration;
}

void Driver::SetStiff(int Stiff)
{
    mStiff = Stiff;
}

void Driver::SetDump(int Dump)
{
    mDump = Dump;
}

void Driver::SetTorque(int Torque)
{
    mTorque = Torque;
}

void Driver::SetEnable(bool Enable)
{
    mEnable = Enable;
}

