#include "BufferController.h"

BufferController * BufferController::m_Instance = 0;

BufferController::BufferController()
{

}

BufferController::~BufferController()
{

}


BufferController *BufferController::Instance()
{
    return m_Instance;
}

void BufferController::initialize()
{
    delete m_Instance;
    m_Instance = new BufferController;
}

void BufferController::shutdown()
{
    delete m_Instance;
    m_Instance = 0;
}

MBRead *BufferController::getReadBuffer()
{
    return &mReadBuffer;
}

MBWrite *BufferController::getWriteBuffer()
{
    return &mWriteBuffer;
}

void BufferController::initBuffers()
{
    //mWriteBuffer.init();
    mReadBuffer.init(mWriteBuffer.GetBuffer());
    mReadBuffer.SetReverceMap(mWriteBuffer.GetReverceMap());
}

