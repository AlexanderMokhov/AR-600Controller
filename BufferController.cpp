#include "BufferController.h"

BufferController * BufferController::mInst = 0;

void BufferController::InitBuffers()
{
    for(auto it = ConfigController::Inst()->GetMotorMap()->begin();
        it != ConfigController::Inst()->GetMotorMap()->end();++it)
    {
        int NumbBuffer = (*it).second.GetNumberBuffer();
        mWriteBuffer.SetDeviceChannel((*it).first,NumbBuffer);
        mReadBuffer.SetDeviceChannel((*it).first,NumbBuffer);
        int PosMin = (*it).second.GetMinPos();
        int PosMax = (*it).second.GetMaxPos();

        mWriteBuffer.SetMotorStiff((*it).first,(*it).second.GetStiff());
        mWriteBuffer.SetMotorDump((*it).first,(*it).second.GetDump());
        mWriteBuffer.SetMotorTorque((*it).first,(*it).second.GetTorque());
        mWriteBuffer.SetMotorCalibration((*it).first,(*it).second.GetCalibration());

        mWriteBuffer.SetMotorReverce((*it).first,(*it).second.GetReverce());
        mReadBuffer.SetMotorReverce((*it).first,(*it).second.GetReverce());

        mWriteBuffer.SetMotorEnable((*it).first,(*it).second.GetEnable());
        mWriteBuffer.SetMotorMinAngle((*it).first,PosMin);
        mWriteBuffer.SetMotorMaxAngle((*it).first,PosMax);
        mWriteBuffer.SetDeviceChannel((*it).first,NumbBuffer);

        mWriteBuffer.MotorStop((*it).first);
    }

    for(auto it2 = ConfigController::Inst()->GetSensorMap()->begin();
        it2 != ConfigController::Inst()->GetSensorMap()->end();++it2)
    {
        int NumbBuffer = (*it2).second.GetNumberBuffer();
        mWriteBuffer.SetDeviceChannel(NumbBuffer,NumbBuffer);
        mReadBuffer.SetDeviceChannel(NumbBuffer,NumbBuffer);
    }
    mReadBuffer.Init(mWriteBuffer.GetRAW());
}

