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
    //ui->ChannelTableView->horizontalHeader()->resizeSections(QHeaderView::ResizeToContents);
    ui->ChannelTableView->resizeColumnsToContents();

    ui->ChannelTableView->horizontalHeader()->setSectionResizeMode(1,QHeaderView::Stretch);
    ui->ChannelTableView->horizontalHeader()->setSectionResizeMode(2,QHeaderView::Stretch);

    ui->ChannelTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

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

void ChannelTableWidget::UpdatePos()
{
    std::map<unsigned int,DriverSettingsItem> * mMap = ConfigController::Instance()->GetConfigMap();
    std::map<unsigned int,DriverSettingsItem>::iterator it;
    int i=0;
    for(it = mMap->begin();it!=mMap->end();++it)
    {
        int NOMB = (*it).second.GetNumberBuffer();
        QString cPos = QString::number(BufferController::Instance()->GetReadBuffer()->Get_MOTOR_CPOS(NOMB));
        mModel->setData(mModel->index(i,3),cPos,Qt::EditRole);

        //начало чтения статуса
        unsigned char status = BufferController::Instance()->GetReadBuffer()->Get_MOTOR_STAT(NOMB);
        int BRK=0,DT=0,RELAX=0,TRACE=0;
        QString statusString;

        if((unsigned char)(status & 0) == 0)
            BRK=1;
        if((unsigned char)(status & 1) == 1)
            DT=1;
        if((unsigned char)(status & 2) == 2)
        {
            RELAX=1;
            BRK=0;
        }
        if((unsigned char)(status & 3) == 3)
        {
            TRACE=1;
            BRK=0;
            DT=0;
            RELAX=0;
        }
        if(BRK){statusString+="BRAKE";}
        if(DT){statusString+="-DT";}
        if(RELAX){statusString+="RELAX";}
        if(TRACE){statusString+="TRACE";}
        //конец чтения статуса

        mModel->setData(mModel->index(i,2),statusString);
        i++;
    }
}

