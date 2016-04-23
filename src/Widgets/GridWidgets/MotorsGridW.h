#ifndef MOTORSGRIDW_H
#define MOTORSGRIDW_H

#include <QWidget>
#include <QItemSelectionModel>
#include <QMenu>

#include "Management/SettingsStorage.h"
#include "Models/MotorTableModel.h"
#include "Packets/ARPacketManager.h"
#include "../DialogWidgets/SetLimitsDialog.h"

namespace Ui {
class MotorsGridW;
}

class MotorsGridW : public QWidget
{
    Q_OBJECT
public:
    //public methods
    explicit MotorsGridW(QWidget *parent = 0);
    ~MotorsGridW();

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
    Ui::MotorsGridW *ui;
    MotorTableModel *mModel;
    QItemSelectionModel *mSelectionModel;
    SetLimitsDialog *mSetLimitsDlg;
};

#endif // MOTORSGRIDW_H
