#ifndef MOTIONCONTROLW_H
#define MOTIONCONTROLW_H

#include <QWidget>
#include <QFileDialog>
#include <QStateMachine>
#include <QState>
#include <QSignalTransition>
#include <QProgressDialog>
#include <QFuture>
#include <QtConcurrent/QtConcurrent>

#include "Management/SettingsStorage.h"
#include "Packets/ARPacketManager.h"
#include "Models/MotorTableModel.h"

#include "Management/MoveController.h"
#include "Management/MoveCorrector.h"
#include "Management/MovesStorage.h"
#include "Management/Mover.h"

namespace Ui {
class MotionControlW;
}

class MotionControlW : public QWidget
{
    Q_OBJECT
public:
    //public methods
    explicit MotionControlW(QWidget *parent = 0);
    ~MotionControlW();

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
    void on_StartB_clicked();
    void on_StopB_clicked();
    void on_GoStartPosB_clicked();
    void on_StartFileB_clicked();
    void on_UseUserPGateB_clicked(bool checked);
    void on_UseUserIGateB_clicked(bool checked);

private:
    //private variable
    Ui::MotionControlW *ui;
    QString DefaultText;
    bool IsLog;

    QStateMachine *machine;
    QState        *statePlay;
    QState        *stateStop;
    QState        *stateNotOpenFile;
    bool          isMoveFile;
    Mover         *m_mover;
};

#endif // MOTIONCONTROLW_H
