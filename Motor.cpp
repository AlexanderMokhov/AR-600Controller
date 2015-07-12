#include "Motor.h"

Motor::Motor() : Device()
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

Motor::~Motor()
{

}

Motor::Motor(unsigned int Number,
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

int Motor::GetMinPos()
{
    return mMinPos;
}

int Motor::GetMaxPos()
{
    return mMaxPos;
}

bool Motor::GetReverce()
{
    return mReverce;
}

int Motor::GetStiff()
{
    return mStiff;
}

int Motor::GetDump()
{
    return mDump;
}

int Motor::GetTorque()
{
    return mTorque;
}

int Motor::GetCalibration()
{
    return mCalibration;
}

bool Motor::GetEnable()
{
    return mEnable;
}

void Motor::SetCalibration(int Calibration)
{
    mCalibration = Calibration;
}

void Motor::SetStiff(int Stiff)
{
    mStiff = Stiff;
}

void Motor::SetDump(int Dump)
{
    mDump = Dump;
}

void Motor::SetTorque(int Torque)
{
    mTorque = Torque;
}

void Motor::SetEnable(bool Enable)
{
    mEnable = Enable;
}

