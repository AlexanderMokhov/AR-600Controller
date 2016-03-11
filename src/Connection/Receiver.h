#ifndef RECEIVER_H
#define RECEIVER_H

#include <QObject>
#include <QThread>
#include <QUdpSocket>
#include <QDebug>
#include <QTime>

#include "Buffers/BufferController.h"
#include "Management/SettingsStorage.h"

class Receiver : public QThread
{
    Q_OBJECT
private:
    QUdpSocket *m_udpSocketResiver;
    QTime *m_time;
    void printConnectionState();
    volatile bool isRunning;
public:
    explicit Receiver( QObject *parent = 0 );
    ~Receiver();
    void run();
    void Connect();
    void Disconnect();
private slots:
    void processPendingDatagrams();
signals:
    void ReadyData();
};

#endif // RECEIVER_H
