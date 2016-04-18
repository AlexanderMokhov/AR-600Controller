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
