#include "MoveController.h"

MoveController * MoveController::m_inst = 0;

MoveController::MoveController()
{
    m_state = States::NotWork; //ничего не делаем

    mGoToPosData.clear();

    m_motors = SettingsStorage::Inst()->GetMotors();
    for(auto it = m_motors->begin(); it != m_motors->end(); ++it)
    {
        PosData item;
        item.CurrentPos = 0;
        item.DestPos = 0;
        item.StartPos = 0;
        item.Step = 0;
        item.isEndPos = false;
        mGoToPosData[(*it).first] = item;
        m_startPosition[(*it).second.getNumber()] = 0;
    }

    MovesStorage::Inst()->Initialize();

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

    if(MovesStorage::Inst()->m_moveID >= MovesStorage::Inst()->m_rowsNumber){goto StopPlay;}

    while(MovesStorage::Inst()->m_moves[MovesStorage::Inst()->m_moveID].Time <= time)
    {
        if(MovesStorage::Inst()->m_moveID >= MovesStorage::Inst()->m_rowsNumber){goto StopPlay;}

        //записываем значение в мотор и проверяем следующую команду
        int Number = MovesStorage::Inst()->m_moves[MovesStorage::Inst()->m_moveID].NumberChannel;
        int Angle = MovesStorage::Inst()->m_moves[MovesStorage::Inst()->m_moveID].Angle;

        int Stiff = 0;
        if(useUserStiff) Stiff = userStiff;
        else Stiff = MovesStorage::Inst()->m_moves[MovesStorage::Inst()->m_moveID].PIDs.Stiff;

        int Dump = 0;
        if(useUserDump) Dump = userDump;
        else Dump = MovesStorage::Inst()->m_moves[MovesStorage::Inst()->m_moveID].PIDs.Dump;

        int Torque = MovesStorage::Inst()->m_moves[MovesStorage::Inst()->m_moveID].PIDs.Torque;

        ARPacketManager::Inst()->getPacketSend()->setMotorPGate( Number, Stiff );
        ARPacketManager::Inst()->getPacketSend()->setMotorIGate( Number, Dump );
        ARPacketManager::Inst()->getPacketSend()->setMotorDGate( Number, Torque );

        int CorrectionValue = MoveCorrector::Inst()->getCorrectValue(Number, MovesStorage::Inst()->m_moves[MovesStorage::Inst()->m_moveID].Time);
        //LogMaster::Inst()->addLine("Корректирующее " + std::to_string(CorrectionValue));

        ARPacketManager::Inst()->getPacketSend()->setMotorAngle( Number, Angle + CorrectionValue);
        MovesStorage::Inst()->m_moveID++;

        if(MovesStorage::Inst()->m_moveID >= MovesStorage::Inst()->m_rowsNumber){goto StopPlay;}
    }

StopPlay:
    //если время закончилось - останавливаем, переводим индекс команды на начало списка
    if(time > MovesStorage::Inst()->m_duration)
    {
        MovesStorage::Inst()->m_moveID = 0;

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
    m_motors = SettingsStorage::Inst()->GetMotors();
    for(auto it = m_motors->begin(); it != m_motors->end(); ++it)
    {
        int Number = (*it).second.getNumber();
        int Angle = ARPacketManager::Inst()->getPacketRecv()->getMotorAngle( Number );
        int Stiff = (*it).second.getPIDGates()->getPGate();
        int Dump = (*it).second.getPIDGates()->getIGate();
        int Torque = (*it).second.getPIDGates()->getDGate();

        ARPacketManager::Inst()->getPacketSend()->setMotorPGate( Number, Stiff );
        ARPacketManager::Inst()->getPacketSend()->setMotorIGate( Number, Dump );
        ARPacketManager::Inst()->getPacketSend()->setMotorDGate( Number, Torque );
        ARPacketManager::Inst()->getPacketSend()->setMotorAngle( Number, Angle );
        ARPacketManager::Inst()->getPacketSend()->motorTrace( Number );
    }
    MovesStorage::Inst()->m_moveID = 0;
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
    m_motors = SettingsStorage::Inst()->GetMotors();
    for(auto it = m_motors->begin(); it != m_motors->end(); ++it)
    {
        int Number = (*it).second.getNumber();
        int MotorAngle = ARPacketManager::Inst()->getPacketRecv()->getMotorAngle( Number );
        int Stiff = (*it).second.getPIDGates()->getPGate();
        int Dump = (*it).second.getPIDGates()->getIGate();
        int Torque = (*it).second.getPIDGates()->getDGate();

        ARPacketManager::Inst()->getPacketSend()->setMotorPGate( Number, Stiff );
        ARPacketManager::Inst()->getPacketSend()->setMotorIGate( Number, Dump );
        ARPacketManager::Inst()->getPacketSend()->setMotorDGate( Number, Torque );
        ARPacketManager::Inst()->getPacketSend()->setMotorAngle( Number, MotorAngle );
        ARPacketManager::Inst()->getPacketSend()->motorStopBrake( Number);
    }
    MovesStorage::Inst()->m_moveID = 0;
    m_state = States::NotWork;
}

void MoveController::stepPlayOnline()
{
    //char* recvPacket = new char(2400);
    //int size = 0;
    QByteArray datagram;
    while(!FrundTransiver::Inst()->recvData(datagram) && this->m_state == States::MovePlayOnline) ;
    if (this->m_state != States::MovePlayOnline) return;

    MovesStorage::Inst()->loadDataFromArray(datagram.data(), datagram.size());

    if(MovesStorage::Inst()->m_moveID >= MovesStorage::Inst()->m_rowsNumber){goto StopPlay;}

    while(MovesStorage::Inst()->m_moveID < MovesStorage::Inst()->m_rowsNumber)
    {
        //записываем значение в мотор и проверяем следующую команду
        int Number = MovesStorage::Inst()->m_moves[MovesStorage::Inst()->m_moveID].NumberChannel;
        int Angle = MovesStorage::Inst()->m_moves[MovesStorage::Inst()->m_moveID].Angle;

        int Stiff = 0;
        if(useUserStiff)
            Stiff = userStiff;
        else
            Stiff = MovesStorage::Inst()->m_moves[MovesStorage::Inst()->m_moveID].PIDs.Stiff;

        int Dump = 0;
        if(useUserDump)
            Dump = userDump;
        else
            Dump = MovesStorage::Inst()->m_moves[MovesStorage::Inst()->m_moveID].PIDs.Dump;

        int Torque = MovesStorage::Inst()->m_moves[MovesStorage::Inst()->m_moveID].PIDs.Torque;

        ARPacketManager::Inst()->getPacketSend()->setMotorPGate( Number, Stiff );
        ARPacketManager::Inst()->getPacketSend()->setMotorIGate( Number, Dump );
        ARPacketManager::Inst()->getPacketSend()->setMotorDGate( Number, Torque );
        ARPacketManager::Inst()->getPacketSend()->setMotorAngle( Number, Angle);
        ARPacketManager::Inst()->getPacketSend()->motorTrace(Number);
        MovesStorage::Inst()->m_moveID++;

        if(MovesStorage::Inst()->m_moveID >= MovesStorage::Inst()->m_rowsNumber){goto StopPlay;}

        //LogMaster::Inst()->addLine("Строка [х]" + std::to_string(MovesStorage::Inst()->m_moveID) + "] была прочитана");
    }
StopPlay:
        MovesStorage::Inst()->m_moveID = 0;
        //LogMaster::Inst()->addLine("Выполнен очередной шаг");

        if(!this->isLog)
            RecordController::Inst()->AddRawData();

        RecordController::Inst()->getLastData(datagram.data());

        FrundTransiver::Inst()->sendData(datagram);
}

bool MoveController::openFile(std::string fileName)
{
    return MovesStorage::Inst()->openFile(fileName);
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
    int i = 0;

    m_motors = SettingsStorage::Inst()->GetMotors();
    for(auto it = m_motors->begin();it != m_motors->end();++it)
    {
        int Number = (*it).first;
        int StartAngle = ARPacketManager::Inst()->getPacketRecv()->getMotorAngle(Number);
        int DestAngle = mGoPosMode == true ?
                    MovesStorage::Inst()->m_moves[i].Angle :
                    m_startPosition[Number];

        int DiffAngle = std::abs(DestAngle - StartAngle);
        MaxDiff = (DiffAngle > MaxDiff && (*it).second.getEnable()) ? DiffAngle : MaxDiff;

        setPosData(Number, DestAngle, StartAngle);

        ARPacketManager::Inst()->getPacketSend()->setMotorAngle(Number, StartAngle);
        ARPacketManager::Inst()->getPacketSend()->motorTrace(Number);
        i++;
    }

    long TimeMs = MaxDiff * 1000 / (SettingsStorage::Inst()->GetDefaultSpeed()*100);
    TimeMs = TimeMs < 1000 ? 1000 : TimeMs;
    setupGoPos(TimeMs);
    mMotorExistCount = 21;
    m_state = States::GoToPos;
}

void MoveController::setupGoPos(long TimeToGo)
{
    int SendDelay = SettingsStorage::Inst()->GetSendDelay();

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
            ARPacketManager::Inst()->getPacketSend()->setMotorAngle((*it).first,(short)(*it).second.DestPos);
            ARPacketManager::Inst()->getPacketSend()->motorStopBrake((*it).first);

            if(!(*it).second.isEndPos)
            {
                mMotorExistCount--;
                (*it).second.isEndPos = true;
            }
            //LogMaster::Inst()->addLine("Отправлено конечное положение " + std::to_string((*it).second.DestPos));
        }
        else
        {
            ARPacketManager::Inst()->getPacketSend()->setMotorAngle((*it).first,(short)(*it).second.CurrentPos);
            //LogMaster::Inst()->addLine("Отправлено положение " + std::to_string((*it).second.CurrentPos));
            (*it).second.CurrentPos += (*it).second.Step;
        }
    }

    //Если равно 0 то конец
    if(mMotorExistCount == 0)
    {
        LogMaster::Inst()->addLine("Достигнуто стартовое положение ");
        m_state = States::GoPosStopping;
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
        int Angle = ARPacketManager::Inst()->getPacketRecv()->getMotorAngle((*it).first);

        ARPacketManager::Inst()->getPacketSend()->setMotorAngle((*it).first, Angle);
        ARPacketManager::Inst()->getPacketSend()->motorStopBrake((*it).first);
    }

    m_state = States::NotWork;
}

void MoveController::setIsLog(bool value)
{
    this->isLog = value;
}

void MoveController::setCurPosAsDefault()
{
    for(auto it = m_motors->begin();it != m_motors->end();++it)
    {
        int Angle = ARPacketManager::Inst()->getPacketRecv()->getMotorAngle((*it).first);
        m_startPosition[(*it).second.getNumber()] = Angle;
    }
}

//Конец команд для перехода в исходную позицию

//Команды для перехода в заданный угол (один двигатель)
void MoveController::startGoToAngle(int Number, int DestAngle, int Time)
{
    LogMaster::Inst()->addLine("MoveController::startGoToAngle()");
    NewMotorNumber = Number;
    NewTimeToGo = Time;
    NewDestAngle = DestAngle;
    m_state = States::GoToAngleStarting;
}

void MoveController::startingGoToAngle()
{
    LogMaster::Inst()->addLine("MoveController::startingGoToAngle()");

    mMotorNumber = NewMotorNumber;
    mTimeToGo = NewTimeToGo;
    mDestAngle = NewDestAngle;
    mStartAngle = ARPacketManager::Inst()->getPacketRecv()->getMotorAngle(mMotorNumber);

    int SendDelay = SettingsStorage::Inst()->GetSendDelay();
    int diffAngle = mDestAngle - mStartAngle;//разница в градус*100
    mStep = (double)diffAngle / ((double)mTimeToGo/(double)SendDelay);//шаг в градус*100
    mCurrentAngle = mStartAngle;

    //включаем мотор
    ARPacketManager::Inst()->getPacketSend()->setMotorAngle(mMotorNumber, mStartAngle);
    ARPacketManager::Inst()->getPacketSend()->motorTrace(mMotorNumber);

    m_state = States::GoToAngle;
}

void MoveController::stepGoToAngle()
{
    LogMaster::Inst()->addLine("MoveController::stepGoToAngle()");

    bool IsFirst = mDestAngle <= mCurrentAngle && mDestAngle >= mStartAngle;
    bool IsSecond = mDestAngle >= mCurrentAngle && mDestAngle <= mStartAngle;

    if(IsFirst || IsSecond)
    {
        ARPacketManager::Inst()->getPacketSend()->setMotorAngle(mMotorNumber,mDestAngle);
        ARPacketManager::Inst()->getPacketSend()->motorStopBrake(mMotorNumber);
        LogMaster::Inst()->addLine("Отправлено конечное положение " + std::to_string(mDestAngle));
        m_state = States::NotWork;
    }
    else
    {
        ARPacketManager::Inst()->getPacketSend()->setMotorAngle(mMotorNumber,(short)mCurrentAngle);
        LogMaster::Inst()->addLine("Отправлено положение " + std::to_string(mCurrentAngle));
        mCurrentAngle += mStep;
    }
}

void MoveController::stopGoToAngle()
{
    LogMaster::Inst()->addLine("MoveController::stopGoToAngle()");
    m_state = States::GoToAngleStopping;
}

void MoveController::stoppingGoToAngle()
{
    ARPacketManager::Inst()->getPacketSend()->motorStop(mMotorNumber);
    m_state = States::NotWork;
}
//Конец команд для перехода в заданный угол (один двигатель)
