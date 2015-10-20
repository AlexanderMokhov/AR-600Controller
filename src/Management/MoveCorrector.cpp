#include "MoveCorrector.h"

MoveCorrector * MoveCorrector::mInst = 0;

MoveCorrector::MoveCorrector()
{
    mSensors = ConfigController::Inst()->GetSensors();

    mMapAmends.clear();
    mMotors = ConfigController::Inst()->GetMotors();

    for(auto it = mMotors->begin(); it != mMotors->end(); ++it)
    {
        vector<Amend> item;
        //Добавляем в контейнер
        mMapAmends[(*it).second.GetNumber()] = item;
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
        for(auto it = mMapAmends.begin(); it != mMapAmends.end(); ++it)
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
            NextAmend.Ak = Ak;
            NextAmend.An = An;
            NextAmend.Kn = Kn;
            NextAmend.N = N;

            //добавляем команду в список
            mMapAmends[NumberChannel].push_back(NextAmend);
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
    if(mMapAmends[NumberChannel].size() != 0)
    {


        for(int i=0; i < mMapAmends[NumberChannel].size(); i++)
        {
            double Ak = mMapAmends[NumberChannel][i].Ak;
            double An = mMapAmends[NumberChannel][i].An;
            int Kn = mMapAmends[NumberChannel][i].Kn;
            int SNumber = mMapAmends[NumberChannel][i].N;

            int K = BufferController::Inst()->GetBufferR()->GetSensorValue(
                        mSensors->at(SNumber).GetChannel(), mSensors->at(SNumber).GetParam() ) ;

            qDebug() << "показания сенсора"  << QString::number(K) << endl;


            double Xk = (double)((K - Kn)/An)*Ak;
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

