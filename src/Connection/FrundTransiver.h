#ifndef FRUNDTRANSIVER_H
#define FRUNDTRANSIVER_H

#include <QObject>
#include <QUdpSocket>

#define KDRIVE 21
#define BUFLEN KDRIVE*9  //Max length of buffer

class FrundTransiver : public QObject
{
    Q_OBJECT
public:
    //public methods
    explicit FrundTransiver(QObject *parent = 0);
    ~FrundTransiver();

    static FrundTransiver* Inst() { if(m_inst == NULL) m_inst = new FrundTransiver; return m_inst; }
    bool recvData(QByteArray &datagram);
    void sendData(QByteArray &datagram);

private:
    //private variable
    static FrundTransiver* m_inst;
    QUdpSocket* sock;
    int m_port = 55556;
    QHostAddress Host;
    quint16 Port;
};

#endif // FRUNDTRANSIVER_H
