#include "Receiver.h"

Receiver::Receiver(QObject *parent) : QThread(parent)
{
    mTime = new QTime;
    mReceiveBuffer = BufferController::Inst()->GetBufferR();
    isRunning = false;
}

void Receiver::PrintConnectionState()
{
    if (mUdpSocketResiver->state() == QUdpSocket::BoundState)
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
    mUdpSocketResiver = new QUdpSocket;

    //New initialisation
    WORD wVersionRequested; // 01.02.2016
    WSADATA wsaData; // 01.02.2016
    wVersionRequested = MAKEWORD(2, 2); // 01.02.2016
    WSAStartup(wVersionRequested, &wsaData); // 01.02.2016

    int ReceivePort = ConfigController::Inst()->GetReceivePort();

    //Prepare the sockaddr_in structure
    sockaddr_in local; // 01.02.2016
    local.sin_family = AF_INET; // 01.02.2016
    local.sin_addr.s_addr = INADDR_ANY; // 01.02.2016
    local.sin_port = htons(ReceivePort); // 01.02.2016

    ReceiveSocket = socket(AF_INET, SOCK_DGRAM, 0); // 01.02.2016
    if( ReceiveSocket == INVALID_SOCKET ) { return; } // 01.02.2016
    if( bind(ReceiveSocket, (sockaddr*) &local, sizeof(local)) != 0 ) { return; } // 01.02.2016

    char buffer[BufferSize]; // 01.02.2016

//    connect(mUdpSocketResiver, SIGNAL(readyRead()), SLOT(ProcessPendingDatagrams()),Qt::DirectConnection);

    qDebug() << "Receiver - binding..." << endl;



//    if (!mUdpSocketResiver->bind(ReceivePort,QUdpSocket::ShareAddress))
//    {
//        qDebug()<< "Receiver - Not Bind!";
//    }

//    PrintConnectionState();

    while (isRunning) {
        if( recv(ReceiveSocket, buffer, BufferSize , 0) < 0 )
                    cout << "recv failed" << endl;
        mReceiveBuffer->Init(buffer);
        //Отправляем пакет на обработку
        emit ReadyData();
        //qDebug() << "Receiver - recv..." << endl;
    }

    //Запускаем цикл обработки событий
    exec();
    //Завершился цикл обработки событий

    closesocket(ReceiveSocket); // 01.02.2016
    WSACleanup(); // 01.02.2016

    qDebug() << "Receiver - unbinding..." << endl;

//    disconnect(mUdpSocketResiver, SIGNAL(readyRead()));
//    mUdpSocketResiver->close();

//    PrintConnectionState();
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

void Receiver::ProcessPendingDatagrams()
{
//    while (mUdpSocketResiver->hasPendingDatagrams())
//    {
//        QByteArray datagram;
//        datagram.resize(mUdpSocketResiver->pendingDatagramSize());
//        QHostAddress Host;
//        quint16 Port;

//        mUdpSocketResiver->readDatagram(datagram.data(), datagram.size(), &Host, &Port);
//        mReceiveBuffer->Init(datagram.data());
//        //Отправляем пакет на обработку
//        emit ReadyData();
//     }
}

