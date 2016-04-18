#ifndef RECORDWIDGET_H
#define RECORDWIDGET_H
#include "windows.h"
#include <QWidget>
#include <QTimer>
#include <QDateTime>
#include <QDebug>

#include "Management/RecordController.h"
#include "Management/Recorder.h"

#include "Management/LogMaster.h"

namespace Ui {
class RecordWidget;
}

class RecordWidget : public QWidget
{
    Q_OBJECT
public:
    //public methods
    explicit RecordWidget(QWidget *parent = 0);
    ~RecordWidget();

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
    Ui::RecordWidget *ui;
    int                  mRecordTime;
    int                  mDelay;
    Recorder             *mRecorder;
    bool isWriteForMove;
};

#endif // RECORDWIDGET_H
