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
    ui->ChannelTableView->verticalHeader()->resizeSections(QHeaderView::Fixed);
    ui->ChannelTableView->resizeColumnsToContents();
    ui->ChannelTableView->horizontalHeader()->setSectionResizeMode(1,QHeaderView::Stretch);
    ui->ChannelTableView->horizontalHeader()->setSectionResizeMode(2,QHeaderView::Stretch);
    ui->ChannelTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    connect(ui->ChannelTableView,SIGNAL(clicked(QModelIndex)),this,SLOT(OnRowChanged()));
}

ChannelTableWidget::~ChannelTableWidget()
{
    delete ui;
}

void ChannelTableWidget::ShowConfigData()
{
    std::map<int,Driver> * mMap = ConfigController::Instance()->GetDriverMap();
    mModel->removeRows(0,mModel->rowCount());

    std::map<int,Driver>::iterator it;

    for(it = mMap->begin();it!=mMap->end();++it)
    {
        QString Number = QString::number((*it).first);
        QString NumberBuffer = QString::number((*it).second.GetNumberBuffer());
        //QString Name = QString::fromStdString((*it).second.GetName());
        QString Name = QString::fromLocal8Bit((*it).second.GetName().c_str());
        QString Status = "0";
        bool Reverce = (*it).second.GetReverce();
        QString sReverce = QString::number(Reverce);
        QString MinPos = QString::number((*it).second.GetMinPos());
        QString MaxPos = QString::number((*it).second.GetMaxPos());
        QString KP = QString::number((*it).second.GetStiff());
        QString KI = QString::number((*it).second.GetDump());
        QString KD = QString::number((*it).second.GetTorque());
        QString Calibration = QString::number((*it).second.GetCalibration());
        bool Enable = (*it).second.GetEnable();
        QString sEnable = QString::number(Enable);
        mModel->insertRow(Number,Name,Status,"0",MinPos,MaxPos,sReverce,KP,KI,KD,Calibration,sEnable);
    }
    ui->ChannelTableView->selectRow(0);
    emit RowChanged(0);
}

//происходит при выборе строки в талице моторов
void ChannelTableWidget::OnRowChanged()
{
    int cRow = mSelectionModel->currentIndex().row();
    emit RowChanged(cRow);
}

ChannelTableModel *ChannelTableWidget::getModel()
{
    return mModel;
}

void ChannelTableWidget::UpdatePos()
{
    std::map<int,Driver> * mMap = ConfigController::Instance()->GetDriverMap();
    std::map<int,Driver>::iterator it;
    int i=0;
    for(it = mMap->begin();it!=mMap->end();++it)
    {
        int NOMB = (*it).second.GetNumberBuffer();
        QString cPos = QString::number(BufferController::Instance()->GetReadBuffer()->Get_MOTOR_CPOS(NOMB));
        mModel->setData(mModel->index(i,3),cPos,Qt::EditRole);

        //начало чтения статуса
        unsigned char status = BufferController::Instance()->GetReadBuffer()->Get_MOTOR_STAT(NOMB);
        QString statusString;

        if((unsigned char)(status & 0) == 0)
        {statusString="BRAKE";}
        if((unsigned char)(status & 1) == 1)
        {statusString+="-DT";}
        if((unsigned char)(status & 2) == 2)
        {statusString="RELAX";}
        if((unsigned char)(status & 3) == 3)
        {statusString="TRACE";}

        mModel->setData(mModel->index(i,2),statusString);
        i++;
    }
}

void ChannelTableWidget::Activate()
{
    ui->ChannelTableView->setEnabled(true);
}

void ChannelTableWidget::DisActivate()
{
    ui->ChannelTableView->setEnabled(false);
}
