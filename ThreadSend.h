#ifndef THREADSEND_H
#define THREADSEND_H

#include <QObject>
#include <QThread>
#include <QUdpSocket>
#include "BufferController.h"
#include "ConfigController.h"
#include "CommandController.h"
#include <QDebug>
#include <QTimer>
#include <mutex>
#include <stdlib.h>
#include <QTime>
class ThreadSend :  public QThread
{
    Q_OBJECT
private:
    QUdpSocket      *mUdpSocketSender;
    WriteBuffer         *mSendBuffer;
    QTimer          *mTimerSend;

    QString         mHost;
    int             mSendPort;
    int             mSendDelay;

    std::mutex *    mLocker;

    QTime *timepres;
public:
    explicit ThreadSend(QObject *parent = 0);
    ~ThreadSend();
    void run();
    void ConnectSocket();
    void DisconnectSocket();

public slots:
    void SendDatagram();
};

#endif // THREADSEND_H
