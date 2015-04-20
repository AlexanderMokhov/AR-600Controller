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

class ThreadSend :  public QThread
{
    Q_OBJECT
private:
    QUdpSocket      *mUdpSocketSender;
    MBWrite         *mSendBuffer;
    QTimer          *mTimerSend;
    int             mPort;
    QString         mHost;
    int             mSendDelay;
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
