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

class Sender : public QThread
{
    Q_OBJECT
public:
    //public methods
    explicit Sender( QObject *parent = 0 );
    ~Sender();

    void run();
    void Connect();
    void Disconnect();
private:
    //private variable
    QUdpSocket *m_udpSocketSender;
    QTimer *m_timerSend;
    QTime *m_time;

    std::mutex *m_locker;

    QString         m_host;
    int             m_sendPort;
    int             m_sendDelay;

    volatile bool isRunning;
    //private methods
    void printConnectionState();
private slots:
    void sendDatagram();
};

#endif // SENDER_H
