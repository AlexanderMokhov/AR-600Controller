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

private:
    Ui::DriverControllerWidget *ui;
    ChannelTableModel * mModel;
    MBRead *mReadBuffer;
    MBWrite *mWriteBuffer;
    int CurrentNumber;

};

#endif // DRIVERCONTROLLERWIDGET_H
