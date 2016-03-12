#ifndef MOTOR_H
#define MOTOR_H

#include "Device.h"
#include "PIDGates.h"

//Класс двигателя робота
class Motor : public Device
{
public:
    //public methods
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
    std::string getState();
    int getAngle();


    void setMinAngle(int angle);
    void setMaxAngle(int angle);
    void setShiftValue( int value );
    void setPIDGates( PIDGates *gates );
    void setEnable(bool enable);
    void setAngle(int angle);
    void setState(std::string state);
    void setReverceState(bool state);

private:
    //private variable
    std::string     m_state;
    int             m_angle;
    int             m_minAngle;
    int             m_maxAngle;
    bool            m_reverceState;
    PIDGates       *m_PIDGates;
    int             m_shiftValue;
    bool            m_enable;
};

#endif // MOTOR_H
