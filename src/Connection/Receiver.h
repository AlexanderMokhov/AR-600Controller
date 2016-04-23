#ifndef RECEIVER_H
#define RECEIVER_H

#include <QObject>
#include <QThread>
#include <QUdpSocket>
#include <QDebug>
#include <QTime>

#include "Packets/ARPacketManager.h"
#include "Management/SettingsStorage.h"

class Receiver : public QThread
{
    Q_OBJECT
public:
    //public methods
    explicit Receiver( QObject *parent = 0 );
    ~Receiver();

    void run();
    void Connect();
    void Disconnect();

signals:
    void ReadyData();

private:
    //private variable
    QUdpSocket *m_udpSocketResiver;
    QTime *m_time;
    volatile bool isRunning;
    //private methods
    void printConnectionState();

private slots:
    void processPendingDatagrams();

};

#endif // RECEIVER_H
