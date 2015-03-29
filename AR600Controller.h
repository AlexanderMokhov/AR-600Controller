#ifndef WIDGET_H
#define WIDGET_H

//#include <iostream>
#include <QWidget>
#include <QUdpSocket>
#include <QTimer>
#include "MBWrite.h"
#include "MBRead.h"
#include "dataplot.h"
#include "TinyXML/tinyxml.h"
#include "AR600ControllerConf.h"

namespace Ui {
	class Widget;
}

class AR600Controller : public QWidget
{
	Q_OBJECT
	
public:
    explicit AR600Controller(QWidget *parent = 0);
    ~AR600Controller();
	
private:
	Ui::Widget *ui;
    QUdpSocket* mUdpSocketResiver;
    QUdpSocket* mUdpSocketSender;
    QTimer*     mTimer;
    QTimer*     mTimer2;

    MBWrite     mSendBuffer;
    MBRead      mResiverBuffer;

	std::string mHost;
	unsigned int mPort;
    //DataPlot mPlot;
    int RangeSize;

    void ProcessTheDatagram(QByteArray& datagramm);
    void UpdatePowerLabel();
    void realtimeData();
    void SetConfigData();

private slots:
    void ProcessPendingDatagrams();
    void StartSending();
    /*void SendMessage();*/



    void on_pButtonSaveXML_clicked();

    void on_pButtonOpenXML_clicked();

public slots:
    void On48Slot(bool value);
    void On8V1Slot(bool value);
    void On8V2Slot(bool value);
    void On6V1Slot(bool value);
    void On6V2Slot(bool value);

	void Connect();
	void Disconnect();
    void UdpSend();
    void AddRow();
    void SetLenght(double lenght);

};

#endif // WIDGET_H
