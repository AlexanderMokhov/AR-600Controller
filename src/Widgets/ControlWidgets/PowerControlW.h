#ifndef POWERCONTROLW_H
#define POWERCONTROLW_H

#include <QWidget>
#include <QPushButton>
#include <QIcon>
#include <QTimer>

#include "Packets/ARPacketManager.h"
#include "Management/LogMaster.h"

namespace Ui {
class PowerControlW;
}

class PowerControlW : public QWidget
{
    Q_OBJECT

public:
    //public methods
    explicit PowerControlW(QWidget *parent = 0);
    ~PowerControlW();

    void updateInfo();

private slots:
    void onPowerButtonsClicked();
    void on48VChanged(bool checked);
    void on8V2Changed(bool checked);
    void on8V1Changed(bool checked);
    void on6V2Changed(bool checked);
    void on6V1Changed(bool checked);

    void onAllPowerChanged(bool checked);
    void onRebootPower();
    void stepRebootPower();

    void OnTimerTick();

private:
    //private variable
    Ui::PowerControlW *ui;
    enum PowerStates {REBOOT_POWER_START, REBOOT_POWER_DOWN, REBOOT_POWER_UP, NOT_REBOOT};

    PowerStates m_state;

    QTimer *mTimer;
    int mTime;
    int mInterval;
    bool isOn;

    //private methods
    void initWidgets();

};

#endif // POWERCONTROLW_H
