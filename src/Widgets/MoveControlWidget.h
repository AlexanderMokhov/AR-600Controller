#ifndef MOVECONTROLWIDGET_H
#define MOVECONTROLWIDGET_H

#include <QWidget>
#include <QFileDialog>
#include <QStateMachine>
#include <QState>
#include <QPropertyAnimation>
#include <QSignalTransition>
#include <QProgressDialog>
#include <QFuture>
#include <QtConcurrent/QtConcurrent>

#include "Management/SettingsStorage.h"
#include "Buffers/BufferController.h"
#include "Models/MotorTableModel.h"

#include "Management/MoveController.h"
#include "Management/MoveCorrector.h"
#include "Management/MovesStorage.h"
#include "Management/Mover.h"

namespace Ui {
class MoveControlWidget;
}

class MoveControlWidget : public QWidget
{
    Q_OBJECT
public:
    //public methods
    explicit MoveControlWidget(QWidget *parent = 0);
    ~MoveControlWidget();

    void StartPlayFile(bool mode);
    void stopMoveAction();

signals:
    StartWriteRecord(int LogTime);
    StopWriteRecord();
    FileLoaded(QString FileName,int CountRows, int Duration, bool Mode);
    PlayStart();
    PlayStop();

public slots:
    void startMove();
    void startMoveOnline();
    void openFile(QString fileName, bool mode);
    void startStdMove();

private slots:
    void on_ButtonLoadFile_clicked();
    void on_ButtonLoadDRIVEMAT_clicked();
    void on_ButtonPlayPause_clicked();
    void on_ButtonStop_clicked();
    void on_checkBoxLog_clicked(bool checked);
    void on_ButtonGoStartPos_clicked();
    void on_ButtonStartFile_clicked();
    void on_cBoxUseUserStiff_clicked(bool checked);
    void on_cBoxUseUserDump_clicked(bool checked);

private:
    //private variable
    Ui::MoveControlWidget *ui;
    QString DefaultText;
    bool IsLog;

    QStateMachine *machine;
    QState        *statePlay;
    QState        *stateStop;
    QState        *stateNotOpenFile;
    bool          isMoveFile;
    Mover         *mMover;
};

#endif // MOVECONTROLWIDGET_H
