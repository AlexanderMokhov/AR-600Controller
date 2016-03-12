#ifndef RECORDWIDGET_H
#define RECORDWIDGET_H
#include "windows.h"
#include <QWidget>
#include <QTimer>
#include <QDateTime>
#include <QDebug>

#include "Management/RecordController.h"
#include "Management/Recorder.h"

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

private:
    //private variable
    Ui::RecordWidget *ui;
    int                  mRecordTime;
    int                  mDelay;
    Recorder             *mRecorder;
};

#endif // RECORDWIDGET_H
