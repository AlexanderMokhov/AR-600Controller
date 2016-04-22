#include "SensorsGridW.h"
#include "ui_SensorsGridW.h"

SensorsGridW::SensorsGridW(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SensorsGridW)
{
    ui->setupUi(this);

    //заполнение таблицы приводов
    mModel = new SensorTableModel();
    ui->SensorTableView->setModel(mModel);

    mSelectionModel = ui->SensorTableView->selectionModel();

    ui->SensorTableView->verticalHeader()->hide();
    ui->SensorTableView->verticalHeader()->resizeSections(QHeaderView::Fixed);
    ui->SensorTableView->resizeColumnsToContents();
    ui->SensorTableView->horizontalHeader()->setSectionResizeMode(1,QHeaderView::Stretch);
    ui->SensorTableView->horizontalHeader()->setSectionResizeMode(2,QHeaderView::Stretch);
    ui->SensorTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    connect(ui->SensorTableView,SIGNAL(clicked(QModelIndex)),this,SLOT(OnRowChanged()));
}

SensorsGridW::~SensorsGridW()
{
    delete ui;
}

void SensorsGridW::ShowConfigData()
{
    std::map<int,Sensor> * mMap = SettingsStorage::Inst()->GetSensors();
    mModel->removeRows(0,mModel->rowCount());

    for(auto it = mMap->begin(); it != mMap->end(); ++it)
    {
        QString Number = QString::number((*it).first);
        QString Name = QString::fromLocal8Bit((*it).second.getName().c_str());
        QString Value = QString::number((*it).second.getValue());
        mModel->insertRow(Number,Name,Value);
    }
    ui->SensorTableView->selectRow(0);
    emit RowChanged(0);
}

SensorTableModel *SensorsGridW::getModel()
{
    return mModel;
}

void SensorsGridW::UpdatePos()
{
    std::map<int,Sensor> * mMap = SettingsStorage::Inst()->GetSensors();
    int i=0;
    for(auto it = mMap->begin(); it != mMap->end(); ++it)
    {
        int Number = (*it).second.getChannel();//в виде исключения
        int Param = (*it).second.getParam();
        QString cValue = QString::number(ARPacketManager::Inst()->getPacketRecv()->getSensorValue(Number,Param));
        mModel->setData(mModel->index(i,2),cValue,Qt::EditRole);
        i++;
    }
}

void SensorsGridW::OnRowChanged()
{
    int cRow = mSelectionModel->currentIndex().row();
    emit RowChanged(cRow);
}
