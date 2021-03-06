#include "ConnectConfigDialog.h"
#include "ui_ConnectConfigDialog.h"

ConnectConfigDialog::ConnectConfigDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConnectConfigDialog)
{
    ui->setupUi(this);

    //Запретить изменение размера окна begin
    setMaximumHeight(sizeHint().height());
    setMaximumWidth(sizeHint().width());
    //Запретить изменение размера окна end

    connect(ui->buttonBox,SIGNAL(accepted()),this,SLOT(accepted()));
}

ConnectConfigDialog::~ConnectConfigDialog()
{
    delete ui;
}

void ConnectConfigDialog::Update()
{
    mHost = QString::fromStdString(SettingsStorage::Inst()->GetHost());
    mSendPort = SettingsStorage::Inst()->GetSendPort();
    mReceivePort = SettingsStorage::Inst()->GetReceivePort();

    ui->lineEditHost->setText(mHost);
    ui->lineEditSendPort->setText(QString::number(mSendPort));
    ui->lineEditReceivePort->setText(QString::number(mReceivePort));
}

void ConnectConfigDialog::accepted()
{
    SettingsStorage::Inst()->SetHost(ui->lineEditHost->text().toStdString());
    SettingsStorage::Inst()->SetReceivePort(ui->lineEditReceivePort->text().toInt());
    SettingsStorage::Inst()->SetSendPort(ui->lineEditSendPort->text().toInt());
}
