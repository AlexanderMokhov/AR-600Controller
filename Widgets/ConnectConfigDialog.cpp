#include "ConnectConfigDialog.h"
#include "ui_ConnectConfigDialog.h"

ConnectConfigDialog::ConnectConfigDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConnectConfigDialog)
{
    ui->setupUi(this);
    connect(ui->buttonBox,SIGNAL(accepted()),this,SLOT(accepted()));

}

ConnectConfigDialog::~ConnectConfigDialog()
{
    delete ui;
}

void ConnectConfigDialog::Update()
{
    mHost=QString::fromStdString(ConfigController::Instance()->GetHost());
    mSendPort=ConfigController::Instance()->GetSendPort();
    mReceivePort=ConfigController::Instance()->GetReceivePort();

    ui->lineEditHost->setText(mHost);
    ui->lineEditSendPort->setText(QString::number(mSendPort));
    ui->lineEditReceivePort->setText(QString::number(mReceivePort));
}

void ConnectConfigDialog::accepted()
{
    ConfigController::Instance()->SetHost(ui->lineEditHost->text().toStdString());
    ConfigController::Instance()->SetReceivePort(ui->lineEditReceivePort->text().toInt());
    ConfigController::Instance()->SetSendPort(ui->lineEditSendPort->text().toInt());
}
