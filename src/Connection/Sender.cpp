#include "Sender.h"

Sender::Sender(QObject *parent) : QThread(parent)
{
    m_time = new QTime;
    m_locker = ARPacketManager::Inst()->getPacketSend()->getLocker();
    isRunning = false;
}

Sender::~Sender()
{
    exit();
}

void Sender::run()
{
    //нить создана
    m_udpSocketSender = new QUdpSocket();

    m_sendPort = SettingsStorage::Inst()->GetSendPort();
    m_host = QString::fromStdString(SettingsStorage::Inst()->GetHost());

    qDebug() << "Sender - connecting..." << endl;

    m_sendDelay = SettingsStorage::Inst()->GetSendDelay();

    m_udpSocketSender->connectToHost(m_host, m_sendPort);
    m_udpSocketSender->waitForConnected(1000);

    m_timerSend = new QTimer;
    m_timerSend->setInterval(m_sendDelay);
    connect(m_timerSend,SIGNAL(timeout()),SLOT(sendDatagram()),Qt::DirectConnection);
    m_timerSend->start(m_sendDelay);

    printConnectionState();

    //Запускаем цикл обработки событий
    exec();
    //Завершился цикл обработки событий

    qDebug() << "Sender - disconnecting..." << endl;
    disconnect(m_timerSend, SIGNAL(timeout()));

    m_udpSocketSender->disconnect();
    m_udpSocketSender->close();
    printConnectionState();
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

void Sender::sendDatagram()
{
    QHostAddress address = QHostAddress(m_host);
    m_locker->lock();
    m_udpSocketSender->writeDatagram(ARPacketManager::Inst()->getPacketSend()->getRAW(), ARPacketManager::Inst()->getPacketSend()->getSize()* sizeof(char), address, m_sendPort);
    m_udpSocketSender->waitForBytesWritten();
    m_locker->unlock();
}

void Sender::printConnectionState()
{
    if (m_udpSocketSender->state() == QUdpSocket::ConnectedState)
    {
        qDebug() << "Sender - connected";
    }
    else
    {
        qDebug() << "Sender - disconnected";
    }
}

