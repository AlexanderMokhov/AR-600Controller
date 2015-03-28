#ifndef DRIVERSETTINGSITEM_H
#define DRIVERSETTINGSITEM_H

#include<iostream>
using namespace std;

class DriverSettingsItem
{
private:
    unsigned int    mNumber;
    unsigned int    mNumberBuffer;

    std::string     mName;

    int    mMinPos;
    int    mMaxPos;
    bool            mReverce;
    unsigned int    mSTIFF;
    unsigned int    mDUMP;

public:
    DriverSettingsItem();
    ~DriverSettingsItem();
    DriverSettingsItem(unsigned int Number,
                       unsigned int NumberBuffer,
                       std::string Name,
                       int MinPos,
                       int MaxPos,
                       bool Reverce,
                       unsigned int STIFF,
                       unsigned int DUMP);

};

#endif // DRIVERSETTINGSITEM_H
