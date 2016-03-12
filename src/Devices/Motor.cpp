#include "Motor.h"

Motor::Motor() : Device()
{
    m_minAngle = 0;
    m_maxAngle = 0;
    m_reverceState = false;
    m_PIDGates = new PIDGates();
    m_shiftValue =  0;
    m_enable = false;
}

Motor::~Motor()
{

}

Motor::Motor(int number,
               int channel,
               string name, int minAngle,
               int maxAngle, bool reverceState,
               PIDGates *gates,
               int shiftValue,
               bool enable) : Device(number, channel, name)
{
    m_minAngle = minAngle;
    m_maxAngle = maxAngle;
    m_reverceState = reverceState;
    m_PIDGates = gates;
    m_shiftValue = shiftValue;
    m_enable = enable;
}

int Motor::getMinAngle()
{
    return m_minAngle;
}

int Motor::getMaxAngle()
{
    return m_maxAngle;
}

bool Motor::getReverceState()
{
    return m_reverceState;
}

PIDGates* Motor::getPIDGates()
{
    return m_PIDGates;
}

int Motor::getShiftValue()
{
    return m_shiftValue;
}

bool Motor::getEnable()
{
    return m_enable;
}

string Motor::getState()
{
    return m_state;
}

int Motor::getAngle()
{
    return m_angle;
}

void Motor::setMinAngle(int angle)
{
    m_minAngle = angle;
}

void Motor::setMaxAngle(int angle)
{
    m_maxAngle = angle;
}

void Motor::setShiftValue(int shiftValue)
{
    m_shiftValue = shiftValue;
}

void Motor::setPIDGates(PIDGates *gates)
{
    m_PIDGates = gates;
}
void Motor::setEnable(bool enable)
{
    m_enable = enable;
}

void Motor::setAngle(int angle)
{
    m_angle = angle;
}

void Motor::setState(string state)
{
    m_state = state;
}

void Motor::setReverceState(bool state)
{
    m_reverceState = state;
}

