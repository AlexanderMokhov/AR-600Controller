#include "CommandController.h"
#include <qdebug.h>

CommandController * CommandController::mInstance = 0;

CommandController::CommandController():
                        mPrevComand(0),
                        mCommandId(0),
                        IsPlayForwardState(false),
                        IsGoToPosState(false),
                        IsPosState(0)

{
    mSendDelay = ConfigController::Instance()->GetSendDelay();

    //переход в состояние отправки последовательности
    mMotorMap=ConfigController::Instance()->GetMotorMap();
    map<int,Motor>::iterator it;

    mMotorPosMap.clear();

    for(it = mMotorMap->begin();it!=mMotorMap->end();++it)
    {
        MotorPos item;
        item.isEndPos = false;
        mMotorPosMap.insert(pair<int,MotorPos>((*it).first,item));
    }
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

//на вход поступает время в микросекундах (10e-6 c)
void CommandController::Update(long time)
{
    if(mCommandId>=mCountRows)
    {
        return;
    }
    while(mCommandsList[mCommandId].GetTime() <= time)
    {
        if(mCommandId>=mCountRows)
        {
            return;
        }
        //записываем значение в мотор и проверяем следующую команду
        int Number = mCommandsList[mCommandId].GetNumber();
        int Position = mCommandsList[mCommandId].GetPosition();
        int Stiff = mCommandsList[mCommandId].GetPID().Stiff;
        int Dump = mCommandsList[mCommandId].GetPID().Dump;
        int Torque = mCommandsList[mCommandId].GetPID().Torque;

        BufferController::Instance()->GetWriteBuffer()->SetMotorStiff(Number,Stiff);
        BufferController::Instance()->GetWriteBuffer()->SetMotorDump(Number,Dump);
        BufferController::Instance()->GetWriteBuffer()->SetMotorTorque(Number,Torque);
        BufferController::Instance()->GetWriteBuffer()->SetMotorAngle(Number,Position);
        mCommandId++;

        if(mCommandId>=mCountRows)
        {
            return;
        }

        //qDebug() << "String Number" << QString::number(mCommandId) << " Time: " << QString::number(time)<< endl;
        //qDebug() << "Motor Number" << QString::number(Number) << endl;
        //qDebug() << "Pisition" << QString::number(Position) << endl;
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
        Command nextCommand;
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
        //переход в состояние отправки последовательности
        mMotorMap=ConfigController::Instance()->GetMotorMap();
        map<int,Motor>::iterator it;
        for(it = mMotorMap->begin();it!=mMotorMap->end();++it)
        {
            int Number = (*it).first;
            int MotorAngle = BufferController::Instance()->GetReadBuffer()->GetMotorAngle(Number);
            int Stiff = (*it).second.GetStiff();
            int Dump = (*it).second.GetDump();
            int Torque = (*it).second.GetTorque();

            BufferController::Instance()->GetWriteBuffer()->SetMotorStiff(Number,Stiff);
            BufferController::Instance()->GetWriteBuffer()->SetMotorDump(Number,Dump);
            BufferController::Instance()->GetWriteBuffer()->SetMotorTorque(Number,Torque);
            BufferController::Instance()->GetWriteBuffer()->SetMotorAngle(Number,MotorAngle);
            BufferController::Instance()->GetWriteBuffer()->MotorTrace(Number);
        }
        mTime.start();
    }
    else
    {
        //переход в состояние после отправки последовательности
        mMotorMap=ConfigController::Instance()->GetMotorMap();
        map<int,Motor>::iterator it;
        for(it = mMotorMap->begin();it!=mMotorMap->end();++it)
        {
            int Number = (*it).second.GetNumberBuffer();
            int MotorAngle = BufferController::Instance()->GetReadBuffer()->GetMotorAngle(Number);
            int Stiff = (*it).second.GetStiff();
            int Dump = (*it).second.GetDump();
            int Torque = (*it).second.GetTorque();

            BufferController::Instance()->GetWriteBuffer()->SetMotorStiff(Number,Stiff);
            BufferController::Instance()->GetWriteBuffer()->SetMotorDump(Number,Dump);
            BufferController::Instance()->GetWriteBuffer()->SetMotorTorque(Number,Torque);

            BufferController::Instance()->GetWriteBuffer()->SetMotorAngle(Number,MotorAngle);
            BufferController::Instance()->GetWriteBuffer()->MotorStop(Number);
        }
    }
    IsPlayForwardState = State;
}

void CommandController::NextCommand()
{
    int Number = mCommandsList[mCommandId].GetNumber();
    int Position = mCommandsList[mCommandId].GetPosition();
    BufferController::Instance()->GetWriteBuffer()->SetMotorAngle(Number,Position);
    BufferController::Instance()->GetWriteBuffer()->MotorTrace(Number);
    mCommandId++;
    //qDebug() << "Выполнена строка " << QString::number(mCommandId) << endl;
}

void CommandController::SendCommand()
{
    if(IsPlayForwardState)
    {
        mCurrentTimeForCommands = mTime.elapsed()*1e3;
        QTime *timepres = new QTime();
        timepres->start();
        Update(mCurrentTimeForCommands);
        long timeprescount = timepres->elapsed();
        qDebug() << "Time Update: " << QString::number(timeprescount) << " ms"<< endl;

        //если время закончилось - останавливаем, переводим индекс команды на начало списка
        if(mTimeRecord<=mCurrentTimeForCommands)
        {
            IsPlayForwardState = false;
            mCurrentTimeForCommands=0;
            mCommandId = 0;
            qDebug() << "Выполнена последняя строка "  << endl;
        }
    }
    if(IsGoToPosState)
    {
        GoNextPos();
    }
    if(IsPosState>0)
    {
        GoPos();
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

void CommandController::SetPos(int Number, int DestPos, int StartPos)
{
    mMotorPosMap[Number].DestPos = DestPos;
    mMotorPosMap[Number].StartPos = StartPos;
}

bool CommandController::GetGoToPosState()
{
    return IsGoToPosState;
}

void CommandController::SetGoToPosState(bool State)
{
    IsGoToPosState = State;
}

void CommandController::SetPosState(int State)
{
    IsPosState = State;
}

void CommandController::GoNextPos()
{
    bool IsFirst = mDestPos <= mCurrentPos && mDestPos >= mStartPos;
    bool IsSecond = mDestPos >=mCurrentPos && mDestPos <=mStartPos;
    if(IsFirst || IsSecond)
    {
        BufferController::Instance()->GetWriteBuffer()->SetMotorAngle(mMotorNumber,mDestPos);
        BufferController::Instance()->GetWriteBuffer()->MotorStopBrake(mMotorNumber);
        IsGoToPosState = false;
        qDebug() << "Отправлено конечное положение " << QString::number(mDestPos) << endl;
        return;
    }
    else
    {
        BufferController::Instance()->GetWriteBuffer()->SetMotorAngle(mMotorNumber,(short)mCurrentPos);
        qDebug() << "Отправлено положение " << QString::number(mCurrentPos) << endl;
        mCurrentPos+=mStepPos;
    }
}

void CommandController::GoPos()
{
    map<int,MotorPos>::iterator it;
    for(it = mMotorPosMap.begin();it!=mMotorPosMap.end();++it)
    {
        bool IsFirst = (*it).second.DestPos <= (*it).second.CurrentPos
                && (*it).second.DestPos >= (*it).second.StartPos;
        bool IsSecond = (*it).second.DestPos >=(*it).second.CurrentPos
                && (*it).second.DestPos <=(*it).second.StartPos;

        if(IsFirst || IsSecond)
        {
            BufferController::Instance()->GetWriteBuffer()->SetMotorAngle((*it).first,(*it).second.DestPos);
            BufferController::Instance()->GetWriteBuffer()->MotorStopBrake((*it).first);
            if(!(*it).second.isEndPos)
            {
                IsPosState--;

                (*it).second.isEndPos = true;

            }
            qDebug() << "Отправлено конечное положение " << QString::number((*it).second.DestPos) << endl;
            //return;
        }
        else
        {
            BufferController::Instance()->GetWriteBuffer()->SetMotorAngle((*it).first,(short)(*it).second.CurrentPos);
            qDebug() << "Отправлено положение " << QString::number((*it).second.CurrentPos) << endl;
            (*it).second.CurrentPos+=(*it).second.StepPos;
        }
    }
    if(!IsPosState) emit initEnd();
}

void CommandController::initPos(bool mode)
{
    IsPosState = 0;
    int MaxDelta = 0;
    map<int,Motor>::iterator it;
    mMotorMap = ConfigController::Instance()->GetMotorMap();
    int i=0;
    for(it = mMotorMap->begin();it!=mMotorMap->end();++it)
    {
        int Number = (*it).first;
        int MotorAngle = BufferController::Instance()->GetReadBuffer()->GetMotorAngle(Number);
        //взять значение из файла
        long pos = 0;
        if(mode)
        {
            pos = mCommandsList[i].GetPosition();
        }
        int TempDelta = std::abs(MotorAngle - pos);
        MaxDelta = (TempDelta > MaxDelta && (*it).second.GetEnable())? TempDelta : MaxDelta;
        if(!mode)
        {
            SetPos(Number,0,MotorAngle);
        }
        else
        {
            SetPos(Number,pos,MotorAngle);
        }
        BufferController::Instance()->GetWriteBuffer()->SetMotorAngle(Number, MotorAngle);
        BufferController::Instance()->GetWriteBuffer()->MotorTrace(Number);
        i++;
    }

    long Time = MaxDelta * 1000/ (ConfigController::Instance()->GetDefaultSpeed()*100);
    CalcPos(Time);
    SetPosState(21);
}

void CommandController::CalcGoToPos()
{
    int SendDelay = ConfigController::Instance()->GetSendDelay();
    int diffPos = mDestPos-mStartPos;//разница в градус*100
    mStepPos = (double)diffPos/((double)mTimeToGo/(double)SendDelay);//шаг в градус*100
    mCurrentPos = mStartPos;
}

void CommandController::CalcPos(long TimeToGo)
{
    int SendDelay = ConfigController::Instance()->GetSendDelay();
    long TimeToGoMs = TimeToGo;
    map<int,MotorPos>::iterator it;
    for(it = mMotorPosMap.begin();it!=mMotorPosMap.end();++it)
    {
        int diffPos = (*it).second.DestPos - (*it).second.StartPos;//разница в градус*100
        if(TimeToGoMs!=0)
        {
            (*it).second.StepPos = (double)diffPos/((double)TimeToGoMs/(double)SendDelay);//шаг в градус*100
        }
        else
        {
            (*it).second.StepPos = diffPos;
        }
        (*it).second.CurrentPos = (*it).second.StartPos;
        (*it).second.isEndPos = false;
    }
}

void CommandController::SetMotorNumber(int Number)
{
    mMotorNumber = Number;
}



