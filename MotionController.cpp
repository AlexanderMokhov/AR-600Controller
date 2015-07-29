#include "MotionController.h"

MotionController * MotionController::mInst = 0;

MotionController::MotionController()
{
    mState = States::NotWork; //ничего не делаем
    mCommandId = 0;
    mSendDelay = ConfigController::Inst()->GetSendDelay();

    mGoToPosData.clear();

    mMotors = ConfigController::Inst()->GetMotors();
    for(auto it = mMotors->begin();it != mMotors->end();++it)
    {
        PosData item;
        item.CurrentPos = 0;
        item.DestPos = 0;
        item.StartPos = 0;
        item.Step = 0;
        item.isEndPos = false;
        mGoToPosData[(*it).first] = item;
    }
}

//на вход поступает время в микросекундах (10e-6 c)
void MotionController::StepPlay()
{
    long time = mTime.elapsed()*1e3;

    if(mCommandId >= mCountRows){goto StopPlay;}

    while(mCommands[mCommandId].Time <= time)
    {
        if(mCommandId >= mCountRows){goto StopPlay;}

        //записываем значение в мотор и проверяем следующую команду
        int Number = mCommands[mCommandId].Number;
        int Angle = mCommands[mCommandId].Angle;
        int Stiff = mCommands[mCommandId].PIDs.Stiff;
        int Dump = mCommands[mCommandId].PIDs.Dump;
        int Torque = mCommands[mCommandId].PIDs.Torque;

        BufferController::Inst()->GetWriteBuffer()->SetMotorStiff(Number,Stiff);
        BufferController::Inst()->GetWriteBuffer()->SetMotorDump(Number,Dump);
        BufferController::Inst()->GetWriteBuffer()->SetMotorTorque(Number,Torque);
        BufferController::Inst()->GetWriteBuffer()->SetMotorAngle(Number,Angle);
        mCommandId++;

        if(mCommandId >= mCountRows){goto StopPlay;}
    }

StopPlay:
    //если время закончилось - останавливаем, переводим индекс команды на начало списка
    if(time > mDuration)
    {
        mCommandId = 0;
        qDebug() << "Выполнена последняя строка"  << endl;
        emit PlayEnd();
        mState = States::PlayStopping;
    }
}

void MotionController::StartPlay()
{
    mState = PlayStarting;
}

void MotionController::StartingPlay()
{
    mMotors = ConfigController::Inst()->GetMotors();
    for(auto it = mMotors->begin(); it != mMotors->end(); ++it)
    {
        int Number = (*it).second.GetNumber();
        int Angle = BufferController::Inst()->GetReadBuffer()->GetMotorAngle(Number);
        int Stiff = (*it).second.GetStiff();
        int Dump = (*it).second.GetDump();
        int Torque = (*it).second.GetTorque();

        BufferController::Inst()->GetWriteBuffer()->SetMotorStiff(Number,Stiff);
        BufferController::Inst()->GetWriteBuffer()->SetMotorDump(Number,Dump);
        BufferController::Inst()->GetWriteBuffer()->SetMotorTorque(Number,Torque);
        BufferController::Inst()->GetWriteBuffer()->SetMotorAngle(Number,Angle);
        BufferController::Inst()->GetWriteBuffer()->MotorTrace(Number);
    }
    mCommandId = 0;
    mState = States::Play;
    mTime.start();
}

void MotionController::StopPlay()
{
    mState = States::PlayStopping;
}

void MotionController::StoppingPlay()
{
    //переход в состояние после отправки последовательности
    mMotors = ConfigController::Inst()->GetMotors();
    for(auto it = mMotors->begin();it!=mMotors->end();++it)
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
    mCommandId = 0;
    mState = States::NotWork;
}

bool MotionController::OpenFile(std::string fileName)
{
    std::ifstream file(fileName.c_str());

    if(file.is_open())
    {
        //очищаем список команд
        mCommands.clear();
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
            mCommands.push_back(nextCommand);
            mCountRows++;
            currentTime=Time;
        }
        mDuration = currentTime;//в микросекундах
        mCommandId = 0;
        qDebug() << "считано " << QString::number(mCountRows) << " строк" << endl;
        qDebug() << "Время записи " << QString::number((double)mDuration/1e6) << " секунд" << endl;

        file.close();
        return true;
    }
    else
    {
        file.close();
        return false;
    }

}

void MotionController::NextCommand()
{
    int Number = mCommands[mCommandId].Number;
    int Angle = mCommands[mCommandId].Angle;
    BufferController::Inst()->GetWriteBuffer()->SetMotorAngle(Number,Angle);
    BufferController::Inst()->GetWriteBuffer()->MotorTrace(Number);
    mCommandId++;
}

void MotionController::DoStepWork()
{
    switch (mState){
    case PlayStarting: //запуск отработки
    {
        StartingPlay();
    }
        break;
    case Play: //отработка команд
    {
        StepPlay();
    }
        break;
    case PlayStopping: //остановка отработки
    {
        StoppingPlay();
    }
        break;
    case GoToAngleStarting: //запуск перехода мотора
    {
        StartingGoToAngle();
    }
        break;
    case GoToAngle: //переход мотора в заданный угол
    {
        StepGoToAngle();
    }
        break;
    case GoToAngleStopping: //остановка перехода мотора
    {
        StoppingGoToAngle();
    }
        break;
    case GoPosStarting: //переход в начальную позицию
    {
        StartingGoPos();
    }
        break;
    case GoToPos: //переход в начальную позицию
    {
        StepGoToPos();
    }
        break;
    case GoPosStopping: //переход в начальную позицию
    {
        StoppingGoPos();
    }
        break;
    default:
        break;
    }
}

//Команды для перехода в исходную позицию
void MotionController::SetPosData(int Number, int DestPos, int StartPos)
{
    mGoToPosData[Number].DestPos = DestPos;
    mGoToPosData[Number].StartPos = StartPos;
}

void MotionController::StartGoPos(bool isCommand)
{
    mState = States::GoPosStarting;
    mGoPosMode = isCommand;
}

void MotionController::StartingGoPos()
{
    emit InitStart();
    int MaxDiff = 0;
    int i=0;

    mMotors = ConfigController::Inst()->GetMotors();
    for(auto it = mMotors->begin();it!=mMotors->end();++it)
    {
        int Number = (*it).first;
        int StartAngle = BufferController::Inst()->GetReadBuffer()->GetMotorAngle(Number);
        int DestAngle = mGoPosMode == true ? mCommands[i].Angle : 0;
        int DiffAngle = std::abs(DestAngle - StartAngle);
        MaxDiff = (DiffAngle > MaxDiff && (*it).second.GetEnable()) ? DiffAngle : MaxDiff;

        SetPosData(Number,DestAngle,StartAngle);

        BufferController::Inst()->GetWriteBuffer()->SetMotorAngle(Number, StartAngle);
        BufferController::Inst()->GetWriteBuffer()->MotorTrace(Number);
        i++;
    }

    long TimeMs = MaxDiff * 1000 / (ConfigController::Inst()->GetDefaultSpeed()*100);
    TimeMs = TimeMs < 1000 ? 1000 : TimeMs;
    SetupGoPos(TimeMs);
    mMotorExistCount = 21;
    mState = States::GoToPos;
}

void MotionController::SetupGoPos(long TimeToGo)
{
    int SendDelay = ConfigController::Inst()->GetSendDelay();

    for(auto it = mGoToPosData.begin();it != mGoToPosData.end();++it)
    {
        int diffPos = (*it).second.DestPos - (*it).second.StartPos;

        if(TimeToGo != 0)
        {
            (*it).second.Step = (double)diffPos/((double)TimeToGo/(double)SendDelay);
        }
        else{(*it).second.Step = diffPos;}

        (*it).second.CurrentPos = (*it).second.StartPos;
        (*it).second.isEndPos = false;
    }
}

void MotionController::StepGoToPos()
{
    for(auto it = mGoToPosData.begin();it != mGoToPosData.end();++it)
    {
        bool IsFirst = (*it).second.DestPos <= (*it).second.CurrentPos
                && (*it).second.DestPos >= (*it).second.StartPos;
        bool IsSecond = (*it).second.DestPos >=(*it).second.CurrentPos
                && (*it).second.DestPos <=(*it).second.StartPos;

        if(IsFirst || IsSecond)
        {
            BufferController::Inst()->GetWriteBuffer()->SetMotorAngle((*it).first,(short)(*it).second.DestPos);
            BufferController::Inst()->GetWriteBuffer()->MotorStopBrake((*it).first);

            if(!(*it).second.isEndPos)
            {
                mMotorExistCount--;
                (*it).second.isEndPos = true;
            }
            qDebug() << QString::number((*it).first) << " Отправлено конечное положение " << QString::number((*it).second.DestPos) << endl;
        }
        else
        {
            BufferController::Inst()->GetWriteBuffer()->SetMotorAngle((*it).first,(short)(*it).second.CurrentPos);
            qDebug() << "Отправлено положение " << QString::number((*it).second.CurrentPos) << endl;
            (*it).second.CurrentPos += (*it).second.Step;
        }
    }

    //Если равно 0 то конец
    if(mMotorExistCount == 0)
    {
        qDebug() << "Достигнуто стартовое положение " << endl;
        mState = States::NotWork;
        emit InitEnd();
    }
}

void MotionController::StopGoPos()
{
    mState = States::GoPosStopping;
}

void MotionController::StoppingGoPos()
{
    for(auto it = mMotors->begin();it!=mMotors->end();++it)
    {
        int Angle = BufferController::Inst()->GetReadBuffer()->GetMotorAngle((*it).first);

        BufferController::Inst()->GetWriteBuffer()->SetMotorAngle((*it).first, Angle);
        BufferController::Inst()->GetWriteBuffer()->MotorStopBrake((*it).first);
    }

    mState = States::NotWork;
}

//Конец команд для перехода в исходную позицию

//Команды для перехода в заданный угол (один двигатель)
void MotionController::StartGoToAngle(int Number, int DestAngle, int Time)
{
    NewMotorNumber = Number;
    NewTimeToGo = Time;
    NewDestAngle = DestAngle;
    mState = States::GoToAngleStarting;
}

void MotionController::StartingGoToAngle()
{
    mMotorNumber = NewMotorNumber;
    mTimeToGo = NewTimeToGo;
    mDestAngle = NewDestAngle;
    mStartAngle = BufferController::Inst()->GetReadBuffer()->GetMotorAngle(mMotorNumber);

    int SendDelay = ConfigController::Inst()->GetSendDelay();
    int diffAngle = mDestAngle - mStartAngle;//разница в градус*100
    mStep = (double)diffAngle/((double)mTimeToGo/(double)SendDelay);//шаг в градус*100
    mCurrentAngle = mStartAngle;

    //включаем мотор
    BufferController::Inst()->GetWriteBuffer()->SetMotorAngle(mMotorNumber, mStartAngle);
    BufferController::Inst()->GetWriteBuffer()->MotorTrace(mMotorNumber);

    mState = States::GoToAngle;
}

void MotionController::StepGoToAngle()
{
    bool IsFirst = mDestAngle <= mCurrentAngle && mDestAngle >= mStartAngle;
    bool IsSecond = mDestAngle >= mCurrentAngle && mDestAngle <= mStartAngle;

    if(IsFirst || IsSecond)
    {
        BufferController::Inst()->GetWriteBuffer()->SetMotorAngle(mMotorNumber,mDestAngle);
        BufferController::Inst()->GetWriteBuffer()->MotorStopBrake(mMotorNumber);
        qDebug() << "Отправлено конечное положение " << QString::number(mDestAngle) << endl;
        mState = States::NotWork;
    }
    else
    {
        BufferController::Inst()->GetWriteBuffer()->SetMotorAngle(mMotorNumber,(short)mCurrentAngle);
        qDebug() << "Отправлено положение " << QString::number(mCurrentAngle) << endl;
        mCurrentAngle += mStep;
    }
}

void MotionController::StopGoToAngle()
{
    mState = States::GoToAngleStopping;
}

void MotionController::StoppingGoToAngle()
{
    BufferController::Inst()->GetWriteBuffer()->MotorStop(mMotorNumber);
    mState = States::NotWork;
}
//Конец команд для перехода в заданный угол (один двигатель)
