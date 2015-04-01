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
    CurrentNOMB = AR600ControllerConf::Instance()->getConfMap()->at(CurrentNumber).getNumberBuffer();
    Reverce = AR600ControllerConf::Instance()->getConfMap()->at(CurrentNumber).getReverce();
}

void DriverControllerWidget::setModel(ChannelTableModel *model)
{
    mModel=model;
}

void DriverControllerWidget::UpdateData()
{
    ui->spinNumber->setValue(CurrentNumber);
    if(Reverce)
    {
        ui->spinPosition->setValue(-1*mReadBuffer->MOTOR_CPOS_get(CurrentNOMB));
        short PosMin = mReadBuffer->MOTOR_POS_MIN_get(CurrentNOMB);
        ui->spinMinPos->setValue(-1*PosMin);
        short PosMax = mReadBuffer->MOTOR_POS_MAX_get(CurrentNOMB);
        ui->spinMaxPos->setValue(-1*PosMax);
    }
    else
    {
        ui->spinPosition->setValue(mReadBuffer->MOTOR_CPOS_get(CurrentNOMB));
        short PosMin = mReadBuffer->MOTOR_POS_MIN_get(CurrentNOMB);
        ui->spinMinPos->setValue(PosMin);
        short PosMax = mReadBuffer->MOTOR_POS_MAX_get(CurrentNOMB);
        ui->spinMaxPos->setValue(PosMax);
    }

    ui->lineStatusI->setText(QString::number(mReadBuffer->MOTOR_IMOT_get(CurrentNOMB)/100.0,'g',6));
    ui->lineStatusU->setText(QString::number(mReadBuffer->MOTOR_UBATT_get(CurrentNOMB)/100.0,'g',6));



    unsigned char status = mReadBuffer->MOTOR_STAT_get(CurrentNOMB);

    int BRK=0,DT=0,RELAX=0,TRACE=0;

    QString statusString;

    if((unsigned char)(status & 0) == 0)
        //STOP
        BRK=1;

    if((unsigned char)(status & 1) == 1)
        DT=1;

    if((unsigned char)(status & 2) == 2)
    {
        RELAX=1;
        BRK=0;
    }

    if((unsigned char)(status & 3) == 3)
    {
        //STOP
        TRACE=1;
        BRK=0;
        DT=0;
        RELAX=0;
    }

    if(BRK){statusString+="BRAKE";}
    if(DT){statusString+="-DT";}
    if(RELAX){statusString+="RELAX";}
    if(TRACE){statusString+="TRACE";}

    ui->lineStatus->setText(statusString);
}

void DriverControllerWidget::on_ButtonSTOP_clicked()
{
    mWriteBuffer->MOTOR_STOP_BR(CurrentNOMB);

}

void DriverControllerWidget::on_ButtonBRAKE_clicked()
{
    mWriteBuffer->MOTOR_STOP(CurrentNOMB);

}

void DriverControllerWidget::on_ButtonRELAX_clicked()
{
    mWriteBuffer->MOTOR_RELAX(CurrentNOMB);

}

void DriverControllerWidget::on_ButtonTRACE_clicked()
{
    mWriteBuffer->MOTOR_TRACE(CurrentNOMB);

}

void DriverControllerWidget::on_spinPosition_valueChanged(int arg1)
{
    mWriteBuffer->MOTOR_ANGLE_set(CurrentNOMB,(short)arg1);
}

void DriverControllerWidget::on_ButtonPosSet_clicked()
{
    mWriteBuffer->MOTOR_ANGLE_set(CurrentNOMB,(short)ui->spinPosSet->value());
}
