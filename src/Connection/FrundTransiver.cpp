#include "FrundTransiver.h"

FrundTransiver* FrundTransiver::m_inst = 0;

FrundTransiver::FrundTransiver(QObject *parent) : QObject(parent)
{
    sock = new QUdpSocket;
    qDebug() << "FrundTransiver - binding..." << endl;
    if(!sock->bind(m_port, QUdpSocket::ShareAddress))
        qDebug()<< "FrundTransiver - Not Bind!";

}

FrundTransiver::~FrundTransiver()
{
    sock->close();
    delete m_inst;
}

QByteArray FrundTransiver::readData()
{
    QByteArray datagram;
    while(!sock->hasPendingDatagrams());
    datagram.resize(sock->pendingDatagramSize());
    sock->readDatagram(datagram.data(), datagram.size(), &Host, &Port);
    return datagram;
}

void FrundTransiver::sendData(QByteArray datagram)
{
    sock->writeDatagram(datagram, Host, Port);
}



