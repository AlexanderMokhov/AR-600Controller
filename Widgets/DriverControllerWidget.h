#ifndef DRIVERCONTROLLERWIDGET_H
#define DRIVERCONTROLLERWIDGET_H

#include <QWidget>
#include "ConfigController.h"
#include "BufferController.h"
#include "ChannelTableModel.h"
#include "CommandController.h"

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

    void on_groupBoxCalibration_clicked(bool checked);

    void on_ButtonSaveZero_clicked();

    void on_SliderPosition_sliderMoved(int position);

    void on_checkBoxTrace_clicked(bool checked);

    void SliderInit();

    void on_ButtonStiffWrite_clicked();

    void on_ButtonStiffSave_clicked();

    void on_ButtonDumpSave_clicked();

    void on_ButtonDumpWrite_clicked();

    void on_ButtonGoToPos_clicked();

    void on_ButtonStopGoToPos_clicked();

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
signals:
    void PropertyChanged(int Number);
public slots:
    void RowChanged(int cRow);

};

#endif // DRIVERCONTROLLERWIDGET_H
