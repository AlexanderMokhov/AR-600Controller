#include "PowerControlWidget.h"
#include "ui_PowerControlWidget.h"

PowerControlWidget::PowerControlWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PowerControlWidget)
{
    ui->setupUi(this);
    mTimer = new QTimer(this);
    mInterval = 500;
    mTimer->setInterval(mInterval);//интервал 2 секунды
    mCurrentTime = 0;
    isOn = true;

    connect(mTimer,SIGNAL(timeout()),this,SLOT(OnTimerTick()));
    mReadBuffer = BufferController::Instance()->GetReadBuffer();
}

PowerControlWidget::~PowerControlWidget()
{
    delete ui;
}

void PowerControlWidget::UpdatePowerLabel()
{
    ui->line48_U->setText(QString::number(mReadBuffer->GetPowerU48()));
    ui->line48_I->setText(QString::number(mReadBuffer->GetPowerI48()));

    ui->line81_U->setText(QString::number(mReadBuffer->GetPowerU81()));
    ui->line81_I->setText(QString::number(mReadBuffer->GetPowerI81()));

    ui->line82_U->setText(QString::number(mReadBuffer->GetPowerU82()));
    ui->line82_I->setText(QString::number(mReadBuffer->GetPowerI82()));

    ui->line61_U->setText(QString::number(mReadBuffer->GetPowerU61()));
    ui->line61_I->setText(QString::number(mReadBuffer->GetPowerI61()));

    ui->line62_U->setText(QString::number(mReadBuffer->GetPowerU62()));
    ui->line62_I->setText(QString::number(mReadBuffer->GetPowerI62()));

}

//включить все
void PowerControlWidget::on_ButtonOnAll_clicked()
{
    isOn = true;
    ChechBoxSetEnable(false);
    if(!mTimer->isActive())
    {
        mTimer->start();
    }
}

void PowerControlWidget::on_ButtonOffAll_clicked()
{
   isOn = false;
   ChechBoxSetEnable(false);
   if(!mTimer->isActive())
   {
       mTimer->start();
   }
}

void PowerControlWidget::OnTimerTick()
{
    if(isOn)
    {
        //включаем очередное напряжение
        switch (mCurrentTime)
        {
        case 0:
        {
            BufferController::Instance()->GetWriteBuffer()->PowerOn48();
            ui->checkBox48V->setChecked(true);
        }
            break;
        case 500:
        {
            BufferController::Instance()->GetWriteBuffer()->PowerOn82();
            ui->checkBox8V2->setChecked(true);
        }
            break;
        case 2*500:
        {
            BufferController::Instance()->GetWriteBuffer()->PowerOn81();
            ui->checkBox8V1->setChecked(true);
        }
            break;
        case 3*500:
        {
            BufferController::Instance()->GetWriteBuffer()->PowerOn62();
            ui->checkBox6V2->setChecked(true);
        }
            break;
        case 4*500:
        {
            BufferController::Instance()->GetWriteBuffer()->PowerOn61();
            ui->checkBox6V1->setChecked(true);
            ChechBoxSetEnable(true);
            mTimer->stop();
            return;
        }
            break;
        }

        mCurrentTime+=mInterval;
    }
    else
    {
        //выключаем очередное напряжение
        switch (mCurrentTime)
        {
        case 0:
        {
            BufferController::Instance()->GetWriteBuffer()->PowerOff48();
            ui->checkBox48V->setChecked(false);
            ChechBoxSetEnable(true);
            mTimer->stop();
            return;
        }
            break;

        case 500:
        {
            BufferController::Instance()->GetWriteBuffer()->PowerOff82();
            ui->checkBox8V2->setChecked(false);
        }
            break;
        case 2*500:
        {
            BufferController::Instance()->GetWriteBuffer()->PowerOff81();
            ui->checkBox8V1->setChecked(false);
        }
            break;
        case 3*500:
        {
            BufferController::Instance()->GetWriteBuffer()->PowerOff62();
            ui->checkBox6V2->setChecked(false);
        }
            break;
        case 4*500:
        {
            BufferController::Instance()->GetWriteBuffer()->PowerOff61();
            ui->checkBox6V1->setChecked(false);
        }
            break;
        }
        mCurrentTime-=mInterval;
    }

}

void PowerControlWidget::ChechBoxSetEnable(bool enable)
{
    ui->checkBox48V->setEnabled(enable);
    ui->checkBox8V2->setEnabled(enable);
    ui->checkBox8V1->setEnabled(enable);
    ui->checkBox6V2->setEnabled(enable);
    ui->checkBox6V1->setEnabled(enable);
}

void PowerControlWidget::on_checkBox48V_clicked(bool checked)
{
    if(checked)
    {
        BufferController::Instance()->GetWriteBuffer()->PowerOn48();
        mCurrentTime=1*500;
    }
    else
    {
       BufferController::Instance()->GetWriteBuffer()->PowerOff48();
       mCurrentTime=0*500;
    }
}

void PowerControlWidget::on_checkBox8V2_clicked(bool checked)
{
    if(checked)
    {
        BufferController::Instance()->GetWriteBuffer()->PowerOn82();
        mCurrentTime=2*500;
    }
    else
    {
       BufferController::Instance()->GetWriteBuffer()->PowerOff82();
       mCurrentTime=1*500;
    }
}

void PowerControlWidget::on_checkBox8V1_clicked(bool checked)
{
    if(checked)
    {
        BufferController::Instance()->GetWriteBuffer()->PowerOn81();
        mCurrentTime=3*500;
    }
    else
    {
       BufferController::Instance()->GetWriteBuffer()->PowerOff81();
       mCurrentTime=2*500;
    }
}

void PowerControlWidget::on_checkBox6V2_clicked(bool checked)
{
    if(checked)
    {
        BufferController::Instance()->GetWriteBuffer()->PowerOn62();
        mCurrentTime=4*500;
    }
    else
    {
       BufferController::Instance()->GetWriteBuffer()->PowerOff62();
       mCurrentTime=3*500;
    }
}

void PowerControlWidget::on_checkBox6V1_clicked(bool checked)
{
    if(checked)
    {
        BufferController::Instance()->GetWriteBuffer()->PowerOn61();
        mCurrentTime=5*500;
    }
    else
    {
       BufferController::Instance()->GetWriteBuffer()->PowerOff61();
       mCurrentTime=4*500;
    }
}
