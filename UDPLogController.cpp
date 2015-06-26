#include "UDPLogController.h"

UDPLogController::UDPLogController()
{
    mReadBuffer = BufferController::Instance()->GetReadBuffer();
    mConfigMap = ConfigController::Instance()->GetConfigMap();
    mSensMap = ConfigController::Instance()->GetSensorMap();

    map<int,DriverSettingsItem>::iterator it;
    for(it = mConfigMap->begin();it!=mConfigMap->end();++it)
    {
        int Number = (*it).first;
        int NumbBuffer = (*it).second.GetNumberBuffer();

        mDriversMap.insert(pair<int, int>(Number,mReadBuffer->Get_MOTOR_CPOS(NumbBuffer)));
    }

    map<int,Sensor>::iterator it2;

    for(it2 = mSensMap->begin();it2!=mSensMap->end();++it2)
    {
        int Number = (*it2).first;
        int Value = (*it2).second.GetValue();
        mSensorsMap.insert(pair<int, int>(Number,Value));
    }
}

UDPLogController::~UDPLogController()
{

}

void UDPLogController::AddRawData(int time)
{
    map<int,int>::iterator it;
    for(it = mDriversMap.begin();it!=mDriversMap.end();++it)
    {
        int NumberBuffer = mConfigMap->at((*it).first).GetNumberBuffer();

        (*it).second=mReadBuffer->Get_MOTOR_CPOS(NumberBuffer);
    }

    for(it = mSensorsMap.begin();it!=mSensorsMap.end();++it)
    {
        int Value = mSensMap->at((*it).first).GetValue();

        (*it).second=Value;
    }

    //создаем элемент вектора с данными моторов
    LogData Data;
    Data.Time=mTime.elapsed();
    //Data.Time=time;
    Data.DriversData=mDriversMap;
    Data.SensorsData=mSensorsMap;
    //окончание создания

    mLogVector.push_back(Data);

}

bool UDPLogController::SaveData(string fileName)
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

        map<int,Sensor>::iterator it2;

        //записываем номера сенсоров
        for(it2 = mSensMap->begin();it2!=mSensMap->end();++it2)
        {
            file << "\t";

            //file << itoa((*it2).first,buffer,10);
            file << (*it2).second.GetNameLog();
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

            //записываем значения сенсоров
            for(it = data.SensorsData.begin();it!=data.SensorsData.end();++it)
            {
                double Value = (*it).second;
                std::sprintf(buffer,"%f",Value);
                file << "\t" << buffer;
            }


            file << "\n";

        }

        file.close();
        return true;
    }

}

void UDPLogController::ClearLog()
{
    mLogVector.clear();
}

void UDPLogController::StartWrite()
{
    mTime.start();
}

