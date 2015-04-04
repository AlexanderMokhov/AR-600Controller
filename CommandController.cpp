#include "CommandController.h"
#include <qdebug.h>

CommandController * CommandController::mInstance = 0;

CommandController::CommandController()
{

}

CommandController::~CommandController()
{

}

CommandController *CommandController::Instance()
{
    return mInstance;
}

void CommandController::Initialize()
{
    delete mInstance;
    mInstance = new CommandController;
}

void CommandController::Shutdown()
{
    delete mInstance;
    mInstance = 0;
}

void CommandController::Update(unsigned int mTime)
{
    if(mCommandsList.at(Id).GetTime()==mTime)//совпало время
    {
        //читаем все команды с таким временем
        while(mCommandsList.at(Id).GetTime()==mTime)
        {
            //записываем значение в мотор и проверяем следующую команду
            BufferController::Instance()->GetWriteBuffer()->Set_MOTOR_ANGLE(mCommandsList.at(Id).GetNumber(),mCommandsList.at(Id).GetPosition());
            Id++;
        }
    }
}

bool CommandController::LoadFromFile(std::string fileName)
{
    std::ifstream file(fileName.c_str());

    if(file.is_open())
    {
        //очищаем список команд
        mCommandsList.clear();
        std::string str;

        int currentTime=0;
        DriverCommand nextCommand;
        mCountRows=0;

        PID mPID;

        //по умолчанию заполняем значениями из файла настроек
        mPID.Stiff=AR600ControllerConf::Instance()->GetDefaultStiff();
        mPID.Dump=AR600ControllerConf::Instance()->GetDefaultDump();
        mPID.Torque=AR600ControllerConf::Instance()->GetDefaultTorque();

        while(std::getline(file, str))
        {
            std::locale loc;
            //читаем очередную строку из файла

            //читаем номер привода
            unsigned int i=0;
            while(std::isspace(str[i],loc))
                i++;
            std::string temp;
            while(!std::isspace(str[i],loc))
            {
                temp+=str.at(i);
                i++;
            }
            //прочитали номер привода

            //записываем номер привода
            int Number = atoi(temp.c_str());
            temp.clear();

            //читаем время(как целое число)
            while(std::isspace(str[i],loc))
                i++;
            while(str[i]!='.')
            {
                temp+=str.at(i);
                i++;
            }
            i++;
            while(!std::isspace(str[i],loc))
            {
                temp+=str.at(i);
                i++;
            }
            //прочитали время

            //записываем время
            int Time = atoi(temp.c_str());
            temp.clear();

            //читаем позицию
            while(std::isspace(str[i],loc))
                i++;
            while(!std::isspace(str[i],loc) && i<str.length())
            {
                temp+=str.at(i);
                i++;
            }
            //прочитали позицию

            //записываем позицию
            double Position = atof(temp.c_str());
            temp.clear();

            //Переводим позицию в градусы*100
            Position=(180.0/M_PI*Position)*100;

            //проверяем есть ли коэффициэнты PID
            while(std::isspace(str[i],loc))
                i++;

            if(str[i]!=NULL)
            {
                //значит здесь записаны коэффициенты PID
                //читаем KP
                while(!std::isspace(str[i],loc) && i<str.length())
                {
                    temp+=str.at(i);
                    i++;
                }
                //прочитали KP
                double KP = atof(temp.c_str());
                temp.clear();

                //читаем KI
                while(std::isspace(str[i],loc))
                    i++;
                while(!std::isspace(str[i],loc) && i<str.length())
                {
                    temp+=str.at(i);
                    i++;
                }
                //прочитали KI
                double KI = atof(temp.c_str());
                temp.clear();

                //читаем KD
                while(std::isspace(str[i],loc))
                    i++;
                while(!std::isspace(str[i],loc) && i<str.length())
                {
                    temp+=str.at(i);
                    i++;
                }
                //прочитали KD
                double KD = atof(temp.c_str());
                temp.clear();

                //заполняем PID
                mPID.Stiff = KP;
                mPID.Dump = KI;
                mPID.Torque = KD;
            }

            //заполняем команду
            nextCommand.SetTime(Time);
            nextCommand.SetNumber(Number);
            nextCommand.SetPosition((int)Position);
            nextCommand.SetPID(mPID);

            //добавляем команду в список
            mCommandsList.push_back(nextCommand);
            mCountRows++;
            currentTime=Time;
        }
        mTimeRecord = currentTime;//в микросекундах
        qDebug() << "считано " << QString::number(mCountRows) << " строк" << endl;
        qDebug() << "Время записи " << QString::number((double)mTimeRecord/1e6) << " секунд" << endl;

        file.close();
        return true;
    }
    else
    {
        file.close();
        return false;
    }

}

int CommandController::GetCountRows()
{
    return mCountRows;
}

int CommandController::GetTimeRecord()
{
    return mTimeRecord;
}

