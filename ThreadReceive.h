#ifndef THREADRECEIVE_H
#define THREADRECEIVE_H

#include <QObject>
#include <QThread>
#include <QUdpSocket>
#include "BufferController.h"
#include "ConfigController.h"
#include <QDebug>
#include <QTime>

class ThreadReceive : public QThread
{
    Q_OBJECT
private:
    QUdpSocket      *mUdpSocketResiver;
    ReadBuffer          *mReceiveBuffer;
    int             mReceivePort;

    QTime *timepres;
public:
    explicit ThreadReceive(QObject *parent = 0);
    ~ThreadReceive();
    void run();
    void ConnectSocket();
    void DisconnectSocket();
private slots:
    void ProcessPendingDatagrams();
signals:
    void ReadyData();
};

#endif // THREADRECEIVE_H
