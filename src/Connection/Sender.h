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
#include "Management/SettingsStorage.h"
#include "Management/MoveController.h"

//#include "Libs/Sockets/Socket.h"

class Sender : public QThread
{
    Q_OBJECT
private:

//    SOCKET SendSocket; // 01.02.2016
//    sockaddr_in dest_addr;
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
