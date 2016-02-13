#include "SetLimitsDialog.h"
#include "ui_SetLimitsDialog.h"

SetLimitsDialog::SetLimitsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SetLimitsDialog)
{
    ui->setupUi(this);
    connect(ui->buttonBox,SIGNAL(accepted()),this,SLOT(accepted()));
}

SetLimitsDialog::~SetLimitsDialog()
{
    delete ui;
}

void SetLimitsDialog::Update(int cNumber)
{
    this->cNumber = cNumber;
    int MinAngle = ConfigController::Inst()->GetMotors()->at(cNumber).GetMinPos();
    int MaxAngle = ConfigController::Inst()->GetMotors()->at(cNumber).GetMaxPos();

    ui->EditMinOld->setText(QString::number( MinAngle));
    ui->EditMaxOld->setText(QString::number( MaxAngle));

    ui->EditNewMin->setValue(MinAngle);
    ui->EditNewMax->setValue(MaxAngle);
}

void SetLimitsDialog::accepted()
{
    //ConfigController::Inst()->GetMotors()->at(cNumber).
}
