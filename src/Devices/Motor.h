#ifndef MOTOR_H
#define MOTOR_H

#include "Device.h"
#include "PIDGates.h"

//Класс двигателя робота
class Motor : public Device
{
public:
    std::string     m_status;
    int             m_angle;
    int             m_minAngle;
    int             m_maxAngle;
    bool            m_reverceState;
    PIDGates       *m_PIDGates;
    int             m_shiftValue;
    bool            m_enable;

public:
    Motor();
    ~Motor();
    Motor(int number,
           int channel,
           std::string name,
           int minAngle,
           int maxAngle,
           bool reverceState,
           PIDGates *gates,
           int shiftValue,
           bool enable);

    int getMinAngle();
    int getMaxAngle();
    bool getReverceState();
    PIDGates *getPIDGates();
    int getShiftValue();
    bool getEnable();

    void setMinAngle(int angle);
    void setMaxAngle(int angle);
    void setShiftValue( int value );
    void setPIDGates( PIDGates *gates );
    void setEnable(bool enable);
};

#endif // MOTOR_H
