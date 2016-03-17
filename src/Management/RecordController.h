#ifndef RECORDCONTROLLER_H
#define RECORDCONTROLLER_H

#include <QTime>
#include <QDebug>

#include <iostream>
#include <map>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <sstream>
#include <stdlib.h>

#include "Buffers/BufferController.h"
#include "SettingsStorage.h"

using namespace std;

struct RecordData
{
    int Time;
    std::map<int, int> DriversData;
    std::map<int, int> SensorsData;
    std::map<int, float> DriversCurrent;
    double DriversPower;
};

class RecordController
{
public:
    //public variable
    BufferRecv *mReadBuffer;

    std::map<int,int> mDriversMap;
    std::map<int,int> mSensorsMap;
    std::map<int, float> mDrivsCurMap;

    std::vector<RecordData> mRecordVector;
    std::map<int,Motor> * mConfigMap;
    std::map<int,Sensor> * mSensMap;
    QTime mTime;
    double driverPower;

    //public methods
    static RecordController* Inst(){return mInst;}
    static void Init(){delete mInst; mInst = new RecordController;}

    void AddRawData();
    bool SaveData(std::string fileName);
    bool SaveCurData(std::string fileName);
    void StartWrite();
    void saveRow(string fileName);

private:
    //private variable
    static RecordController* mInst;

    //private methods
    RecordController();
    ~RecordController(){}
    RecordController(RecordController const&);
};

#endif // RECORDCONTROLLER_H
