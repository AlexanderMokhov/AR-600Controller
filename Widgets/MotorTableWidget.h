#ifndef MOTORTABLEWIDGET_H
#define MOTORTABLEWIDGET_H

#include <QWidget>
#include "ConfigController.h"
#include "TableModelMotor.h"
#include <QItemSelectionModel>
#include "BufferController.h"

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
    TableModelMotor *getModel();
    void UpdatePos();
private:
    Ui::MotorTableWidget *ui;
    TableModelMotor *mModel;
    QItemSelectionModel *mSelectionModel;
public slots:
    void Activate();
    void Disactivate();
signals:
    void RowChanged(int cRow);
private slots:
    void OnRowChanged();
};

#endif // MOTORTABLEWIDGET_H
