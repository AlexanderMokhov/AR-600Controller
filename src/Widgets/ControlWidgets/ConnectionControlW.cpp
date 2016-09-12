#include "ConnectionControlW.h"
#include "ui_ConnectionControlW.h"

ConnectionControlW::ConnectionControlW(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ConnectionControlW)
{
    ui->setupUi(this);
}

ConnectionControlW::~ConnectionControlW()
{
    delete ui;
}

void ConnectionControlW::connectionHandler(bool isConnect)
{
    ui->ButtonConnect->setChecked(isConnect);
}

void ConnectionControlW::on_ButtonConnect_clicked(bool checked)
{
    if(checked)
    {
        std::string host = ui->HostAddress->text().toStdString();
        int receivePort = ui->LocalPort->value();
        int sendPort = ui->RemotePort->value();

        SettingsStorage::Inst()->SetHost(host);
        SettingsStorage::Inst()->SetSendPort(sendPort);
        SettingsStorage::Inst()->SetReceivePort(receivePort);

        emit connectEvent(true);
    }
    else
    {
        emit connectEvent(false);
    }

}
