#ifndef MOVER_H
#define MOVER_H

#include <QObject>
#include <QThread>
#include <QDebug>
#include <QTimer>
#include <QTime>

#include <stdlib.h>
#include "MoveController.h"
#include "MotorController.h"

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

    void startGoToAngle(int number, int destAngle, int time);
    void stopGoToAngle();

    void openFile(QString fileName, bool mode);

signals:
    void PrepStart(); //Подготовка начата
    void PrepEnd(); //Подготовка закончена
    void MoveEnd(); //Движение закончено
    void playOnlineStart();
    void fileLoadStep(int percent);

private:
    //private variable
    QTimer *m_timer;
    int m_delay;
    bool isRunning;
    bool isRestart;
    bool isTransit;

private slots:
    void Move();
    void Calibrate();
};

#endif // MOVER_H
