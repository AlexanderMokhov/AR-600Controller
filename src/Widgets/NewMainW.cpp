#include "NewMainW.h"
#include "ui_NewMainW.h"

NewMainW::NewMainW(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NewMainW)
{
    ui->setupUi(this);
}

NewMainW::~NewMainW()
{
    delete ui;
}
