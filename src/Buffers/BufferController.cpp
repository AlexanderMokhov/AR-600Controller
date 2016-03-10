#include "BufferController.h"

BufferController * BufferController::mInst = 0;

void BufferController::InitBuffers()
{
    for(auto it = SettingsStorage::Inst()->GetMotors()->begin();
        it != SettingsStorage::Inst()->GetMotors()->end();++it)
    {
        int Channel = (*it).second.getChannel();
        int PosMin = (*it).second.getMinAngle();
        int PosMax = (*it).second.getMaxAngle();

        mBufferSend.SetDeviceChannel((*it).first,Channel);
        mBufferReceive.SetDeviceChannel((*it).first,Channel);

        mBufferSend.SetMotorStiff((*it).first,(*it).second.getPIDGates()->getPGate());
        mBufferSend.SetMotorDump((*it).first,(*it).second.getPIDGates()->getIGate());
        mBufferSend.SetMotorTorque((*it).first,(*it).second.getPIDGates()->getDGate());
        mBufferSend.SetMotorCalibration((*it).first,(*it).second.getShiftValue());

        mBufferSend.SetMotorReverce((*it).first,(*it).second.getReverceState());
        mBufferReceive.SetMotorReverce((*it).first,(*it).second.getReverceState());

        mBufferSend.SetMotorEnable((*it).first,(*it).second.getEnable());
        mBufferSend.SetMotorMinAngle((*it).first,PosMin);
        mBufferSend.SetMotorMaxAngle((*it).first,PosMax);
        mBufferSend.MotorStopBrake((*it).first);
    }

    for(auto it = SettingsStorage::Inst()->GetSensors()->begin();
        it != SettingsStorage::Inst()->GetSensors()->end();++it)
    {
        int Channel = (*it).second.getChannel();
        mBufferSend.SetDeviceChannel(Channel,Channel);
        mBufferReceive.SetDeviceChannel(Channel,Channel);
    }
    mBufferReceive.Init(mBufferSend.GetRAW());
}

