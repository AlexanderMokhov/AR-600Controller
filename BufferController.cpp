#include "BufferController.h"

BufferController * BufferController::mInst = 0;

void BufferController::InitBuffers()
{
    for(auto it = ConfigController::Inst()->GetMotors()->begin();
        it != ConfigController::Inst()->GetMotors()->end();++it)
    {
        int Channel = (*it).second.GetChannel();
        int PosMin = (*it).second.GetMinPos();
        int PosMax = (*it).second.GetMaxPos();

        mWriteBuffer.SetDeviceChannel((*it).first,Channel);
        mReadBuffer.SetDeviceChannel((*it).first,Channel);

        mWriteBuffer.SetMotorStiff((*it).first,(*it).second.GetStiff());
        mWriteBuffer.SetMotorDump((*it).first,(*it).second.GetDump());
        mWriteBuffer.SetMotorTorque((*it).first,(*it).second.GetTorque());
        mWriteBuffer.SetMotorCalibration((*it).first,(*it).second.GetCalibration());

        mWriteBuffer.SetMotorReverce((*it).first,(*it).second.GetReverce());
        mReadBuffer.SetMotorReverce((*it).first,(*it).second.GetReverce());

        mWriteBuffer.SetMotorEnable((*it).first,(*it).second.GetEnable());
        mWriteBuffer.SetMotorMinAngle((*it).first,PosMin);
        mWriteBuffer.SetMotorMaxAngle((*it).first,PosMax);
        mWriteBuffer.MotorStop((*it).first);
    }

    for(auto it = ConfigController::Inst()->GetSensors()->begin();
        it != ConfigController::Inst()->GetSensors()->end();++it)
    {
        int Channel = (*it).second.GetChannel();
        mWriteBuffer.SetDeviceChannel(Channel,Channel);
        mReadBuffer.SetDeviceChannel(Channel,Channel);
    }
    mReadBuffer.Init(mWriteBuffer.GetRAW());
}

