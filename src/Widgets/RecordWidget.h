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

private:
    Ui::RecordWidget *ui;
    int                  mRecordTime;
    int                  mDelay;
    Recorder             *mRecorder;
public:
    explicit RecordWidget(QWidget *parent = 0);
    ~RecordWidget();
private slots:
    void on_ButtonStartRecord_clicked();
    void on_ButtonStopRecord_clicked();
    void StartWriteRecord(int TimeRecord);
    void StopWriteRecord();
public slots:
    void OnUpdateTime(long time);
};

#endif // RECORDWIDGET_H
