#ifndef DRIVERCOMMAND_H
#define DRIVERCOMMAND_H

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

class DriverCommand
{
private:
    //unsigned int mNumber; //номер канала

    //int mPosition; //Позиция мотора
    //int mPID; //ПИД кооэффициенты регулятора


public:
    std::map<int,int> mDriversMap;
    int mTime; //Время исполнения

    DriverCommand();
    ~DriverCommand();

    unsigned int getNumber();
    unsigned int getTime();
    int getPosition();
    void Clear();
    std::map<int, int> &GetDriverMap();
    int GetTime();


};

#endif // DRIVERCOMMAND_H
