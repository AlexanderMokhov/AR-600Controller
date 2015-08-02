#include "PowerControlWidget.h"
#include "ui_PowerControlWidget.h"

PowerControlWidget::PowerControlWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PowerControlWidget)
{
    ui->setupUi(this);
    mTimer = new QTimer(this);
    mInterval = 500;
    mTimer->setInterval(mInterval);//интервал 0.5 секунды
    mTime = 0;
    isOn = true;

    connect(mTimer,SIGNAL(timeout()),this,SLOT(OnTimerTick()));
}

PowerControlWidget::~PowerControlWidget()
{
    delete ui;
}

void PowerControlWidget::UpdatePowerLabel()
{
    ui->line48_U->setText(QString::number(BufferController::Inst()->GetBufferR()->GetPowerU48()));
    ui->line48_I->setText(QString::number(BufferController::Inst()->GetBufferR()->GetPowerI48()));

    ui->line81_U->setText(QString::number(BufferController::Inst()->GetBufferR()->GetPowerU81()));
    ui->line81_I->setText(QString::number(BufferController::Inst()->GetBufferR()->GetPowerI81()));

    ui->line82_U->setText(QString::number(BufferController::Inst()->GetBufferR()->GetPowerU82()));
    ui->line82_I->setText(QString::number(BufferController::Inst()->GetBufferR()->GetPowerI82()));

    ui->line61_U->setText(QString::number(BufferController::Inst()->GetBufferR()->GetPowerU61()));
    ui->line61_I->setText(QString::number(BufferController::Inst()->GetBufferR()->GetPowerI61()));

    ui->line62_U->setText(QString::number(BufferController::Inst()->GetBufferR()->GetPowerU62()));
    ui->line62_I->setText(QString::number(BufferController::Inst()->GetBufferR()->GetPowerI62()));

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
        switch (mTime)
        {
        case 0:
        {
            BufferController::Inst()->GetBufferS()->PowerOn48();
            ui->checkBox48V->setChecked(true);
        }
            break;
        case 500:
        {
            BufferController::Inst()->GetBufferS()->PowerOn82();
            ui->checkBox8V2->setChecked(true);
        }
            break;
        case 2*500:
        {
            BufferController::Inst()->GetBufferS()->PowerOn81();
            ui->checkBox8V1->setChecked(true);
        }
            break;
        case 3*500:
        {
            BufferController::Inst()->GetBufferS()->PowerOn62();
            ui->checkBox6V2->setChecked(true);
        }
            break;
        case 4*500:
        {
            BufferController::Inst()->GetBufferS()->PowerOn61();
            ui->checkBox6V1->setChecked(true);
            ChechBoxSetEnable(true);
            mTimer->stop();
            return;
        }
            break;
        }

        mTime+=mInterval;
    }
    else
    {
        //выключаем очередное напряжение
        switch (mTime)
        {
        case 0:
        {
            BufferController::Inst()->GetBufferS()->PowerOff48();
            ui->checkBox48V->setChecked(false);
            ChechBoxSetEnable(true);
            mTimer->stop();
            return;
        }
            break;

        case 500:
        {
            BufferController::Inst()->GetBufferS()->PowerOff82();
            ui->checkBox8V2->setChecked(false);
        }
            break;
        case 2*500:
        {
            BufferController::Inst()->GetBufferS()->PowerOff81();
            ui->checkBox8V1->setChecked(false);
        }
            break;
        case 3*500:
        {
            BufferController::Inst()->GetBufferS()->PowerOff62();
            ui->checkBox6V2->setChecked(false);
        }
            break;
        case 4*500:
        {
            BufferController::Inst()->GetBufferS()->PowerOff61();
            ui->checkBox6V1->setChecked(false);
        }
            break;
        }
        mTime-=mInterval;
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
        BufferController::Inst()->GetBufferS()->PowerOn48();
        mTime=1*500;
    }
    else
    {
       BufferController::Inst()->GetBufferS()->PowerOff48();
       mTime=0*500;
    }
}

void PowerControlWidget::on_checkBox8V2_clicked(bool checked)
{
    if(checked)
    {
        BufferController::Inst()->GetBufferS()->PowerOn82();
        mTime=2*500;
    }
    else
    {
       BufferController::Inst()->GetBufferS()->PowerOff82();
       mTime=1*500;
    }
}

void PowerControlWidget::on_checkBox8V1_clicked(bool checked)
{
    if(checked)
    {
        BufferController::Inst()->GetBufferS()->PowerOn81();
        mTime=3*500;
    }
    else
    {
       BufferController::Inst()->GetBufferS()->PowerOff81();
       mTime=2*500;
    }
}

void PowerControlWidget::on_checkBox6V2_clicked(bool checked)
{
    if(checked)
    {
        BufferController::Inst()->GetBufferS()->PowerOn62();
        mTime=4*500;
    }
    else
    {
       BufferController::Inst()->GetBufferS()->PowerOff62();
       mTime=3*500;
    }
}

void PowerControlWidget::on_checkBox6V1_clicked(bool checked)
{
    if(checked)
    {
        BufferController::Inst()->GetBufferS()->PowerOn61();
        mTime=5*500;
    }
    else
    {
       BufferController::Inst()->GetBufferS()->PowerOff61();
       mTime=4*500;
    }
}
