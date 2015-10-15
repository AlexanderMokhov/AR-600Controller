#ifndef MOTORTABLEWIDGET_H
#define MOTORTABLEWIDGET_H

#include <QWidget>
#include <QItemSelectionModel>

#include "Management/ConfigController.h"
#include "Models/MotorTableModel.h"
#include "Buffers/BufferController.h"

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
public slots:
    void Activate();
    void Disactivate();
signals:
    void RowChanged(int cRow);
private slots:
    void OnRowChanged();
};

#endif // MOTORTABLEWIDGET_H
