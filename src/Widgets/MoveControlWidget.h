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
#include "Buffers/ARPacketManager.h"
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

    void Initialize();
    void StartPlayFile(bool mode);
    void stopMoveAction();

    void setMover(Mover * mover){ m_mover = mover; }

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
    void on_LoadFileB_clicked();
    void on_ButtonLoadDRIVEMAT_clicked();
    void on_StartB_clicked();
    void on_StopB_clicked();
    void on_checkBoxLog_clicked(bool checked);
    void on_GoStartPosB_clicked();
    void on_StartFileB_clicked();
    void on_UseUserPGateB_clicked(bool checked);
    void on_UseUserIGateB_clicked(bool checked);

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
    Mover         *m_mover;
};

#endif // MOVECONTROLWIDGET_H
