#include "ThreadSend.h"

ThreadSend::ThreadSend(QObject *parent) : QThread(parent)
{
    mUdpSocketSender = new QUdpSocket;
    mTimerSend = new QTimer;
    mSendBuffer = BufferController::Instance()->GetWriteBuffer();
}

ThreadSend::~ThreadSend()
{
    mUdpSocketSender->close();
    delete mUdpSocketSender;
    exit();
}

void ThreadSend::run()
{
    qDebug() << "Sender - running..." << endl;
    exec();
}

void ThreadSend::ConnectSocket()
{
    qDebug() << "Sender - connecting..." << endl;
    mPort = ConfigController::Instance()->GetPort();
    mHost = QString::fromStdString(ConfigController::Instance()->GetHost());
    mSendDelay = ConfigController::Instance()->GetSendDelay();

    mUdpSocketSender->connectToHost(mHost, mPort);
    mUdpSocketSender->waitForConnected(1000);

    if (mUdpSocketSender->state()==QUdpSocket::ConnectedState)
    {
        qDebug() << "Sender - connected";
    }
    else
    {
        qDebug() << "Sender - disconnected";
    }
    connect(mTimerSend,SIGNAL(timeout()),this,SLOT(SendDatagram()),Qt::DirectConnection);
    mTimerSend->start(mSendDelay);

}

void ThreadSend::DisconnectSocket()
{
    qDebug() << "Sender - disconnecting..." << endl;
    mTimerSend->stop();
    mUdpSocketSender->disconnect();
    mUdpSocketSender->close();

    if (mUdpSocketSender->state()==QUdpSocket::ConnectedState)
    {
        qDebug() << "Sender - connected";
    }
    else
    {
        qDebug() << "Sender - disconnected";
    }
}

void ThreadSend::SendDatagram()
{
    qDebug() << "Sender - send..." << endl;
    QHostAddress mAddress = QHostAddress(mHost);
    //while (*mLock) {;}
    //*mLock = true;
    mUdpSocketSender->writeDatagram(mSendBuffer->GetBuffer(), mSendBuffer->GetSize()* sizeof(char), mAddress, mPort);
    mUdpSocketSender->waitForBytesWritten();
    //*mLock = false;
    CommandController::Instance()->SendCommand();
}

