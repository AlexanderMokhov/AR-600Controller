#ifndef MOVER_H
#define MOVER_H

#include <QObject>
#include <QThread>
#include <QDebug>
#include <QTimer>
#include <QTime>

#include <stdlib.h>

class Mover : public QThread
{
    Q_OBJECT
private:
    QTimer *mTimer;

    bool isRunning;
    bool isRestart;

public:
    explicit Mover(QObject *parent = 0);
    ~Mover();
    void run();

private slots:

signals:
};

#endif // MOVER_H
