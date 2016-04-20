#include "AdditionControlW.h"
#include "ui_AdditionControlW.h"

AdditionControlW::AdditionControlW(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AdditionControlW)
{
    ui->setupUi(this);
}

AdditionControlW::~AdditionControlW()
{
    delete ui;
}
