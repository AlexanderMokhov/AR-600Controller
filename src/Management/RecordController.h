#ifndef RECORDCONTROLLER_H
#define RECORDCONTROLLER_H

#include <chrono>

#include <iostream>
#include <map>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <cmath>

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#include "Packets/ARPacketManager.h"
#include "SettingsStorage.h"

using namespace std;

struct RecordData
{
    long Time;
    std::map<int, int> MotorsData;
    std::map<int, int> SensorsData;
    std::map<int, float> MotorsCurrent;
    double DriversPower;
};

class RecordController
{
public:
    //public variable
    ARPacketRecv *mReadBuffer;

    std::map<int,int> mDriversMap;
    std::map<int,int> mSensorsMap;
    std::map<int, float> mDrivsCurMap;

    std::vector<RecordData> mRecordVector;
    std::map<int,Motor> * mConfigMap;
    std::map<int,Sensor> * mSensMap;
    double driverPower;

    //public methods
    static RecordController* Inst(){return mInst;}
    static void Initialize(){delete mInst; mInst = new RecordController;}

    void addRawData();
    bool SaveData(std::string fileName, bool mode);
    bool SaveCurData(std::string fileName);
    void StartWrite();

    void getLastData(char* retData);

    long getElapsedTime();

private:
    //private variable
    static RecordController* mInst;

    std::chrono::time_point<std::chrono::system_clock> startTime, endTime;

    //private methods
    RecordController();
    ~RecordController(){}
    RecordController(RecordController const&);
};

#endif // RECORDCONTROLLER_H
