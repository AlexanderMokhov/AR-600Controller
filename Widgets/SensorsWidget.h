#ifndef SENSORSWIDGET_H
#define SENSORSWIDGET_H

#include <QWidget>
#include "ConfigController.h"
#include "SensorTableModel.h"
#include <QItemSelectionModel>
#include "BufferController.h"

namespace Ui {
class SensorsWidget;
}

class SensorsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SensorsWidget(QWidget *parent = 0);
    ~SensorsWidget();
    void ShowConfigData();
    SensorTableModel *getModel();
    void UpdatePos();
private:
    Ui::SensorsWidget *ui;
    SensorTableModel *mModel;
    QItemSelectionModel *mSelectionModel;
signals:
    void RowChanged(int cRow);
private slots:
    void OnRowChanged();

};

#endif // SENSORSWIDGET_H
