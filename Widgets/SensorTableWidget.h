#ifndef SENSORTABLEWIDGET_H
#define SENSORTABLEWIDGET_H

#include <QWidget>
#include "ConfigController.h"
#include "SensorTableModel.h"
#include <QItemSelectionModel>
#include "BufferController.h"

namespace Ui {
class SensorTableWidget;
}

class SensorTableWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SensorTableWidget(QWidget *parent = 0);
    ~SensorTableWidget();
    void ShowConfigData();
    SensorTableModel *getModel();
    void UpdatePos();
private:
    Ui::SensorTableWidget *ui;
    SensorTableModel *mModel;
    QItemSelectionModel *mSelectionModel;
signals:
    void RowChanged(int cRow);
private slots:
    void OnRowChanged();

};

#endif // SENSORSWIDGET_H
