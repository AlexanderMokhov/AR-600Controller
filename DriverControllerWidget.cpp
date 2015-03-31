#include "DriverControllerWidget.h"
#include "ui_DriverControllerWidget.h"

DriverControllerWidget::DriverControllerWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DriverControllerWidget)
{
    ui->setupUi(this);
    mReadBuffer = BufferController::Instance()->getReadBuffer();
    mWriteBuffer = BufferController::Instance()->getWriteBuffer();
}

DriverControllerWidget::~DriverControllerWidget()
{
    delete ui;
}

void DriverControllerWidget::setNumber(int Number)
{
    ui->spinNumber->setValue(Number);
}

void DriverControllerWidget::setCurrentRow(int Row)
{
    CurrentNumber = mModel->data(mModel->index(Row,0),Qt::EditRole).toInt();
    ui->spinNumber->setValue(CurrentNumber);
    ui->spinPosition->setValue(mReadBuffer->MOTOR_CPOS_get(CurrentNumber));
    short PosMin = mReadBuffer->MOTOR_POS_MIN_get(CurrentNumber);
    ui->spinMinPos->setValue(PosMin);
    short PosMax = mReadBuffer->MOTOR_POS_MAX_get(CurrentNumber);
    ui->spinMaxPos->setValue(PosMax);
}

void DriverControllerWidget::setModel(ChannelTableModel *model)
{
    mModel=model;
}
