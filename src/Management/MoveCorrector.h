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
#include "SettingsStorage.h"

struct Amend //поправка
{
    int Type = 0;         //Тип строки
    int sNumber = 0;      //номер датчика
    int spNumber = 0;       //номер датчика в DRIVEMAT
    double sZeroValue = 0;  //нулевое значение датчика
    double mScale = 0;  //масштаб. коэфф. для коэфф. обр. связи
    double sScale = 0;  //масштаб. коэфф. для датчика
};

//New
struct DriveMatData
{
    long int Time;
    std::map<int, double> SensorsData;
};

class MoveCorrector
{
private:
    std::map<int, std::vector<Amend>> mAmends;//карта поправок
    std::map<int, Motor> *aMotors;
    std::map<int, Sensor> *aSensors;

    std::vector<DriveMatData> mDriveMatVector;//New
    std::map<int, double> mSensorsMap;
    std::vector<int> mSensorsNumbers;

    void SkipSpace( std::locale loc, std::string str, unsigned int *i );
    void ReadValue( std::string *temp, std::locale loc, unsigned int *i, std::string str );

    MoveCorrector();
    ~MoveCorrector(){}
    MoveCorrector( MoveCorrector const& );
    static MoveCorrector* mInst;

    long int mLineId;

public:
    static MoveCorrector* Inst(){ return mInst; }
    void Init();

    bool OpenFile( std::string fileName );
    bool OpenDriveMatFile( std::string fileName );
    int getCorrectValue(int NumberChannel, int CTime);

    void setCurLine(long id){mLineId = id;}

    long int mDuration;
    long int mCountRows;
};

#endif // MOVECORRECTOR_H
