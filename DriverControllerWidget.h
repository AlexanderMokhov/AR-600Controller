#ifndef DRIVERCONTROLLERWIDGET_H
#define DRIVERCONTROLLERWIDGET_H

#include <QWidget>
#include "AR600ControllerConf.h"
#include "BufferController.h"
#include "ChannelTableModel.h"

namespace Ui {
class DriverControllerWidget;
}

class DriverControllerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DriverControllerWidget(QWidget *parent = 0);
    ~DriverControllerWidget();
    void setNumber(int Number);
    void setCurrentRow(int Row);
    void setModel(ChannelTableModel *model);
    void UpdateData();

private slots:
    void on_ButtonSTOP_clicked();

    void on_ButtonBRAKE_clicked();

    void on_ButtonRELAX_clicked();

    void on_ButtonTRACE_clicked();

    void on_ButtonPosSet_clicked();

    void on_groupBoxCalibration_clicked(bool checked);

    void on_ButtonSaveZero_clicked();

    void on_SliderPosition_sliderMoved(int position);

    void on_checkBoxTrace_clicked(bool checked);

    void SliderInit();

private:
    Ui::DriverControllerWidget *ui;
    ChannelTableModel * mModel;
    MBRead *mReadBuffer;
    MBWrite *mWriteBuffer;
    int CurrentNumber;
    int CurrentNOMB;
    bool Reverce;
    bool Calibration;
    bool TRACE;
    int ReverceCoeff;

};

#endif // DRIVERCONTROLLERWIDGET_H
