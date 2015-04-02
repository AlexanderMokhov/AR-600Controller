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
    mIlim =         0;
}

DriverSettingsItem::DriverSettingsItem(unsigned int Number,unsigned int NumberBuffer,string Name,
                                       int MinPos,int MaxPos, bool Reverce,
                                       int Stiff,int Dump,int Torque,int Ilim)
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
    mIlim = Ilim;
}

unsigned int DriverSettingsItem::getNumber()
{
    return mNumber;
}

unsigned int DriverSettingsItem::getNumberBuffer()
{
    return mNumberBuffer;
}

string DriverSettingsItem::getName()
{
    return mName;
}

int DriverSettingsItem::getMinPos()
{
    return mMinPos;
}

int DriverSettingsItem::getMaxPos()
{
    return mMaxPos;
}

bool DriverSettingsItem::getReverce()
{
    return mReverce;
}

//получить KP
int DriverSettingsItem::getStiff()
{
    return mStiff;
}

//получить KI
int DriverSettingsItem::getDump()
{
    return mDump;
}

//получить KD
int DriverSettingsItem::getTorque()
{
    return mTorque;
}

int DriverSettingsItem::getIlim()
{
    return mIlim;
}

void DriverSettingsItem::setIlim(int calibrationPos)
{
    mIlim=calibrationPos;
}

