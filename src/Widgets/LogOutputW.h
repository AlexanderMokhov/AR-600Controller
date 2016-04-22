#ifndef LOGOUTPUTW_H
#define LOGOUTPUTW_H

#include <QWidget>
#include <QTime>
#include <QTimer>

#include <string>
#include <vector>

#include "Management/LogMaster.h"

namespace Ui {
class LogOutputW;
}

class LogOutputW : public QWidget
{
    Q_OBJECT

public:
    explicit LogOutputW(QWidget *parent = 0);
    ~LogOutputW();

    void addMessage(QString message);
    void startWrite();

private slots:
    void OnTimerTick();

private:
    //private variable
    Ui::LogOutputW *ui;
    QTimer *mTimer;
    int mTime;
    int mInterval;

    //private methods
    void updateData();

};

#endif // LOGOUTPUTW_H
