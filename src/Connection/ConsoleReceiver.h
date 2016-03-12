#ifndef CONSOLERECEIVER_H
#define CONSOLERECEIVER_H

#include <QObject>
#include <QThread>
#include <QUdpSocket>
#include <QDebug>
#include <QTime>
#include <QFile>

#include "Buffers/BufferController.h"
#include "Management/SettingsStorage.h"

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
private:
    //private variable
    QUdpSocket *m_udpSocketReceiver;
    volatile bool isRunning;

    //private methods
    void writeToFile(QByteArray data);
private slots:
    void processPendingDatagrams();
};

#endif // CONSOLERECEIVER_H
