#ifndef DEVICELOGWIDGET_H
#define DEVICELOGWIDGET_H
#include "windows.h"
#include <QWidget>
#include <QTimer>
#include <QDateTime>
#include "DeviceLogController.h"
#include <QDebug>

namespace Ui {
class DeviceLogWidget;
}

class DeviceLogWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DeviceLogWidget(QWidget *parent = 0);
    ~DeviceLogWidget();

private slots:
    void on_ButtonStartRecord_clicked();

    void on_ButtonStopRecord_clicked();

private:
    Ui::DeviceLogWidget *ui;
    QTimer              *mRecordTimer;
    int                  mCurrentTime;
    int                  mRecordTime;
    int                  mDelay;

    void SaveData();
private slots:
    void WriteRecord();
    void StartWriteLog(int TimeRecord);
    void StopWriteLog();
};

#endif // DEVICELOGWIDGET_H
