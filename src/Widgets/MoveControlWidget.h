#ifndef MOVECONTROLWIDGET_H
#define MOVECONTROLWIDGET_H

#include <QWidget>
#include <QFileDialog>
#include <QStateMachine>
#include <QState>
#include <QPropertyAnimation>
#include <QSignalTransition>

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
    explicit MoveControlWidget(QWidget *parent = 0);
    ~MoveControlWidget();

    void StartPlayFile(bool mode);
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
    Ui::MoveControlWidget *ui;
    QString DefaultText;
    bool IsLog;

    QStateMachine *machine;
    QState        *statePlay;
    QState        *stateStop;
    QState        *stateNotOpenFile;
    bool          isMoveFile;
    Mover         *mMover;

signals:
    StartWriteRecord(int LogTime);
    StopWriteRecord();
    FileLoaded(QString FileName,int CountRows, int Duration, bool Mode);
    PlayStart();
    PlayStop();
public slots:
    void startMove();
    void openFile(QString fileName, bool mode);
    void startStdMove();
};

#endif // MOVECONTROLWIDGET_H
