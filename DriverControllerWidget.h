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

    void on_spinPosition_valueChanged(int arg1);

    void on_ButtonPosSet_clicked();

private:
    Ui::DriverControllerWidget *ui;
    ChannelTableModel * mModel;
    MBRead *mReadBuffer;
    MBWrite *mWriteBuffer;
    int CurrentNumber;
    int CurrentNOMB;
    bool Reverce;

};

#endif // DRIVERCONTROLLERWIDGET_H
