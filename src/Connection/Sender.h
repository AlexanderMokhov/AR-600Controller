#ifndef SENDER_H
#define SENDER_H

#include <QObject>
#include <QThread>
#include <QUdpSocket>
#include <QTime>
#include <QDebug>
#include <QTimer>

#include <mutex>
#include <stdlib.h>

#include "Buffers/BufferController.h"
#include "Management/ConfigController.h"
#include "Management/MoveController.h"

class Sender : public QThread
{
    Q_OBJECT
private:
    QUdpSocket *mUdpSocketSender;
    BufferSend *mSendBuffer;
    QTimer *mTimerSend;
    std::mutex *mLocker;
    QTime *mTime;

    QString         mHost;
    int             mSendPort;
    int             mSendDelay;

    volatile bool isRunning;
    void PrintConnectionState();
public:
    explicit Sender( QObject *parent = 0 );
    ~Sender();
    void run();
    void Connect();
    void Disconnect();
private slots:
    void SendDatagram();
};

#endif // SENDER_H
