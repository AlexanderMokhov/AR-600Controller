#include "MovesStorage.h"

MovesStorage * MovesStorage::m_inst = 0;

MovesStorage::MovesStorage()
{
    m_moveID = 0;
    m_motors = SettingsStorage::Inst()->GetMotors();
    loadForwardMoves();
    loadBackMoves();
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
    if(loadFile(SettingsStorage::Inst()->GetFileForward()))
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
    if(loadFile(SettingsStorage::Inst()->GetFileBack()))
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
        mPID.Stiff = SettingsStorage::Inst()->GetDefaultStiff();
        mPID.Dump = SettingsStorage::Inst()->GetDefaultDump();
        mPID.Torque = SettingsStorage::Inst()->GetDefaultTorque();

        mPID.StiffFactor = SettingsStorage::Inst()->GetDefaultStiffFactor();
        mPID.DumpFactor = SettingsStorage::Inst()->GetDefaultDumpFactor();
        mPID.TorqueFactor = SettingsStorage::Inst()->GetDefaultTorqueFactor();

        while( std::getline(file, line) )
        {
            const char * s = line.c_str();
            char * ptr = 0;
            errno = 0;
            int Number_ = strtol(s, &ptr, 10);
            if (!(errno != ERANGE && ptr > s))
                break;

            double Time_ = strtod(ptr, &ptr);
            if (!(errno != ERANGE && ptr > s))
                break;

            //читаем очередную строку из файла
            std::locale loc;
            std::string temp;
            int pos = 0;

            //читаем номер привода
            skipSpace(loc, line, &pos);
            readValue(&temp, loc, &pos, line);

            //записываем номер привода
            int Number = atoi( temp.c_str() );
            temp.clear();

            //читаем время (как целое число)
            skipSpace(loc, line, &pos);
            while( line[pos] != '.' ){ temp += line.at(pos); pos++; } pos++;
            readValue(&temp, loc, &pos, line);

            //записываем время
            int Time = atoi( temp.c_str() );
            temp.clear();

            //читаем угол
            skipSpace(loc, line, &pos);
            readValue(&temp, loc, &pos, line);

            //записываем угол
            double Angle = atof( temp.c_str() );
            temp.clear();

            //Переводим угол в градусы*100
            Angle = (180.0 / M_PI) * Angle * 100.0;

            skipSpace(loc, line, &pos);

            if(line[pos] != '\0') //проверяем есть ли коэффициэнты PID
            {
                //значит здесь записаны коэффициенты PID
                //читаем KP
                readValue(&temp, loc, &pos, line);
                double KP = atof( temp.c_str() );
                temp.clear();

                //читаем KI
                skipSpace(loc, line, &pos);
                readValue(&temp, loc, &pos, line);
                double KI = atof( temp.c_str() );
                temp.clear();

                //читаем KD
                skipSpace(loc, line, &pos);
                readValue(&temp, loc, &pos, line);
                double KD = atof( temp.c_str() );
                temp.clear();

                //заполняем PID
                mPID.Stiff = KP;
                mPID.Dump = KI;
                mPID.Torque = KD;

                skipSpace(loc, line, &pos);

                if(line[pos] != '\0') //проверяем есть ли коэффициэнты проп. PID
                {
                    //значит здесь записаны коэффициенты проп. PID
                    //читаем KP
                    readValue(&temp, loc, &pos, line);
                    double KPFactor = atof( temp.c_str() );
                    temp.clear();

                    //читаем KI
                    skipSpace(loc, line, &pos);
                    readValue(&temp, loc, &pos, line);
                    double KIFactor = atof( temp.c_str() );
                    temp.clear();

                    //читаем KD
                    skipSpace(loc, line, &pos);
                    readValue(&temp, loc, &pos, line);
                    double KDFactor = atof( temp.c_str() );
                    temp.clear();

                    //заполняем коэффициенты проп. PID
                    mPID.StiffFactor = KPFactor;
                    mPID.DumpFactor = KIFactor;
                    mPID.TorqueFactor = KDFactor;

                    mPID.Stiff *= mPID.StiffFactor;
                    mPID.Dump *= mPID.DumpFactor;
                    mPID.Torque *= mPID.TorqueFactor;
                }
            }

            //заполняем команду
            nextCommand.Time = (int)Time;
            nextCommand.NumberChannel = Number;
            nextCommand.Angle = (int)Angle;
            nextCommand.PIDs = mPID;

            //добавляем команду в список
            m_moves.push_back(nextCommand);
            m_rowsNumber++;
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


