#include "RecordController.h"

RecordController * RecordController::mInst = 0;

RecordController::RecordController()
{
    mReadBuffer = BufferController::Inst()->getBufferRecv();
    mConfigMap = SettingsStorage::Inst()->GetMotors();
    mSensMap = SettingsStorage::Inst()->GetSensors();

    for(auto it = mConfigMap->begin();it != mConfigMap->end(); ++it)
    {
        int Number = (*it).second.getNumber();
        mDriversMap.insert(pair<int, int>(Number, mReadBuffer->getMotorAngle(Number)));
        mDrivsCurMap.insert(pair<int,float>(Number, -1*mReadBuffer->getMotorCurrent(Number)/100.0));
    }

    for(auto it = mSensMap->begin(); it != mSensMap->end(); ++it)
    {
        int Number = (*it).second.getNumber();
        int Value = (*it).second.getValue();
        mSensorsMap.insert(pair<int, int>(Number,Value));
    }

}

void RecordController::AddRawData()
{
    for(auto it = mDriversMap.begin(); it != mDriversMap.end(); ++it)
    {
        (*it).second = mReadBuffer->getMotorAngle((*it).first);
    }

    for(auto it = mSensorsMap.begin(); it != mSensorsMap.end(); ++it)
    {
        int Value = mReadBuffer->getSensorValue(mSensMap->at((*it).first).getChannel(),
                                                mSensMap->at((*it).first).getParam()) ;
        (*it).second=Value;
    }

    for(auto it = mDrivsCurMap.begin(); it != mDrivsCurMap.end(); ++it)
    {
        (*it).second = -1 * mReadBuffer->getMotorCurrent((*it).first) / 100.0;
    }

    //создаем элемент вектора с данными моторов
    RecordData Data;
    Data.Time = mTime.elapsed();
    Data.DriversData = mDriversMap;
    Data.SensorsData = mSensorsMap;
    Data.DriversCurrent = mDrivsCurMap;
    //окончание создания

    mRecordVector.push_back(Data);
}

bool RecordController::SaveData(string fileName)
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
        for(auto it = mDriversMap.begin();it != mDriversMap.end(); ++it)
        {
            file << "\t";
            file << itoa((*it).first, buffer,10);
        }

        //записываем номера сенсоров
        for(auto it2 = mSensMap->begin();it2 != mSensMap->end(); ++it2)
        {
            file << "\t";
            file << (*it2).second.getNameLog();
        }

        file << "\n";

        //теперь можно писать время и значения
        for(auto itv = mRecordVector.begin(); itv != mRecordVector.end(); ++itv)
        {
            RecordData data = (*itv);
            double Time = data.Time / 1000.0;
            std::sprintf(buffer, "%f", Time);
            file << "\t" << buffer;

            //записываем позиции приводов
            for(auto it = data.DriversData.begin(); it != data.DriversData.end(); ++it)
            {
                double Pos = (*it).second;
                double pi = 4 * std::atan(1);
                Pos = (pi*Pos)/(180*100);
                std::sprintf(buffer,"%f",Pos);
                file << "\t" << buffer;
            }

            //записываем значения сенсоров
            for(auto it = data.SensorsData.begin(); it != data.SensorsData.end(); ++it)
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

bool RecordController::SaveCurData(string fileName)
{
    std::ofstream file;
    file.open(fileName.c_str(),ios_base::out | ios_base::trunc);

    if (!file.is_open()) // если файл не был открыт
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
        for(auto it = mDriversMap.begin();it != mDriversMap.end(); ++it)
        {
            file << "\t";
            file << itoa((*it).first, buffer,10);
        }

        file << "\n";

        //теперь можно писать время и значения
        for(auto itv = mRecordVector.begin(); itv != mRecordVector.end(); ++itv)
        {
            RecordData data = (*itv);
            double Time = data.Time / 1000.0;
            std::sprintf(buffer, "%f", Time);
            file << "\t" << buffer;

            //записываем Токи приводов
            for(auto it = data.DriversCurrent.begin(); it != data.DriversCurrent.end(); ++it)
            {
                float Pos = (*it).second;
                std::sprintf(buffer,"%f",Pos);
                file << "\t" << buffer;
            }

            file << "\n";
        }

        file.close();
        return true;
    }
}

void RecordController::StartWrite()
{
    mRecordVector.clear();
    mTime.start();
}

