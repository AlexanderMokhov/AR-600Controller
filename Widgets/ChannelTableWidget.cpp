#include "ChanneTableWidget.h"
#include "ui_ChannelTableWidget.h"

ChannelTableWidget::ChannelTableWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChannelTableWidget)
{
    ui->setupUi(this);
    //заполнение таблицы приводов
    mModel = new ChannelTableModel();
    ui->ChannelTableView->setModel(mModel);
    mSelectionModel = ui->ChannelTableView->selectionModel();
    ui->ChannelTableView->verticalHeader()->hide();
    ui->ChannelTableView->verticalHeader()->resizeSections(QHeaderView::ResizeToContents);
    ui->ChannelTableView->horizontalHeader()->resizeSections(QHeaderView::ResizeToContents);
    ui->ChannelTableView->resizeColumnsToContents();

    connect(ui->ChannelTableView,SIGNAL(clicked(QModelIndex)),this,SLOT(OnRowChanged(QModelIndex)));
}

ChannelTableWidget::~ChannelTableWidget()
{
    delete ui;
}

void ChannelTableWidget::ShowConfigData()
{
    std::map<unsigned int,DriverSettingsItem> * mMap = ConfigController::Instance()->GetConfigMap();
    mModel->removeRows(0,mModel->rowCount());

    std::map<unsigned int,DriverSettingsItem>::iterator it;

    for(it = mMap->begin();it!=mMap->end();++it)
    {
        QString Number = QString::number((*it).first);
        QString NumberBuffer = QString::number((*it).second.GetNumberBuffer());
        QString Name = QString::fromStdString((*it).second.GetName());
        QString Status = "0";
        bool Reverce = (*it).second.GetReverce();
        QString sReverce = QString::number(Reverce);
        QString MinPos = QString::number((*it).second.GetMinPos());
        QString MaxPos = QString::number((*it).second.GetMaxPos());
        QString KP = QString::number((*it).second.GetStiff());
        QString KI = QString::number((*it).second.GetDump());
        QString KD = QString::number((*it).second.GetTorque());
        QString Ilim = QString::number((*it).second.GetIlim());
        mModel->insertRow(Number,Name,Status,"0",MinPos,MaxPos,sReverce,KP,KI,KD,Ilim);
    }
    ui->ChannelTableView->selectRow(0);
    emit RowChanged(0);
}

//происходит при выборе строки в талице моторов
void ChannelTableWidget::OnRowChanged(QModelIndex index)
{
    int cRow = mSelectionModel->currentIndex().row();
    emit RowChanged(cRow);
}

ChannelTableModel *ChannelTableWidget::getModel()
{
    return mModel;
}

