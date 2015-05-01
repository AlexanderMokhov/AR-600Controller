#include "DriverSettingsItem.h"

DriverSettingsItem::DriverSettingsItem()
{

}

DriverSettingsItem::~DriverSettingsItem()
{
    mNumber =       0;
    mNumberBuffer = 0;
    mName =         "";
    mMinPos =       0;
    mMaxPos =       0;
    mReverce =      false;
    mStiff =        0;//KP
    mDump =         0;//KI
    mTorque =       0;//KD
    mCalibration =  0;
    mEnable =       false;
}

DriverSettingsItem::DriverSettingsItem(unsigned int Number,unsigned int NumberBuffer,string Name,
                                       int MinPos,int MaxPos, bool Reverce,
                                       int Stiff,int Dump,int Torque,int Calibration,bool Enable)
{
    mNumber = Number;
    mNumberBuffer = NumberBuffer;
    mName = Name;
    mMinPos = MinPos;
    mMaxPos = MaxPos;
    mReverce = Reverce;
    mStiff = Stiff;
    mDump = Dump;
    mTorque = Torque;
    mCalibration = Calibration;
    mEnable = Enable;
}

unsigned int DriverSettingsItem::GetNumber()
{
    return mNumber;
}

unsigned int DriverSettingsItem::GetNumberBuffer()
{
    return mNumberBuffer;
}

string DriverSettingsItem::GetName()
{
    return mName;
}

int DriverSettingsItem::GetMinPos()
{
    return mMinPos;
}

int DriverSettingsItem::GetMaxPos()
{
    return mMaxPos;
}

bool DriverSettingsItem::GetReverce()
{
    return mReverce;
}

//получить KP
int DriverSettingsItem::GetStiff()
{
    return mStiff;
}

//получить KI
int DriverSettingsItem::GetDump()
{
    return mDump;
}

//получить KD
int DriverSettingsItem::GetTorque()
{
    return mTorque;
}

int DriverSettingsItem::GetCalibration()
{
    return mCalibration;
}

void DriverSettingsItem::SetCalibration(int Calibration)
{
    mCalibration=Calibration;
}

void DriverSettingsItem::SetStiff(int oStiff)
{
    mStiff=oStiff;
}

void DriverSettingsItem::SetDump(int oDump)
{
    mDump=oDump;
}

bool DriverSettingsItem::GetEnable()
{
    return mEnable;
}

