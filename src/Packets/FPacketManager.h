#ifndef FPACKETMANAGER_H
#define FPACKETMANAGER_H

#include <iostream>
#include "stdlib.h"

#include "FPacketSend.h"
#include "FPacketRecv.h"

using namespace std;

class FPacketManager
{
public:
    // public methods
    static FPacketManager* Inst() { return m_inst; }
    static void Initialize(){ delete m_inst; m_inst = new FPacketManager; }

    FPacketRecv *getPacketRecv(){ return &m_packetRecv; }
    FPacketSend *getPacketSend(){ return &m_packetSend; }

private:
    // private variable
    static FPacketManager* m_inst;
    FPacketRecv m_packetRecv;
    FPacketSend m_packetSend;

    // private methods
    FPacketManager();
    FPacketManager( FPacketManager const& );
    ~FPacketManager(){}
};

#endif // FPACKETMANAGER_H
