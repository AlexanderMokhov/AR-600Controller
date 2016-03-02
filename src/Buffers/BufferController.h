#ifndef BUFFERCONTROLLER_H
#define BUFFERCONTROLLER_H

#include <iostream>
#include "stdlib.h"

#include "Management/SettingsStorage.h"
#include "BufferSend.h"
#include "BufferReceive.h"

using namespace std;
class BufferController
{
private:
    BufferController(){}
    ~BufferController(){}
    BufferController( BufferController const& );

    static BufferController* mInst;

    BufferReceive mBufferReceive;
    BufferSend mBufferSend;
public:
    static BufferController* Inst() { return mInst; }
    static void Init(){ delete mInst; mInst = new BufferController; }

    BufferReceive *GetBufferR(){ return &mBufferReceive; }
    BufferSend *GetBufferS(){ return &mBufferSend; }
    void InitBuffers();
};

#endif // BUFFERCONTROLLER_H


