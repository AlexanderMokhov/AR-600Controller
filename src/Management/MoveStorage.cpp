#include "MoveStorage.h"

MoveStorage * MoveStorage::mInst = 0;

MoveStorage::MoveStorage()
{
    mMoveID = 0;
    mMotors = ConfigController::Inst()->GetMotors();
    LoadForwardMoves();
    LoadBackMoves();
}

void MoveStorage::SkipSpace(locale loc, string str, int *pos)
{
    while( std::isspace(str[(*pos)], loc) )
        (*pos)++;
}

void MoveStorage::ReadValue(string *temp, locale loc, int *pos, string str)
{
    while( !std::isspace(str[*pos], loc) && *pos < str.length() )
    {
        *temp += str.at(*pos);
        (*pos)++;
    }
}

bool MoveStorage::OpenFile(string fileName)
{
    if(LoadFile(fileName))
    {
        qDebug() << "считано " << QString::number(mCountRows) << " строк" << endl;
        qDebug() << "Время записи " << QString::number((double)mDuration/1e6) << " секунд" << endl;
        return true;
    }
    else
        return false;

    /*std::ifstream file(fileName.c_str());

    if( file.is_open() )
    {
        //очищаем список команд
        mMoves.clear();
        mCountRows = 0;

        std::string line;
        MoveCommand nextCommand;
        PID mPID;

        //по умолчанию заполняем значениями из файла настроек
        mPID.Stiff = ConfigController::Inst()->GetDefaultStiff();
        mPID.Dump = ConfigController::Inst()->GetDefaultDump();
        mPID.Torque = ConfigController::Inst()->GetDefaultTorque();

        mPID.StiffFactor = ConfigController::Inst()->GetDefaultStiffFactor();
        mPID.DumpFactor = ConfigController::Inst()->GetDefaultDumpFactor();
        mPID.TorqueFactor = ConfigController::Inst()->GetDefaultTorqueFactor();

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
            SkipSpace(loc, line, &pos);
            ReadValue(&temp, loc, &pos, line);

            //записываем номер привода
            int Number = atoi( temp.c_str() );
            temp.clear();

            //читаем время (как целое число)
            SkipSpace(loc, line, &pos);
            while( line[pos] != '.' ){ temp += line.at(pos); pos++; } pos++;
            ReadValue(&temp, loc, &pos, line);

            //записываем время
            int Time = atoi( temp.c_str() );
            temp.clear();

            //читаем угол
            SkipSpace(loc, line, &pos);
            ReadValue(&temp, loc, &pos, line);

            //записываем угол
            double Angle = atof( temp.c_str() );
            temp.clear();

            //Переводим угол в градусы*100
            Angle = (180.0 / M_PI) * Angle * 100.0;

            SkipSpace(loc, line, &pos);

            if(line[pos] != '\0') //проверяем есть ли коэффициэнты PID
            {
                //значит здесь записаны коэффициенты PID
                //читаем KP
                ReadValue(&temp, loc, &pos, line);
                double KP = atof( temp.c_str() );
                temp.clear();

                //читаем KI
                SkipSpace(loc, line, &pos);
                ReadValue(&temp, loc, &pos, line);
                double KI = atof( temp.c_str() );
                temp.clear();

                //читаем KD
                SkipSpace(loc, line, &pos);
                ReadValue(&temp, loc, &pos, line);
                double KD = atof( temp.c_str() );
                temp.clear();

                //заполняем PID
                mPID.Stiff = KP;
                mPID.Dump = KI;
                mPID.Torque = KD;

                SkipSpace(loc, line, &pos);

                if(line[pos] != '\0') //проверяем есть ли коэффициэнты проп. PID
                {
                    //значит здесь записаны коэффициенты проп. PID
                    //читаем KP
                    ReadValue(&temp, loc, &pos, line);
                    double KPFactor = atof( temp.c_str() );
                    temp.clear();

                    //читаем KI
                    SkipSpace(loc, line, &pos);
                    ReadValue(&temp, loc, &pos, line);
                    double KIFactor = atof( temp.c_str() );
                    temp.clear();

                    //читаем KD
                    SkipSpace(loc, line, &pos);
                    ReadValue(&temp, loc, &pos, line);
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
            mMoves.push_back(nextCommand);
            mCountRows++;
            mDuration = Time;//в микросекундах
        }

        mMoveID = 0;
        qDebug() << "считано " << QString::number(mCountRows) << " строк" << endl;
        qDebug() << "Время записи " << QString::number((double)mDuration/1e6) << " секунд" << endl;

        file.close();
        return true;
    }
    else
    {
        file.close();
        return false;
    }*/
}

bool MoveStorage::LoadForwardMoves()
{
    if(LoadFile(ConfigController::Inst()->GetFileForward()))
    {
        mForwardMoves = mMoves;
        mForwardDuration = mDuration;
        mForwardCountRows = mCountRows;
        mMoves.clear();
        mCountRows = 0;
        qDebug() << "Cчитан файл движения вперед" << endl;
        return true;
    }
    else
    {
        qDebug() << "Файл с движениями отстутствует" << endl;
        return false;
    }
}

bool MoveStorage::LoadBackMoves()
{
    if(LoadFile(ConfigController::Inst()->GetFileBack()))
    {
        mBackMoves = mMoves;
        mBackDuration = mDuration;
        mBackCountRows = mCountRows;
        mMoves.clear();
        mCountRows = 0;
        qDebug() << "Cчитан файл движения назад" << endl;
        return true;
    }
    else
    {
        qDebug() << "Файл с движениями отстутствует" << endl;
        return false;
    }
}

bool MoveStorage::LoadFile(std::string filename)
{
    std::ifstream file(filename.c_str());
    if( file.is_open() )
    {
        //очищаем список команд
        mMoves.clear();
        mCountRows = 0;

        std::string line;
        MoveCommand nextCommand;
        PID mPID;

        //по умолчанию заполняем значениями из файла настроек
        mPID.Stiff = ConfigController::Inst()->GetDefaultStiff();
        mPID.Dump = ConfigController::Inst()->GetDefaultDump();
        mPID.Torque = ConfigController::Inst()->GetDefaultTorque();

        mPID.StiffFactor = ConfigController::Inst()->GetDefaultStiffFactor();
        mPID.DumpFactor = ConfigController::Inst()->GetDefaultDumpFactor();
        mPID.TorqueFactor = ConfigController::Inst()->GetDefaultTorqueFactor();

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
            SkipSpace(loc, line, &pos);
            ReadValue(&temp, loc, &pos, line);

            //записываем номер привода
            int Number = atoi( temp.c_str() );
            temp.clear();

            //читаем время (как целое число)
            SkipSpace(loc, line, &pos);
            while( line[pos] != '.' ){ temp += line.at(pos); pos++; } pos++;
            ReadValue(&temp, loc, &pos, line);

            //записываем время
            int Time = atoi( temp.c_str() );
            temp.clear();

            //читаем угол
            SkipSpace(loc, line, &pos);
            ReadValue(&temp, loc, &pos, line);

            //записываем угол
            double Angle = atof( temp.c_str() );
            temp.clear();

            //Переводим угол в градусы*100
            Angle = (180.0 / M_PI) * Angle * 100.0;

            SkipSpace(loc, line, &pos);

            if(line[pos] != '\0') //проверяем есть ли коэффициэнты PID
            {
                //значит здесь записаны коэффициенты PID
                //читаем KP
                ReadValue(&temp, loc, &pos, line);
                double KP = atof( temp.c_str() );
                temp.clear();

                //читаем KI
                SkipSpace(loc, line, &pos);
                ReadValue(&temp, loc, &pos, line);
                double KI = atof( temp.c_str() );
                temp.clear();

                //читаем KD
                SkipSpace(loc, line, &pos);
                ReadValue(&temp, loc, &pos, line);
                double KD = atof( temp.c_str() );
                temp.clear();

                //заполняем PID
                mPID.Stiff = KP;
                mPID.Dump = KI;
                mPID.Torque = KD;

                SkipSpace(loc, line, &pos);

                if(line[pos] != '\0') //проверяем есть ли коэффициэнты проп. PID
                {
                    //значит здесь записаны коэффициенты проп. PID
                    //читаем KP
                    ReadValue(&temp, loc, &pos, line);
                    double KPFactor = atof( temp.c_str() );
                    temp.clear();

                    //читаем KI
                    SkipSpace(loc, line, &pos);
                    ReadValue(&temp, loc, &pos, line);
                    double KIFactor = atof( temp.c_str() );
                    temp.clear();

                    //читаем KD
                    SkipSpace(loc, line, &pos);
                    ReadValue(&temp, loc, &pos, line);
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
            mMoves.push_back(nextCommand);
            mCountRows++;
            mDuration = Time;//в микросекундах
        }

        mMoveID = 0;
        //qDebug() << "считано " << QString::number(mCountRows) << " строк" << endl;
        //qDebug() << "Время записи " << QString::number((double)mDuration/1e6) << " секунд" << endl;

        file.close();
        return true;
    }
    else
    {
        file.close();
        return false;
    }
}

void MoveStorage::setForwardMoves()
{
    mMoves = mForwardMoves;
    mDuration = mForwardDuration;
    mCountRows = mForwardCountRows;
}

void MoveStorage::setBackMoves()
{
    mMoves = mBackMoves;
    mDuration = mBackDuration;
    mCountRows = mBackCountRows;
}


