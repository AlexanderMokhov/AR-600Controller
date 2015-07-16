#include "DeviceLogController.h"

DeviceLogController * DeviceLogController::mInst = 0;

DeviceLogController::DeviceLogController()
{
    mReadBuffer = BufferController::Inst()->GetReadBuffer();
    mConfigMap = ConfigController::Inst()->GetMotorMap();
    mSensMap = ConfigController::Inst()->GetSensorMap();

    map<int,Motor>::iterator it;
    for(it = mConfigMap->begin();it!=mConfigMap->end();++it)
    {
        int Number = (*it).first;
        int NumbBuffer = (*it).second.GetNumberBuffer();

        mDriversMap.insert(pair<int, int>(Number,mReadBuffer->GetMotorAngle(NumbBuffer)));
    }

    map<int,Sensor>::iterator it2;

    for(it2 = mSensMap->begin();it2!=mSensMap->end();++it2)
    {
        int Number = (*it2).first;
        int Value = (*it2).second.GetValue();
        mSensorsMap.insert(pair<int, int>(Number,Value));
    }

}

void DeviceLogController::AddRawData()
{
    map<int,int>::iterator it;
    for(it = mDriversMap.begin();it!=mDriversMap.end();++it)
    {
        int NumberBuffer = mConfigMap->at((*it).first).GetNumberBuffer();

        (*it).second=mReadBuffer->GetMotorAngle(NumberBuffer);
    }

    for(it = mSensorsMap.begin();it!=mSensorsMap.end();++it)
    {
        int Value = mReadBuffer->GetSensorValue(mSensMap->at((*it).first).GetNumberBuffer(),
                                                mSensMap->at((*it).first).GetParam()) ;
        (*it).second=Value;
    }

    //создаем элемент вектора с данными моторов
    LogData Data;
    Data.Time=mTime.elapsed();

    //Mi=(Mi*countTimers-(Data.Time-LastTime))/++countTimers;
    if(dt_max<(Data.Time-LastTime)){dt_max=(Data.Time-LastTime);}
    if(dt_min>(Data.Time-LastTime)){dt_min=(Data.Time-LastTime);}
    LastTime = Data.Time;
    qDebug() << " DtMax=: " << QString::number(dt_max)<< " DtMin=: " << QString::number(dt_min)<< endl;

    //Data.Time=time;
    Data.DriversData=mDriversMap;
    Data.SensorsData=mSensorsMap;
    //окончание создания

    mLogVector.push_back(Data);
}

bool DeviceLogController::SaveData(string fileName)
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

void DeviceLogController::ClearLog()
{
    mLogVector.clear();
}

void DeviceLogController::StartWrite()
{
    mLogVector.clear();
    mTime.start();
    dt_min = 10000000;
    dt_max = -10000000;
    countTimers=0;
    LastTime=0;
}

