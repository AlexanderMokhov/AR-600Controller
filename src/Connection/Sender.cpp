#include "Sender.h"

Sender::Sender(QObject *parent) : QThread(parent)
{
    mTime = new QTime;
    mSendBuffer = BufferController::Inst()->GetBufferS();
    mLocker = mSendBuffer->GetLocker();
    isRunning = false;
}

Sender::~Sender()
{
    exit();
}

void Sender::run()
{
    //нить создана
    mUdpSocketSender = new QUdpSocket();

    //New initialisation
    //WORD wVersionRequested; // 01.02.2016
    //WSADATA wsaData; // 01.02.2016
    //wVersionRequested = MAKEWORD(2, 2); // 01.02.2016
    //WSAStartup(wVersionRequested, &wsaData); // 01.02.2016

    mSendPort = ConfigController::Inst()->GetSendPort();
    mHost = QString::fromStdString(ConfigController::Inst()->GetHost());

    //Prepare the sockaddr_in structure
    //dest_addr.sin_family = AF_INET; // 01.02.2016
    //dest_addr.sin_addr.s_addr = inet_addr(ConfigController::Inst()->GetHost().c_str()); // 01.02.2016
    //dest_addr.sin_port = htons(mSendPort); // 01.02.2016

    qDebug() << "Sender - connecting..." << endl;


    mSendDelay = ConfigController::Inst()->GetSendDelay();

    mUdpSocketSender->connectToHost(mHost, mSendPort);
    mUdpSocketSender->waitForConnected(1000);

    mTimerSend = new QTimer;
    mTimerSend->setInterval(mSendDelay);
    connect(mTimerSend,SIGNAL(timeout()),SLOT(SendDatagram()),Qt::DirectConnection);
    mTimerSend->start(mSendDelay);

    PrintConnectionState();

    //Запускаем цикл обработки событий
    exec();
    //Завершился цикл обработки событий

    qDebug() << "Sender - disconnecting..." << endl;
    disconnect(mTimerSend, SIGNAL(timeout()));

    mUdpSocketSender->disconnect();
    mUdpSocketSender->close();
    PrintConnectionState();
    //нить удалена
}

void Sender::Connect()
{
    if(isRunning == false)
    {
        isRunning = true;
        start();
    }
}

void Sender::Disconnect()
{
    if(isRunning == true)
    {
        isRunning = false;
        exit();
    }
}

void Sender::SendDatagram()
{
    QHostAddress mAddress = QHostAddress(mHost);
    mLocker->lock();
    //sendto(SendSocket,mSendBuffer->GetRAW(),mSendBuffer->GetSize()* sizeof(char),0,
            //(sockaddr *) &dest_addr,sizeof(dest_addr));
    //qDebug() << "Sender - send..." << endl;
    mUdpSocketSender->writeDatagram(mSendBuffer->GetRAW(), mSendBuffer->GetSize()* sizeof(char), mAddress, mSendPort);
    mUdpSocketSender->waitForBytesWritten();
    mLocker->unlock();
    //MoveController::Inst()->DoStepWork();
}

void Sender::PrintConnectionState()
{
    if (mUdpSocketSender->state() == QUdpSocket::ConnectedState)
    {
        qDebug() << "Sender - connected";
    }
    else
    {
        qDebug() << "Sender - disconnected";
    }
}

