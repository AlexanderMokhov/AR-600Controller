#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "string.h"
#include <QUdpSocket>
#include <QTimer>
#include <QItemSelectionModel>
#include <QLabel>
#include <QDesktopWidget>
#include <QFileDialog>
#include <QMessageBox>
#include <QProcess>

#include "Management/SettingsStorage.h"
#include "Management/MoveController.h"
#include "Management/MoveCorrector.h"
#include "Management/RecordController.h"
#include "Management/LogMaster.h"
#include "Management/Mover.h"

#include "Models/MotorTableModel.h"

#include "ControlWidgets/MotorsControlW.h"
#include "ControlWidgets/MotionControlW.h"
#include "ControlWidgets/PowerControlW.h"
#include "ControlWidgets/ConnectionControlW.h"
#include "ControlWidgets/AdditionalControlW.h"
#include "ControlWidgets/RecordControlW.h"

#include "GridWidgets/MotorsGridW.h"
#include "GridWidgets/SensorsGridW.h"
#include "GridWidgets/MovesGridW.h"

#include "DialogWidgets/ConnectionSetupDialog.h"

#include "Widgets/StdMovesWidget.h"
#include "Widgets/LogOutputW.h"

#include "Packets/ARPacketManager.h"

#include "Connection/Receiver.h"
#include "Connection/Sender.h"
#include "Connection/ConsoleReceiver.h"
#include "Connection/FrundTransiver.h"

#include <Windows.h>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    //public methods
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void ActivateActions();

private slots:
    void ProcessTheDatagram();
    void SaveXML();
    void OpenXML();

    void OpenCorrectionFile();
    void OpenDRIVEMATFile();

    void StartPlayOnline();
    void StopPlayOnline();

    void StartFrund();

    void Connect();
    void Disconnect();

    void OpenConnectConfig();

private:
    //private variable
    Ui::MainWindow *ui;

    QTimer*                 mTimerUpdate;
    int                     mUpdateDelay;

    //виджеты
    MotorsControlW      *mMotorControlWidget;
    MotionControlW       *mMoveControlWidget;
    MotorsGridW        *mMotorTableWidget;
    RecordControlW            *mRecordWidget;
    QLabel                  *mConnectStatusLabel;
    QLabel                  *mCommandControllerStatusLabel;
    ConnectionSetupDialog     *mConnectDialog;
    SensorsGridW       *mSensorTableWidget;
    MovesGridW         *mMoveFilesWidget;
    StdMovesWidget          *mStdMovesWidget;
    LogOutputW               *mLogWidget;
    PowerControlW           *mPowerCW;
    ConnectionControlW      *mConnectionCW;
    AdditionalControlW        *mAdditionCW;

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
    QAction *TBactionOpenMoveFile;
    QAction *TBactionStartFrund;
    QAction *TBactionStartPlayOnline;
    QAction *TBactionStopPlayOnline;

    //потоки
    Receiver                *mReceiver;
    Sender                  *mSender;
    ConsoleReceiver         *mConsoleReceiver;

    Mover         *mMover;

    //private methods
    void ActionsLoad();
    void WidgetsInit();
    void ConnectionsInit();
    void ToolBarInit();

    void closeEvent(QCloseEvent *event);
};

#endif // MAINWINDOW_H
