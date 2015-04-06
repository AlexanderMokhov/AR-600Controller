#ifndef WIDGET_H
#define WIDGET_H

//#include <iostream>
#include "string.h"
#include <QWidget>
#include <QUdpSocket>
#include <QTimer>
#include <QItemSelectionModel>
#include "dataplot.h"
#include "TinyXML/tinyxml.h"
#include "AR600ControllerConf.h"
#include "ChannelTableModel.h"
#include "Widgets/DriverControllerWidget.h"
#include "Widgets/CommandControllerWidget.h"
#include "BufferController.h"
#include "CommandController.h"
#include <QMessageBox>
#include <qfiledialog.h>
#include "DriverLogController.h"


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
    Ui::Widget*         ui;
    QUdpSocket*         mUdpSocketResiver;
    QUdpSocket*         mUdpSocketSender;
    QTimer*             mTimer;
    QTimer*             mTimer2;
    QTimer*             mLogTimer;

    MBWrite             *mSendBuffer;
    MBRead              *mReceiveBuffer;

    std::string         mHost;
    unsigned int        mPort;
    int                 mSendDelay;
    //DataPlot mPlot;
    int                 RangeSize;
    DriverControllerWidget * mDriverControllerWidget;
    CommandControllerWidget * mCommandControllerWidget;

    void ProcessTheDatagram(QByteArray& datagramm);
    void UpdatePowerLabel();
    void realtimeData();
    void SetConfigData();
    void ShowConfigData();

    ChannelTableModel *m_CLModel;
    QItemSelectionModel *m_SelectionModel;
    LogController *mLogController;
    uint CurrentTime;
    long CurrentTimeForCommands;


private slots:
    void ProcessPendingDatagrams();
    void StartSending();

    void on_pButtonSaveXML_clicked();
    void on_pButtonOpenXML_clicked();
    /*void SendMessage();*/

    void on_ButtonStartLog_clicked();

    void on_LogWrite();

    void on_ButtonStopLog_clicked();

    void on_ButtonSaveLog_clicked();

public slots:
    void On48Slot(bool value);
    void On8V1Slot(bool value);
    void On8V2Slot(bool value);
    void On6V1Slot(bool value);
    void On6V2Slot(bool value);

	void Connect();
	void Disconnect();
    void UdpSend();
    void SetLenght(double lenght);
    void OnEnterTable(QModelIndex index);
    void OnStartPlayForward();

};

#endif // WIDGET_H
