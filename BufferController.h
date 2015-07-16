#ifndef BUFFERCONTROLLER_H
#define BUFFERCONTROLLER_H

#include "ConfigController.h"
#include "WriteBuffer.h"
#include "ReadBuffer.h"
#include <iostream>
#include "stdlib.h"

//BufferController * BufferController::mInst = 0;

using namespace std;
class BufferController
{
private:
    BufferController(){}
    ~BufferController(){}
    BufferController(BufferController const&);

    static BufferController* mInst;

    ReadBuffer mReadBuffer;
    WriteBuffer mWriteBuffer;
public:
    static BufferController* Inst() {return mInst;}
    static void Init(){delete mInst; mInst = new BufferController;}

    ReadBuffer *GetReadBuffer(){return &mReadBuffer;}
    WriteBuffer *GetWriteBuffer(){return &mWriteBuffer;}
    void InitBuffers();
};

#endif // BUFFERCONTROLLER_H


