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
    int ReceivePort = port;

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

        if(datagram == "0")         // записать файл
        {
            datagram.resize(m_udpSocketReceiver->pendingDatagramSize());
            m_udpSocketReceiver->readDatagram(datagram.data(), datagram.size(), &Host, &Port);
            qDebug() << "ConsoleReceiver data: " << datagram.data() <<"size"<< QString::number(datagram.size()) << endl;
            writeToFile(datagram);
        }
        else if(datagram == "1")    // запустить решение
            emit startPlayOnline();
        else if(datagram == "2")    // остановить решение
            emit stopPlayOnline();
        else if(datagram == "8")    // перейти в стартовое
            emit goToStartPos();
        else if(datagram == "3")
            emit rebootPower();
     }
}

void ConsoleReceiver::writeToFile(QByteArray data)
{
    QFile file("sinhron/CONTROLFILE.TXT");
    if(file.open(QIODevice::WriteOnly))
    {
        file.write(data);
        file.close();
    }
}

void ConsoleReceiver::sendFile()
{
    QFile file("controlFile.txt");
    QByteArray datagram;
    if(!file.open(QIODevice::WriteOnly))
        return;
    datagram = file.readAll();
    file.close();
    m_udpSocketReceiver->writeDatagram(datagram.data(), datagram.size(), host, port);
}
