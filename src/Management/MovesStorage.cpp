#include "MovesStorage.h"

//MovesStorage * MovesStorage::m_inst = 0;

MovesStorage::MovesStorage(): ICoreClass()
{
    m_moveID = 0;
    //loadForwardMoves();
    //loadBackMoves();
}

void MovesStorage::skipSpace(locale loc, string str, int *pos)
{
    while( std::isspace(str[(*pos)], loc) )
        (*pos)++;
}

void MovesStorage::readValue(string *temp, locale loc, int *pos, string str)
{
    while( !std::isspace(str[*pos], loc) && *pos < str.length() )
    {
        *temp += str.at(*pos);
        (*pos)++;
    }
}

bool MovesStorage::openFile(string fileName)
{
    if(loadFile(fileName))
    {
        //qDebug() << "считано " << QString::number(mCountRows) << " строк" << endl;
        //qDebug() << "Время записи " << QString::number((double)mDuration/1e6) << " секунд" << endl;
        return true;
    }
    else
        return false;
}

bool MovesStorage::loadForwardMoves()
{
    if(loadFile(static_cast<SettingsStorage*>(m_Registry->getClass(0))->GetFileForward()))
    {
        m_forwardMoves = m_moves;
        m_forwardDuration = m_duration;
        m_forwardRowsNumber = m_rowsNumber;
        m_moves.clear();
        m_rowsNumber = 0;
        qDebug() << "Cчитан файл движения вперед" << endl;
        return true;
    }
    else
    {
        qDebug() << "Файл с движениями отстутствует" << endl;
        return false;
    }
}

bool MovesStorage::loadBackMoves()
{
    if(loadFile(static_cast<SettingsStorage*>(m_Registry->getClass(0))->GetFileBack()))
    {
        m_backMoves = m_moves;
        m_backDuration = m_duration;
        m_backRowsNumber = m_rowsNumber;
        m_moves.clear();
        m_rowsNumber = 0;
        qDebug() << "Cчитан файл движения назад" << endl;
        return true;
    }
    else
    {
        qDebug() << "Файл с движениями отстутствует" << endl;
        return false;
    }
}

bool MovesStorage::loadFile(std::string filename)
{
    std::ifstream file(filename.c_str());

    if( file.is_open() )
    {
        //очищаем список команд
        m_moves.clear();
        m_rowsNumber = 0;

        std::string line;
        MoveCommand nextCommand;
        PID mPID;

        //по умолчанию заполняем значениями из файла настроек
        mPID.Stiff = (static_cast<SettingsStorage*>(m_Registry->getClass(0))->GetDefaultStiff());
        mPID.Dump = (static_cast<SettingsStorage*>(m_Registry->getClass(0))->GetDefaultDump());
        mPID.Torque = (static_cast<SettingsStorage*>(m_Registry->getClass(0))->GetDefaultTorque());

        mPID.StiffFactor = (static_cast<SettingsStorage*>(m_Registry->getClass(0))->GetDefaultStiffFactor());
        mPID.DumpFactor = (static_cast<SettingsStorage*>(m_Registry->getClass(0))->GetDefaultDumpFactor());
        mPID.TorqueFactor = (static_cast<SettingsStorage*>(m_Registry->getClass(0))->GetDefaultTorqueFactor());

        while( std::getline(file, line) )
        {
            if(line.length() < 5)
            {
                countErrors++;
                continue;
            }

            const char * str = line.c_str();
            char * ptr = 0;
            char* ptrOld = 0;
            errno = 0;

            int Number = strtol(str, &ptr, 10);
            if (!(errno != ERANGE && ptr > str)) return false;

            long Time = strtol(ptr, &ptr, 10);
            if (!(errno != ERANGE && ptr > str)) return false;

            ptr++;
            long TimeMs = strtol(ptr, &ptr, 10);
            if (!(errno != ERANGE && ptr > str)) return false;

            Time *= 1e6;
            Time += TimeMs;

            double Angle = strtod(ptr, &ptr);
            if (!(errno != ERANGE && ptr > str)) return false;

            while(isspace(*(++ptr)));
            if(*ptr != '\0')
            {
                ptrOld = ptr;
                double PGate = strtod(ptr, &ptr);
                if (!(errno != ERANGE && ptr > str)) return false;
                if(*ptrOld == *ptr)
                {
                }

                ptrOld = ptr;
                double IGate = strtod(ptr, &ptr);
                if (!(errno != ERANGE && ptr > str)) return false;
                if(*ptrOld == *ptr)
                {
                }

                ptrOld = ptr;
                double DGate = strtod(ptr, &ptr);
                if (!(errno != ERANGE && ptr > str)) return false;
                if(*ptrOld == *ptr)
                {
                }

                //заполняем PID
                mPID.Stiff = PGate;
                mPID.Dump = IGate;
                mPID.Torque = DGate;

                while(isspace(*(ptr)) && *ptr != '\0'){ptr++;}
                if(*ptr != '\0')
                {
                    ptrOld = ptr;
                    double PGateFactor = strtod(ptr, &ptr);
                    if (!(errno != ERANGE && ptr > str)) return false;
                    if(*ptrOld == *ptr)
                    {
                    }

                    ptrOld = ptr;
                    double IGateFactor = strtod(ptr, &ptr);
                    if (!(errno != ERANGE && ptr > str)) return false;
                    if(*ptrOld == *ptr)
                    {
                    }

                    ptrOld = ptr;
                    double DGateFactor = strtod(ptr, &ptr);
                    if (!(errno != ERANGE && ptr > str)) return false;
                    if(*ptrOld == *ptr)
                    {
                    }

                    //заполняем коэффициенты проп. PID
                    mPID.StiffFactor = PGateFactor;
                    mPID.DumpFactor = IGateFactor;
                    mPID.TorqueFactor = DGateFactor;

                    mPID.Stiff *= mPID.StiffFactor;
                    mPID.Dump *= mPID.DumpFactor;
                    mPID.Torque *= mPID.TorqueFactor;

                }
            }






{
            //читаем очередную строку из файла
//            std::locale loc;
//            std::string temp;
//            int pos = 0;

//            //читаем номер привода
//            skipSpace(loc, line, &pos);
//            readValue(&temp, loc, &pos, line);

//            //записываем номер привода
//            int Number = atoi( temp.c_str() );
//            temp.clear();

//            //читаем время (как целое число)
//            skipSpace(loc, line, &pos);
//            while( line[pos] != '.' ){ temp += line.at(pos); pos++; } pos++;
//            readValue(&temp, loc, &pos, line);

//            //записываем время
//            int Time = atoi( temp.c_str() );
//            temp.clear();

//            //читаем угол
//            skipSpace(loc, line, &pos);
//            readValue(&temp, loc, &pos, line);

//            //записываем угол
//            double Angle = atof( temp.c_str() );
//            temp.clear();

//            //Переводим угол в градусы*100
//            Angle = (180.0 / M_PI) * Angle * 100.0;

//            skipSpace(loc, line, &pos);
}
//            if(line[pos] != '\0') //проверяем есть ли коэффициэнты PID
//            {
//                //значит здесь записаны коэффициенты PID
//                //читаем KP
//                readValue(&temp, loc, &pos, line);
//                double KP = atof( temp.c_str() );
//                temp.clear();

//                //читаем KI
//                skipSpace(loc, line, &pos);
//                readValue(&temp, loc, &pos, line);
//                double KI = atof( temp.c_str() );
//                temp.clear();

//                //читаем KD
//                skipSpace(loc, line, &pos);
//                readValue(&temp, loc, &pos, line);
//                double KD = atof( temp.c_str() );
//                temp.clear();

//                //заполняем PID
//                mPID.Stiff = KP;
//                mPID.Dump = KI;
//                mPID.Torque = KD;

//                skipSpace(loc, line, &pos);

//                if(line[pos] != '\0') //проверяем есть ли коэффициэнты проп. PID
//                {
//                    //значит здесь записаны коэффициенты проп. PID
//                    //читаем KP
//                    readValue(&temp, loc, &pos, line);
//                    double KPFactor = atof( temp.c_str() );
//                    temp.clear();

//                    //читаем KI
//                    skipSpace(loc, line, &pos);
//                    readValue(&temp, loc, &pos, line);
//                    double KIFactor = atof( temp.c_str() );
//                    temp.clear();

//                    //читаем KD
//                    skipSpace(loc, line, &pos);
//                    readValue(&temp, loc, &pos, line);
//                    double KDFactor = atof( temp.c_str() );
//                    temp.clear();

//                    //заполняем коэффициенты проп. PID
//                    mPID.StiffFactor = KPFactor;
//                    mPID.DumpFactor = KIFactor;
//                    mPID.TorqueFactor = KDFactor;

//                    mPID.Stiff *= mPID.StiffFactor;
//                    mPID.Dump *= mPID.DumpFactor;
//                    mPID.Torque *= mPID.TorqueFactor;
//                }
//            }

            //заполняем команду
            nextCommand.Time = (int)Time;
            nextCommand.NumberChannel = Number;
            nextCommand.Angle = (int)Angle;
            nextCommand.PIDs = mPID;

            //добавляем команду в список
            m_moves.push_back(nextCommand);

            m_locker.lock();
            m_rowsNumber++;
            m_locker.unlock();

            m_duration = Time;//в микросекундах
        }

        m_moveID = 0;
        qDebug() << "считано " << QString::number(m_rowsNumber) << " строк" << endl;
        qDebug() << "Время записи " << QString::number((double)m_duration/1e6) << " секунд" << endl;

        file.close();
        return true;
    }
    else
    {
        file.close();
        return false;
    }
}

void MovesStorage::setForwardMoves()
{
    m_moves = m_forwardMoves;
    m_duration = m_forwardDuration;
    m_rowsNumber = m_forwardRowsNumber;
}

void MovesStorage::setBackMoves()
{
    m_moves = m_backMoves;
    m_duration = m_backDuration;
    m_rowsNumber = m_backRowsNumber;
}

void MovesStorage::resetErrors()
{
    countErrors = 0;
}

int MovesStorage::getCountErrors()
{
    return countErrors;
}

void MovesStorage::loadDataFromArray(char *array, uint size)
{
    //qDebug() << "Load from array begin" << endl;

    //FILE *f = fopen("DRIVEMAG1.txt","at");

    //очищаем список команд
    m_moves.clear();
    m_rowsNumber = 0;

    MoveCommand nextCommand;
    PID mPID;

    //по умолчанию заполняем значениями из файла настроек
    mPID.Stiff = static_cast<SettingsStorage*>(m_Registry->getClass(0))->GetDefaultStiff();
    mPID.Dump = static_cast<SettingsStorage*>(m_Registry->getClass(0))->GetDefaultDump();
    mPID.Torque = static_cast<SettingsStorage*>(m_Registry->getClass(0))->GetDefaultTorque();

    mPID.StiffFactor = static_cast<SettingsStorage*>(m_Registry->getClass(0))->GetDefaultStiffFactor();
    mPID.DumpFactor = static_cast<SettingsStorage*>(m_Registry->getClass(0))->GetDefaultDumpFactor();
    mPID.TorqueFactor = static_cast<SettingsStorage*>(m_Registry->getClass(0))->GetDefaultTorqueFactor();

    for(int i = 0; i < 21*72; i += 72)
    {
        double Number;
        memcpy(&Number, array + i, sizeof(double));
        double Time;
        memcpy(&Time, array + i + 8, sizeof(double));
        double Angle;
        memcpy(&Angle, array + i + 16, sizeof(double));
        double PGate;
        memcpy(&PGate, array + i + 24, sizeof(double));
        double IGate;
        memcpy(&IGate, array + i + 32, sizeof(double));
        double DGate;
        memcpy(&DGate, array + i + 40, sizeof(double));
        double PGateProp;
        memcpy(&PGateProp, array + i + 48, sizeof(double));
        double IGateProp;
        memcpy(&IGateProp, array + i + 56, sizeof(double));
        double DGateProp;
        memcpy(&DGateProp, array + i + 64, sizeof(double));

        mPID.Stiff = PGate;
        mPID.Dump = IGate;
        mPID.Torque = DGate;

        mPID.StiffFactor = PGateProp;
        mPID.DumpFactor = IGateProp;
        mPID.TorqueFactor = DGateProp;

        mPID.Stiff *= mPID.StiffFactor;
        mPID.Dump *= mPID.DumpFactor;
        mPID.Torque *= mPID.TorqueFactor;

        //Переводим угол в градусы*100
        Angle = (180.0 / M_PI) * Angle * 100.0;

        //заполняем команду
        nextCommand.Time = (int)(Time*10e6);
        nextCommand.NumberChannel = Number;
        nextCommand.Angle = (int)Angle;
        nextCommand.PIDs = mPID;

        //добавляем команду в список
        m_moves.push_back(nextCommand);

        m_rowsNumber++;

        m_duration = Time;//в микросекундах

        //fprintf(f,"%4d", nextCommand.NumberChannel);
        //fprintf(f," %12.6f ", (double)(nextCommand.Time)/10e6);
        //fprintf(f," %12.6f ", (double)nextCommand.Angle);
        //fprintf(f," %12.6f ", (double)nextCommand.PIDs.Stiff);
        //fprintf(f," %12.6f ", (double)nextCommand.PIDs.Dump);
        //fprintf(f," %12.6f ", (double)nextCommand.PIDs.Torque);
        //fprintf(f," %12.6f ", (double)nextCommand.PIDs.StiffFactor);
        //fprintf(f," %12.6f ", (double)nextCommand.PIDs.DumpFactor);
        //fprintf(f," %12.6f ", (double)nextCommand.PIDs.TorqueFactor);
        //fprintf(f, "\n");


        //qDebug() << "LDFA channel " << Number << "was read" << endl;
    }
    //fclose(f);
    m_moveID = 0;
   // qDebug() << "LDFA считано " << QString::number(m_rowsNumber) << " строк" << endl;
    //qDebug() << "LDFA Время записи " << QString::number((double)m_duration/1e6) << " секунд" << endl;

    return;
}

int MovesStorage::getCurrentRow()
{
    m_locker.lock();
    return m_rowsNumber;
    m_locker.unlock();
}
