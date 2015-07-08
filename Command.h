#ifndef COMMAND_H
#define COMMAND_H

#include <iostream>
#include <fstream>
#include <string>
#include <map>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <cmath>

using namespace std;

struct PID
{
    int Stiff;
    int Dump;
    int Torque;
};

class Command
{
private:
    int mTime; //Время исполнения
    int mNumber; //номер канала

    int mPosition; //Позиция мотора
    PID mPID; //ПИД кооэффициенты регулятора

public:

    Command();
    ~Command();

    int GetNumber();
    int GetTime();
    int GetPosition();
    PID GetPID();

    void SetTime(int Time);
    void SetPosition(int Position);
    void SetNumber(int Number);
    void SetPID(PID oPID);


};

#endif // COMMAND_H
