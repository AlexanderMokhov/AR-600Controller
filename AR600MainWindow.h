#ifndef AR600MAINWINDOW_H
#define AR600MAINWINDOW_H

#include <QMainWindow>
#include "string.h"
#include <QUdpSocket>
#include <QTimer>
#include <QItemSelectionModel>
#include "TinyXML/tinyxml.h"
#include "ConfigController.h"
#include "MotorTableModel.h"
#include "Widgets/MotorControlWidget.h"
#include "Widgets/CommandControlWidget.h"
#include "Widgets/MotorTableWidget.h"
#include "Widgets/DeviceLogWidget.h"
#include "Widgets/PowerControlWidget.h"
#include "BufferController.h"
#include "CommandController.h"
#include <QMessageBox>
#include <qfiledialog.h>
#include "DeviceLogController.h"
#include "ThreadReceive.h"
#include "ThreadSend.h"
#include <QLabel>
#include <QDesktopWidget>
#include "Widgets/ConnectConfigDialog.h"
#include "Widgets/SensorTableWidget.h"

namespace Ui {
class AR600MainWindow;
}

class AR600MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit AR600MainWindow(QWidget *parent = 0);
    ~AR600MainWindow();

private:
    Ui::AR600MainWindow *ui;

    QTimer*             mTimerUpdate;

    WriteBuffer             *mSendBuffer;
    ReadBuffer              *mReceiveBuffer;

    std::string         mHost;
    unsigned int        mSendPort;
    int                 mSendDelay;
    unsigned int        mReceivePort;
    int                 mReceiveDelay;

    //виджеты
    MotorControlWidget   *mMotorControlWidget;
    CommandControlWidget *mCommandControlWidget;
    MotorTableWidget        *mMotorTableWidget;
    DeviceLogWidget         *mDeviceLogWidget;
    PowerControlWidget      *mPowerControlWidget;
    QLabel                  *mConnectStatusLabel;
    QLabel                  *mCommandControllerStatusLabel;
    ConnectConfigDialog     *mConnectDialog;
    SensorTableWidget       *mSensorTableWidget;

    //действия
    QAction *TBactionOpenCF;
    QAction *TBactionSaveCF;
    QAction *TBactionPlay;
    QAction *TBactionStop;
    QAction *TBactionNext;
    QAction *TBactionOnPower;
    QAction *TBactionOffPower;
    QAction *TBactionOpenConnectSettings;
    QAction *TBactionConnect;
    QAction *TBactionDisconnect;
    QAction *TBactionOpenCommandFile;

    //потоки
    ThreadReceive           *mThreadRecieve;
    ThreadSend              *mThreadSend;

    void ActionsLoad();
private slots:
    void ProcessTheDatagram();
    void SaveXML();
    void OpenXML();

public slots:
    void Connect();
    void Disconnect();
    void ActivateActions();
    void OpenConnectConfig();

};

#endif // AR600MAINWINDOW_H
