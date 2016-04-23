#include "MoveController.h"

MoveController * MoveController::m_inst = 0;

MoveController::MoveController()
{
    m_state = States::NOT_WORK; //ничего не делаем

    m_positionTransitData.clear();

    m_motors = SettingsStorage::Inst()->GetMotors();
    for(auto it = m_motors->begin(); it != m_motors->end(); ++it)
    {
        PosData item;
        item.CurrentPos = 0;
        item.DestPos = 0;
        item.StartPos = 0;
        item.Step = 0;
        item.isEndPos = false;
        m_positionTransitData[(*it).first] = item;
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
void MoveController::stepMove()
{
    endTime = std::chrono::high_resolution_clock::now();

    long elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>
            (endTime - startTime).count();

    //long time = m_time.elapsed()*1e3;

    if(MovesStorage::Inst()->m_moveID >= MovesStorage::Inst()->m_rowsNumber){goto StopPlay;}

    while(MovesStorage::Inst()->m_moves[MovesStorage::Inst()->m_moveID].Time <= elapsedTime)
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
    if(elapsedTime > MovesStorage::Inst()->m_duration)
    {
        MovesStorage::Inst()->m_moveID = 0;

        LogMaster::Inst()->addLine("Выполнена последняя строка");
        m_state = States::END_MOVE;
    }
}

void MoveController::startMove()
{
    m_state = BEGIN_MOVE;
}

void MoveController::startingMove()
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

    m_state = States::STEP_MOVE;
    startTime = std::chrono::high_resolution_clock::now();
    //m_time.start();
}

void MoveController::stopMove()
{
    m_state = States::END_MOVE;
}

void MoveController::stoppingMove()
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
    m_state = States::NOT_WORK;
}

void MoveController::stepMoveFrund()
{
    //char* recvPacket = new char(2400);
    //int size = 0;
    QByteArray datagram;
    while(!FrundTransiver::Inst()->recvData(datagram) && this->m_state == States::STEP_MOVE_FRUND) ;
    if (this->m_state != States::STEP_MOVE_FRUND) return;

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
            RecordController::Inst()->addRawData();

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
    case BEGIN_MOVE: //запуск отработки
        startingMove();
        break;
    case STEP_MOVE: //отработка команд
        stepMove();
        break;
    case STEP_MOVE_FRUND: //отработка команд
        stepMoveFrund();
        break;
    case END_MOVE: //остановка отработки
        stoppingMove();
        break;
    case BEGIN_MOTOR_TRANSIT: //запуск перехода мотора
        startingMotorTransit();
        break;
    case STEP_MOTOR_TRANSIT: //переход мотора в заданный угол
        stepMotorTransit();
        break;
    case END_MOTOR_TRANSIT: //остановка перехода мотора
        stoppingMotorTransit();
        break;
    case BEGIN_POSITION_TRANSIT: //переход в начальную позицию
        startingPositionTransit();
        break;
    case STEP_POSITION_TRANSIT: //переход в начальную позицию
        stepPositionTransit();
        break;
    case END_POSITION_TRANSIT: //переход в начальную позицию
        stoppingPositionTransit();
        break;
    default:
        break;
    }
}

//Команды для перехода в исходную позицию
void MoveController::setPositionData(int Number, int DestPos, int StartPos)
{
    m_positionTransitData[Number].DestPos = DestPos;
    m_positionTransitData[Number].StartPos = StartPos;
}

void MoveController::startPositionTransit(bool isCommand)
{
    m_state = States::BEGIN_POSITION_TRANSIT;
    m_positionTransitMode = isCommand;
}

void MoveController::startingPositionTransit()
{
    int MaxDiff = 0;
    int i = 0;

    m_motors = SettingsStorage::Inst()->GetMotors();
    for(auto it = m_motors->begin();it != m_motors->end();++it)
    {
        int Number = (*it).first;
        int StartAngle = ARPacketManager::Inst()->getPacketRecv()->getMotorAngle(Number);
        int DestAngle = m_positionTransitMode == true ?
                    MovesStorage::Inst()->m_moves[i].Angle :
                    m_startPosition[Number];

        int DiffAngle = std::abs(DestAngle - StartAngle);
        MaxDiff = (DiffAngle > MaxDiff && (*it).second.getEnable()) ? DiffAngle : MaxDiff;

        setPositionData(Number, DestAngle, StartAngle);

        ARPacketManager::Inst()->getPacketSend()->setMotorAngle(Number, StartAngle);
        ARPacketManager::Inst()->getPacketSend()->motorTrace(Number);
        i++;
    }

    long TimeMs = MaxDiff * 1000 / (SettingsStorage::Inst()->GetDefaultSpeed()*100);
    TimeMs = TimeMs < 1000 ? 1000 : TimeMs;
    setupPositionTransit(TimeMs);
    m_motorExistCount = 21;
    m_state = States::STEP_POSITION_TRANSIT;
}

void MoveController::setupPositionTransit(long TimeToGo)
{
    int SendDelay = SettingsStorage::Inst()->GetSendDelay();

    for(auto it = m_positionTransitData.begin();it != m_positionTransitData.end();++it)
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

void MoveController::stepPositionTransit()
{
    for(auto it = m_positionTransitData.begin();it != m_positionTransitData.end();++it)
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
                m_motorExistCount--;
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
    if(m_motorExistCount == 0)
    {
        LogMaster::Inst()->addLine("Достигнуто стартовое положение ");
        m_state = States::END_POSITION_TRANSIT;
    }
}

void MoveController::stopPositionTransit()
{
    m_state = States::END_POSITION_TRANSIT;
}

void MoveController::stoppingPositionTransit()
{
    for(auto it = m_motors->begin();it != m_motors->end();++it)
    {
        int Angle = ARPacketManager::Inst()->getPacketRecv()->getMotorAngle((*it).first);

        ARPacketManager::Inst()->getPacketSend()->setMotorAngle((*it).first, Angle);
        ARPacketManager::Inst()->getPacketSend()->motorStopBrake((*it).first);
    }

    m_state = States::NOT_WORK;
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
void MoveController::startMotorTransit(int Number, int DestAngle, int Time)
{
    LogMaster::Inst()->addLine("MoveController::startGoToAngle()");
    newMotorNumber = Number;
    newTimeToTransit = Time;
    newDestAngle = DestAngle;
    m_state = States::BEGIN_MOTOR_TRANSIT;
}

void MoveController::startingMotorTransit()
{
    LogMaster::Inst()->addLine("MoveController::startingGoToAngle()");

    m_motorNumber = newMotorNumber;
    m_timeToTransit = newTimeToTransit;
    m_destAngle = newDestAngle;
    m_startAngle = ARPacketManager::Inst()->getPacketRecv()->getMotorAngle(m_motorNumber);

    int SendDelay = SettingsStorage::Inst()->GetSendDelay();
    int diffAngle = m_destAngle - m_startAngle;//разница в градус*100
    m_stepAngle = (double)diffAngle / ((double)m_timeToTransit/(double)SendDelay);//шаг в градус*100
    m_currentAngle = m_startAngle;

    //включаем мотор
    ARPacketManager::Inst()->getPacketSend()->setMotorAngle(m_motorNumber, m_startAngle);
    ARPacketManager::Inst()->getPacketSend()->motorTrace(m_motorNumber);

    m_state = States::STEP_MOTOR_TRANSIT;
}

void MoveController::stepMotorTransit()
{
    LogMaster::Inst()->addLine("MoveController::stepGoToAngle()");

    bool IsFirst = m_destAngle <= m_currentAngle && m_destAngle >= m_startAngle;
    bool IsSecond = m_destAngle >= m_currentAngle && m_destAngle <= m_startAngle;

    if(IsFirst || IsSecond)
    {
        ARPacketManager::Inst()->getPacketSend()->setMotorAngle(m_motorNumber,m_destAngle);
        ARPacketManager::Inst()->getPacketSend()->motorStopBrake(m_motorNumber);
        LogMaster::Inst()->addLine("Отправлено конечное положение " + std::to_string(m_destAngle));
        m_state = States::NOT_WORK;
    }
    else
    {
        ARPacketManager::Inst()->getPacketSend()->setMotorAngle(m_motorNumber,(short)m_currentAngle);
        LogMaster::Inst()->addLine("Отправлено положение " + std::to_string(m_currentAngle));
        m_currentAngle += m_stepAngle;
    }
}

void MoveController::stopMotorTransit()
{
    LogMaster::Inst()->addLine("MoveController::stopGoToAngle()");
    m_state = States::END_MOTOR_TRANSIT;
}

void MoveController::stoppingMotorTransit()
{
    ARPacketManager::Inst()->getPacketSend()->motorStop(m_motorNumber);
    m_state = States::NOT_WORK;
}
//Конец команд для перехода в заданный угол (один двигатель)
