#include "ThreadReceive.h"

ThreadReceive::ThreadReceive(QObject *parent) : QThread(parent)
{

}

ThreadReceive::~ThreadReceive()
{
    mUdpSocketResiver->close();
    delete mUdpSocketResiver;
    exit();
}

void ThreadReceive::run()
{
    qDebug() << "Receiver is running..." << endl;
    mUdpSocketResiver = new QUdpSocket();
    mReceiveBuffer = BufferController::Instance()->GetReadBuffer();
    mLock=mReceiveBuffer->GetLock();

    connect(mUdpSocketResiver, SIGNAL(readyRead()), this, SLOT(ProcessPendingDatagrams()),Qt::DirectConnection);
    exec();
}

void ThreadReceive::ProcessPendingDatagrams()
{
    qDebug()<< "UDPRead";
    while (mUdpSocketResiver->hasPendingDatagrams())
    {
        QByteArray datagram;
        datagram.resize(mUdpSocketResiver->pendingDatagramSize());
        QHostAddress sender;
        quint16 senderPort;

        mUdpSocketResiver->readDatagram(datagram.data(), datagram.size(),&sender, &senderPort);
        //while (*mLock) {;}
        //*mLock = true;
        mReceiveBuffer->Init(datagram.data());
        //*mLock = false;
        //Отправляем пакет на обработку
        emit ReadyData();
     }
}

void ThreadReceive::ConnectSocket()
{
    qDebug() << "I am Connected" << endl;
    mPort=ConfigController::Instance()->GetPort();

    if (!mUdpSocketResiver->bind(10002,QUdpSocket::ShareAddress))
    {
        qDebug()<< "Not Bind!";
    }
}

void ThreadReceive::DisconnectSocket()
{
    qDebug() << "I am DisConnected" << endl;
    mUdpSocketResiver->disconnect();
}

