#include "MoveController.h"

MoveController * MoveController::mInst = 0;

MoveController::MoveController()
{
    mState = States::NotWork; //ничего не делаем
    mCommandId = 0;
    mSendDelay = ConfigController::Inst()->GetSendDelay();

    mGoToPosData.clear();

    mMotors = ConfigController::Inst()->GetMotors();
    for(auto it = mMotors->begin(); it != mMotors->end(); ++it)
    {
        PosData item;
        item.CurrentPos = 0;
        item.DestPos = 0;
        item.StartPos = 0;
        item.Step = 0;
        item.isEndPos = false;
        mGoToPosData[(*it).first] = item;
    }

    MoveStorage::Inst()->Init();

    UserStiff = 0;
    UserDump = 0;

    useUserStiff = false;
    useUserDump = false;
}

//на вход поступает время в микросекундах (10e-6 c)
void MoveController::StepPlay()
{
    long time = mTime.elapsed()*1e3;

    QTime t;
    t.start();

    if(MoveStorage::Inst()->mMoveID >= MoveStorage::Inst()->mCountRows){goto StopPlay;}

    while(MoveStorage::Inst()->mMoves[MoveStorage::Inst()->mMoveID].Time <= time)
    {
        if(MoveStorage::Inst()->mMoveID >= MoveStorage::Inst()->mCountRows){goto StopPlay;}

        //записываем значение в мотор и проверяем следующую команду
        int Number = MoveStorage::Inst()->mMoves[MoveStorage::Inst()->mMoveID].NumberChannel;
        int Angle = MoveStorage::Inst()->mMoves[MoveStorage::Inst()->mMoveID].Angle;

        int Stiff = 0;
        if(useUserStiff)
            Stiff = UserStiff;
        else
            Stiff = MoveStorage::Inst()->mMoves[MoveStorage::Inst()->mMoveID].PIDs.Stiff;

        int Dump = 0;
        if(useUserDump)
            Dump = UserDump;
        else
            Dump = MoveStorage::Inst()->mMoves[MoveStorage::Inst()->mMoveID].PIDs.Dump;

        int Torque = MoveStorage::Inst()->mMoves[MoveStorage::Inst()->mMoveID].PIDs.Torque;

        BufferController::Inst()->GetBufferS()->SetMotorStiff( Number, Stiff );
        BufferController::Inst()->GetBufferS()->SetMotorDump( Number, Dump );
        BufferController::Inst()->GetBufferS()->SetMotorTorque( Number, Torque );

        int CorrectionValue = MoveCorrector::Inst()->getCorrectValue(Number, MoveStorage::Inst()->mMoves[MoveStorage::Inst()->mMoveID].Time);
        qDebug() << "Корректирующее "  << QString::number(CorrectionValue) << endl;

        BufferController::Inst()->GetBufferS()->SetMotorAngle( Number, Angle + CorrectionValue);
        MoveStorage::Inst()->mMoveID++;

        if(MoveStorage::Inst()->mMoveID >= MoveStorage::Inst()->mCountRows){goto StopPlay;}
    }

StopPlay:
    //qDebug() << "Time elapsed: " << QString::number(t.elapsed()) << "ms\n";

    //если время закончилось - останавливаем, переводим индекс команды на начало списка
    if(time > MoveStorage::Inst()->mDuration)
    {
        MoveStorage::Inst()->mMoveID = 0;
        qDebug() << "Выполнена последняя строка"  << endl;
        emit PlayEnd();
        mState = States::MoveStopping;
    }
}

void MoveController::StartPlay()
{
    mState = MoveStarting;
}

void MoveController::StartingPlay()
{
    mMotors = ConfigController::Inst()->GetMotors();
    for(auto it = mMotors->begin(); it != mMotors->end(); ++it)
    {
        int Number = (*it).second.GetNumber();
        int Angle = BufferController::Inst()->GetBufferR()->GetMotorAngle( Number );
        int Stiff = (*it).second.GetStiff();
        int Dump = (*it).second.GetDump();
        int Torque = (*it).second.GetTorque();

        BufferController::Inst()->GetBufferS()->SetMotorStiff( Number, Stiff );
        BufferController::Inst()->GetBufferS()->SetMotorDump( Number, Dump );
        BufferController::Inst()->GetBufferS()->SetMotorTorque( Number, Torque );
        BufferController::Inst()->GetBufferS()->SetMotorAngle( Number, Angle );
        BufferController::Inst()->GetBufferS()->MotorTrace( Number );
    }
    MoveStorage::Inst()->mMoveID = 0;
    MoveCorrector::Inst()->setCurLine(0);

    mState = States::MovePlay;
    mTime.start();
}

void MoveController::StopPlay()
{
    mState = States::MoveStopping;
}

void MoveController::StoppingPlay()
{
    //переход в состояние после отправки последовательности
    mMotors = ConfigController::Inst()->GetMotors();
    for(auto it = mMotors->begin(); it != mMotors->end(); ++it)
    {
        int Number = (*it).second.GetNumber();
        int MotorAngle = BufferController::Inst()->GetBufferR()->GetMotorAngle( Number );
        int Stiff = (*it).second.GetStiff();
        int Dump = (*it).second.GetDump();
        int Torque = (*it).second.GetTorque();

        BufferController::Inst()->GetBufferS()->SetMotorStiff( Number, Stiff );
        BufferController::Inst()->GetBufferS()->SetMotorDump( Number, Dump );
        BufferController::Inst()->GetBufferS()->SetMotorTorque( Number, Torque );
        BufferController::Inst()->GetBufferS()->SetMotorAngle( Number, MotorAngle );
        BufferController::Inst()->GetBufferS()->MotorStopBrake( Number);
    }
    MoveStorage::Inst()->mMoveID = 0;
    mState = States::NotWork;
}

void MoveController::SkipSpace(std::locale loc, std::string str, unsigned int *i)
{
    while( std::isspace(str[(*i)], loc) )
        (*i)++;
}

void MoveController::ReadValue(std::string *temp, std::locale loc, unsigned int *i, std::string str)
{
    while( !std::isspace(str[*i], loc) && *i < str.length() )
    {
        *temp += str.at(*i);
        (*i)++;
    }
}

bool MoveController::OpenFile(std::string fileName)
{
    return MoveStorage::Inst()->OpenFile(fileName);
}

void MoveController::NextCommand()
{
    int Number = MoveStorage::Inst()->mMoves[MoveStorage::Inst()->mMoveID].NumberChannel;
    int Angle = MoveStorage::Inst()->mMoves[MoveStorage::Inst()->mMoveID].Angle;
    BufferController::Inst()->GetBufferS()->SetMotorAngle(Number,Angle);
    BufferController::Inst()->GetBufferS()->MotorTrace(Number);
    MoveStorage::Inst()->mMoveID++;
}

void MoveController::DoStepWork()
{
    switch (mState){
    case MoveStarting: //запуск отработки
    {
        StartingPlay();
    }
        break;
    case MovePlay: //отработка команд
    {
        StepPlay();
    }
        break;
    case MoveStopping: //остановка отработки
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
        StepGoPos();
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
void MoveController::SetPosData(int Number, int DestPos, int StartPos)
{
    mGoToPosData[Number].DestPos = DestPos;
    mGoToPosData[Number].StartPos = StartPos;
}

void MoveController::StartGoPos(bool isCommand)
{
    mState = States::GoPosStarting;
    mGoPosMode = isCommand;
}

void MoveController::StartingGoPos()
{
    emit InitStart();
    int MaxDiff = 0;
    int i=0;

    mMotors = ConfigController::Inst()->GetMotors();
    for(auto it = mMotors->begin();it != mMotors->end();++it)
    {
        int Number = (*it).first;
        int StartAngle = BufferController::Inst()->GetBufferR()->GetMotorAngle(Number);
        int DestAngle = mGoPosMode == true ? MoveStorage::Inst()->mMoves[i].Angle : 0;
        int DiffAngle = std::abs(DestAngle - StartAngle);
        MaxDiff = (DiffAngle > MaxDiff && (*it).second.GetEnable()) ? DiffAngle : MaxDiff;

        SetPosData(Number,DestAngle,StartAngle);

        BufferController::Inst()->GetBufferS()->SetMotorAngle(Number, StartAngle);
        BufferController::Inst()->GetBufferS()->MotorTrace(Number);
        i++;
    }

    long TimeMs = MaxDiff * 1000 / (ConfigController::Inst()->GetDefaultSpeed()*100);
    TimeMs = TimeMs < 1000 ? 1000 : TimeMs;
    SetupGoPos(TimeMs);
    mMotorExistCount = 21;
    mState = States::GoToPos;
}

void MoveController::SetupGoPos(long TimeToGo)
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

void MoveController::StepGoPos()
{
    for(auto it = mGoToPosData.begin();it != mGoToPosData.end();++it)
    {
        bool IsFirst = (*it).second.DestPos <= (*it).second.CurrentPos
                && (*it).second.DestPos >= (*it).second.StartPos;
        bool IsSecond = (*it).second.DestPos >=(*it).second.CurrentPos
                && (*it).second.DestPos <=(*it).second.StartPos;

        if(IsFirst || IsSecond)
        {
            BufferController::Inst()->GetBufferS()->SetMotorAngle((*it).first,(short)(*it).second.DestPos);
            BufferController::Inst()->GetBufferS()->MotorStopBrake((*it).first);

            if(!(*it).second.isEndPos)
            {
                mMotorExistCount--;
                (*it).second.isEndPos = true;
            }
            qDebug() << QString::number((*it).first) << " Отправлено конечное положение " << QString::number((*it).second.DestPos) << endl;
        }
        else
        {
            BufferController::Inst()->GetBufferS()->SetMotorAngle((*it).first,(short)(*it).second.CurrentPos);
            qDebug() << "Отправлено положение " << QString::number((*it).second.CurrentPos) << endl;
            (*it).second.CurrentPos += (*it).second.Step;
        }
    }

    //Если равно 0 то конец
    if(mMotorExistCount == 0)
    {
        qDebug() << "Достигнуто стартовое положение " << endl;
        mState = States::GoPosStopping;
        //emit InitEnd();
    }
}

void MoveController::StopGoPos()
{
    mState = States::GoPosStopping;
}

void MoveController::StoppingGoPos()
{
    for(auto it = mMotors->begin();it != mMotors->end();++it)
    {
        int Angle = BufferController::Inst()->GetBufferR()->GetMotorAngle((*it).first);

        BufferController::Inst()->GetBufferS()->SetMotorAngle((*it).first, Angle);
        BufferController::Inst()->GetBufferS()->MotorStopBrake((*it).first);
    }

    mState = States::NotWork;
}

//Конец команд для перехода в исходную позицию

//Команды для перехода в заданный угол (один двигатель)
void MoveController::StartGoToAngle(int Number, int DestAngle, int Time)
{
    NewMotorNumber = Number;
    NewTimeToGo = Time;
    NewDestAngle = DestAngle;
    mState = States::GoToAngleStarting;
}

void MoveController::StartingGoToAngle()
{
    mMotorNumber = NewMotorNumber;
    mTimeToGo = NewTimeToGo;
    mDestAngle = NewDestAngle;
    mStartAngle = BufferController::Inst()->GetBufferR()->GetMotorAngle(mMotorNumber);

    int SendDelay = ConfigController::Inst()->GetSendDelay();
    int diffAngle = mDestAngle - mStartAngle;//разница в градус*100
    mStep = (double)diffAngle / ((double)mTimeToGo/(double)SendDelay);//шаг в градус*100
    mCurrentAngle = mStartAngle;

    //включаем мотор
    BufferController::Inst()->GetBufferS()->SetMotorAngle(mMotorNumber, mStartAngle);
    BufferController::Inst()->GetBufferS()->MotorTrace(mMotorNumber);

    mState = States::GoToAngle;
}

void MoveController::StepGoToAngle()
{
    bool IsFirst = mDestAngle <= mCurrentAngle && mDestAngle >= mStartAngle;
    bool IsSecond = mDestAngle >= mCurrentAngle && mDestAngle <= mStartAngle;

    if(IsFirst || IsSecond)
    {
        BufferController::Inst()->GetBufferS()->SetMotorAngle(mMotorNumber,mDestAngle);
        BufferController::Inst()->GetBufferS()->MotorStopBrake(mMotorNumber);
        qDebug() << "Отправлено конечное положение " << QString::number(mDestAngle) << endl;
        mState = States::NotWork;
    }
    else
    {
        BufferController::Inst()->GetBufferS()->SetMotorAngle(mMotorNumber,(short)mCurrentAngle);
        qDebug() << "Отправлено положение " << QString::number(mCurrentAngle) << endl;
        mCurrentAngle += mStep;
    }
}

void MoveController::StopGoToAngle()
{
    mState = States::GoToAngleStopping;
}

void MoveController::StoppingGoToAngle()
{
    BufferController::Inst()->GetBufferS()->MotorStop(mMotorNumber);
    mState = States::NotWork;
}
//Конец команд для перехода в заданный угол (один двигатель)
