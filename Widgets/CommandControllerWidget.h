#ifndef COMMANDCONTROLLERWIDGET_H
#define COMMANDCONTROLLERWIDGET_H

#include <QWidget>
#include "ConfigController.h"
#include "BufferController.h"
#include "ChannelTableModel.h"
#include <QFileDialog>
#include <QStateMachine>
#include <QState>
#include <QPropertyAnimation>
#include <QSignalTransition>
#include "CommandController.h"

namespace Ui {
class CommandControllerWidget;
}

class CommandControllerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CommandControllerWidget(QWidget *parent = 0);
    ~CommandControllerWidget();

private slots:
    void on_ButtonLoadFile_clicked();

    void on_ButtonPlayPause_clicked();

    void on_ButtonStop_clicked();

    void on_ButtonNext_clicked();

    void on_checkBoxLog_clicked(bool checked);

private:
    Ui::CommandControllerWidget *ui;
    QString DefaultText;
    bool IsLog;

    QStateMachine *machine;
    QState        *statePlay;
    QState        *stateStop;
    QState        *statePause;
    QState        *stateNotOpenFile;
signals:
    StartWriteLog(int LogTime);
    StopWriteLog();
    FileLoaded(QString Description, QString CountRows, QString Duration);
public slots:
    void onRowChanged(int Row);
};

#endif // COMMANDCONTROLLERWIDGET_H
