#include "DriverLogController.h"

DriverLogController::DriverLogController()
{
    mReadBuffer = BufferController::Instance()->GetReadBuffer();
    mConfigMap = ConfigController::Instance()->GetConfigMap();
    map<unsigned int,DriverSettingsItem>::iterator it;
    for(it = mConfigMap->begin();it!=mConfigMap->end();++it)
    {
        int Number = (*it).first;
        int NumbBuffer = (*it).second.GetNumberBuffer();

        mDriversMap.insert(pair<int, int>(Number,mReadBuffer->Get_MOTOR_CPOS(NumbBuffer)));
    }
}

DriverLogController::~DriverLogController()
{

}

void DriverLogController::AddRawData(int time)
{
    map<int,int>::iterator it;
    for(it = mDriversMap.begin();it!=mDriversMap.end();++it)
    {
        int NumberBuffer = ConfigController::Instance()->GetConfigMap()->at((*it).first).GetNumberBuffer();

        (*it).second=mReadBuffer->Get_MOTOR_CPOS(NumberBuffer);
    }

    //создаем элемент вектора с данными моторов
    LogData Data;
    Data.Time=time;
    Data.DriversData=mDriversMap;
    //окончание создания

    mLogVector.push_back(Data);

}

bool DriverLogController::SaveData(string fileName)
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
            double Time=data.Time/1000.0;
            std::sprintf(buffer,"%f",Time);
            file << "\t" << buffer;

            //записываем позиции приводов
            for(it = data.DriversData.begin();it!=data.DriversData.end();++it)
            {
                double Pos = (*it).second;
                double pi = 4 * std::atan(1);
                Pos = (pi*Pos)/(180*100);
                std::sprintf(buffer,"%f",Pos);
                file << "\t" << buffer;
            }

            file << "\n";

        }

        file.close();
        return true;
    }

}

void DriverLogController::ClearLog()
{
   mLogVector.clear();
}

