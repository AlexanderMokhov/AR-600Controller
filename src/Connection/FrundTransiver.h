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
    explicit FrundTransiver(QObject *parent = 0);
    ~FrundTransiver();
    static FrundTransiver* Inst() { if(m_inst == NULL) m_inst = new FrundTransiver; return m_inst; }
    QByteArray readData();
    void sendData(QByteArray datagram);

private:
    static FrundTransiver* m_inst;
    QUdpSocket* sock;
    int m_port = 55556;
    QHostAddress Host;
    quint16 Port;

signals:

private slots:
};

#endif // FRUNDTRANSIVER_H
