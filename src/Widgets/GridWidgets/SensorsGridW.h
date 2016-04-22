#ifndef SENSORSGRIDW_H
#define SENSORSGRIDW_H

#include <QWidget>
#include <QItemSelectionModel>

#include "Management/SettingsStorage.h"
#include "Models/SensorTableModel.h"
#include "Buffers/ARPacketManager.h"

namespace Ui {
class SensorsGridW;
}

class SensorsGridW : public QWidget
{
    Q_OBJECT
public:
    //public methods
    explicit SensorsGridW(QWidget *parent = 0);
    ~SensorsGridW();

    void ShowConfigData();
    SensorTableModel *getModel();
    void UpdatePos();

signals:
    void RowChanged(int cRow);

private slots:
    void OnRowChanged();

private:
    //private variable
    Ui::SensorsGridW *ui;
    SensorTableModel *mModel;
    QItemSelectionModel *mSelectionModel;
};

#endif // SENSORSGRIDW_H
