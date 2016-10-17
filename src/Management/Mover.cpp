#include "Mover.h"

Mover::Mover(QObject *parent) : QThread(parent)
{
    isRunning = false;
    isRestart = false;
    m_delay = SettingsStorage::Inst()->GetSendDelay();
    isTransit = false;
}

Mover::~Mover()
{

}

void Mover::run()
{
    //нить потока создана
pointStart:
    isRestart = false;
    isRunning = true;

    m_timer = new QTimer;
    m_timer->setInterval(m_delay);
    connect(m_timer, SIGNAL(timeout()), SLOT(Move()), Qt::DirectConnection);
    m_timer->start();
    //Запускаем цикл обработки событий
    exec();
    //Завершился цикл обработки событий
    m_timer->stop();

    isRunning = false;
    if(isRestart) goto pointStart;
    //нить потока удалена
}

void Mover::startMove()
{
    MoveController::Inst()->startMove();
    if( !isRunning ) start();
}

void Mover::startMoveOnline()
{
    MoveController::Inst()->startMoveFrund();
    if( !isRunning ) start();
    emit playOnlineStart();
    RecordController::Inst()->StartWrite();
    MovesStorage::Inst()->resetErrors();
}

void Mover::stopMove()
{
    MoveController::Inst()->stopMove();
    qDebug() << "Count Errors = " << QString::number(MovesStorage::Inst()->getCountErrors()) << endl;
    isTransit = false;
}

void Mover::startGoToPos(bool isNullPos)
{
    MoveController::Inst()->startPositionTransit(!isNullPos);
    isTransit = true;
    if( !isRunning ) start();
}

void Mover::stopGoToPos()
{
    MoveController::Inst()->stopPositionTransit();
    isTransit = false;
}

void Mover::startGoToAngle(int number, int destAngle, int time)
{
    MoveController::Inst()->startMotorTransit(number, destAngle, time);
    if( !isRunning ) start();
}

void Mover::openFile(QString fileName, bool mode)
{
    //TODO: дописать MoveController::OpenFile();...
}

void Mover::Move()
{
    MoveController::Inst()->doStepWork();
    //Если закончилось выполнение движения
    if(MoveController::Inst()->getState() == MoveController::NOT_WORK)
    {
        LogMaster::Inst()->addLine("Mover stop");
        exit();
        if(isTransit)
        {
            isTransit = false; emit PrepEnd();
        }
        else
        {
            emit MoveEnd();
        }
    }
}

void Mover::Calibrate()
{
//    MoveController::Inst()->doStepWork();
//    //Если закончилось выполнение движения
//    if(MoveController::Inst()->getState() == States::NotWork)
//    {
//        exit();
//        if(isTransit)
//        {
//            isTransit = false; emit PrepEnd();
//        }
//        else
//        {
//            emit MoveEnd();
//        }
//    }
}
