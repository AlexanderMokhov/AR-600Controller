#ifndef MOTORTABLEWIDGET_H
#define MOTORTABLEWIDGET_H

#include <QWidget>
#include <QItemSelectionModel>
#include <QMenu>

#include "Management/ARCore.h"
#include "Models/MotorTableModel.h"
#include "Buffers/BufferController.h"
#include "SetLimitsDialog.h"

namespace Ui {
class MotorTableWidget;
}

class MotorTableWidget : public QWidget
{
    Q_OBJECT
public:
    //public methods
    explicit MotorTableWidget(QWidget *parent = 0);
    ~MotorTableWidget();

    void ShowConfigData();
    MotorTableModel *getModel();
    void UpdateAngle();

signals:
    void RowChanged(int cRow);

public slots:
    void Activate();
    void Disactivate();

private slots:
    void OnRowChanged();
    void ShowContextMenu(const QPoint& pos);
    void onSetEnableAction();
    void onSetLimitsAction();
    void onSetLimitsAccepted();

private:
    //private variable
    Ui::MotorTableWidget *ui;
    MotorTableModel *mModel;
    QItemSelectionModel *mSelectionModel;
    SetLimitsDialog *mSetLimitsDlg;
};

#endif // MOTORTABLEWIDGET_H
