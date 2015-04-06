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
<<<<<<< HEAD
    mReadBuffer.init(mWriteBuffer.GetBuffer());
=======
    //mWriteBuffer.init();
    mReadBuffer.Init(mWriteBuffer.GetBuffer());
>>>>>>> origin/master
    mReadBuffer.SetReverceMap(mWriteBuffer.GetReverceMap());
}

