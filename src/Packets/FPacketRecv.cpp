#include "FPacketRecv.h"

FPacketRecv::FPacketRecv()
{

}

FPacketRecv::~FPacketRecv()
{

}

void FPacketRecv::initialize(const char RAW_other[])
{
    for(int i = 0; i < FBufferSize; i++) m_RAW[i] = RAW_other[i];
}

const char *FPacketRecv::getRAW()
{
    return m_RAW;
}

double FPacketRecv::getNumber(int chunnel)
{
    double Number;
    memcpy(&Number, m_RAW + (chunnel * 72) + NUMBER, sizeof(double));
    return Number;
}

double FPacketRecv::getTime(int chunnel)
{
    double Time;
    memcpy(&Time, m_RAW + (chunnel * 72) + TIME, sizeof(double));
    return Time;
}

double FPacketRecv::getAngle(int chunnel)
{
    double Angle;
    memcpy(&Angle, m_RAW + (chunnel * 72) + ANGLE, sizeof(double));
    return Angle;
}

double FPacketRecv::getPGate(int chunnel)
{
    double PGate;
    memcpy(&PGate, m_RAW + (chunnel * 72) + P_GATE, sizeof(double));
    return PGate;
}

double FPacketRecv::getIGate(int chunnel)
{
    double IGate;
    memcpy(&IGate, m_RAW + (chunnel * 72) + I_GATE, sizeof(double));
    return IGate;
}

double FPacketRecv::getDGate(int chunnel)
{
    double DGate;
    memcpy(&DGate, m_RAW + (chunnel * 72) + D_GATE, sizeof(double));
    return DGate;
}

double FPacketRecv::getPGateFactor(int chunnel)
{
    double PGateFactor;
    memcpy(&PGateFactor, m_RAW + (chunnel * 72) + P_GATE_FACTOR, sizeof(double));
    return PGateFactor;
}

double FPacketRecv::getIGateFactor(int chunnel)
{
    double IGateFactor;
    memcpy(&IGateFactor, m_RAW + (chunnel * 72) + I_GATE_FACTOR, sizeof(double));
    return IGateFactor;
}

double FPacketRecv::getDGateFactor(int chunnel)
{
    double DGateFactor;
    memcpy(&DGateFactor, m_RAW + (chunnel * 72) + D_GATE_FACTOR, sizeof(double));
    return DGateFactor;
}


