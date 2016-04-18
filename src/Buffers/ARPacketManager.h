#ifndef ARPACKETMANAGER_H
#define ARPACKETMANAGER_H

#include <iostream>
#include "stdlib.h"

#include "Management/SettingsStorage.h"
#include "ARPacketSend.h"
#include "ARPacketRecv.h"

using namespace std;

class ARPacketManager
{
public:
    // public methods
    static ARPacketManager* Inst() { return m_inst; }
    static void Initialize(){ delete m_inst; m_inst = new ARPacketManager; }
    void initPackets();

    ARPacketRecv *getPacketRecv(){ return &m_packetRecv; }
    ARPacketSend *getPacketSend(){ return &m_packetSend; }

private:
    // private variable
    static ARPacketManager* m_inst;
    ARPacketRecv m_packetRecv;
    ARPacketSend m_packetSend;

    // private methods
    ARPacketManager();
    ARPacketManager( ARPacketManager const& );
    ~ARPacketManager(){}
};

#endif // ARPACKETMANAGER_H


