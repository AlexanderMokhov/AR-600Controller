#ifndef DRIVERLOGWIDGET_H
#define DRIVERLOGWIDGET_H

#include <QWidget>
#include <QTimer>
#include <QDateTime>
#include "DriverLogController.h"

namespace Ui {
class DriverLogWidget;
}

class DriverLogWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DriverLogWidget(QWidget *parent = 0);
    ~DriverLogWidget();

private slots:
    void on_ButtonStartRecord_clicked();

    void on_ButtonStopRecord_clicked();

private:
    Ui::DriverLogWidget *ui;
    DriverLogController *mDriverLogController;
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

#endif // DRIVERLOGWIDGET_H
