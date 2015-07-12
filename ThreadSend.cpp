#include "ThreadSend.h"

ThreadSend::ThreadSend(QObject *parent) : QThread(parent)
{
    mUdpSocketSender = new QUdpSocket;
    mTimerSend = new QTimer;
    mSendBuffer = BufferController::Instance()->GetWriteBuffer();
    mLocker=mSendBuffer->GetLocker();

    timepres = new QTime();
}

ThreadSend::~ThreadSend()
{
    mUdpSocketSender->close();
    delete mUdpSocketSender;
    exit();
}

void ThreadSend::run()
{
    exec();
}

void ThreadSend::ConnectSocket()
{
    qDebug() << "Sender - connecting..." << endl;
    mSendPort = ConfigController::Instance()->GetSendPort();
    mHost = QString::fromStdString(ConfigController::Instance()->GetHost());
    mSendDelay = ConfigController::Instance()->GetSendDelay();

    mUdpSocketSender->connectToHost(mHost, mSendPort);
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
    long timeprescount = timepres->elapsed();
    //qDebug() << "Time Send Delay: " << QString::number(timeprescount) << " ms"<< endl;

    QHostAddress mAddress = QHostAddress(mHost);
    mLocker->lock();
    mUdpSocketSender->writeDatagram(mSendBuffer->GetRAW(), mSendBuffer->GetSize()* sizeof(char), mAddress, mSendPort);
    mUdpSocketSender->waitForBytesWritten();
    mLocker->unlock();
    CommandController::Instance()->SendCommand();

    timepres->start();

}

