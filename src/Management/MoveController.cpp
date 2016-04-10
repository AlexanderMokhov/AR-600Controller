#include "MoveController.h"

MoveController * MoveController::m_inst = 0;

MoveController::MoveController()
{
    m_state = States::NotWork; //ничего не делаем

    mGoToPosData.clear();

    m_motors = ARCore::Inst()->getSettingStore()->GetMotors();
    for(auto it = m_motors->begin(); it != m_motors->end(); ++it)
    {
        PosData item;
        item.CurrentPos = 0;
        item.DestPos = 0;
        item.StartPos = 0;
        item.Step = 0;
        item.isEndPos = false;
        mGoToPosData[(*it).first] = item;
    }

    //ARCore::Inst()->getMovesStore()->initialize();

    userStiff = 0;
    userDump = 0;

    useUserStiff = false;
    useUserDump = false;

    this->isLog = false;
}

//на вход поступает время в микросекундах (10e-6 c)
void MoveController::stepPlay()
{
    long time = m_time.elapsed()*1e3;

    QTime t;
    t.start();

    if(ARCore::Inst()->getMovesStore()->m_moveID >= ARCore::Inst()->getMovesStore()->m_rowsNumber){goto StopPlay;}

    while(ARCore::Inst()->getMovesStore()->m_moves[ARCore::Inst()->getMovesStore()->m_moveID].Time <= time)
    {
        if(ARCore::Inst()->getMovesStore()->m_moveID >= ARCore::Inst()->getMovesStore()->m_rowsNumber){goto StopPlay;}

        //записываем значение в мотор и проверяем следующую команду
        int Number = ARCore::Inst()->getMovesStore()->m_moves[ARCore::Inst()->getMovesStore()->m_moveID].NumberChannel;
        int Angle = ARCore::Inst()->getMovesStore()->m_moves[ARCore::Inst()->getMovesStore()->m_moveID].Angle;

        int Stiff = 0;
        if(useUserStiff) Stiff = userStiff;
        else Stiff = ARCore::Inst()->getMovesStore()->m_moves[ARCore::Inst()->getMovesStore()->m_moveID].PIDs.Stiff;

        int Dump = 0;
        if(useUserDump) Dump = userDump;
        else Dump = ARCore::Inst()->getMovesStore()->m_moves[ARCore::Inst()->getMovesStore()->m_moveID].PIDs.Dump;

        int Torque = ARCore::Inst()->getMovesStore()->m_moves[ARCore::Inst()->getMovesStore()->m_moveID].PIDs.Torque;

        BufferController::Inst()->getBufferSend()->setMotorPGate( Number, Stiff );
        BufferController::Inst()->getBufferSend()->setMotorIGate( Number, Dump );
        BufferController::Inst()->getBufferSend()->setMotorDGate( Number, Torque );

        int CorrectionValue = MoveCorrector::Inst()->getCorrectValue(Number, ARCore::Inst()->getMovesStore()->m_moves[ARCore::Inst()->getMovesStore()->m_moveID].Time);
        //qDebug() << "Корректирующее "  << QString::number(CorrectionValue) << endl;

        BufferController::Inst()->getBufferSend()->setMotorAngle( Number, Angle + CorrectionValue);
        ARCore::Inst()->getMovesStore()->m_moveID++;

        if(ARCore::Inst()->getMovesStore()->m_moveID >= ARCore::Inst()->getMovesStore()->m_rowsNumber){goto StopPlay;}
    }

StopPlay:
    //qDebug() << "Time elapsed: " << QString::number(t.elapsed()) << "ms\n";

    //если время закончилось - останавливаем, переводим индекс команды на начало списка
    if(time > ARCore::Inst()->getMovesStore()->m_duration)
    {
        ARCore::Inst()->getMovesStore()->m_moveID = 0;
        //qDebug() << "Выполнена последняя строка"  << endl;

        LogMaster::Inst()->addLine("Выполнена последняя строка");
        emit PlayEnd();
        m_state = States::MoveStopping;
    }
}

void MoveController::startPlay()
{
    m_state = MoveStarting;
}

void MoveController::startingPlay()
{
    LogMaster::Inst()->addLine("MoveController::StartingPlay()");
    m_motors = ARCore::Inst()->getSettingStore()->GetMotors();
    for(auto it = m_motors->begin(); it != m_motors->end(); ++it)
    {
        int Number = (*it).second.getNumber();
        int Angle = BufferController::Inst()->getBufferRecv()->getMotorAngle( Number );
        int Stiff = (*it).second.getPIDGates()->getPGate();
        int Dump = (*it).second.getPIDGates()->getIGate();
        int Torque = (*it).second.getPIDGates()->getDGate();

        BufferController::Inst()->getBufferSend()->setMotorPGate( Number, Stiff );
        BufferController::Inst()->getBufferSend()->setMotorIGate( Number, Dump );
        BufferController::Inst()->getBufferSend()->setMotorDGate( Number, Torque );
        BufferController::Inst()->getBufferSend()->setMotorAngle( Number, Angle );
        BufferController::Inst()->getBufferSend()->motorTrace( Number );
    }
    ARCore::Inst()->getMovesStore()->m_moveID = 0;
    MoveCorrector::Inst()->setCurLine(0);

    m_state = States::MovePlay;
    m_time.start();
}

void MoveController::stopPlay()
{
    m_state = States::MoveStopping;
}

void MoveController::stoppingPlay()
{
    //переход в состояние после отправки последовательности
    m_motors = ARCore::Inst()->getSettingStore()->GetMotors();
    for(auto it = m_motors->begin(); it != m_motors->end(); ++it)
    {
        int Number = (*it).second.getNumber();
        int MotorAngle = BufferController::Inst()->getBufferRecv()->getMotorAngle( Number );
        int Stiff = (*it).second.getPIDGates()->getPGate();
        int Dump = (*it).second.getPIDGates()->getIGate();
        int Torque = (*it).second.getPIDGates()->getDGate();

        BufferController::Inst()->getBufferSend()->setMotorPGate( Number, Stiff );
        BufferController::Inst()->getBufferSend()->setMotorIGate( Number, Dump );
        BufferController::Inst()->getBufferSend()->setMotorDGate( Number, Torque );
        BufferController::Inst()->getBufferSend()->setMotorAngle( Number, MotorAngle );
        BufferController::Inst()->getBufferSend()->motorStopBrake( Number);
    }
    ARCore::Inst()->getMovesStore()->m_moveID = 0;
    m_state = States::NotWork;
}

void MoveController::stepPlayOnline()
{
    //char* recvPacket = new char(2400);
    //int size = 0;
    QByteArray datagram;
    while(!FrundTransiver::Inst()->recvData(datagram) && this->m_state == States::MovePlayOnline) ;
    if (this->m_state != States::MovePlayOnline) return;

    ARCore::Inst()->getMovesStore()->loadDataFromArray(datagram.data(), datagram.size());

    if(ARCore::Inst()->getMovesStore()->m_moveID >= ARCore::Inst()->getMovesStore()->m_rowsNumber){goto StopPlay;}

    while(ARCore::Inst()->getMovesStore()->m_moveID < ARCore::Inst()->getMovesStore()->m_rowsNumber)
    {
        //записываем значение в мотор и проверяем следующую команду
        int Number = ARCore::Inst()->getMovesStore()->m_moves[ARCore::Inst()->getMovesStore()->m_moveID].NumberChannel;
        int Angle = ARCore::Inst()->getMovesStore()->m_moves[ARCore::Inst()->getMovesStore()->m_moveID].Angle;

        int Stiff = 0;
        if(useUserStiff)
            Stiff = userStiff;
        else
            Stiff = ARCore::Inst()->getMovesStore()->m_moves[ARCore::Inst()->getMovesStore()->m_moveID].PIDs.Stiff;

        int Dump = 0;
        if(useUserDump)
            Dump = userDump;
        else
            Dump = ARCore::Inst()->getMovesStore()->m_moves[ARCore::Inst()->getMovesStore()->m_moveID].PIDs.Dump;

        int Torque = ARCore::Inst()->getMovesStore()->m_moves[ARCore::Inst()->getMovesStore()->m_moveID].PIDs.Torque;

        BufferController::Inst()->getBufferSend()->setMotorPGate( Number, Stiff );
        BufferController::Inst()->getBufferSend()->setMotorIGate( Number, Dump );
        BufferController::Inst()->getBufferSend()->setMotorDGate( Number, Torque );
        BufferController::Inst()->getBufferSend()->setMotorAngle( Number, Angle);
        BufferController::Inst()->getBufferSend()->motorTrace(Number);
        ARCore::Inst()->getMovesStore()->m_moveID++;

        if(ARCore::Inst()->getMovesStore()->m_moveID >= ARCore::Inst()->getMovesStore()->m_rowsNumber){goto StopPlay;}

        //qDebug() << "String number " << QString::number(MovesStorage::Inst()->m_moveID) << "have been read"  << endl;
    }
StopPlay:
        ARCore::Inst()->getMovesStore()->m_moveID = 0;
        //qDebug() << "Выполнен очередной шаг"  << endl;

        if(!this->isLog)
            RecordController::Inst()->AddRawData();

        RecordController::Inst()->getLastData(datagram.data());

        FrundTransiver::Inst()->sendData(datagram);
}

bool MoveController::openFile(std::string fileName)
{
    return ARCore::Inst()->getMovesStore()->openFile(fileName);
}

void MoveController::doStepWork()
{
    switch (m_state){
    case MoveStarting: //запуск отработки
    {
        startingPlay();
    }
        break;
    case MovePlay: //отработка команд
    {
        stepPlay();
    }
        break;
    case MovePlayOnline: //отработка команд
    {
        stepPlayOnline();
    }
        break;
    case MoveStopping: //остановка отработки
    {
        stoppingPlay();
    }
        break;
    case GoToAngleStarting: //запуск перехода мотора
    {
        startingGoToAngle();
    }
        break;
    case GoToAngle: //переход мотора в заданный угол
    {
        stepGoToAngle();
    }
        break;
    case GoToAngleStopping: //остановка перехода мотора
    {
        stoppingGoToAngle();
    }
        break;
    case GoPosStarting: //переход в начальную позицию
    {
        startingGoPos();
    }
        break;
    case GoToPos: //переход в начальную позицию
    {
        stepGoPos();
    }
        break;
    case GoPosStopping: //переход в начальную позицию
    {
        stoppingGoPos();
    }
        break;
    default:
        break;
    }
}

//Команды для перехода в исходную позицию
void MoveController::setPosData(int Number, int DestPos, int StartPos)
{
    mGoToPosData[Number].DestPos = DestPos;
    mGoToPosData[Number].StartPos = StartPos;
}

void MoveController::startGoPos(bool isCommand)
{
    m_state = States::GoPosStarting;
    mGoPosMode = isCommand;
}

void MoveController::startingGoPos()
{
    emit InitStart();
    int MaxDiff = 0;
    int i=0;

    m_motors = ARCore::Inst()->getSettingStore()->GetMotors();
    for(auto it = m_motors->begin();it != m_motors->end();++it)
    {
        int Number = (*it).first;
        int StartAngle = BufferController::Inst()->getBufferRecv()->getMotorAngle(Number);
        int DestAngle = mGoPosMode == true ? ARCore::Inst()->getMovesStore()->m_moves[i].Angle : 0;
        int DiffAngle = std::abs(DestAngle - StartAngle);
        MaxDiff = (DiffAngle > MaxDiff && (*it).second.getEnable()) ? DiffAngle : MaxDiff;

        setPosData(Number,DestAngle,StartAngle);

        BufferController::Inst()->getBufferSend()->setMotorAngle(Number, StartAngle);
        BufferController::Inst()->getBufferSend()->motorTrace(Number);
        i++;
    }

    long TimeMs = MaxDiff * 1000 / (ARCore::Inst()->getSettingStore()->GetDefaultSpeed()*100);
    TimeMs = TimeMs < 1000 ? 1000 : TimeMs;
    setupGoPos(TimeMs);
    mMotorExistCount = 21;
    m_state = States::GoToPos;
}

void MoveController::setupGoPos(long TimeToGo)
{
    int SendDelay = ARCore::Inst()->getSettingStore()->GetSendDelay();

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

void MoveController::stepGoPos()
{
    for(auto it = mGoToPosData.begin();it != mGoToPosData.end();++it)
    {
        bool IsFirst = (*it).second.DestPos <= (*it).second.CurrentPos
                && (*it).second.DestPos >= (*it).second.StartPos;
        bool IsSecond = (*it).second.DestPos >=(*it).second.CurrentPos
                && (*it).second.DestPos <=(*it).second.StartPos;

        if(IsFirst || IsSecond)
        {
            BufferController::Inst()->getBufferSend()->setMotorAngle((*it).first,(short)(*it).second.DestPos);
            BufferController::Inst()->getBufferSend()->motorStopBrake((*it).first);

            if(!(*it).second.isEndPos)
            {
                mMotorExistCount--;
                (*it).second.isEndPos = true;
            }
            qDebug() << QString::number((*it).first) << " Отправлено конечное положение " << QString::number((*it).second.DestPos) << endl;
        }
        else
        {
            BufferController::Inst()->getBufferSend()->setMotorAngle((*it).first,(short)(*it).second.CurrentPos);
            qDebug() << "Отправлено положение " << QString::number((*it).second.CurrentPos) << endl;
            (*it).second.CurrentPos += (*it).second.Step;
        }
    }

    //Если равно 0 то конец
    if(mMotorExistCount == 0)
    {
        qDebug() << "Достигнуто стартовое положение " << endl;
        m_state = States::GoPosStopping;
        //emit InitEnd();
    }
}

void MoveController::stopGoPos()
{
    m_state = States::GoPosStopping;
}

void MoveController::stoppingGoPos()
{
    for(auto it = m_motors->begin();it != m_motors->end();++it)
    {
        int Angle = BufferController::Inst()->getBufferRecv()->getMotorAngle((*it).first);

        BufferController::Inst()->getBufferSend()->setMotorAngle((*it).first, Angle);
        BufferController::Inst()->getBufferSend()->motorStopBrake((*it).first);
    }

    m_state = States::NotWork;
}

void MoveController::setIsLog(bool value)
{
    this->isLog = value;
}

//Конец команд для перехода в исходную позицию

//Команды для перехода в заданный угол (один двигатель)
void MoveController::startGoToAngle(int Number, int DestAngle, int Time)
{
    NewMotorNumber = Number;
    NewTimeToGo = Time;
    NewDestAngle = DestAngle;
    m_state = States::GoToAngleStarting;
}

void MoveController::startingGoToAngle()
{
    mMotorNumber = NewMotorNumber;
    mTimeToGo = NewTimeToGo;
    mDestAngle = NewDestAngle;
    mStartAngle = BufferController::Inst()->getBufferRecv()->getMotorAngle(mMotorNumber);

    int SendDelay = ARCore::Inst()->getSettingStore()->GetSendDelay();
    int diffAngle = mDestAngle - mStartAngle;//разница в градус*100
    mStep = (double)diffAngle / ((double)mTimeToGo/(double)SendDelay);//шаг в градус*100
    mCurrentAngle = mStartAngle;

    //включаем мотор
    BufferController::Inst()->getBufferSend()->setMotorAngle(mMotorNumber, mStartAngle);
    BufferController::Inst()->getBufferSend()->motorTrace(mMotorNumber);

    m_state = States::GoToAngle;
}

void MoveController::stepGoToAngle()
{
    bool IsFirst = mDestAngle <= mCurrentAngle && mDestAngle >= mStartAngle;
    bool IsSecond = mDestAngle >= mCurrentAngle && mDestAngle <= mStartAngle;

    if(IsFirst || IsSecond)
    {
        BufferController::Inst()->getBufferSend()->setMotorAngle(mMotorNumber,mDestAngle);
        BufferController::Inst()->getBufferSend()->motorStopBrake(mMotorNumber);
        qDebug() << "Отправлено конечное положение " << QString::number(mDestAngle) << endl;
        m_state = States::NotWork;
    }
    else
    {
        BufferController::Inst()->getBufferSend()->setMotorAngle(mMotorNumber,(short)mCurrentAngle);
        qDebug() << "Отправлено положение " << QString::number(mCurrentAngle) << endl;
        mCurrentAngle += mStep;
    }
}

void MoveController::stopGoToAngle()
{
    m_state = States::GoToAngleStopping;
}

void MoveController::stoppingGoToAngle()
{
    BufferController::Inst()->getBufferSend()->motorStop(mMotorNumber);
    m_state = States::NotWork;
}
//Конец команд для перехода в заданный угол (один двигатель)
