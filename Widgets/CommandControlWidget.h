#ifndef COMMANDCONTROLWIDGET_H
#define COMMANDCONTROLWIDGET_H

#include <QWidget>
#include "ConfigController.h"
#include "BufferController.h"
#include "Models/MotorTableModel.h"
#include <QFileDialog>
#include <QStateMachine>
#include <QState>
#include <QPropertyAnimation>
#include <QSignalTransition>
#include "MoveController.h"

namespace Ui {
class CommandControlWidget;
}

class CommandControlWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CommandControlWidget(QWidget *parent = 0);
    ~CommandControlWidget();

private slots:
    void on_ButtonLoadFile_clicked();

    void on_ButtonPlayPause_clicked();

    void on_ButtonStop_clicked();

    void on_ButtonNext_clicked();

    void on_checkBoxLog_clicked(bool checked);

    void on_ButtonGoStartPos_clicked();

    void on_ButtonStartFile_clicked();

private:
    Ui::CommandControlWidget *ui;
    QString DefaultText;
    bool IsLog;

    QStateMachine *machine;
    QState        *statePlay;
    QState        *stateStop;
    QState        *stateNotOpenFile;
    bool          isFileCommand;

signals:
    StartWriteLog(int LogTime);
    StopWriteLog();
    FileLoaded(QString FileName,int CountRows, int Duration,bool Mode);
    PlayStart();
    PlayStop();
public slots:
    void startCommand();
    void openFile(QString fileName, bool mode);
};

#endif // COMMANDCONTROLWIDGET_H
