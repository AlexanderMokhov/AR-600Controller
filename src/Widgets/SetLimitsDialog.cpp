#include "SetLimitsDialog.h"
#include "ui_SetLimitsDialog.h"

SetLimitsDialog::SetLimitsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SetLimitsDialog)
{
    ui->setupUi(this);

    //Запретить изменение размера окна begin
    setMaximumHeight(sizeHint().height());
    setMaximumWidth(this->width());
    setMinimumWidth(this->width());
    //Запретить изменение размера окна end

    connect(ui->buttonBox,SIGNAL(accepted()),this,SLOT(accepted()));
}

SetLimitsDialog::~SetLimitsDialog()
{
    delete ui;
}

void SetLimitsDialog::Update(int cNumber)
{
    this->cNumber = cNumber;
    int MinAngle = SettingsStorage::Inst()->GetMotors()->at(cNumber).GetMinPos();
    int MaxAngle = SettingsStorage::Inst()->GetMotors()->at(cNumber).GetMaxPos();

    ui->EditMinOld->setText(QString::number( MinAngle));
    ui->EditMaxOld->setText(QString::number( MaxAngle));

    ui->EditNewMin->setValue(MinAngle);
    ui->EditNewMax->setValue(MaxAngle);
}

void SetLimitsDialog::accepted()
{
    int MinAngle = ui->EditNewMin->value();
    int MaxAngle = ui->EditNewMax->value();
    SettingsStorage::Inst()->GetMotors()->at(cNumber).SetMinPos(MinAngle);
    SettingsStorage::Inst()->GetMotors()->at(cNumber).SetMaxPos(MaxAngle);

    BufferController::Inst()->GetBufferS()->SetMotorMinAngle(cNumber, MinAngle);
    BufferController::Inst()->GetBufferS()->SetMotorMaxAngle(cNumber, MaxAngle);
}
