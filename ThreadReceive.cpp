#include "ThreadReceive.h"

ThreadReceive::ThreadReceive(QObject *parent) : QThread(parent)
{
    mUdpSocketResiver = new QUdpSocket;
    mReceiveBuffer = BufferController::Instance()->GetReadBuffer();
    timepres = new QTime();
}

ThreadReceive::~ThreadReceive()
{
    mUdpSocketResiver->close();
    delete mUdpSocketResiver;
    exit();
}

void ThreadReceive::run()
{
    exec();
}

void ThreadReceive::ProcessPendingDatagrams()
{
    long timeprescount = timepres->elapsed();
    //qDebug() << "Time Receive Delay: " << QString::number(timeprescount) << " ms"<< endl;


    while (mUdpSocketResiver->hasPendingDatagrams())
    {
        QByteArray datagram;
        datagram.resize(mUdpSocketResiver->pendingDatagramSize());
        QHostAddress sender;
        quint16 senderPort;

        mUdpSocketResiver->readDatagram(datagram.data(), datagram.size(),&sender, &senderPort);
        mReceiveBuffer->Init(datagram.data());
        //Отправляем пакет на обработку
        emit ReadyData();
     }

    timepres->start();
}

void ThreadReceive::ConnectSocket()
{
    qDebug() << "Receiver - connecting..." << endl;
    mReceivePort=ConfigController::Instance()->GetReceivePort();

    if (!mUdpSocketResiver->bind(mReceivePort,QUdpSocket::ShareAddress))
    {
        qDebug()<< "Receiver - Not Bind!";
    }
    connect(mUdpSocketResiver, SIGNAL(readyRead()), this, SLOT(ProcessPendingDatagrams()),Qt::DirectConnection);
    if (mUdpSocketResiver->state()==QUdpSocket::ConnectedState)
    {
        qDebug() << "Receiver - connected";
    }
    else
    {
        qDebug() << "Receiver - disconnected";
    }
}

void ThreadReceive::DisconnectSocket()
{
    qDebug() << "Receiver - disconnecting..." << endl;
    disconnect(mUdpSocketResiver, SIGNAL(readyRead()), this, SLOT(ProcessPendingDatagrams()));
    mUdpSocketResiver->close();

    if (mUdpSocketResiver->state()==QUdpSocket::ConnectedState)
    {
        qDebug() << "Receiver - connected";
    }
    else
    {
        qDebug() << "Receiver - disconnected";
    }

}

