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
    //нить создана
    mUdpSocketResiver = new QUdpSocket;

    connect(mUdpSocketResiver, SIGNAL(readyRead()), SLOT(ProcessPendingDatagrams()),Qt::DirectConnection);

    qDebug() << "Receiver - connecting..." << endl;

    int ReceivePort = ConfigController::Inst()->GetReceivePort();

    if (!mUdpSocketResiver->bind(ReceivePort,QUdpSocket::ShareAddress))
    {
        qDebug()<< "Receiver - Not Bind!";
    }

    PrintConnectionState();

    //Запускаем цикл обработки событий
    exec();
    //Завершился цикл обработки событий

    qDebug() << "Receiver - disconnecting..." << endl;

    disconnect(mUdpSocketResiver, SIGNAL(readyRead()));
    mUdpSocketResiver->close();

    PrintConnectionState();
    //нить удалена
}

void Receiver::Connect()
{
    if(isRunning == false)
    {
        isRunning = true;
        start();
    }
}

void Receiver::Disconnect()
{
    if(isRunning == true)
    {
        isRunning = false;
        exit();
    }
}

void Receiver::ProcessPendingDatagrams()
{
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
}

