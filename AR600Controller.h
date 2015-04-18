#ifndef AR600CONTROLLER_H
#define AR600CONTROLLER_H

//#include <iostream>
#include "string.h"
#include <QWidget>
#include <QUdpSocket>
#include <QTimer>
#include <QItemSelectionModel>
#include "DataPlot.h"
#include "TinyXML/tinyxml.h"
#include "ConfigController.h"
#include "ChannelTableModel.h"
#include "Widgets/DriverControllerWidget.h"
#include "Widgets/CommandControllerWidget.h"
#include "Widgets/ChanneTableWidget.h"
#include "Widgets/DriverLogWidget.h"
#include "BufferController.h"
#include "CommandController.h"
#include <QMessageBox>
#include <qfiledialog.h>
#include "DriverLogController.h"
#include "ThreadReceive.h"


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

    int                 RangeSize;

    DriverControllerWidget  *mDriverControllerWidget;
    CommandControllerWidget *mCommandControllerWidget;
    ChannelTableWidget      *mChannelTableWidget;
    DriverLogWidget         *mDriverLogWidget;

    ThreadReceive *mThreadRecieve;

    void ProcessTheDatagram(QByteArray& datagramm);
    void UpdatePowerLabel();
    void realtimeData();
    void SetConfigData();

    ChannelTableModel *m_CLModel;
    QItemSelectionModel *m_SelectionModel;
    uint CurrentTime;
    long CurrentTimeForCommands;


private slots:
    void ProcessPendingDatagrams();

    void on_pButtonSaveXML_clicked();
    void on_pButtonOpenXML_clicked();
    /*void SendMessage();*/

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
    void OnStartPlayForward();

};

#endif // AR600CONTROLLER_H
