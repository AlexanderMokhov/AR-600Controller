#include "DeviceLogController.h"

DeviceLogController * DeviceLogController::mInst = 0;

DeviceLogController::DeviceLogController()
{
    mReadBuffer = BufferController::Inst()->GetReadBuffer();
    mConfigMap = ConfigController::Inst()->GetMotors();
    mSensMap = ConfigController::Inst()->GetSensors();

    for(auto it = mConfigMap->begin();it!=mConfigMap->end();++it)
    {
        int Number = (*it).second.GetNumber();
        mDriversMap.insert(pair<int, int>(Number,mReadBuffer->GetMotorAngle(Number)));
    }

    for(auto it = mSensMap->begin();it!=mSensMap->end();++it)
    {
        int Number = (*it).second.GetNumber();
        int Value = (*it).second.GetValue();
        mSensorsMap.insert(pair<int, int>(Number,Value));
    }

}

void DeviceLogController::AddRawData()
{
    for(auto it = mDriversMap.begin();it!=mDriversMap.end();++it)
    {
        (*it).second = mReadBuffer->GetMotorAngle((*it).first);
    }

    for(auto it = mSensorsMap.begin();it!=mSensorsMap.end();++it)
    {
        int Value = mReadBuffer->GetSensorValue(mSensMap->at((*it).first).GetChannel(),
                                                mSensMap->at((*it).first).GetParam()) ;
        (*it).second=Value;
    }

    //создаем элемент вектора с данными моторов
    LogData Data;
    Data.Time=mTime.elapsed();
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

        //записываем номера приводов
        for(auto it = mDriversMap.begin();it!=mDriversMap.end();++it)
        {
            file << "\t";

            file << itoa((*it).first,buffer,10);
        }

        //записываем номера сенсоров
        for(auto it2 = mSensMap->begin();it2!=mSensMap->end();++it2)
        {
            file << "\t";

            //file << itoa((*it2).first,buffer,10);
            file << (*it2).second.GetNameLog();
        }

        file << "\n";

        //теперь можно писать время и значения
        for(auto itv=mLogVector.begin();itv!=mLogVector.end();++itv)
        {
            LogData data = (*itv);
            double Time=data.Time/1000.0;
            std::sprintf(buffer,"%f",Time);
            file << "\t" << buffer;

            //записываем позиции приводов
            for(auto it = data.DriversData.begin();it!=data.DriversData.end();++it)
            {
                double Pos = (*it).second;
                double pi = 4 * std::atan(1);
                Pos = (pi*Pos)/(180*100);
                std::sprintf(buffer,"%f",Pos);
                file << "\t" << buffer;
            }

            //записываем значения сенсоров
            for(auto it = data.SensorsData.begin();it!=data.SensorsData.end();++it)
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

void DeviceLogController::StartWrite()
{
    mLogVector.clear();
    mTime.start();
}

