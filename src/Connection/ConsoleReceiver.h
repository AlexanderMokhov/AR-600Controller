#ifndef CONSOLERECEIVER_H
#define CONSOLERECEIVER_H

#include <QObject>
#include <QThread>
#include <QUdpSocket>
#include <QDebug>
#include <QTime>

#include "Buffers/BufferController.h"
#include "Management/ConfigController.h"

class ConsoleReceiver : public QThread
{
    Q_OBJECT
private:
    QUdpSocket *mUdpSocketReceiver;
    volatile bool isRunning;
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
