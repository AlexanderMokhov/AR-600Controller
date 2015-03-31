#include "logcontroller.h"

LogController::LogController()
{
    mReadBuffer = BufferController::Instance()->getReadBuffer();
    ConfMap=AR600ControllerConf::Instance()->getConfMap();
    map<unsigned int,DriverSettingsItem>::iterator it;
    for(it = ConfMap->begin();it!=ConfMap->end();++it)
    {
        int Number = (*it).first;
        m_DriversMap.insert(pair<int, int>(Number,mReadBuffer->MOTOR_CPOS_get((Number))));
    }
}

LogController::~LogController()
{

}

void LogController::AddRawData(int time)
{
    map<int,int>::iterator it;
    for(it = m_DriversMap.begin();it!=m_DriversMap.end();++it)
    {
        (*it).second=mReadBuffer->MOTOR_CPOS_get((*it).first);
    }

    LogData Data;
    Data.Time=time;
    Data.DriversData=m_DriversMap;
    LogVector.push_back(Data);

}

void LogController::ClearLog()
{
   LogVector.clear();
}

