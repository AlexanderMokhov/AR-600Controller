#include "ConsoleReceiver.h"

ConsoleReceiver::ConsoleReceiver(QObject *parent) : QThread(parent)
{
    isRunning = false;
}

ConsoleReceiver::~ConsoleReceiver()
{
    exit();
}

void ConsoleReceiver::run()
{
    //нить создана
    m_udpSocketReceiver = new QUdpSocket;
    int ReceivePort = 55555;

    connect(m_udpSocketReceiver, SIGNAL(readyRead()), SLOT(processPendingDatagrams()), Qt::DirectConnection);

    qDebug() << "ConsoleReceiver - binding..." << endl;


    if (!m_udpSocketReceiver->bind(ReceivePort, QUdpSocket::ShareAddress))
    {
        qDebug()<< "ConsoleReceiver - Not Bind!";
    }

    //Запускаем цикл обработки событий
    exec();
    //Завершился цикл обработки событий

    qDebug() << "ConsoleReceiver - unbinding..." << endl;

    disconnect(m_udpSocketReceiver, SIGNAL(readyRead()));
    m_udpSocketReceiver->close();
}

void ConsoleReceiver::Connect()
{
    if(isRunning == false)
    {
        isRunning = true;
        start();
    }
}

void ConsoleReceiver::Disconnect()
{
    if(isRunning == true)
    {
        isRunning = false;
        exit();
    }
}

void ConsoleReceiver::processPendingDatagrams()
{
    while (m_udpSocketReceiver->hasPendingDatagrams())
    {
        QByteArray datagram;
        datagram.resize(m_udpSocketReceiver->pendingDatagramSize());
        QHostAddress Host;
        quint16 Port;

        m_udpSocketReceiver->readDatagram(datagram.data(), datagram.size(), &Host, &Port);
        qDebug() << "ConsoleReceiver data: " << datagram.data() <<"size"<< QString::number(datagram.size()) << endl;

        if(datagram.data() == "0")
        {
            m_udpSocketReceiver->readDatagram(datagram.data(), datagram.size(), &Host, &Port);
            qDebug() << "ConsoleReceiver data: " << datagram.data() <<"size"<< QString::number(datagram.size()) << endl;
            writeToFile(datagram);
        }
     }
}

void ConsoleReceiver::writeToFile(QByteArray data)
{
    QFile file("controlFile.txt");
    if(file.open(QIODevice::WriteOnly))
    {
        file.write(data);
        file.close();
    }
}
