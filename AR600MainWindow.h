#ifndef AR600MAINWINDOW_H
#define AR600MAINWINDOW_H

#include <QMainWindow>
#include "string.h"
#include <QUdpSocket>
#include <QTimer>
#include <QItemSelectionModel>
#include "TinyXML/tinyxml.h"
#include "ConfigController.h"
#include "ChannelTableModel.h"
#include "Widgets/DriverControllerWidget.h"
#include "Widgets/CommandControllerWidget.h"
#include "Widgets/ChanneTableWidget.h"
#include "Widgets/DriverLogWidget.h"
#include "Widgets/PowerWidget.h"
#include "BufferController.h"
#include "CommandController.h"
#include <QMessageBox>
#include <qfiledialog.h>
#include "DriverLogController.h"
#include "ThreadReceive.h"
#include "ThreadSend.h"
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

    MBWrite             *mSendBuffer;
    MBRead              *mReceiveBuffer;

    std::string         mHost;
    unsigned int        mSendPort;
    int                 mSendDelay;
    unsigned int        mReceivePort;
    int                 mReceiveDelay;

    //виджеты
    DriverControllerWidget  *mDriverControllerWidget;
    CommandControllerWidget *mCommandControllerWidget;
    ChannelTableWidget      *mChannelTableWidget;
    DriverLogWidget         *mDriverLogWidget;
    PowerWidget             *mPowerWidget;

    //действия
    QAction *actionOpen;
    QAction *actionPlay;
    QAction *actionStop;
    QAction *actionNext;

    //потоки
    ThreadReceive           *mThreadRecieve;
    ThreadSend              *mThreadSend;

    void ActionsLoad();
private slots:
    void ProcessTheDatagram();
    void SaveXML();
    void OpenXML();

    void play();
    void pause();
    void stop();

public slots:
    void Connect();
    void Disconnect();
    void ActivateActions();

};

#endif // AR600MAINWINDOW_H
