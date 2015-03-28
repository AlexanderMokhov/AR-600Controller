#include "driversettingsitem.h"

DriverSettingsItem::DriverSettingsItem()
{

}

DriverSettingsItem::~DriverSettingsItem()
{
    mNumber=0;
    mNumberBuffer=0;
    mName = "";
    mMinPos = 0;
    mMaxPos = 0;
    mReverce = false;
    mSTIFF = 0;
    mDUMP = 0;
}

DriverSettingsItem::DriverSettingsItem(unsigned int Number,
                                       unsigned int NumberBuffer,
                                       string Name, int MinPos,
                                       int MaxPos, bool Reverce,
                                       unsigned int STIFF,
                                       unsigned int DUMP)
{
    mNumber=Number;
    mNumberBuffer=NumberBuffer;
    mName = Name;
    mMinPos = MinPos;
    mMaxPos = MaxPos;
    mReverce = Reverce;
    mSTIFF = STIFF;
    mDUMP = DUMP;
}

