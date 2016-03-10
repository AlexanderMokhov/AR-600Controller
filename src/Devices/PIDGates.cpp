#include "PIDGates.h"

PIDGates::PIDGates()
{
    this->PGate =
    this->IGate =
    this->DGate = 0;
}

PIDGates::PIDGates(int PGate, int IGate, int DGate)
{
    this->PGate = PGate;
    this->IGate = IGate;
    this->DGate = DGate;
}
