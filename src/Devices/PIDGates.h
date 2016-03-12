#ifndef PIDGATES_H
#define PIDGATES_H

class PIDGates
{
public:
    //public methods
    PIDGates();
    PIDGates(int PGate, int IGate, int DGate);

    int getPGate() { return this->PGate; }
    int getIGate() { return this->IGate; }
    int getDGate() { return this->DGate; }

    void setPGate( int PGate ) { this->PGate = PGate; }
    void setIGate( int IGate ) { this->IGate = IGate; }
    void setDGate( int DGate ) { this->DGate = DGate; }
private:
    //private variable
    int PGate;
    int IGate;
    int DGate;
};

#endif // PIDGATES_H
