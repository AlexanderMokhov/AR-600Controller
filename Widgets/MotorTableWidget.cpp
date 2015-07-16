#include "MotorTableWidget.h"
#include "ui_MotorTableWidget.h"

MotorTableWidget::MotorTableWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MotorTableWidget)
{
    ui->setupUi(this);

    //заполнение таблицы приводов
    mModel = new MotorTableModel();
    ui->MotorTableView->setModel(mModel);

    mSelectionModel = ui->MotorTableView->selectionModel();

    ui->MotorTableView->verticalHeader()->hide();
    ui->MotorTableView->verticalHeader()->resizeSections(QHeaderView::Fixed);
    ui->MotorTableView->resizeColumnsToContents();
    ui->MotorTableView->horizontalHeader()->setSectionResizeMode(1,QHeaderView::Stretch);
    ui->MotorTableView->horizontalHeader()->setSectionResizeMode(2,QHeaderView::Stretch);
    ui->MotorTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    connect(ui->MotorTableView,SIGNAL(clicked(QModelIndex)),this,SLOT(OnRowChanged()));
}

MotorTableWidget::~MotorTableWidget()
{
    delete ui;
}

void MotorTableWidget::ShowConfigData()
{
    std::map<int,Motor> * mMap = ConfigController::Inst()->GetMotorMap();
    mModel->removeRows(0,mModel->rowCount());

    std::map<int,Motor>::iterator it;

    for(it = mMap->begin();it!=mMap->end();++it)
    {
        QString Number = QString::number((*it).first);
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
    ui->MotorTableView->selectRow(0);
    emit RowChanged(0);
}

//происходит при выборе строки в талице моторов
void MotorTableWidget::OnRowChanged()
{
    int cRow = mSelectionModel->currentIndex().row();
    emit RowChanged(cRow);
}

MotorTableModel *MotorTableWidget::getModel()
{
    return mModel;
}

void MotorTableWidget::UpdatePos()
{
    std::map<int,Motor> * mMap = ConfigController::Inst()->GetMotorMap();
    std::map<int,Motor>::iterator it;
    int i=0;
    for(it = mMap->begin();it!=mMap->end();++it)
    {
        int Number = (*it).second.GetNumber();
        QString cPos = QString::number(BufferController::Inst()->GetReadBuffer()->GetMotorAngle(Number));
        mModel->setData(mModel->index(i,3),cPos,Qt::EditRole);

        //начало чтения статуса
        unsigned char status = BufferController::Inst()->GetReadBuffer()->GetMotorStatus(Number);
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

void MotorTableWidget::Activate()
{
    ui->MotorTableView->setEnabled(true);
}

void MotorTableWidget::DisActivate()
{
    ui->MotorTableView->setEnabled(false);
}
