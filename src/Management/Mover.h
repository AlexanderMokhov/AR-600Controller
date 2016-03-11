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
private:
    QTimer *m_timer;
    int m_delay;
    bool isRunning;
    bool isRestart;

    bool isPrep;

public:
    explicit Mover(QObject *parent = 0);
    ~Mover();
    void run();

    void startMove();
    void startMoveOnline();
    void stopMove();

    void startGoToPos( bool isNullPos );
    void stopGoToPos();

private slots:
    void Move();

signals:
    void PrepStart(); //Подготовка начата
    void PrepEnd(); //Подготовка закончена
    void MoveEnd(); //Движение закончено
};

#endif // MOVER_H
