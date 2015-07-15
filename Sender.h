#ifndef SENDER_H
#define SENDER_H

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

class Sender : public QThread
{
    Q_OBJECT
private:
    QUdpSocket      *mUdpSocketSender;
    WriteBuffer     *mSendBuffer;
    QTimer          *mTimerSend;
    std::mutex      *mLocker;
    QTime           *mTime;

    QString         mHost;
    int             mSendPort;
    int             mSendDelay;

    bool isRunning;
    void PrintConnectionState();
public:
    explicit Sender(QObject *parent = 0);
    ~Sender();
    void run();
    void Connect();
    void Disconnect();
private slots:
    void SendDatagram();
};

#endif // SENDER_H
