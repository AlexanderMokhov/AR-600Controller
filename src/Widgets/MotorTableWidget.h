#ifndef MOTORTABLEWIDGET_H
#define MOTORTABLEWIDGET_H

#include <QWidget>
#include <QItemSelectionModel>
#include <QMenu>

#include "Management/SettingsStorage.h"
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
    explicit MotorTableWidget(QWidget *parent = 0);
    ~MotorTableWidget();

    void ShowConfigData();
    MotorTableModel *getModel();
    void UpdatePos();
private:
    Ui::MotorTableWidget *ui;
    MotorTableModel *mModel;
    QItemSelectionModel *mSelectionModel;
    SetLimitsDialog *mSetLimitsDlg;
public slots:
    void Activate();
    void Disactivate();
signals:
    void RowChanged(int cRow);
private slots:
    void OnRowChanged();
    void ShowContextMenu(const QPoint& pos);
    void onSetEnableAction();
    void onSetLimitsAction();
    void onSetLimitsAccepted();
};

#endif // MOTORTABLEWIDGET_H
