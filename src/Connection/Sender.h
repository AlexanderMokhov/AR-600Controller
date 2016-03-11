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
private:

//    SOCKET SendSocket; // 01.02.2016
//    sockaddr_in dest_addr;
    QUdpSocket *m_udpSocketSender;
    QTimer *m_timerSend;
    std::mutex *m_locker;
    QTime *m_time;

    QString         m_host;
    int             m_sendPort;
    int             m_sendDelay;

    volatile bool isRunning;
    void printConnectionState();
public:
    explicit Sender( QObject *parent = 0 );
    ~Sender();
    void run();
    void Connect();
    void Disconnect();
private slots:
    void sendDatagram();
};

#endif // SENDER_H
