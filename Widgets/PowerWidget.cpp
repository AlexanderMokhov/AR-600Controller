#include "PowerWidget.h"
#include "ui_PowerWidget.h"

PowerWidget::PowerWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PowerWidget)
{
    ui->setupUi(this);
    mTimer = new QTimer(this);
    mTimer.setInterval(2000);//интервал 2 секунды
}

PowerWidget::~PowerWidget()
{
    delete ui;
}

//включить все
void PowerWidget::on_ButtonOnAll_clicked()
{
    QTest::qSleep(2000);
}
