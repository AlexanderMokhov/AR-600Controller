#ifndef FRUNDPACKETRECV_H
#define FRUNDPACKETRECV_H

#include <iostream>

//
class FrundPacketRecv
{
public:
    // public methods
    FrundPacketRecv();
    ~FrundPacketRecv();

private:
    // private variable
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

#endif // FRUNDPACKETRECV_H
