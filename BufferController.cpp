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

void BufferController::Shutdown()
{
    delete mInstance;
    mInstance = 0;
}

MBRead *BufferController::GetReadBuffer()
{
    return &mReadBuffer;
}

MBWrite *BufferController::GetWriteBuffer()
{
    return &mWriteBuffer;
}

void BufferController::InitBuffers()
{
    //mWriteBuffer.init();
    mReadBuffer.Init(mWriteBuffer.GetBuffer());
    mReadBuffer.SetReverceMap(mWriteBuffer.GetReverceMap());
}

