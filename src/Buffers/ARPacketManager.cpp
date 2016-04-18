#include "ARPacketManager.h"

ARPacketManager * ARPacketManager::m_inst = 0;

void ARPacketManager::initPackets()
{
    for(auto it = SettingsStorage::Inst()->GetMotors()->begin();
        it != SettingsStorage::Inst()->GetMotors()->end();++it)
    {
        m_packetSend.setDeviceChannel((*it).first,(*it).second.getChannel());
        m_packetRecv.setDeviceChannel((*it).first,(*it).second.getChannel());

        m_packetSend.setMotorPGate((*it).first,(*it).second.getPIDGates()->getPGate());
        m_packetSend.setMotorIGate((*it).first,(*it).second.getPIDGates()->getIGate());
        m_packetSend.setMotorDGate((*it).first,(*it).second.getPIDGates()->getDGate());
        m_packetSend.setMotorShiftValue((*it).first,(*it).second.getShiftValue());

        m_packetSend.setMotorReverceState((*it).first,(*it).second.getReverceState());
        m_packetRecv.setMotorReverce((*it).first,(*it).second.getReverceState());

        m_packetSend.setMotorEnable((*it).first,(*it).second.getEnable());
        m_packetSend.setMotorMinAngle((*it).first,(*it).second.getMinAngle());
        m_packetSend.setMotorMaxAngle((*it).first,(*it).second.getMaxAngle());
        m_packetSend.motorStopBrake((*it).first);
    }

    for(auto it = SettingsStorage::Inst()->GetSensors()->begin();
        it != SettingsStorage::Inst()->GetSensors()->end();++it)
    {
        int Channel = (*it).second.getChannel();
        m_packetSend.setDeviceChannel(Channel,Channel);
        m_packetRecv.setDeviceChannel(Channel,Channel);
    }
    m_packetRecv.initialize(m_packetSend.getRAW());
}

ARPacketManager::ARPacketManager()
{

}
