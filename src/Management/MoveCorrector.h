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
public:
    //public methods
    static MoveCorrector* Inst(){ return m_inst; }
    void initialize();

    bool openFile( std::string fileName );
    bool openDriveMatFile( std::string fileName );
    int getCorrectValue(int NumberChannel, int CTime);

    void setCurLine(long id){m_lineId = id;}
    //!!!
    long int m_duration;
    long int m_RowsNumber;

private:
    //private variable
    static MoveCorrector* m_inst;
    long int m_lineId;

    std::map<int, std::vector<Amend>> m_amends;//карта поправок
    std::map<int, Motor> *m_motors;
    std::map<int, Sensor> *m_sensors;

    std::vector<DriveMatData> m_driveMatVector;//New
    std::map<int, double> m_sensorsMap;
    std::vector<int> m_sensorsNumbers;

    //private methods
    void skipSpace( std::locale loc, std::string str, unsigned int *i );
    void readValue( std::string *temp, std::locale loc, unsigned int *i, std::string str );

    MoveCorrector();
    ~MoveCorrector(){}
    MoveCorrector( MoveCorrector const& );

};

#endif // MOVECORRECTOR_H
