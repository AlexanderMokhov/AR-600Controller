#include "BufferController.h"

BufferController * BufferController::mInstance = 0;

BufferController::BufferController()
{

}

BufferController::~BufferController()
{

}


BufferController *BufferController::Instance()
{
    return mInstance;
}

void BufferController::Initialize()
{
    delete mInstance;
    mInstance = new BufferController;
}

ReadBuffer *BufferController::GetReadBuffer()
{
    return &mReadBuffer;
}

WriteBuffer *BufferController::GetWriteBuffer()
{
    return &mWriteBuffer;
}

void BufferController::InitBuffers()
{
    map<int,Motor>::iterator it;
    for(it = ConfigController::Instance()->GetMotorMap()->begin();
        it != ConfigController::Instance()->GetMotorMap()->end();++it)
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
    map<int,Sensor>::iterator it2;
    for(it2 = ConfigController::Instance()->GetSensorMap()->begin();
        it2 != ConfigController::Instance()->GetSensorMap()->end();++it2)
    {
        int NumbBuffer = (*it2).second.GetNumberBuffer();
        mWriteBuffer.SetDeviceChannel(NumbBuffer,NumbBuffer);
        mReadBuffer.SetDeviceChannel(NumbBuffer,NumbBuffer);
    }
    mReadBuffer.Init(mWriteBuffer.GetRAW());
}

