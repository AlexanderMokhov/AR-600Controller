#ifndef FPACKETRECV_H
#define FPACKETRECV_H

#include <mutex>

#include "FPacketDefinition.h"
//
class FPacketRecv
{
public:
    // public methods
    FPacketRecv();
    ~FPacketRecv();

    void initialize( const char RAW_other[] );
    const char *getRAW();

    double getNumber(int chunnel);
    double getTime(int chunnel);
    double getAngle(int chunnel);
    double getPGate(int chunnel);
    double getIGate(int chunnel);
    double getDGate(int chunnel);
    double getPGateFactor(int chunnel);
    double getIGateFactor(int chunnel);
    double getDGateFactor(int chunnel);

private:
    // private variable
    char m_RAW [FBufferSize];
    std::mutex m_locker;

    const uint16_t NUMBER = 0;
    const uint16_t TIME = 8;
    const uint16_t ANGLE = 16;
    const uint16_t P_GATE = 24;
    const uint16_t I_GATE = 32;
    const uint16_t D_GATE = 40;
    const uint16_t P_GATE_FACTOR = 48;
    const uint16_t I_GATE_FACTOR = 56;
    const uint16_t D_GATE_FACTOR = 64;
};

#endif // FPACKETRECV_H
