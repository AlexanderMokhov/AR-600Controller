#ifndef RECEIVER_H
#define RECEIVER_H

#include <QObject>
#include <QThread>
#include <QUdpSocket>
#include <QDebug>
#include <QTime>

#include "Buffers/BufferController.h"
#include "Management/ConfigController.h"

#include "Libs/Sockets/Socket.h"

class Receiver : public QThread
{
    Q_OBJECT
private:

    SOCKET ReceiveSocket; // 01.02.2016

    QUdpSocket *mUdpSocketResiver;
    BufferReceive *mReceiveBuffer;
    QTime *mTime;
    void PrintConnectionState();
    volatile bool isRunning;
public:
    explicit Receiver( QObject *parent = 0 );
    ~Receiver();
    void run();
    void Connect();
    void Disconnect();
private slots:
    void ProcessPendingDatagrams();
signals:
    void ReadyData();
};

#endif // RECEIVER_H
