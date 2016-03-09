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
private:
    QUdpSocket *mUdpSocketReceiver;
    volatile bool isRunning;
    void writeToFile(QByteArray data);
public:
    explicit ConsoleReceiver(QObject *parent = 0);
    ~ConsoleReceiver();
    void run();
    void Connect();
    void Disconnect();
private slots:
    void ProcessPendingDatagrams();
signals:
    void ReadyData();
};

#endif // CONSOLERECEIVER_H
