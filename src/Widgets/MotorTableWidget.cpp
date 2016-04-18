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
    ui->MotorTableView->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    ui->MotorTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    connect(ui->MotorTableView,SIGNAL(clicked(QModelIndex)),this,SLOT(OnRowChanged()));

    ui->MotorTableView->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->MotorTableView, SIGNAL(customContextMenuRequested(const QPoint&)),
        this, SLOT(ShowContextMenu(const QPoint&)));
}

MotorTableWidget::~MotorTableWidget()
{
    delete ui;
}

void MotorTableWidget::ShowConfigData()
{
    std::map<int,Motor> * mMap = SettingsStorage::Inst()->GetMotors();
    mModel->removeRows(0,mModel->rowCount());

    for(auto it = mMap->begin();it != mMap->end(); ++it)
    {
        QString Number = QString::number((*it).first);
        QString Name = QString::fromLocal8Bit((*it).second.getName().c_str());
        QString Status = "0";
        QString MinAngle = QString::number((*it).second.getMinAngle());
        QString MaxAngle = QString::number((*it).second.getMaxAngle());
        QString KP = QString::number((*it).second.getPIDGates()->getPGate());
        QString KI = QString::number((*it).second.getPIDGates()->getIGate());
        QString KD = QString::number((*it).second.getPIDGates()->getDGate());
        mModel->insertRow(Number,Name,"0",MinAngle,MaxAngle,KP,KI,KD,Status);
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

void MotorTableWidget::UpdateAngle()
{
    ui->MotorTableView->resizeColumnsToContents();
    ui->MotorTableView->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);

    std::map<int,Motor> * mMap = SettingsStorage::Inst()->GetMotors();
    int i=0;
    for(auto it = mMap->begin(); it != mMap->end(); ++it)
    {
        int Number = (*it).second.getNumber();
        QString cPos = QString::number(ARPacketManager::Inst()->getPacketRecv()->getMotorAngle(Number));
        mModel->setData(mModel->index(i,2),cPos,Qt::EditRole);

        //начало чтения статуса
        unsigned char status = ARPacketManager::Inst()->getPacketRecv()->getMotorState(Number);
        QString statusString;

        if((unsigned char)(status & 0) == 0)
        {statusString = "Фиксация";}
        if((unsigned char)(status & 1) == 1)
        {statusString = "Выключен";}
        if((unsigned char)(status & 2) == 2)
        {statusString = "Свободен";}
        if((unsigned char)(status & 3) == 3)
        {statusString = "Слежение";}

        mModel->setData(mModel->index(i,8),statusString);
        i++;
    }
}

void MotorTableWidget::Activate()
{
    ui->MotorTableView->setEnabled(true);
}

void MotorTableWidget::Disactivate()
{
    ui->MotorTableView->setEnabled(false);
}

void MotorTableWidget::ShowContextMenu(const QPoint &pos)
{
    if( mModel->rowCount() == 0 ) return;

    QPoint globalPos = ui->MotorTableView->mapToGlobal(pos);

    QMenu myMenu;

    int cRow = mSelectionModel->currentIndex().row();
    int Number = mModel->mDataList.at(cRow)->getNumber();
    bool isEnable = SettingsStorage::Inst()->GetMotors()->at(Number).getEnable();

    string text = "Выключить";
    if(!isEnable) text = "Включить";
    QAction *SetEnableAction = new QAction(tr(text.c_str()), this);
    QAction *SetLimitsAction = new QAction(tr("Изменение пределов по позиции"), this);

    connect(SetEnableAction,SIGNAL(triggered()), SLOT(onSetEnableAction()));
    connect(SetLimitsAction,SIGNAL(triggered()), SLOT(onSetLimitsAction()));

    myMenu.addAction(SetEnableAction);
    myMenu.addAction(SetLimitsAction);

    myMenu.exec(globalPos);
}

void MotorTableWidget::onSetEnableAction()
{
    int cRow = mSelectionModel->currentIndex().row();
    int Number = mModel->mDataList.at(cRow)->getNumber();
    bool isEnable = SettingsStorage::Inst()->GetMotors()->at(Number).getEnable();
    ARPacketManager::Inst()->getPacketSend()->setMotorEnable(Number, !isEnable);
    SettingsStorage::Inst()->GetMotors()->at(Number).setEnable(!isEnable);
    mModel->setData(mModel->index(cRow,11), QString::number(!isEnable));
}

void MotorTableWidget::onSetLimitsAction()
{
    int cRow = mSelectionModel->currentIndex().row();
    int Number = mModel->mDataList.at(cRow)->getNumber();
    mSetLimitsDlg = new SetLimitsDialog();
    connect(mSetLimitsDlg, SIGNAL(accepted()),this,SLOT(onSetLimitsAccepted()));
    mSetLimitsDlg->setModal(true);
    mSetLimitsDlg->Update(Number);
    mSetLimitsDlg->show();
}

void MotorTableWidget::onSetLimitsAccepted()
{
    int cRow = mSelectionModel->currentIndex().row();
    int Number = mModel->mDataList.at(cRow)->getNumber();
    mModel->mDataList.at(cRow)->setMinAngle(SettingsStorage::Inst()->GetMotors()->at(Number).getMinAngle());
    mModel->mDataList.at(cRow)->setMaxAngle(SettingsStorage::Inst()->GetMotors()->at(Number).getMaxAngle());
}
