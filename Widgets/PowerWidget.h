#ifndef POWERWIDGET_H
#define POWERWIDGET_H

#include <QWidget>
#include <QTimer>
#include "BufferController.h"

namespace Ui {
class PowerWidget;
}

class PowerWidget : public QWidget
{
    Q_OBJECT
private:
    Ui::PowerWidget *ui;
    QTimer *mTimer;//для задержек включения/откулючения напряжений
    int mCurrentTime;
    int mInterval;
    bool isOn;
    MBRead              *mReadBuffer;
public:
    explicit PowerWidget(QWidget *parent = 0);
    ~PowerWidget();
    void UpdatePowerLabel();

private slots:
    void on_ButtonOnAll_clicked();
    void on_ButtonOffAll_clicked();

    void OnTimerTick();


private:
    void ChechBoxSetEnable(bool enable);


};

#endif // POWERWIDGET_H
