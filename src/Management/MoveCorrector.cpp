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

            double Ak, An, Kn;
            int N, NumberChannel = 0;

            //читаем номер датчика
            SkipSpace(loc, line, &i);
            ReadValue(&temp, loc, &i, line);
            N = atoi( temp.c_str() );
            temp.clear();

            //читаем номер привода
            SkipSpace(loc, line, &i);
            ReadValue(&temp, loc, &i, line);
            NumberChannel = atoi( temp.c_str() );
            temp.clear();

            //читаем Ak - масшт. к-т привода
            SkipSpace(loc, line, &i);
            ReadValue(&temp, loc, &i, line);
            Ak = atof( temp.c_str() );
            temp.clear();

            //читаем An - масшт. к-т датчика
            SkipSpace(loc, line, &i);
            ReadValue(&temp, loc, &i, line);
            An = atof( temp.c_str() );
            temp.clear();

            //читаем Kn - нулевое значение датчика
            SkipSpace(loc, line, &i);
            ReadValue(&temp, loc, &i, line);
            Kn = atof( temp.c_str() );
            temp.clear();

            //заполняем команду
            NextAmend.mScale = Ak;
            NextAmend.sScale = An;
            NextAmend.sZeroValue = Kn;
            NextAmend.sNumber = N;

            //добавляем команду в список
            mAmends[NumberChannel].push_back(NextAmend);
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

int MoveCorrector::getCorrectValue(int NumberChannel)
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


            double Xk = (double)((sValue - sZeroValue)/sScale)*mScale;
            qDebug() << "Xk"  << QString::number(Xk) << endl;
            CorrAngle += Xk;
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

