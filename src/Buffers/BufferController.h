#ifndef BUFFERCONTROLLER_H
#define BUFFERCONTROLLER_H

#include <iostream>
#include "stdlib.h"

#include "Management/SettingsStorage.h"
#include "BufferSend.h"
#include "BufferRecv.h"

using namespace std;
class BufferController
{
private:
    BufferController(){}
    ~BufferController(){}
    BufferController( BufferController const& );

    static BufferController* m_inst;

    BufferRecv m_bufferRecv;
    BufferSend m_bufferSend;
public:
    static BufferController* Inst() { return m_inst; }
    static void Init(){ delete m_inst; m_inst = new BufferController; }

    BufferRecv *getBufferRecv(){ return &m_bufferRecv; }
    BufferSend *getBufferSend(){ return &m_bufferSend; }
    void buffersInitialize();
};

#endif // BUFFERCONTROLLER_H


