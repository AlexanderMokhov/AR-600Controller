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

    int             mMinPos;
    int             mMaxPos;
    bool            mReverce;
    int             mStiff;
    int             mDump;
    int             mTorque;
    int             mIlim;

public:
    DriverSettingsItem();
    ~DriverSettingsItem();
    DriverSettingsItem(unsigned int Number,
                       unsigned int NumberBuffer,
                       std::string Name,
                       int MinPos,
                       int MaxPos,
                       bool Reverce,
                       int Stiff,
                       int Dump,
                       int Torque,
                       int Ilim);
    unsigned int getNumber();
    unsigned int getNumberBuffer();
    std::string getName();
    int getMinPos();
    int getMaxPos();
    bool getReverce();
    int getStiff();//получить KP
    int getDump();//получить KI
    int getTorque();//получить KD
    int getIlim();

};

#endif // DRIVERSETTINGSITEM_H
