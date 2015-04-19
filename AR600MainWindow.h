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
    unsigned int        mPort;
    int                 mSendDelay;

    //виджеты
    DriverControllerWidget  *mDriverControllerWidget;
    CommandControllerWidget *mCommandControllerWidget;
    ChannelTableWidget      *mChannelTableWidget;
    DriverLogWidget         *mDriverLogWidget;
    PowerWidget             *mPowerWidget;

    //потоки
    ThreadReceive           *mThreadRecieve;
    ThreadSend              *mThreadSend;

private slots:
    void ProcessTheDatagram();
    void on_pButtonSaveXML_clicked();
    void on_pButtonOpenXML_clicked();

    void play();
    void pause();
    void stop();

public slots:
    void Connect();
    void Disconnect();

};

#endif // AR600MAINWINDOW_H
