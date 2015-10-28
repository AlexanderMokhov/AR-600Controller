#include "Mover.h"

Mover::Mover(QObject *parent) : QThread(parent)
{
    isRunning = false;
    isRestart = false;
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

    mTimer->start();
    //Запускаем цикл обработки событий
    exec();
    //Завершился цикл обработки событий
    mTimer->stop();

    isRunning = false;
    if(isRestart) goto pointStart;
    //нить потока удалена
}
