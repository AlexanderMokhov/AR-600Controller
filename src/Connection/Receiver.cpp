#include "Receiver.h"

Receiver::Receiver(QObject *parent) : QThread(parent)
{
    m_time = new QTime;
    isRunning = false;
}

void Receiver::printConnectionState()
{
    if (m_udpSocketResiver->state() == QUdpSocket::BoundState)
    {
        qDebug() << "Receiver - bounded";
    }
    else
    {
        qDebug() << "Receiver - unbounded";
    }
}

Receiver::~Receiver()
{
    exit();
}

void Receiver::run()
{
    //нить создана
    m_udpSocketResiver = new QUdpSocket;
    int ReceivePort = SettingsStorage::Inst()->GetReceivePort();

    connect(m_udpSocketResiver, SIGNAL(readyRead()), SLOT(processPendingDatagrams()),Qt::DirectConnection);

    qDebug() << "Receiver - binding..." << endl;

    if (!m_udpSocketResiver->bind(ReceivePort,QUdpSocket::ShareAddress))
        qDebug()<< "Receiver - Not Bind!";

    printConnectionState();

    //Запускаем цикл обработки событий
    exec();
    //Завершился цикл обработки событий

    qDebug() << "Receiver - unbinding..." << endl;

    disconnect(m_udpSocketResiver, SIGNAL(readyRead()));
    m_udpSocketResiver->close();

    printConnectionState();
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

void Receiver::processPendingDatagrams()
{
    while (m_udpSocketResiver->hasPendingDatagrams())
    {
        QByteArray datagram;
        datagram.resize(m_udpSocketResiver->pendingDatagramSize());
        QHostAddress Host;
        quint16 Port;

        m_udpSocketResiver->readDatagram(datagram.data(), datagram.size(), &Host, &Port);
        ARPacketManager::Inst()->getPacketRecv()->initialize(datagram.data());
        //Отправляем пакет на обработку
        emit ReadyData();
     }
}

