#include "PowerWidget.h"
#include "ui_PowerWidget.h"

PowerWidget::PowerWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PowerWidget)
{
    ui->setupUi(this);
    mTimer = new QTimer(this);
    mInterval = 500;
    mTimer->setInterval(mInterval);//интервал 0.5 секунды
    mTime = 0;
    isOn = true;

    connect(mTimer,SIGNAL(timeout()),this,SLOT(OnTimerTick()));
}

PowerWidget::~PowerWidget()
{
    delete ui;
}

void PowerWidget::UpdatePowerLabel()
{
    ui->line48_U->setText(QString::number(BufferController::Inst()->getBufferRecv()->getPowerVoltage48()));
    ui->line48_I->setText(QString::number(BufferController::Inst()->getBufferRecv()->getPowerCurrent48()));

    ui->line81_U->setText(QString::number(BufferController::Inst()->getBufferRecv()->getPowerVoltage8_1()));
    ui->line81_I->setText(QString::number(BufferController::Inst()->getBufferRecv()->getPowerCurrent8_1()));

    ui->line82_U->setText(QString::number(BufferController::Inst()->getBufferRecv()->getPowerVoltage8_2()));
    ui->line82_I->setText(QString::number(BufferController::Inst()->getBufferRecv()->getPowerCurrent8_2()));

    ui->line61_U->setText(QString::number(BufferController::Inst()->getBufferRecv()->getPowerVoltage6_1()));
    ui->line61_I->setText(QString::number(BufferController::Inst()->getBufferRecv()->getPowerCurrent6_1()));

    ui->line62_U->setText(QString::number(BufferController::Inst()->getBufferRecv()->getPowerVoltage6_2()));
    ui->line62_I->setText(QString::number(BufferController::Inst()->getBufferRecv()->getPowerCurrent6_2()));

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
        switch (mTime)
        {
        case 0:
        {
            BufferController::Inst()->getBufferSend()->onPower48();
            ui->checkBox48V->setChecked(true);
        }
            break;
        case 500:
        {
            BufferController::Inst()->getBufferSend()->onPower8_2();
            ui->checkBox8V2->setChecked(true);
        }
            break;
        case 2*500:
        {
            BufferController::Inst()->getBufferSend()->onPower8_1();
            ui->checkBox8V1->setChecked(true);
        }
            break;
        case 3*500:
        {
            BufferController::Inst()->getBufferSend()->onPower6_2();
            ui->checkBox6V2->setChecked(true);
        }
            break;
        case 4*500:
        {
            BufferController::Inst()->getBufferSend()->onPower6_1();
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
            BufferController::Inst()->getBufferSend()->offPower48();
            ui->checkBox48V->setChecked(false);
            ChechBoxSetEnable(true);
            mTimer->stop();
            return;
        }
            break;

        case 500:
        {
            BufferController::Inst()->getBufferSend()->offPower8_2();
            ui->checkBox8V2->setChecked(false);
        }
            break;
        case 2*500:
        {
            BufferController::Inst()->getBufferSend()->offPower8_1();
            ui->checkBox8V1->setChecked(false);
        }
            break;
        case 3*500:
        {
            BufferController::Inst()->getBufferSend()->offPower6_2();
            ui->checkBox6V2->setChecked(false);
        }
            break;
        case 4*500:
        {
            BufferController::Inst()->getBufferSend()->offPower6_1();
            ui->checkBox6V1->setChecked(false);
        }
            break;
        }
        mTime-=mInterval;
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
        BufferController::Inst()->getBufferSend()->onPower48();
        mTime=1*500;
    }
    else
    {
       BufferController::Inst()->getBufferSend()->offPower48();
       mTime=0*500;
    }
}

void PowerWidget::on_checkBox8V2_clicked(bool checked)
{
    if(checked)
    {
        BufferController::Inst()->getBufferSend()->onPower8_2();
        mTime=2*500;
    }
    else
    {
       BufferController::Inst()->getBufferSend()->offPower8_2();
       mTime=1*500;
    }
}

void PowerWidget::on_checkBox8V1_clicked(bool checked)
{
    if(checked)
    {
        BufferController::Inst()->getBufferSend()->onPower8_1();
        mTime=3*500;
    }
    else
    {
       BufferController::Inst()->getBufferSend()->offPower8_1();
       mTime=2*500;
    }
}

void PowerWidget::on_checkBox6V2_clicked(bool checked)
{
    if(checked)
    {
        BufferController::Inst()->getBufferSend()->onPower6_2();
        mTime=4*500;
    }
    else
    {
       BufferController::Inst()->getBufferSend()->offPower6_2();
       mTime=3*500;
    }
}

void PowerWidget::on_checkBox6V1_clicked(bool checked)
{
    if(checked)
    {
        BufferController::Inst()->getBufferSend()->onPower6_1();
        mTime=5*500;
    }
    else
    {
       BufferController::Inst()->getBufferSend()->offPower6_1();
       mTime=4*500;
    }
}
