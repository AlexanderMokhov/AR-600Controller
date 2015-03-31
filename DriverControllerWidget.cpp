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
}

void DriverControllerWidget::setModel(ChannelTableModel *model)
{
    mModel=model;
}

void DriverControllerWidget::UpdateData()
{
    ui->spinNumber->setValue(CurrentNumber);
    ui->spinPosition->setValue(mReadBuffer->MOTOR_CPOS_get(CurrentNumber));
    short PosMin = mReadBuffer->MOTOR_POS_MIN_get(CurrentNumber);
    ui->spinMinPos->setValue(PosMin);
    short PosMax = mReadBuffer->MOTOR_POS_MAX_get(CurrentNumber);
    ui->spinMaxPos->setValue(PosMax);
    char status = mReadBuffer->MOTOR_STAT_get(CurrentNumber);

    int BRK=0,DT=0,RELAX=0,TRACE=0;

    QString statusString;

    if(status & 0 == 0)
        //STOP
        BRK=1;

    if(status & 1 == 1)
        DT=1;

    if(status & 2 == 2)
    {
        RELAX=1;
        BRK=0;
    }

    if(status & 3 == 3)
    {
        //STOP
        TRACE=1;
        BRK=0;
        DT=0;
        RELAX=0;
    }

    if(BRK){statusString+="BRK-";}
    if(TRACE){statusString+="DT-";}
    if(RELAX){statusString+="RELAX-";}
    if(TRACE){statusString+="TRACE";}

    ui->lineStatus->setText(statusString);




}

void DriverControllerWidget::on_ButtonSTOP_clicked()
{
    mWriteBuffer->MOTOR_STOP_BR(CurrentNumber);

}

void DriverControllerWidget::on_ButtonBRAKE_clicked()
{
    mWriteBuffer->MOTOR_STOP(CurrentNumber);

}

void DriverControllerWidget::on_ButtonRELAX_clicked()
{
    mWriteBuffer->MOTOR_RELAX(CurrentNumber);

}

void DriverControllerWidget::on_ButtonTRACE_clicked()
{
    mWriteBuffer->MOTOR_TRACE(CurrentNumber);

}

void DriverControllerWidget::on_spinPosition_valueChanged(int arg1)
{
    mWriteBuffer->MOTOR_ANGLE_set(CurrentNumber,(short)arg1);
}

void DriverControllerWidget::on_ButtonPosSet_clicked()
{
    mWriteBuffer->MOTOR_ANGLE_set(CurrentNumber,(short)ui->spinPosSet->value());
}
