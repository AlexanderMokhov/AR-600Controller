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
    mUdpSocketReceiver = new QUdpSocket;
    int ReceivePort = 55555;

    connect(mUdpSocketReceiver, SIGNAL(readyRead()), SLOT(ProcessPendingDatagrams()), Qt::DirectConnection);

    qDebug() << "ConsoleReceiver - binding..." << endl;


    if (!mUdpSocketReceiver->bind(ReceivePort, QUdpSocket::ShareAddress))
    {
        qDebug()<< "ConsoleReceiver - Not Bind!";
    }

    //Запускаем цикл обработки событий
    exec();
    //Завершился цикл обработки событий

    qDebug() << "ConsoleReceiver - unbinding..." << endl;

    disconnect(mUdpSocketReceiver, SIGNAL(readyRead()));
    mUdpSocketReceiver->close();
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

void ConsoleReceiver::ProcessPendingDatagrams()
{
    while (mUdpSocketReceiver->hasPendingDatagrams())
    {
        QByteArray datagram;
        datagram.resize(mUdpSocketReceiver->pendingDatagramSize());
        QHostAddress Host;
        quint16 Port;

        mUdpSocketReceiver->readDatagram(datagram.data(), datagram.size(), &Host, &Port);
        qDebug() << "ConsoleReceiver data: " << datagram.data() <<"size"<< QString::number(datagram.size()) << endl;

        if(datagram.data() == "0")
        {
            mUdpSocketReceiver->readDatagram(datagram.data(), datagram.size(), &Host, &Port);
            qDebug() << "ConsoleReceiver data: " << datagram.data() <<"size"<< QString::number(datagram.size()) << endl;
        }

        //writeToFile(datagram);
        //Отправляем пакет на обработку
        //emit ReadyData();
     }
}

void ConsoleReceiver::writeToFile(QByteArray data)
{
    QFile file("controlFile.txt");
    /*QString control;
    control += QString::number(acc,'g',2) + " " + QString::number(angAcc,'g',2);
    control += " " + QString::number(hstep,'g',2) + " " + QString::number(lstep,'g',2);
    control += " " + QString::number(K) + " " + QString::number(I);*/
    if(file.open(QIODevice::WriteOnly))
    {
        file.write(data);
        file.close();
    }

    /*command[0] = '0';
    sender->writeDatagram(command, 1, host, port);
    QByteArray packet = control.toUtf8();
    sender->writeDatagram(packet, host, port);*/
}
