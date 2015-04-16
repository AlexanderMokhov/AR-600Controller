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

public:
    explicit PowerWidget(QWidget *parent = 0);
    ~PowerWidget();

private slots:
    void on_ButtonOnAll_clicked();
    void on_ButtonOffAll_clicked();

    void OnTimerTick();

    void on_checkBox48V_clicked(bool checked);

    void on_checkBox8V1_clicked(bool checked);

    void on_checkBox8V2_clicked(bool checked);

    void on_checkBox6V1_clicked(bool checked);

    void on_checkBox6V2_clicked(bool checked);

private:
    Ui::PowerWidget *ui;
    QTimer *mTimer;//для задержек включения/откулючения напряжений
    int mCurrentTime;
    int mInterval = 2000;
    bool isOn;

};

#endif // POWERWIDGET_H
