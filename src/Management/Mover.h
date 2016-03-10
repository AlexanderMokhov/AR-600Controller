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
    enum StatesMover { playFrund, playMove };

    Q_OBJECT
private:
    QTimer *mTimer;
    int mDelay;
    bool isRunning;
    bool isRestart;

    bool isPrep;

    StatesMover mState;

public:
    explicit Mover(QObject *parent = 0);
    ~Mover();
    void run();

    void StartMove();
    void StartMoveOnline();
    void StopMove();

    void StartGoToPos( bool isNullPos );
    void StopGoToPos();

private slots:
    void Move();

signals:
    void PrepStart(); //Подготовка начата
    void PrepEnd(); //Подготовка закончена
    void MoveEnd(); //Движение закончено
};

#endif // MOVER_H
