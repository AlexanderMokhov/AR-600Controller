#include "SensorTableWidget.h"
#include "ui_SensorTableWidget.h"

SensorTableWidget::SensorTableWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SensorTableWidget)
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

SensorTableWidget::~SensorTableWidget()
{
    delete ui;
}

void SensorTableWidget::ShowConfigData()
{
    std::map<int,Sensor> * mMap = ConfigController::Instance()->GetSensorMap();
    mModel->removeRows(0,mModel->rowCount());

    std::map<int,Sensor>::iterator it;

    for(it = mMap->begin();it!=mMap->end();++it)
    {
        QString Number = QString::number((*it).first);
        QString Name = QString::fromLocal8Bit((*it).second.GetName().c_str());
        QString Value = QString::number((*it).second.GetValue());
        mModel->insertRow(Number,Name,Value);
    }
    ui->SensorTableView->selectRow(0);
    emit RowChanged(0);
}

SensorTableModel *SensorTableWidget::getModel()
{
    return mModel;
}

void SensorTableWidget::UpdatePos()
{
    std::map<int,Sensor> * mMap = ConfigController::Instance()->GetSensorMap();
    std::map<int,Sensor>::iterator it;
    int i=0;
    for(it = mMap->begin();it!=mMap->end();++it)
    {
        int Number = (*it).second.GetNumber();
        int Param = (*it).second.GetParam();
        QString cValue = QString::number(BufferController::Instance()->GetReadBuffer()->GetSensorValue(Number,Param));
        mModel->setData(mModel->index(i,2),cValue,Qt::EditRole);
        i++;
    }
}

void SensorTableWidget::OnRowChanged()
{
    int cRow = mSelectionModel->currentIndex().row();
    emit RowChanged(cRow);
}
