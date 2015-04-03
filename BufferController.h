#ifndef BUFFERCONTROLLER_H
#define BUFFERCONTROLLER_H

#include "MBWrite.h"
#include "MBRead.h"
#include <iostream>
#include "stdlib.h"
#include "windows.h"
#include "winsock2.h"

using namespace std;
class BufferController
{
private:
    BufferController();
    ~BufferController();
    BufferController(BufferController const&);

    static BufferController* m_Instance;

    MBRead mReadBuffer;
    MBWrite mWriteBuffer;
public:
    static BufferController* Instance();
    static void initialize();
    static void shutdown();

    MBRead *getReadBuffer();
    MBWrite *getWriteBuffer();
    void initBuffers();


};

#endif // BUFFERCONTROLLER_H
