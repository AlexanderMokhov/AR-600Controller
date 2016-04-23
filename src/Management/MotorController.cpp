#include "MotorController.h"

MotorController * MotorController::m_inst = 0;

MotorController::MotorController()
{
    m_state = NOT_WORK;
    motorNumber = -1;
    waitCount = 0;
}

void MotorController::stepWork()
{
    switch (m_state) {
    case START_ZEROING:
        startingZeroing();
        break;
    case DO_ZEROING:
        doZeroing();
        break;
    case STOP_ZEROING:
        stoppingZeroing();
        break;
    default:
        break;
    }
}

void MotorController::startZeroing(int motorNumber)
{
    newMotorNumber = motorNumber;
    m_state = START_ZEROING;
}

void MotorController::startingZeroing()
{
    motorNumber = newMotorNumber;
    ARPacketManager::Inst()->getPacketSend()->motorStopBrake(motorNumber);
    ARPacketManager::Inst()->getPacketSend()->setMotorShiftValue(motorNumber, 0);
    waitCount = 5;
    m_state = DO_ZEROING;
}

void MotorController::stoppingZeroing()
{
    if(waitCount-- == 0)
    {
        m_state = NOT_WORK;
    }
}

void MotorController::doZeroing()
{
    if(waitCount-- == 0)
    {
        //записываем в файл настроек новые калибровочные коэффициенты
        int currentValue = ARPacketManager::Inst()->getPacketRecv()->getMotorAngle(motorNumber);
        if(SettingsStorage::Inst()->GetMotors()->at(motorNumber).getReverceState())
            currentValue = -1*currentValue;
        SettingsStorage::Inst()->GetMotors()->at(motorNumber).setShiftValue(currentValue);
        ARPacketManager::Inst()->getPacketSend()->setMotorShiftValue(motorNumber, currentValue);
        ARPacketManager::Inst()->getPacketSend()->setMotorAngle(motorNumber, 0);
        SettingsStorage::Inst()->SaveFile("config.xml");

        waitCount = 5;
        m_state = STOP_ZEROING;
    }
}
