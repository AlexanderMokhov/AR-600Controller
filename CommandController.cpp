#include "CommandController.h"

CommandController * CommandController::mInst = 0;

CommandController::CommandController():
                        mCommandId(0),
                        IsPlaySequenceState(false),
                        IsGoToPosState(false),
                        IsGoToStartPosState(0)

{
    mSendDelay = ConfigController::Inst()->GetSendDelay();

    //переход в состояние отправки последовательности
    mMotorMap = ConfigController::Inst()->GetMotorMap();

    mMotorPosMap.clear();

    for(auto it = mMotorMap->begin();it!=mMotorMap->end();++it)
    {
        MotorPos item;
        item.isEndPos = false;
        mMotorPosMap.insert(pair<int,MotorPos>((*it).first,item));
    }
}

//на вход поступает время в микросекундах (10e-6 c)
void CommandController::Update(long time)
{
    if(mCommandId>=mCountRows)
    {
        return;
    }
    while(mCommandsList[mCommandId].Time <= time)
    {
        if(mCommandId>=mCountRows)
        {
            return;
        }
        //записываем значение в мотор и проверяем следующую команду
        int Number = mCommandsList[mCommandId].Number;
        int Angle = mCommandsList[mCommandId].Angle;
        int Stiff = mCommandsList[mCommandId].PIDs.Stiff;
        int Dump = mCommandsList[mCommandId].PIDs.Dump;
        int Torque = mCommandsList[mCommandId].PIDs.Torque;

        BufferController::Inst()->GetWriteBuffer()->SetMotorStiff(Number,Stiff);
        BufferController::Inst()->GetWriteBuffer()->SetMotorDump(Number,Dump);
        BufferController::Inst()->GetWriteBuffer()->SetMotorTorque(Number,Torque);
        BufferController::Inst()->GetWriteBuffer()->SetMotorAngle(Number,Angle);
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
        mPID.Stiff = ConfigController::Inst()->GetDefaultStiff();
        mPID.Dump = ConfigController::Inst()->GetDefaultDump();
        mPID.Torque = ConfigController::Inst()->GetDefaultTorque();

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
            //прочитали угол

            //записываем угол
            double Angle = atof(temp.c_str());
            temp.clear();

            //Переводим угол в градусы*100
            Angle=(180.0/M_PI)*Angle*100.0;

            //проверяем есть ли коэффициэнты PID
            while(std::isspace(str[i],loc))
                i++;

            if(str[i]!='\0')
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
            nextCommand.Time = (int)Time;
            nextCommand.Number = Number;
            nextCommand.Angle = (int)Angle;
            nextCommand.PIDs = mPID;

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

bool CommandController::GetPlaySequenceState()
{
    return IsPlaySequenceState;
}

void CommandController::SetPlaySequenceState(bool State)
{
    if(State)
    {
        //переход в состояние отправки последовательности
        mMotorMap=ConfigController::Inst()->GetMotorMap();
        for(auto it = mMotorMap->begin();it!=mMotorMap->end();++it)
        {
            int Number = (*it).second.GetNumber();
            int MotorAngle = BufferController::Inst()->GetReadBuffer()->GetMotorAngle(Number);
            int Stiff = (*it).second.GetStiff();
            int Dump = (*it).second.GetDump();
            int Torque = (*it).second.GetTorque();

            BufferController::Inst()->GetWriteBuffer()->SetMotorStiff(Number,Stiff);
            BufferController::Inst()->GetWriteBuffer()->SetMotorDump(Number,Dump);
            BufferController::Inst()->GetWriteBuffer()->SetMotorTorque(Number,Torque);
            BufferController::Inst()->GetWriteBuffer()->SetMotorAngle(Number,MotorAngle);
            BufferController::Inst()->GetWriteBuffer()->MotorTrace(Number);
        }
        mTime.start();
    }
    else
    {
        //переход в состояние после отправки последовательности
        mMotorMap=ConfigController::Inst()->GetMotorMap();
        for(auto it = mMotorMap->begin();it!=mMotorMap->end();++it)
        {
            int Number = (*it).second.GetNumber();
            int MotorAngle = BufferController::Inst()->GetReadBuffer()->GetMotorAngle(Number);
            int Stiff = (*it).second.GetStiff();
            int Dump = (*it).second.GetDump();
            int Torque = (*it).second.GetTorque();

            BufferController::Inst()->GetWriteBuffer()->SetMotorStiff(Number,Stiff);
            BufferController::Inst()->GetWriteBuffer()->SetMotorDump(Number,Dump);
            BufferController::Inst()->GetWriteBuffer()->SetMotorTorque(Number,Torque);
            BufferController::Inst()->GetWriteBuffer()->SetMotorAngle(Number,MotorAngle);
            BufferController::Inst()->GetWriteBuffer()->MotorStop(Number);
        }
    }
    IsPlaySequenceState = State;
}

void CommandController::NextCommand()
{
    int Number = mCommandsList[mCommandId].Number;
    int Angle = mCommandsList[mCommandId].Angle;
    BufferController::Inst()->GetWriteBuffer()->SetMotorAngle(Number,Angle);
    BufferController::Inst()->GetWriteBuffer()->MotorTrace(Number);
    mCommandId++;
    //qDebug() << "Выполнена строка " << QString::number(mCommandId) << endl;
}

void CommandController::SendCommand()
{
    if(IsPlaySequenceState)
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
            mCurrentTimeForCommands=0;
            mCommandId = 0;
            qDebug() << "Выполнена последняя строка "  << endl;
            emit PlayEnd();
            SetPlaySequenceState(false);
        }
    }
    if(IsGoToPosState)
    {
        GoNextPos();
    }
    if(IsGoToStartPosState>0)
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

void CommandController::SetGoToStartPosState(int State)
{
    IsGoToStartPosState = State;
}

void CommandController::GoNextPos()
{
    bool IsFirst = mDestPos <= mCurrentPos && mDestPos >= mStartPos;
    bool IsSecond = mDestPos >= mCurrentPos && mDestPos <= mStartPos;
    if(IsFirst || IsSecond)
    {
        BufferController::Inst()->GetWriteBuffer()->SetMotorAngle(mMotorNumber,mDestPos);
        BufferController::Inst()->GetWriteBuffer()->MotorStopBrake(mMotorNumber);
        IsGoToPosState = false;
        qDebug() << "Отправлено конечное положение " << QString::number(mDestPos) << endl;
        return;
    }
    else
    {
        BufferController::Inst()->GetWriteBuffer()->SetMotorAngle(mMotorNumber,(short)mCurrentPos);
        qDebug() << "Отправлено положение " << QString::number(mCurrentPos) << endl;
        mCurrentPos+=mStepPos;
    }
}

void CommandController::GoPos()
{
    for(auto it = mMotorPosMap.begin();it!=mMotorPosMap.end();++it)
    {
        bool IsFirst = (*it).second.DestPos <= (*it).second.CurrentPos
                && (*it).second.DestPos >= (*it).second.StartPos;
        bool IsSecond = (*it).second.DestPos >=(*it).second.CurrentPos
                && (*it).second.DestPos <=(*it).second.StartPos;

        if(IsFirst || IsSecond)
        {
            BufferController::Inst()->GetWriteBuffer()->SetMotorAngle((*it).first,(*it).second.DestPos);
            BufferController::Inst()->GetWriteBuffer()->MotorStopBrake((*it).first);
            if(!(*it).second.isEndPos)
            {
                IsGoToStartPosState--;

                (*it).second.isEndPos = true;

            }
            qDebug() << "Отправлено конечное положение " << QString::number((*it).second.DestPos) << endl;
            //return;
        }
        else
        {
            BufferController::Inst()->GetWriteBuffer()->SetMotorAngle((*it).first,(short)(*it).second.CurrentPos);
            qDebug() << "Отправлено положение " << QString::number((*it).second.CurrentPos) << endl;
            (*it).second.CurrentPos+=(*it).second.Step;
        }
    }
    if(!IsGoToStartPosState) emit initEnd();
}

void CommandController::initPos(bool mode)
{
    emit initStart();
    IsGoToStartPosState = 0;
    int MaxDelta = 0;
    mMotorMap = ConfigController::Inst()->GetMotorMap();
    int i=0;
    for(auto it = mMotorMap->begin();it!=mMotorMap->end();++it)
    {
        int Number = (*it).first;
        int MotorAngle = BufferController::Inst()->GetReadBuffer()->GetMotorAngle(Number);
        //взять значение из файла
        long pos = 0;
        if(mode)
        {
            pos = mCommandsList[i].Angle;
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
        BufferController::Inst()->GetWriteBuffer()->SetMotorAngle(Number, MotorAngle);
        BufferController::Inst()->GetWriteBuffer()->MotorTrace(Number);
        i++;
    }

    long Time = MaxDelta * 1000/ (ConfigController::Inst()->GetDefaultSpeed()*100);
    CalcGoToStartPos(Time);
    SetGoToStartPosState(21);
}

void CommandController::CalcGoToPos()
{
    int SendDelay = ConfigController::Inst()->GetSendDelay();
    int diffPos = mDestPos-mStartPos;//разница в градус*100
    mStepPos = (double)diffPos/((double)mTimeToGo/(double)SendDelay);//шаг в градус*100
    mCurrentPos = mStartPos;
}

void CommandController::CalcGoToStartPos(long TimeToGo)
{
    int SendDelay = ConfigController::Inst()->GetSendDelay();
    long TimeToGoMs = TimeToGo;
    for(auto it = mMotorPosMap.begin();it!=mMotorPosMap.end();++it)
    {
        int diffPos = (*it).second.DestPos - (*it).second.StartPos;//разница в градус*100
        if(TimeToGoMs!=0)
        {
            (*it).second.Step = (double)diffPos/((double)TimeToGoMs/(double)SendDelay);//шаг в градус*100
        }
        else
        {
            (*it).second.Step = diffPos;
        }
        (*it).second.CurrentPos = (*it).second.StartPos;
        (*it).second.isEndPos = false;
    }
}

void CommandController::SetMotorNumber(int Number)
{
    mMotorNumber = Number;
}



