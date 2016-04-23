#ifndef CONSOLERECEIVER_H
#define CONSOLERECEIVER_H

#include <QObject>
#include <QThread>
#include <QUdpSocket>
#include <QDebug>
#include <QTime>
#include <QFile>

#include "Packets/ARPacketManager.h"
#include "Management/SettingsStorage.h"
#include "Management/MoveController.h"

class ConsoleReceiver : public QThread
{
    Q_OBJECT
public:
    //public methods
    explicit ConsoleReceiver(QObject *parent = 0);
    ~ConsoleReceiver();

    void run();
    void Connect();
    void Disconnect();

signals:
    void ReadyData();
    void startPlayOnline();
    void stopPlayOnline();
    void goToStartPos();
    void rebootPower();

private:
    //private variable
    QUdpSocket *m_udpSocketReceiver;
    volatile bool isRunning;
    QHostAddress host = QHostAddress::LocalHost;
    int port = 55555;

    //private methods
    void writeToFile(QByteArray data);
    void sendFile();

private slots:
    void processPendingDatagrams();
};

#endif // CONSOLERECEIVER_H
