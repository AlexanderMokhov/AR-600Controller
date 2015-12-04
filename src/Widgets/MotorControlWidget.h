#ifndef MOTORCONTROLWIDGET_H
#define MOTORCONTROLWIDGET_H

#include <QWidget>

#include "Management/ConfigController.h"
#include "Buffers/BufferController.h"
#include "Models/MotorTableModel.h"
#include "Management/MoveController.h"

namespace Ui {
class MotorControlWidget;
}

class MotorControlWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MotorControlWidget(QWidget *parent = 0);
    ~MotorControlWidget();
    void setModel(MotorTableModel *model);
    void UpdateData();

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
    enum States {TRACE, STOP, STOPBRAKE, RELAX, CALIBRATE};
    States state;

    Ui::MotorControlWidget *ui;
    MotorTableModel * mModel;
    BufferReceive *mReadBuffer;
    BufferSend *mWriteBuffer;
    int currentRow;
    int CurrentNumber;
    bool Reverce;
    int ReverceCoeff;
signals:
    void PropertyChanged(int Number);
public slots:
    void RowChanged(int cRow);

};

#endif // MOTORCONTROLWIDGET_H
