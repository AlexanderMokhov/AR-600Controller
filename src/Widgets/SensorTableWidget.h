#ifndef SENSORTABLEWIDGET_H
#define SENSORTABLEWIDGET_H

#include <QWidget>
#include <QItemSelectionModel>

#include "Management/SettingsStorage.h"
#include "Models/SensorTableModel.h"
#include "Buffers/ARPacketManager.h"

namespace Ui {
class SensorTableWidget;
}

class SensorTableWidget : public QWidget
{
    Q_OBJECT
public:
    //public methods
    explicit SensorTableWidget(QWidget *parent = 0);
    ~SensorTableWidget();

    void ShowConfigData();
    SensorTableModel *getModel();
    void UpdatePos();

signals:
    void RowChanged(int cRow);

private slots:
    void OnRowChanged();

private:
    //private variable
    Ui::SensorTableWidget *ui;
    SensorTableModel *mModel;
    QItemSelectionModel *mSelectionModel;
};

#endif // SENSORSWIDGET_H
