#ifndef MOTORSCONTROLW_H
#define MOTORSCONTROLW_H

#include <QWidget>

#include "Management/SettingsStorage.h"
#include "Packets/ARPacketManager.h"
#include "Models/MotorTableModel.h"
#include "Management/MoveController.h"
#include "Management/Mover.h"

namespace Ui {
class MotorsControlW;
}

class MotorsControlW : public QWidget
{
    Q_OBJECT
public:
    //public methods
    explicit MotorsControlW(QWidget *parent = 0);
    ~MotorsControlW();
    void setModel(MotorTableModel *model);
    void UpdateData();

    void setMover(Mover * mover){ m_mover = mover; }

signals:
    void PropertyChanged(int Number);

public slots:
    void RowChanged(int cRow);

private slots:
    void on_ButtonSTOP_clicked();
    void on_ButtonBRAKE_clicked();
    void on_ButtonRELAX_clicked();

    void on_groupBoxCalibration_clicked(bool checked);
    void on_ButtonSaveZero_clicked();

    void on_checkBoxTrace_clicked(bool checked);
    void on_SliderAngle_sliderMoved(int position);

    void on_ButtonStiffWrite_clicked();
    void on_ButtonStiffSave_clicked();
    void on_ButtonDumpSave_clicked();
    void on_ButtonDumpWrite_clicked();

    void on_ButtonGoToPos_clicked();
    void on_ButtonStopGoToPos_clicked();

    void SliderInit();

private:
    //private variable
    enum States {TRACE, STOP, STOPBRAKE, RELAX, CALIBRATE};
    States state;

    Ui::MotorsControlW *ui;
    MotorTableModel * mModel;
    ARPacketRecv *mReadBuffer;
    ARPacketSend *mWriteBuffer;

    int currentRow;
    int CurrentNumber;
    bool Reverce;
    int ReverceCoeff;
    Mover * m_mover;

    //private methods
    void initWidgets();
    void updateInfo();
};

#endif // MOTORSCONTROLW_H
