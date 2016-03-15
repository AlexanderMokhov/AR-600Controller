#include "modelWidget.h"
#include "ui_modelWidget.h"

modelWidget::modelWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::modelWidget)
{
    ui->setupUi(this);
}

modelWidget::~modelWidget()
{
    delete ui;
}
