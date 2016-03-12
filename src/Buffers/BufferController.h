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
public:
    // public methods
    static BufferController* Inst() { return m_inst; }
    static void Init(){ delete m_inst; m_inst = new BufferController; }

    BufferRecv *getBufferRecv(){ return &m_bufferRecv; }
    BufferSend *getBufferSend(){ return &m_bufferSend; }
    void Initialize();

private:
    // private variable
    static BufferController* m_inst;
    BufferRecv m_bufferRecv;
    BufferSend m_bufferSend;

    // private methods
    BufferController(){}
    BufferController( BufferController const& );
    ~BufferController(){}
};

#endif // BUFFERCONTROLLER_H


