#ifndef BUFFERCONTROLLER_H
#define BUFFERCONTROLLER_H

#include "MBWrite.h"
#include "MBRead.h"
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

    MBRead mReadBuffer;
    MBWrite mWriteBuffer;
public:
    static BufferController* Instance();
    static void Initialize();
    static void Shutdown();

    MBRead *GetReadBuffer();
    MBWrite *GetWriteBuffer();
    void InitBuffers();


};

#endif // BUFFERCONTROLLER_H
