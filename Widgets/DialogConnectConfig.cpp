#include "DialogConnectConfig.h"
#include "ui_DialogConnectConfig.h"

DialogConnectConfig::DialogConnectConfig(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogConnectConfig)
{
    ui->setupUi(this);
    connect(ui->buttonBox,SIGNAL(accepted()),this,SLOT(accepted()));

}

DialogConnectConfig::~DialogConnectConfig()
{
    delete ui;
}

void DialogConnectConfig::Update()
{
    mHost=QString::fromStdString(ConfigController::Instance()->GetHost());
    mSendPort=ConfigController::Instance()->GetSendPort();
    mReceivePort=ConfigController::Instance()->GetReceivePort();

    ui->lineEditHost->setText(mHost);
    ui->lineEditSendPort->setText(QString::number(mSendPort));
    ui->lineEditReceivePort->setText(QString::number(mReceivePort));
}

DialogConnectConfig::accepted()
{
    ConfigController::Instance()->SetHost(ui->lineEditHost->text().toStdString());
    ConfigController::Instance()->SetReceivePort(ui->lineEditReceivePort->text().toInt());
    ConfigController::Instance()->SetSendPort(ui->lineEditSendPort->text().toInt());
}
