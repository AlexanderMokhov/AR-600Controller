#ifndef LOGCONTROLLER_H
#define LOGCONTROLLER_H
#include "BufferController.h"
#include "AR600ControllerConf.h"

#include <iostream>
#include <map>
#include "TinyXML/tinyxml.h"
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <cmath>

using namespace std;

struct LogData
{
    int Time;
    std::map<int,int> DriversData;
};

class LogController
{
public:
    LogController();
    ~LogController();



    MBRead *mReadBuffer;
    std::map<int,int> mDriversMap;
    std::vector<LogData> mLogVector;
    std::map<unsigned int,DriverSettingsItem> * mConfigMap;

    void AddRawData(int time);
    bool SaveData(std::string fileName);
    void ClearLog();



};

#endif // LOGCONTROLLER_H
