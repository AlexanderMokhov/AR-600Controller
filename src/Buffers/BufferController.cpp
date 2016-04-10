#include "BufferController.h"

BufferController * BufferController::m_inst = 0;

void BufferController::Initialize()
{
    for(auto it = ARCore::Inst()->getSettingStore()->GetMotors()->begin();
        it != ARCore::Inst()->getSettingStore()->GetMotors()->end();++it)
    {
        m_bufferSend.setDeviceChannel((*it).first,(*it).second.getChannel());
        m_bufferRecv.setDeviceChannel((*it).first,(*it).second.getChannel());

        m_bufferSend.setMotorPGate((*it).first,(*it).second.getPIDGates()->getPGate());
        m_bufferSend.setMotorIGate((*it).first,(*it).second.getPIDGates()->getIGate());
        m_bufferSend.setMotorDGate((*it).first,(*it).second.getPIDGates()->getDGate());
        m_bufferSend.setMotorShiftValue((*it).first,(*it).second.getShiftValue());

        m_bufferSend.setMotorReverceState((*it).first,(*it).second.getReverceState());
        m_bufferRecv.setMotorReverce((*it).first,(*it).second.getReverceState());

        m_bufferSend.setMotorEnable((*it).first,(*it).second.getEnable());
        m_bufferSend.setMotorMinAngle((*it).first,(*it).second.getMinAngle());
        m_bufferSend.setMotorMaxAngle((*it).first,(*it).second.getMaxAngle());
        m_bufferSend.motorStopBrake((*it).first);
    }

    for(auto it = ARCore::Inst()->getSettingStore()->GetSensors()->begin();
        it != ARCore::Inst()->getSettingStore()->GetSensors()->end();++it)
    {
        int Channel = (*it).second.getChannel();
        m_bufferSend.setDeviceChannel(Channel,Channel);
        m_bufferRecv.setDeviceChannel(Channel,Channel);
    }
    m_bufferRecv.initialize(m_bufferSend.getRAW());
}

