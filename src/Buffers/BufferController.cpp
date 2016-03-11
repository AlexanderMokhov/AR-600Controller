#include "BufferController.h"

BufferController * BufferController::m_inst = 0;

void BufferController::buffersInitialize()
{
    for(auto it = SettingsStorage::Inst()->GetMotors()->begin();
        it != SettingsStorage::Inst()->GetMotors()->end();++it)
    {
        int Channel = (*it).second.getChannel();
        int PosMin = (*it).second.getMinAngle();
        int PosMax = (*it).second.getMaxAngle();

        m_bufferSend.setDeviceChannel((*it).first,Channel);
        m_bufferRecv.setDeviceChannel((*it).first,Channel);

        m_bufferSend.setMotorPGate((*it).first,(*it).second.getPIDGates()->getPGate());
        m_bufferSend.setMotorIGate((*it).first,(*it).second.getPIDGates()->getIGate());
        m_bufferSend.setMotorDGate((*it).first,(*it).second.getPIDGates()->getDGate());
        m_bufferSend.setMotorShiftValue((*it).first,(*it).second.getShiftValue());

        m_bufferSend.setMotorReverceState((*it).first,(*it).second.getReverceState());
        m_bufferRecv.setMotorReverce((*it).first,(*it).second.getReverceState());

        m_bufferSend.setMotorEnable((*it).first,(*it).second.getEnable());
        m_bufferSend.setMotorMinAngle((*it).first,PosMin);
        m_bufferSend.setMotorMaxAngle((*it).first,PosMax);
        m_bufferSend.motorStopBrake((*it).first);
    }

    for(auto it = SettingsStorage::Inst()->GetSensors()->begin();
        it != SettingsStorage::Inst()->GetSensors()->end();++it)
    {
        int Channel = (*it).second.getChannel();
        m_bufferSend.setDeviceChannel(Channel,Channel);
        m_bufferRecv.setDeviceChannel(Channel,Channel);
    }
    m_bufferRecv.initialize(m_bufferSend.getRAW());
}

