#include "SetLimitsDialog.h"
#include "ui_SetLimitsDialog.h"

SetLimitsDialog::SetLimitsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SetLimitsDialog)
{
    ui->setupUi(this);
}

SetLimitsDialog::~SetLimitsDialog()
{
    delete ui;
}

void SetLimitsDialog::Update(int cNumber)
{
    int MinAngle = ConfigController::Inst()->GetMotors()->at(2).GetMinPos();
    int MaxAngle = ConfigController::Inst()->GetMotors()->at(2).GetMaxPos();

    ui->EditMinOld->setText(QString::number( MinAngle));
}
