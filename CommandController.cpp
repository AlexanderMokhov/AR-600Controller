#include "CommandController.h"
#include <qdebug.h>

CommandController * CommandController::mInstance = 0;

CommandController::CommandController()
{
    mCommandId=0;
    IsPlayForwardState=false;
    IsGoToPosState=false;
    mSendDelay = ConfigController::Instance()->GetSendDelay();
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

//на вход поступает время в микросекундах (10e-6 c)
void CommandController::Update(long mTime)
{
    while(mCommandsList.at(mCommandId).GetTime() <= mTime)
    {
        //записываем значение в мотор и проверяем следующую команду
        int Number = mCommandsList.at(mCommandId).GetNumber();
        int NumberBuffer = ConfigController::Instance()->GetConfigMap()->at(Number).GetNumberBuffer();
        int Position = mCommandsList.at(mCommandId).GetPosition();
        BufferController::Instance()->GetWriteBuffer()->Set_MOTOR_ANGLE(NumberBuffer,Position);
        mCommandId++;
        qDebug() << "Выполнена строка " << QString::number(mCommandId) << endl;
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
        mPID.Stiff=ConfigController::Instance()->GetDefaultStiff();
        mPID.Dump=ConfigController::Instance()->GetDefaultDump();
        mPID.Torque=ConfigController::Instance()->GetDefaultTorque();

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
            Position=(180.0/M_PI)*Position*100.0;

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
            nextCommand.SetTime((int)Time);
            nextCommand.SetNumber(Number);
            nextCommand.SetPosition((int)Position);
            nextCommand.SetPID(mPID);

            //добавляем команду в список
            mCommandsList.push_back(nextCommand);
            mCountRows++;
            currentTime=Time;
        }
        mTimeRecord = currentTime;//в микросекундах
        mCommandId=0;
        mCurrentTimeForCommands=0;
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

bool CommandController::GetPlayForwardState()
{
    return IsPlayForwardState;
}

void CommandController::SetPlayForwardState(bool State)
{
    if(State)
    {
        mConfigMap=ConfigController::Instance()->GetConfigMap();
        map<unsigned int,DriverSettingsItem>::iterator it;
        for(it = mConfigMap->begin();it!=mConfigMap->end();++it)
        {
            int NumbBuffer = (*it).second.GetNumberBuffer();
            int MotorAngle = BufferController::Instance()->GetReadBuffer()->Get_MOTOR_CPOS(NumbBuffer);
            BufferController::Instance()->GetWriteBuffer()->Set_MOTOR_ANGLE(NumbBuffer,MotorAngle);
            BufferController::Instance()->GetWriteBuffer()->MOTOR_TRACE(NumbBuffer);
        }
    }
    else
    {
        mConfigMap=ConfigController::Instance()->GetConfigMap();
        map<unsigned int,DriverSettingsItem>::iterator it;
        for(it = mConfigMap->begin();it!=mConfigMap->end();++it)
        {
            int NumbBuffer = (*it).second.GetNumberBuffer();
            int MotorAngle = BufferController::Instance()->GetReadBuffer()->Get_MOTOR_CPOS(NumbBuffer);
            BufferController::Instance()->GetWriteBuffer()->Set_MOTOR_ANGLE(NumbBuffer,MotorAngle);
            BufferController::Instance()->GetWriteBuffer()->MOTOR_STOP(NumbBuffer);
        }
    }
    IsPlayForwardState = State;
}

void CommandController::NextCommand()
{
    int Number = mCommandsList.at(mCommandId).GetNumber();
    int NumberBuffer = ConfigController::Instance()->GetConfigMap()->at(Number).GetNumberBuffer();
    int Position = mCommandsList.at(mCommandId).GetPosition();
    BufferController::Instance()->GetWriteBuffer()->Set_MOTOR_ANGLE(NumberBuffer,Position);
    BufferController::Instance()->GetWriteBuffer()->MOTOR_TRACE(NumberBuffer);
    mCommandId++;
    qDebug() << "Выполнена строка " << QString::number(mCommandId) << endl;
}

void CommandController::SendCommand()
{
    if(IsPlayForwardState)
    {
        Update(mCurrentTimeForCommands);
        mCurrentTimeForCommands+=(mSendDelay*1e3);

        //если время закончилось - останавливаем, переводим индекс команды на начало списка
        if(mTimeRecord<=mCurrentTimeForCommands)
        {
            IsPlayForwardState = false;
            mCommandId = 0;
        }
    }
    if(IsGoToPosState)
    {
        GoNextPos();
    }
}

void CommandController::SetCurrentTimeForCommands(int Time)
{
    mCurrentTimeForCommands = Time;
}

void CommandController::SetCommandId(int cId)
{
    mCommandId=cId;
}

void CommandController::SetTimeToGo(int TimeToGo)
{
    mTimeToGo = TimeToGo;
}

void CommandController::SetDestPos(int DestPos)
{
    mDestPos = DestPos;
}

void CommandController::SetStartPos(int StartPos)
{
    mStartPos = StartPos;
}

int CommandController::GetCurrentPos()
{
    return mCurrentPos;
}

bool CommandController::GetGoToPosState()
{
    return IsGoToPosState;
}

void CommandController::SetGoToPosState(bool State)
{
    IsGoToPosState = State;
}

void CommandController::GoNextPos()
{
    bool IsFirst = mDestPos <= mCurrentPos && mDestPos >= mStartPos;
    bool IsSecond = mDestPos >=mCurrentPos && mDestPos <=mStartPos;
    if(IsFirst || IsSecond)
    {
        BufferController::Instance()->GetWriteBuffer()->Set_MOTOR_ANGLE(mDriverNumberBuffer,mDestPos);
        BufferController::Instance()->GetWriteBuffer()->MOTOR_STOP(mDriverNumberBuffer);
        IsGoToPosState = false;
        qDebug() << "Отправлено конечное положение " << QString::number(mDestPos) << endl;
        return;
    }
    else
    {
        BufferController::Instance()->GetWriteBuffer()->Set_MOTOR_ANGLE(mDriverNumberBuffer,(short)mCurrentPos);
        qDebug() << "Отправлено положение " << QString::number(mCurrentPos) << endl;
        mCurrentPos+=mStepPos;
    }


}

void CommandController::CalcGoToPos()
{
    int SendDelay = ConfigController::Instance()->GetSendDelay();
    int diffPos = mDestPos-mStartPos;//разница в градус*100
    mStepPos = (double)diffPos/((double)mTimeToGo/(double)SendDelay);//шаг в градус*100
    mCurrentPos = mStartPos;
}

void CommandController::SetDriverNumberBuffer(int Number)
{
    mDriverNumberBuffer = Number;
}



