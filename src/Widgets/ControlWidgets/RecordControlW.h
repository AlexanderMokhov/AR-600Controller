#ifndef RECORDCONTROLW_H
#define RECORDCONTROLW_H
#include "windows.h"
#include <QWidget>
#include <QTimer>
#include <QDateTime>
#include <QDebug>

#include "Management/RecordController.h"
#include "Management/Recorder.h"

#include "Management/LogMaster.h"

namespace Ui {
class RecordControlW;
}

class RecordControlW : public QWidget
{
    Q_OBJECT
public:
    //public methods
    explicit RecordControlW(QWidget *parent = 0);
    ~RecordControlW();

public slots:
    void OnUpdateTime(long time);

private slots:
    void on_ButtonStartRecord_clicked();
    void on_ButtonStopRecord_clicked();
    void StartWriteRecord(int TimeRecord);
    void StopWriteRecord();
    void on_CheckWriteB_clicked(bool checked);

private:
    //private variable
    Ui::RecordControlW *ui;
    int                  mRecordTime;
    int                  mDelay;
    Recorder             *mRecorder;
    bool isWriteForMove;
};

#endif // RECORDCONTROLW_H
