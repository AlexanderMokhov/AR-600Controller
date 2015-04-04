#include "LogController.h"

LogController::LogController()
{
    mReadBuffer = BufferController::Instance()->GetReadBuffer();
    mConfigMap=AR600ControllerConf::Instance()->GetConfigMap();
    map<unsigned int,DriverSettingsItem>::iterator it;
    for(it = mConfigMap->begin();it!=mConfigMap->end();++it)
    {
        int Number = (*it).first;
        int NumbBuffer = (*it).second.GetNumberBuffer();
        mDriversMap.insert(pair<int, int>(Number,mReadBuffer->Get_MOTOR_CPOS((NumbBuffer))));
    }
}

LogController::~LogController()
{

}

void LogController::AddRawData(int time)
{
    map<int,int>::iterator it;
    for(it = mDriversMap.begin();it!=mDriversMap.end();++it)
    {
        (*it).second=mReadBuffer->Get_MOTOR_CPOS((*it).first);
    }

    //создаем элемент вектора с данными моторов
    LogData Data;
    Data.Time=time;
    Data.DriversData=mDriversMap;
    //окончание создания

    mLogVector.push_back(Data);

}

bool LogController::SaveData(string fileName)
{
    std::ofstream file;
    file.open(fileName.c_str(),ios_base::out | ios_base::trunc);

    if (!file.is_open()) // если файл небыл открыт
    {
     //Файл не может быть открыт или создан
     return false;
    }
    else
    {
        char * buffer ;
        buffer = (char*)malloc(15*sizeof(char));

        file << "\t" << "TIME";
        map<int,int>::iterator it;

        //записываем номера приводов
        for(it = mDriversMap.begin();it!=mDriversMap.end();++it)
        {
            file << "\t";
            file << itoa((*it).first,buffer,10);
        }

        file << "\n";

        //теперь можно писать время и значения
        vector<LogData>::iterator itv;
        for(itv=mLogVector.begin();itv!=mLogVector.end();++itv)
        {
            LogData data = (*itv);
            file << "\t" << itoa(data.Time*1000,buffer,10);

            //записываем номера приводов
            for(it = data.DriversData.begin();it!=data.DriversData.end();++it)
            {
                std::string ff;
                ff = itoa((*it).second,buffer,10);
                int size = ff.size();
                if(size<6)
                    for(int i=0;i<6-size;i++)
                    {
                        ff.insert(0,"0");
                    }
                file << "\t";
                file << ff.c_str();
            }

            file << "\n";

        }

        file.close();
        return true;
    }

}

void LogController::ClearLog()
{
   mLogVector.clear();
}

