#include "AdditionalControlW.h"
#include "ui_AdditionalControlW.h"

AdditionalControlW::AdditionalControlW(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AdditionalControlW)
{
    ui->setupUi(this);
}

AdditionalControlW::~AdditionalControlW()
{
    delete ui;
}
