#ifndef MOVECORRECTOR_H
#define MOVECORRECTOR_H

#include <QDebug>

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <cmath>
#include <mutex>

#include "Buffers/BufferController.h"
#include "ConfigController.h"

struct Amend //поправка
{
    int sNumber = 0;      //номер датчика
    double sZeroValue = 0;  //нулевое значение датчика
    double mScale = 0;  //масштаб. коэфф. для коэфф. обр. связи
    double sScale = 0;  //масштаб. коэфф. для датчика
};

class MoveCorrector
{
private:
    std::map<int, std::vector<Amend>> mAmends;//карта поправок
    std::map<int, Motor> *aMotors;
    std::map<int, Sensor> *aSensors;

    void SkipSpace( std::locale loc, std::string str, unsigned int *i );
    void ReadValue( std::string *temp, std::locale loc, unsigned int *i, std::string str );

    MoveCorrector();
    ~MoveCorrector(){}
    MoveCorrector( MoveCorrector const& );
    static MoveCorrector* mInst;

public:
    static MoveCorrector* Inst(){ return mInst; }
    void Init();

    bool OpenFile( std::string fileName );
    int getCorrectValue( int NumberChannel );
};

#endif // MOVECORRECTOR_H
