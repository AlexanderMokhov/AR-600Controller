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
    int MinAngle = SettingsStorage::Inst()->GetMotors()->at(cNumber).getMinAngle();
    int MaxAngle = SettingsStorage::Inst()->GetMotors()->at(cNumber).getMaxAngle();

    ui->EditMinOld->setText(QString::number( MinAngle));
    ui->EditMaxOld->setText(QString::number( MaxAngle));

    ui->EditNewMin->setValue(MinAngle);
    ui->EditNewMax->setValue(MaxAngle);
}

void SetLimitsDialog::accepted()
{
    int MinAngle = ui->EditNewMin->value();
    int MaxAngle = ui->EditNewMax->value();
    SettingsStorage::Inst()->GetMotors()->at(cNumber).setMinAngle(MinAngle);
    SettingsStorage::Inst()->GetMotors()->at(cNumber).setMaxAngle(MaxAngle);

    BufferController::Inst()->getBufferSend()->setMotorMinAngle(cNumber, MinAngle);
    BufferController::Inst()->getBufferSend()->setMotorMaxAngle(cNumber, MaxAngle);
}
