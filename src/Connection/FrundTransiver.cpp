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

bool FrundTransiver::recvData(QByteArray &datagram)
{
    if(!sock->hasPendingDatagrams())
        return false;
    datagram.resize(sock->pendingDatagramSize());
    sock->readDatagram(datagram.data(), datagram.size(), &Host, &Port);
    //size = datagram.size();
    //for(int i = 0; i < size; i++)
        //data[i] = datagram.data()[i];
    return true;
}

void FrundTransiver::sendData(QByteArray &datagram)
{
    //datagram.setRawData(data, size);
    sock->writeDatagram(datagram, Host, Port);
}



