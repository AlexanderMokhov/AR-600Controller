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
    bool            mEnable;

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
                       int Ilim,
                       bool Enable);
    unsigned int GetNumber();
    unsigned int GetNumberBuffer();
    std::string GetName();
    int GetMinPos();
    int GetMaxPos();
    bool GetReverce();
    int GetStiff();//получить KP
    int GetDump();//получить KI
    int GetTorque();//получить KD
    int GetIlim();
    void SetIlim(int calibrationPos);
    void SetStiff(int oStiff);
    void SetDump(int oDump);
    bool GetEnable();

};

#endif // DRIVERSETTINGSITEM_H
