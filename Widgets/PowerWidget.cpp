#include "PowerWidget.h"
#include "ui_PowerWidget.h"

PowerWidget::PowerWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PowerWidget)
{
    ui->setupUi(this);
    mTimer = new QTimer(this);
    mTimer->setInterval(mInterval);//интервал 2 секунды
    mCurrentTime = 0;
    isOn = true;

    connect(mTimer,SIGNAL(timeout()),this,SLOT(OnTimerTick()));
}

PowerWidget::~PowerWidget()
{
    delete ui;
}

//включить все
void PowerWidget::on_ButtonOnAll_clicked()
{
    isOn = true;

    if(!mTimer->isActive())
    {
        mTimer->start();
    }
}

void PowerWidget::on_ButtonOffAll_clicked()
{
   isOn = false;

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
            BufferController::Instance()->GetWriteBuffer()->ON48();break;
        case 2000:
            BufferController::Instance()->GetWriteBuffer()->ON82();break;
        case 2*2000:
            BufferController::Instance()->GetWriteBuffer()->ON81();break;
        case 3*2000:
            BufferController::Instance()->GetWriteBuffer()->ON62();break;
        case 4*2000:
        {
            BufferController::Instance()->GetWriteBuffer()->ON61();
            mTimer->stop();
        }
            break;
        }
        mCurrentTime+=mInterval;
    }
    else
    {
        switch (mCurrentTime)
        {
        case 0:
        {
            BufferController::Instance()->GetWriteBuffer()->OFF48();
            mTimer->stop();
        }
            break;

        case 2000:
            BufferController::Instance()->GetWriteBuffer()->OFF82();break;
        case 2*2000:
            BufferController::Instance()->GetWriteBuffer()->OFF81();break;
        case 3*2000:
            BufferController::Instance()->GetWriteBuffer()->OFF62();break;
        case 4*2000:
            BufferController::Instance()->GetWriteBuffer()->OFF61();break;
        }
        mCurrentTime-=mInterval;
    }

}



void PowerWidget::on_checkBox48V_clicked(bool checked)
{

}

void PowerWidget::on_checkBox8V1_clicked(bool checked)
{

}

void PowerWidget::on_checkBox8V2_clicked(bool checked)
{

}

void PowerWidget::on_checkBox6V1_clicked(bool checked)
{

}

void PowerWidget::on_checkBox6V2_clicked(bool checked)
{

}
