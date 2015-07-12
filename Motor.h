#ifndef MOTOR_H
#define MOTOR_H
#include "Device.h"

//Класс двигателя робота
class Motor : public Device
{
public:
    std::string     mStatus;
    int             mPos;
    int             mMinPos;
    int             mMaxPos;
    bool            mReverce;
    int             mStiff;
    int             mDump;
    int             mTorque;
    int             mCalibration;
    bool            mEnable;

public:
    Motor();
    ~Motor();
    Motor(unsigned int Number,
           unsigned int NumberBuffer,
           std::string Name,
           int MinPos,
           int MaxPos,
           bool Reverce,
           int Stiff,
           int Dump,
           int Torque,
           int Calibration,
           bool Enable);

    int GetMinPos();
    int GetMaxPos();
    bool GetReverce();
    int GetStiff();//получить KP
    int GetDump();//получить KI
    int GetTorque();//получить KD
    int GetCalibration();
    bool GetEnable();
    void SetCalibration(int Calibration);
    void SetStiff(int Stiff);
    void SetDump(int Dump);
    void SetTorque(int Torque);
    void SetEnable(bool Enable);
};

#endif // MOTOR_H
