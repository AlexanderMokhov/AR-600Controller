#ifndef UDPLOGCONTROLLER_H
#define UDPLOGCONTROLLER_H
#include "BufferController.h"
#include "ConfigController.h"

#include <iostream>
#include <map>
#include "TinyXML/tinyxml.h"
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <math.h>
//#include <cmath>
#include <sstream>
#include <stdlib.h>
#include <QTime>
using namespace std;

struct LogData
{
    int Time;
    std::map<int,int> DriversData;
    std::map<int,int> SensorsData;
};

class UDPLogController
{
public:
    UDPLogController();
    ~UDPLogController();



    MBRead *mReadBuffer;
    std::map<int,int> mDriversMap;
    std::map<int,int> mSensorsMap;
    std::vector<LogData> mLogVector;
    std::map<unsigned int,DriverSettingsItem> * mConfigMap;
    std::map<int,Sensor> * mSensMap;
    QTime mTime;

    void AddRawData(int time);
    bool SaveData(std::string fileName);
    void ClearLog();
    void StartWrite();



};

#endif // UDPLOGCONTROLLER_H
