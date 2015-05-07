#include "SensorsWidget.h"
#include "ui_SensorsWidget.h"

SensorsWidget::SensorsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SensorsWidget)
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

SensorsWidget::~SensorsWidget()
{
    delete ui;
}

void SensorsWidget::ShowConfigData()
{
    std::map<int,Sensor> * mMap = ConfigController::Instance()->GetSensorMap();
    mModel->removeRows(0,mModel->rowCount());

    std::map<int,Sensor>::iterator it;

    for(it = mMap->begin();it!=mMap->end();++it)
    {
        QString Number = QString::number((*it).first);
        QString Name = QString::fromStdString((*it).second.GetName());
        QString Value = QString::number((*it).second.GetValue());
        mModel->insertRow(Number,Name,Value);
    }
    ui->SensorTableView->selectRow(0);
    emit RowChanged(0);
}

SensorTableModel *SensorsWidget::getModel()
{
    return mModel;
}

void SensorsWidget::UpdatePos()
{
    std::map<int,Sensor> * mMap = ConfigController::Instance()->GetSensorMap();
    std::map<int,Sensor>::iterator it;
    int i=0;
    for(it = mMap->begin();it!=mMap->end();++it)
    {
        QString cValue = QString::number((*it).second.GetValue());
        mModel->setData(mModel->index(i,2),cValue,Qt::EditRole);
        i++;
    }
}

void SensorsWidget::OnRowChanged()
{
    int cRow = mSelectionModel->currentIndex().row();
    emit RowChanged(cRow);
}
