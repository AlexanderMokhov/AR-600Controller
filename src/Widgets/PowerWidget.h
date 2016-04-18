#ifndef POWERWIDGET_H
#define POWERWIDGET_H

#include <QWidget>
#include <QTimer>

#include "Buffers/ARPacketManager.h"

namespace Ui {
class PowerWidget;
}

class PowerWidget : public QWidget
{
    Q_OBJECT
public:
    //public methods
    explicit PowerWidget(QWidget *parent = 0);
    ~PowerWidget();
    void UpdatePowerLabel();

private slots:
    void on_ButtonOnAll_clicked();
    void on_ButtonOffAll_clicked();
    void onReboot();
    void OnTimerTick();

    void on_checkBox48V_clicked(bool checked);
    void on_checkBox8V2_clicked(bool checked);
    void on_checkBox8V1_clicked(bool checked);
    void on_checkBox6V2_clicked(bool checked);
    void on_checkBox6V1_clicked(bool checked);

private:
    //private variable
    Ui::PowerWidget *ui;
    QTimer *mTimer;
    int mTime;
    int mInterval;
    bool isOn;

    //private methods
    void ChechBoxSetEnable(bool enable);
};

#endif // POWERWIDGET_H
