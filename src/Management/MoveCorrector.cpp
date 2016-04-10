#include "MoveCorrector.h"

MoveCorrector * MoveCorrector::m_inst = 0;

MoveCorrector::MoveCorrector()
{
    m_sensors = ARCore::Inst()->getSettingStore()->GetSensors();

    m_amends.clear();
    m_motors = ARCore::Inst()->getSettingStore()->GetMotors();

    for(auto it = m_motors->begin(); it != m_motors->end(); ++it)
    {
        vector<Amend> item;
        //Добавляем в контейнер
        m_amends[(*it).second.getNumber()] = item;
    }

    //очищаем вектор
    m_driveMatVector.clear();
    m_sensorsNumbers.clear();

    m_lineId = 0;
    m_RowsNumber = 0;
    m_duration = 0;
}

void MoveCorrector::initialize()
{
    delete m_inst; m_inst = new MoveCorrector;
}

bool MoveCorrector::openFile(string fileName)
{
    std::ifstream file(fileName.c_str());

    if( file.is_open() )
    {
        //очищаем поправки
        for(auto it = m_amends.begin(); it != m_amends.end(); ++it)
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
            skipSpace(loc, line, &i);
            readValue(&temp, loc, &i, line);

            //Проверка на комментарий
            if( temp.find("//") == 0 )
                continue;

            Type = atoi( temp.c_str() );
            temp.clear();

            //читаем номер датчика
            skipSpace(loc, line, &i);
            readValue(&temp, loc, &i, line);
            sNumber = atoi( temp.c_str() );
            temp.clear();

            //читаем номер привода
            skipSpace(loc, line, &i);
            readValue(&temp, loc, &i, line);
            mNumber = atoi( temp.c_str() );
            temp.clear();

            if(Type == 2)
            {
                //читаем номер датчика в файле DRIVEMAT
                skipSpace(loc, line, &i);
                readValue(&temp, loc, &i, line);
                spNumber = atoi( temp.c_str() );
                temp.clear();

                NextAmend.spNumber = spNumber;
            }

            //читаем Ak - масшт. к-т привода
            skipSpace(loc, line, &i);
            readValue(&temp, loc, &i, line);
            mScale = atof( temp.c_str() );
            temp.clear();

            //читаем An - масшт. к-т датчика
            skipSpace(loc, line, &i);
            readValue(&temp, loc, &i, line);
            sScale = atof( temp.c_str() );
            temp.clear();

            //читаем Kn - нулевое значение датчика
            skipSpace(loc, line, &i);
            readValue(&temp, loc, &i, line);
            sZeroValue = atof( temp.c_str() );
            temp.clear();

            //заполняем команду
            NextAmend.Type = Type;
            NextAmend.mScale = mScale;
            NextAmend.sScale = sScale;
            NextAmend.sZeroValue = sZeroValue;
            NextAmend.sNumber = sNumber;

            qDebug() << "Type "  << QString::number(Type) << endl;

            //добавляем команду в список
            m_amends[mNumber].push_back(NextAmend);
            countLines++;
        }

        qDebug() << "Считано " << QString::number(countLines) << " строк" << endl;

        file.close();
        return true;
    }
    else
    {
        file.close();
        return false;
    }
}

bool MoveCorrector::openDriveMatFile(string fileName)
{
    std::ifstream file(fileName.c_str());

    if( file.is_open() )
    {
        std::locale loc;
        std::string temp;
        unsigned int pos = 0;

        //очищаем вектор
        m_driveMatVector.clear();
        m_sensorsNumbers.clear();
        m_RowsNumber = 0;
        m_duration = 0;

        std::string line;

        DriveMatData NextData;
        int countLines = 0;

        std::getline(file, line);
        {
            //считываем номера сенсоров
            //пропускаем TIME
            skipSpace(loc, line, &pos);
            readValue(&temp, loc, &pos, line);
            temp.clear();
            skipSpace(loc, line, &pos);

            int number = 1;
            while(line[pos] != '\0')
            {
                //читаем номер сенсора
                int sNumber = 0;

                readValue(&temp, loc, &pos, line);
                sNumber = atoi( temp.c_str() );
                temp.clear();
                skipSpace(loc, line, &pos);

                //mSensorsNumbers.push_back(sNumber);
                m_sensorsNumbers.push_back(number);
                number++;
            }
        }

        //теперь считываем значения времени и сенсоров
        while( std::getline(file, line) )
        {
            pos = 0;
            //читаем очередную строку из файла

            skipSpace(loc, line, &pos);

            //читаем время (как целое число)
            while( line[pos] != '.' ){ temp += line.at(pos); pos++; } pos++;
            readValue(&temp, loc, &pos, line);
            int Time = atoi( temp.c_str() );
            temp.clear();

            skipSpace(loc, line, &pos);

            NextData.Time = Time;

            for(int j = 0; j < m_sensorsNumbers.size(); j++)
            {
                //номер сенсора
                int sNumber = m_sensorsNumbers[j];
                double sValue = 0;

                readValue(&temp, loc, &pos, line);
                sValue = atof( temp.c_str() );
                temp.clear();
                skipSpace(loc, line, &pos);
                NextData.SensorsData[sNumber] = sValue;
            }

            m_driveMatVector.push_back(NextData);
            countLines++;
        }
        qDebug() << "считано " << QString::number(countLines) << " строк" << endl;

        m_RowsNumber = countLines;
        m_duration = m_driveMatVector[countLines-1].Time;
        m_lineId = 0;

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

    for(int i=0; i < m_amends[NumberChannel].size(); i++)
    {
        double sScale = m_amends[NumberChannel][i].sScale;
        double mScale = m_amends[NumberChannel][i].mScale;
        int sZeroValue = m_amends[NumberChannel][i].sZeroValue;
        int sNumber = m_amends[NumberChannel][i].sNumber;

        int sValue = BufferController::Inst()->getBufferRecv()->getSensorValue(
                    m_sensors->at(sNumber).getChannel(), m_sensors->at(sNumber).getParam() ) ;

        int spNumber = m_amends[NumberChannel][i].spNumber;
        qDebug() << "показания сенсора"  << QString::number(sValue) << endl;

        double Amend = 0;

        if(m_amends[NumberChannel][i].Type == 2)
        {
            while(m_driveMatVector[m_lineId].Time < CTime){ m_lineId++; }

            double sZValue = m_driveMatVector[m_lineId].SensorsData[spNumber];

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

    return CorrAngle;
}

void MoveCorrector::skipSpace(std::locale loc, std::string str, unsigned int *i)
{
    while( std::isspace(str[(*i)], loc) )
        (*i)++;
}

void MoveCorrector::readValue(std::string *temp, std::locale loc, unsigned int *i, std::string str)
{
    while( !std::isspace(str[*i], loc) && *i < str.length() )
    {
        *temp += str.at(*i);
        (*i)++;
    }
}

