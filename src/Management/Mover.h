#ifndef MOVER_H
#define MOVER_H

#include <QObject>
#include <QThread>
#include <QDebug>
#include <QTimer>
#include <QTime>

#include <stdlib.h>
#include "MoveController.h"
#include "MoveControllerFrund.h"

class Mover : public QThread
{
    Q_OBJECT
public:
    //public methods
    explicit Mover(QObject *parent = 0);
    ~Mover();
    void run();

    void startMove();
    void startMoveOnline();
    void stopMove();

    void startGoToPos( bool isNullPos );
    void stopGoToPos();

signals:
    void PrepStart(); //Подготовка начата
    void PrepEnd(); //Подготовка закончена
    void MoveEnd(); //Движение закончено
    void playOnlineStart();

private:
    //private variable
    QTimer *m_timer;
    int m_delay;
    bool isRunning;
    bool isRestart;
    bool isPrep;

private slots:
    void Move();
};

#endif // MOVER_H
