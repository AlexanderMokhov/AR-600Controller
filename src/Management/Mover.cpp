#include "Mover.h"

Mover::Mover(QObject *parent) : QThread(parent)
{
    isRunning = false;
    isRestart = false;
    m_delay = SettingsStorage::Inst()->GetSendDelay();
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
    MoveController::Inst()->startPlay();
    if( !isRunning ) start();
}

void Mover::startMoveOnline()
{
    MoveController::Inst()->startPlayOnline();
    if( !isRunning ) start();
    emit playOnlineStart();
    RecordController::Inst()->StartWrite();
    MovesStorage::Inst()->resetErrors();
}

void Mover::stopMove()
{
    MoveController::Inst()->stopPlay();
    qDebug() << "Count Errors = " << QString::number(MovesStorage::Inst()->getCountErrors()) << endl;
    isPrep = false;
}

void Mover::startGoToPos(bool isNullPos)
{
    MoveController::Inst()->startGoPos(!isNullPos);
    isPrep = true;
    if( !isRunning ) start();
}

void Mover::stopGoToPos()
{
    MoveController::Inst()->stopGoPos();
    isPrep = false;
}

void Mover::openFile(QString fileName, bool mode)
{
    //TODO: дописать MoveController::OpenFile();...
}

void Mover::Move()
{
    MoveController::Inst()->doStepWork();
    //Если закончилось выполнение движения
    if(MoveController::Inst()->getState() == States::NotWork)
    {
        exit();
        if(isPrep)
        {
            isPrep = false; emit PrepEnd();
        }
        else
        {
            emit MoveEnd();
        }
    }
}
