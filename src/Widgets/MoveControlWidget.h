#ifndef MOVECONTROLWIDGET_H
#define MOVECONTROLWIDGET_H

#include <QWidget>
#include <QFileDialog>
#include <QStateMachine>
#include <QState>
#include <QPropertyAnimation>
#include <QSignalTransition>

#include "Management/ConfigController.h"
#include "Buffers/BufferController.h"
#include "Models/MotorTableModel.h"
#include "Management/MoveController.h"
#include "Management/MoveCorrector.h"

namespace Ui {
class MoveControlWidget;
}

class MoveControlWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MoveControlWidget(QWidget *parent = 0);
    ~MoveControlWidget();

private slots:
    void on_ButtonLoadFile_clicked();
    void on_ButtonLoadDRIVEMAT_clicked();
    void on_ButtonPlayPause_clicked();
    void on_ButtonStop_clicked();
    void on_ButtonNext_clicked();
    void on_checkBoxLog_clicked(bool checked);
    void on_ButtonGoStartPos_clicked();
    void on_ButtonStartFile_clicked();

private:
    Ui::MoveControlWidget *ui;
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

#endif // MOVECONTROLWIDGET_H
