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

#include "Models/MotorTableModel.h"

#include "Widgets/MotorControlWidget.h"
#include "Widgets/MoveControlWidget.h"
#include "Widgets/MotorTableWidget.h"
#include "Widgets/RecordWidget.h"
#include "Widgets/PowerWidget.h"
#include "Widgets/ConnectConfigDialog.h"
#include "Widgets/SensorTableWidget.h"
#include "Widgets/MoveFilesWidget.h"
#include "Widgets/StdMovesWidget.h"

#include "Buffers/BufferController.h"

#include "Connection/Receiver.h"
#include "Connection/Sender.h"
#include "Connection/ConsoleReceiver.h"

#include <Windows.h>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    QTimer*                 mTimerUpdate;
    int                     mUpdateDelay;

    //виджеты
    MotorControlWidget      *mMotorControlWidget;
    MoveControlWidget       *mMoveControlWidget;
    MotorTableWidget        *mMotorTableWidget;
    RecordWidget            *mRecordWidget;
    PowerWidget             *mPowerWidget;
    QLabel                  *mConnectStatusLabel;
    QLabel                  *mCommandControllerStatusLabel;
    ConnectConfigDialog     *mConnectDialog;
    SensorTableWidget       *mSensorTableWidget;
    MoveFilesWidget         *mMoveFilesWidget;
    StdMovesWidget          *mStdMovesWidget;

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

    //потоки
    Receiver                *mReceiver;
    Sender                  *mSender;
    ConsoleReceiver         *mConsoleReceiver;

    void ActionsLoad();
    void WidgetsInit();
    void ConnectionsInit();
    void ToolBarInit();

    void closeEvent(QCloseEvent *event);

private slots:
    void ProcessTheDatagram();
    void SaveXML();
    void OpenXML();

    void OpenCorrectionFile();
    void OpenDRIVEMATFile();

public slots:
    void Connect();
    void Disconnect();
    void ActivateActions();
    void OpenConnectConfig();
    void StartPlayOnline();
    void StartFrund();

};

#endif // MAINWINDOW_H
