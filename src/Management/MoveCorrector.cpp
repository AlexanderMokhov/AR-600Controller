#include "MoveCorrector.h"

MoveCorrector * MoveCorrector::mInst = 0;

MoveCorrector::MoveCorrector()
{
    aSensors = ConfigController::Inst()->GetSensors();

    mAmends.clear();
    aMotors = ConfigController::Inst()->GetMotors();

    for(auto it = aMotors->begin(); it != aMotors->end(); ++it)
    {
        vector<Amend> item;
        //Добавляем в контейнер
        mAmends[(*it).second.GetNumber()] = item;
    }

    //очищаем вектор
    mDriveMatVector.clear();
    mSensorsNumbers.clear();

    mLineId = 0;
    mCountRows = 0;
    mDuration = 0;
}

void MoveCorrector::Init()
{
    delete mInst; mInst = new MoveCorrector;
}

bool MoveCorrector::OpenFile(string fileName)
{
    std::ifstream file(fileName.c_str());

    if( file.is_open() )
    {
        //очищаем поправки
        for(auto it = mAmends.begin(); it != mAmends.end(); ++it)
        {
            (*it).second.clear();
        }

        std::string line;

        Amend NextAmend;
        int countLines = 0;

        while( std::getline(file, line) )
        {
            //читаем очередную строку из файла
            std::locale loc;
            std::string temp;
            unsigned int i = 0;

            double mScale, sScale, sZeroValue;
            int sNumber = 0, Type = 0, mNumber = 0, spNumber;

            //читаем тип строки
            SkipSpace(loc, line, &i);
            ReadValue(&temp, loc, &i, line);
            Type = atoi( temp.c_str() );
            temp.clear();

            //читаем номер датчика
            SkipSpace(loc, line, &i);
            ReadValue(&temp, loc, &i, line);
            sNumber = atoi( temp.c_str() );
            temp.clear();

            //читаем номер привода
            SkipSpace(loc, line, &i);
            ReadValue(&temp, loc, &i, line);
            mNumber = atoi( temp.c_str() );
            temp.clear();

            if(Type == 2)
            {
                //читаем номер датчика в файле DRIVEMAT
                SkipSpace(loc, line, &i);
                ReadValue(&temp, loc, &i, line);
                spNumber = atoi( temp.c_str() );
                temp.clear();
            }

            //читаем Ak - масшт. к-т привода
            SkipSpace(loc, line, &i);
            ReadValue(&temp, loc, &i, line);
            mScale = atof( temp.c_str() );
            temp.clear();

            //читаем An - масшт. к-т датчика
            SkipSpace(loc, line, &i);
            ReadValue(&temp, loc, &i, line);
            sScale = atof( temp.c_str() );
            temp.clear();

            //читаем Kn - нулевое значение датчика
            SkipSpace(loc, line, &i);
            ReadValue(&temp, loc, &i, line);
            sZeroValue = atof( temp.c_str() );
            temp.clear();

            //заполняем команду
            NextAmend.Type = Type;

            NextAmend.mScale = mScale;
            NextAmend.sScale = sScale;
            NextAmend.sZeroValue = sZeroValue;
            NextAmend.sNumber = sNumber;

            if(Type == 2)
            {
                NextAmend.spNumber = spNumber;
                qDebug() << "Type "  << QString::number(Type) << endl;
            }

            //добавляем команду в список
            mAmends[mNumber].push_back(NextAmend);
            countLines++;
        }

        qDebug() << "считано " << QString::number(countLines) << " строк" << endl;

        file.close();
        return true;
    }
    else
    {
        file.close();
        return false;
    }
}

bool MoveCorrector::OpenDriveMatFile(string fileName)
{
    std::ifstream file(fileName.c_str());

    if( file.is_open() )
    {
        std::locale loc;
        std::string temp;
        unsigned int pos = 0;

        //очищаем вектор
        mDriveMatVector.clear();
        mSensorsNumbers.clear();
        mCountRows = 0;
        mDuration = 0;

        std::string line;

        DriveMatData NextData;
        int countLines = 0;

        std::getline(file, line);
        {
            //считываем номера сенсоров
            //пропускаем TIME
            SkipSpace(loc, line, &pos);
            ReadValue(&temp, loc, &pos, line);
            temp.clear();
            SkipSpace(loc, line, &pos);

            while(line[pos] != '\0')
            {
                //читаем номер сенсора
                int sNumber = 0;

                ReadValue(&temp, loc, &pos, line);
                sNumber = atoi( temp.c_str() );
                temp.clear();
                SkipSpace(loc, line, &pos);

                mSensorsNumbers.push_back(sNumber);
            }
        }

        //теперь считываем значения времени и сенсоров
        while( std::getline(file, line) )
        {
            pos = 0;
            //читаем очередную строку из файла

            SkipSpace(loc, line, &pos);

            //читаем время (как целое число)
            while( line[pos] != '.' ){ temp += line.at(pos); pos++; } pos++;
            ReadValue(&temp, loc, &pos, line);
            int Time = atoi( temp.c_str() );
            temp.clear();

            SkipSpace(loc, line, &pos);

            NextData.Time = Time;

            for(int j = 0; j < mSensorsNumbers.size(); j++)
            {
                //номер сенсора
                int sNumber = mSensorsNumbers[j];
                double sValue = 0;

                ReadValue(&temp, loc, &pos, line);
                sValue = atof( temp.c_str() );
                temp.clear();
                SkipSpace(loc, line, &pos);
                NextData.SensorsData[sNumber] = sValue;
            }

            mDriveMatVector.push_back(NextData);
            countLines++;
        }
        qDebug() << "считано " << QString::number(countLines) << " строк" << endl;

        mCountRows = countLines;
        mDuration = mDriveMatVector[countLines-1].Time;
        mLineId = 0;

        file.close();

        return true;
    }
    else
    {
        file.close();
        return false;
    }

}

int MoveCorrector::getCorrectValue(int NumberChannel, int CTime)
{
    double CorrAngle = 0;//поправочное значение
    // если есть корректирующие значения для этого канала
    if(mAmends[NumberChannel].size() != 0)
    {
        for(int i=0; i < mAmends[NumberChannel].size(); i++)
        {
            double sScale = mAmends[NumberChannel][i].sScale;
            double mScale = mAmends[NumberChannel][i].mScale;
            int sZeroValue = mAmends[NumberChannel][i].sZeroValue;
            int sNumber = mAmends[NumberChannel][i].sNumber;

            int sValue = BufferController::Inst()->GetBufferR()->GetSensorValue(
                        aSensors->at(sNumber).GetChannel(), aSensors->at(sNumber).GetParam() ) ;

            qDebug() << "показания сенсора"  << QString::number(sValue) << endl;

            double Amend = 0;

            if(mAmends[NumberChannel][i].Type == 2)
            {
                while(mDriveMatVector[mLineId].Time < CTime){mLineId++;}
                double sZValue = mDriveMatVector[mLineId].SensorsData[sNumber];

                qDebug() << "Time: "  << QString::number(CTime) <<
                            " SValue: "<< QString::number(sZValue) << endl;

                Amend = (double)(((sValue - sZeroValue)/sScale) - sZValue)*mScale;
            }
            else
            {
                Amend = (double)((sValue - sZeroValue)/sScale)*mScale;
            }

            qDebug() << "Amend: "  << QString::number(Amend) << endl;
            CorrAngle += Amend;
        }
    }
    return CorrAngle;
}

void MoveCorrector::SkipSpace(std::locale loc, std::string str, unsigned int *i)
{
    while( std::isspace(str[(*i)], loc) )
        (*i)++;
}

void MoveCorrector::ReadValue(std::string *temp, std::locale loc, unsigned int *i, std::string str)
{
    while( !std::isspace(str[*i], loc) && *i < str.length() )
    {
        *temp += str.at(*i);
        (*i)++;
    }
}

