#ifndef DRIVERLOGCONTROLLER_H
#define DRIVERLOGCONTROLLER_H
#include "BufferController.h"
#include "ConfigController.h"

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
#include <sstream>

using namespace std;

struct LogData
{
    int Time;
    std::map<int,int> DriversData;
};

class DriverLogController
{
public:
    DriverLogController();
    ~DriverLogController();



    MBRead *mReadBuffer;
    std::map<int,int> mDriversMap;
    std::vector<LogData> mLogVector;
    std::map<unsigned int,DriverSettingsItem> * mConfigMap;

    void AddRawData(int time);
    bool SaveData(std::string fileName);
    void ClearLog();



};

#endif // DRIVERLOGCONTROLLER_H
