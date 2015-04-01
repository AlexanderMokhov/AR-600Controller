#include "LogController.h"

LogController::LogController()
{
    mReadBuffer = BufferController::Instance()->getReadBuffer();
    ConfMap=AR600ControllerConf::Instance()->getConfMap();
    map<unsigned int,DriverSettingsItem>::iterator it;
    for(it = ConfMap->begin();it!=ConfMap->end();++it)
    {
        int Number = (*it).first;
        int NumbBuffer = (*it).second.getNumberBuffer();
        m_DriversMap.insert(pair<int, int>(Number,mReadBuffer->MOTOR_CPOS_get((NumbBuffer))));
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

    //создаем элемент вектора с данными моторов
    LogData Data;
    Data.Time=time;
    Data.DriversData=m_DriversMap;
    //окончание создания

    LogVector.push_back(Data);

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
        for(it = m_DriversMap.begin();it!=m_DriversMap.end();++it)
        {
            file << "\t";
            file << itoa((*it).first,buffer,10);
        }

        file << "\n";

        //теперь можно писать время и значения
        vector<LogData>::iterator itv;
        for(itv=LogVector.begin();itv!=LogVector.end();++itv)
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
   LogVector.clear();
}

