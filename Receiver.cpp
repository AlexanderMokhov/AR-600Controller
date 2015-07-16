#include "Receiver.h"

Receiver::Receiver(QObject *parent) : QThread(parent)
{
    mTime = new QTime;
    mReceiveBuffer = BufferController::Inst()->GetReadBuffer();
    isRunning = false;
}

void Receiver::PrintConnectionState()
{
    if (mUdpSocketResiver->state() == QUdpSocket::ConnectedState)
    {
        qDebug() << "Receiver - connected";
    }
    else
    {
        qDebug() << "Receiver - disconnected";
    }
}

Receiver::~Receiver()
{
    exit();
}

void Receiver::run()
{
    mUdpSocketResiver = new QUdpSocket;

    connect(mUdpSocketResiver, SIGNAL(readyRead()), SLOT(ProcessPendingDatagrams()),Qt::DirectConnection);

    qDebug() << "Receiver - connecting..." << endl;

    int ReceivePort = ConfigController::Inst()->GetReceivePort();

    if (!mUdpSocketResiver->bind(ReceivePort,QUdpSocket::ShareAddress))
    {
        qDebug()<< "Receiver - Not Bind!";
    }

    PrintConnectionState();

    exec();

    qDebug() << "Receiver - disconnecting..." << endl;

    disconnect(mUdpSocketResiver, SIGNAL(readyRead()));
    mUdpSocketResiver->close();

    PrintConnectionState();
}

void Receiver::Connect()
{
    isRunning = true;
    start();
}

void Receiver::Disconnect()
{
    isRunning = false;
    exit();
}

void Receiver::ProcessPendingDatagrams()
{
    //qDebug() << "Time Receive Delay: " << QString::number(mTime->elapsed()) << " ms"<< endl;

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

    //mTime->start();
}

