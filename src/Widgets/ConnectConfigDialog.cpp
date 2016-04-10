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
    mHost = QString::fromStdString(ARCore::Inst()->getSettingStore()->GetHost());
    mSendPort = ARCore::Inst()->getSettingStore()->GetSendPort();
    mReceivePort = ARCore::Inst()->getSettingStore()->GetReceivePort();

    ui->lineEditHost->setText(mHost);
    ui->lineEditSendPort->setText(QString::number(mSendPort));
    ui->lineEditReceivePort->setText(QString::number(mReceivePort));
}

void ConnectConfigDialog::accepted()
{
    ARCore::Inst()->getSettingStore()->SetHost(ui->lineEditHost->text().toStdString());
    ARCore::Inst()->getSettingStore()->SetReceivePort(ui->lineEditReceivePort->text().toInt());
    ARCore::Inst()->getSettingStore()->SetSendPort(ui->lineEditSendPort->text().toInt());
}
