#include "Mover.h"

Mover::Mover(QObject *parent) : QThread(parent)
{
    isRunning = false;
    isRestart = false;
    mDelay = 5;
    isPrep = false;
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

    mTimer = new QTimer;
    mTimer->setInterval(mDelay);
    connect(mTimer, SIGNAL(timeout()), SLOT(Move()), Qt::DirectConnection);
    mTimer->start();
    //Запускаем цикл обработки событий
    exec();
    //Завершился цикл обработки событий
    mTimer->stop();

    isRunning = false;
    if(isRestart) goto pointStart;
    //нить потока удалена
}

void Mover::StartMove()
{
    MoveController::Inst()->StartPlay();
    isPrep = true;
    emit PrepStart();

    if( !isRunning )
        start();
}

void Mover::StopMove()
{
    MoveController::Inst()->StopPlay();
    isPrep = false;
}

void Mover::StartGoToPos(bool isNullPos)
{
    MoveController::Inst()->StartGoPos(!isNullPos);
    isPrep = true;
    if( !isRunning )
        start();

}

void Mover::StopGoToPos()
{
    MoveController::Inst()->StopGoPos();
    isPrep = false;
}

void Mover::Move()
{
    MoveController::Inst()->DoStepWork();
    //Если закончилось выполнение движения
    if(MoveController::Inst()->getState() == States::NotWork)
    {
        emit MoveEnd();
        exit();
    }

    if(MoveController::Inst()->getState() == States::GoPosStopping && isPrep)
    {
        emit PrepEnd();
        isPrep = false;
    }
}
