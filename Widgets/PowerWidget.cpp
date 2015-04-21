#include "PowerWidget.h"
#include "ui_PowerWidget.h"

PowerWidget::PowerWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PowerWidget)
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

PowerWidget::~PowerWidget()
{
    delete ui;
}

void PowerWidget::UpdatePowerLabel()
{
    ui->line48_U->setText(QString::number(mReadBuffer->GetU48()));
    ui->line48_I->setText(QString::number(mReadBuffer->GetI48()));

    ui->line81_U->setText(QString::number(mReadBuffer->GetU81()));
    ui->line81_I->setText(QString::number(mReadBuffer->GetI81()));

    ui->line82_U->setText(QString::number(mReadBuffer->GetU82()));
    ui->line82_I->setText(QString::number(mReadBuffer->GetI82()));

    ui->line61_U->setText(QString::number(mReadBuffer->GetU61()));
    ui->line61_I->setText(QString::number(mReadBuffer->GetI61()));

    ui->line62_U->setText(QString::number(mReadBuffer->GetU62()));
    ui->line62_I->setText(QString::number(mReadBuffer->GetI62()));

}

//включить все
void PowerWidget::on_ButtonOnAll_clicked()
{
    isOn = true;
    ChechBoxSetEnable(false);
    if(!mTimer->isActive())
    {
        mTimer->start();
    }
}

void PowerWidget::on_ButtonOffAll_clicked()
{
   isOn = false;
   ChechBoxSetEnable(false);
   if(!mTimer->isActive())
   {
       mTimer->start();
   }
}

void PowerWidget::OnTimerTick()
{
    if(isOn)
    {
        //включаем очередное напряжение
        switch (mCurrentTime)
        {
        case 0:
        {
            BufferController::Instance()->GetWriteBuffer()->ON48();
            ui->checkBox48V->setChecked(true);
        }
            break;
        case 500:
        {
            BufferController::Instance()->GetWriteBuffer()->ON82();
            ui->checkBox8V2->setChecked(true);
        }
            break;
        case 2*500:
        {
            BufferController::Instance()->GetWriteBuffer()->ON81();
            ui->checkBox8V1->setChecked(true);
        }
            break;
        case 3*500:
        {
            BufferController::Instance()->GetWriteBuffer()->ON62();
            ui->checkBox6V2->setChecked(true);
        }
            break;
        case 4*500:
        {
            BufferController::Instance()->GetWriteBuffer()->ON61();
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
            BufferController::Instance()->GetWriteBuffer()->OFF48();
            ui->checkBox48V->setChecked(false);
            ChechBoxSetEnable(true);
            mTimer->stop();
            return;
        }
            break;

        case 500:
        {
            BufferController::Instance()->GetWriteBuffer()->OFF82();
            ui->checkBox8V2->setChecked(false);
        }
            break;
        case 2*500:
        {
            BufferController::Instance()->GetWriteBuffer()->OFF81();
            ui->checkBox8V1->setChecked(false);
        }
            break;
        case 3*500:
        {
            BufferController::Instance()->GetWriteBuffer()->OFF62();
            ui->checkBox6V2->setChecked(false);
        }
            break;
        case 4*500:
        {
            BufferController::Instance()->GetWriteBuffer()->OFF61();
            ui->checkBox6V1->setChecked(false);
        }
            break;
        }
        mCurrentTime-=mInterval;
    }

}

void PowerWidget::ChechBoxSetEnable(bool enable)
{
    ui->checkBox48V->setEnabled(enable);
    ui->checkBox8V2->setEnabled(enable);
    ui->checkBox8V1->setEnabled(enable);
    ui->checkBox6V2->setEnabled(enable);
    ui->checkBox6V1->setEnabled(enable);
}

void PowerWidget::on_checkBox48V_clicked(bool checked)
{
    if(checked)
    {
        BufferController::Instance()->GetWriteBuffer()->ON48();
        mCurrentTime=1*500;
    }
    else
    {
       BufferController::Instance()->GetWriteBuffer()->OFF48();
       mCurrentTime=0*500;
    }
}

void PowerWidget::on_checkBox8V2_clicked(bool checked)
{
    if(checked)
    {
        BufferController::Instance()->GetWriteBuffer()->ON82();
        mCurrentTime=2*500;
    }
    else
    {
       BufferController::Instance()->GetWriteBuffer()->OFF82();
       mCurrentTime=1*500;
    }
}

void PowerWidget::on_checkBox8V1_clicked(bool checked)
{
    if(checked)
    {
        BufferController::Instance()->GetWriteBuffer()->ON81();
        mCurrentTime=3*500;
    }
    else
    {
       BufferController::Instance()->GetWriteBuffer()->OFF81();
       mCurrentTime=2*500;
    }
}

void PowerWidget::on_checkBox6V2_clicked(bool checked)
{
    if(checked)
    {
        BufferController::Instance()->GetWriteBuffer()->ON62();
        mCurrentTime=4*500;
    }
    else
    {
       BufferController::Instance()->GetWriteBuffer()->OFF62();
       mCurrentTime=3*500;
    }
}

void PowerWidget::on_checkBox6V1_clicked(bool checked)
{
    if(checked)
    {
        BufferController::Instance()->GetWriteBuffer()->ON61();
        mCurrentTime=5*500;
    }
    else
    {
       BufferController::Instance()->GetWriteBuffer()->OFF61();
       mCurrentTime=4*500;
    }
}
