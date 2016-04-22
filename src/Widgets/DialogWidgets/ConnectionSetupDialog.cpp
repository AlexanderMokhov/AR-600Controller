#include "ConnectionSetupDialog.h"
#include "ui_ConnectionSetupDialog.h"

ConnectionSetupDialog::ConnectionSetupDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConnectionSetupDialog)
{
    ui->setupUi(this);

    //Запретить изменение размера окна begin
    setMaximumHeight(sizeHint().height());
    setMaximumWidth(sizeHint().width());
    //Запретить изменение размера окна end

    connect(ui->buttonBox,SIGNAL(accepted()),this,SLOT(accepted()));
}

ConnectionSetupDialog::~ConnectionSetupDialog()
{
    delete ui;
}

void ConnectionSetupDialog::Update()
{
    mHost = QString::fromStdString(SettingsStorage::Inst()->GetHost());
    mSendPort = SettingsStorage::Inst()->GetSendPort();
    mReceivePort = SettingsStorage::Inst()->GetReceivePort();

    ui->lineEditHost->setText(mHost);
    ui->lineEditSendPort->setText(QString::number(mSendPort));
    ui->lineEditReceivePort->setText(QString::number(mReceivePort));
}

void ConnectionSetupDialog::accepted()
{
    SettingsStorage::Inst()->SetHost(ui->lineEditHost->text().toStdString());
    SettingsStorage::Inst()->SetReceivePort(ui->lineEditReceivePort->text().toInt());
    SettingsStorage::Inst()->SetSendPort(ui->lineEditSendPort->text().toInt());
}
