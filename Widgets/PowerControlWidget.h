#ifndef POWERCONTROLWIDGET_H
#define POWERCONTROLWIDGET_H

#include <QWidget>
#include <QTimer>
#include "BufferController.h"

namespace Ui {
class PowerControlWidget;
}

class PowerControlWidget : public QWidget
{
    Q_OBJECT
private:
    Ui::PowerControlWidget *ui;
    QTimer *mTimer;//для задержек включения/откулючения напряжений
    int mCurrentTime;
    int mInterval;
    bool isOn;
    ReadBuffer              *mReadBuffer;
public:
    explicit PowerControlWidget(QWidget *parent = 0);
    ~PowerControlWidget();
    void UpdatePowerLabel();

private slots:
    void on_ButtonOnAll_clicked();
    void on_ButtonOffAll_clicked();

    void OnTimerTick();


    void on_checkBox48V_clicked(bool checked);

    void on_checkBox8V2_clicked(bool checked);

    void on_checkBox8V1_clicked(bool checked);

    void on_checkBox6V2_clicked(bool checked);

    void on_checkBox6V1_clicked(bool checked);

private:
    void ChechBoxSetEnable(bool enable);


};

#endif // POWERCONTROLWIDGET_H
