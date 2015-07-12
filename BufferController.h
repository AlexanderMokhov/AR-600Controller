#ifndef BUFFERCONTROLLER_H
#define BUFFERCONTROLLER_H

#include "ConfigController.h"
#include "WriteBuffer.h"
#include "ReadBuffer.h"
#include <iostream>
#include "stdlib.h"

using namespace std;
class BufferController
{
private:
    BufferController();
    ~BufferController();
    BufferController(BufferController const&);

    static BufferController* mInstance;

    ReadBuffer mReadBuffer;
    WriteBuffer mWriteBuffer;
public:
    static BufferController* Instance();
    static void Initialize();

    ReadBuffer *GetReadBuffer();
    WriteBuffer *GetWriteBuffer();
    void InitBuffers();


};

#endif // BUFFERCONTROLLER_H
