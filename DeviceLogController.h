#ifndef DEVICELOGCONTROLLER_H
#define DEVICELOGCONTROLLER_H

#include "BufferController.h"
#include "ConfigController.h"

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
#include <QTime>
#include <QDebug>

using namespace std;

struct LogData
{
    int Time;
    std::map<int,int> DriversData;
    std::map<int,int> SensorsData;
};

class DeviceLogController
{

private:
    DeviceLogController();
    ~DeviceLogController(){}
    DeviceLogController(DeviceLogController const&);
    static DeviceLogController* mInst;
public:
    BufferReceive *mReadBuffer;
    std::map<int,int> mDriversMap;
    std::map<int,int> mSensorsMap;
    std::vector<LogData> mLogVector;
    std::map<int,Motor> * mConfigMap;
    std::map<int,Sensor> * mSensMap;
    QTime mTime;

    static DeviceLogController* Inst(){return mInst;}
    static void Init(){delete mInst; mInst = new DeviceLogController;}

    void AddRawData();
    bool SaveData(std::string fileName);
    void StartWrite();
};

#endif // DEVICELOGCONTROLLER_H
