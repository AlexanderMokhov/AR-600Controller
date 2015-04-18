#include "ThreadSend.h"

ThreadSend::ThreadSend(QObject *parent) : QThread(parent)
{

}

ThreadSend::~ThreadSend()
{
    mUdpSocketSender->close();
    delete mUdpSocketSender;
    exit();
}

void ThreadSend::run()
{
    qDebug() << "Sender is running..." << endl;
    mUdpSocketSender = new QUdpSocket(this);
    mTimerSend = new QTimer();
    mSendBuffer = BufferController::Instance()->GetWriteBuffer();
    //mLock=mSendBuffer->GetLock();



    connect(mTimerSend, SIGNAL(timeout()), SLOT(SendDatagram()));

            exec();
}

void ThreadSend::ConnectSocket()
{
    mPort = ConfigController::Instance()->GetPort();
    mHost = QString::fromStdString(ConfigController::Instance()->GetHost());
    mSendDelay = ConfigController::Instance()->GetSendDelay();

    mUdpSocketSender->connectToHost(mHost, mPort);
    mUdpSocketSender->waitForConnected(1000);

    if (mUdpSocketSender->state()==QUdpSocket::ConnectedState)
    {
        qDebug() << "Sender - Connected";
    }
    else
    {
        qDebug() << "Sender - Disconnected";
    }

    mTimerSend->start(mSendDelay);

}

void ThreadSend::DisconnectSocket()
{
    mTimerSend->stop();
    mUdpSocketSender->disconnect();

    if (mUdpSocketSender->state()==QUdpSocket::ConnectedState)
    {
        qDebug() << "Sender - Connected";
    }
    else
    {
        qDebug() << "Sender - Disconnected";
    }
}

void ThreadSend::SendDatagram()
{
    qDebug() << "Sender - Send..." << endl;
    QHostAddress mAddress = QHostAddress(mHost);
    mUdpSocketSender->writeDatagram(mSendBuffer->GetBuffer(), mSendBuffer->GetSize()* sizeof(char), mAddress, mPort);
    mUdpSocketSender->waitForBytesWritten();
}

