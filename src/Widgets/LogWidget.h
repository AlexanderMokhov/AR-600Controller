#ifndef LOGWIDGET_H
#define LOGWIDGET_H

#include <QWidget>
#include <QTime>
#include <QTimer>

#include <string>
#include <vector>

#include "Management/LogMaster.h"

namespace Ui {
class LogWidget;
}

class LogWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LogWidget(QWidget *parent = 0);
    ~LogWidget();

    void addMessage(QString message);
    void startWrite();

private slots:
    void OnTimerTick();

private:
    //private variable
    Ui::LogWidget *ui;
    QTimer *mTimer;
    int mTime;
    int mInterval;

    //private methods
    void updateData();

};

#endif // LOGWIDGET_H
