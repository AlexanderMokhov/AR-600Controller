#include "DriverControllerWidget.h"
#include "ui_DriverControllerWidget.h"

DriverControllerWidget::DriverControllerWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DriverControllerWidget)
{
    ui->setupUi(this);
    mReadBuffer = BufferController::Instance()->getReadBuffer();
    mWriteBuffer = BufferController::Instance()->getWriteBuffer();
    Calibration = false;
    TRACE = false;
}

DriverControllerWidget::~DriverControllerWidget()
{
    delete ui;
}

void DriverControllerWidget::setNumber(int Number)
{
    ui->spinNumber->setValue(Number);
}

//Происходит при выборе строки в таблице
void DriverControllerWidget::setCurrentRow(int Row)
{
    //Считываем номер мотра, адрес буфера, реверс
    CurrentNumber = mModel->data(mModel->index(Row,0),Qt::EditRole).toInt();
    CurrentNOMB = AR600ControllerConf::Instance()->getConfMap()->at(CurrentNumber).getNumberBuffer();
    Reverce = AR600ControllerConf::Instance()->getConfMap()->at(CurrentNumber).getReverce();
    if(Reverce)
        ReverceCoeff = -1;
    else
        ReverceCoeff = 1;
    //инициализируем слайдер
    SliderInit();
    //отключаем режим калибрации и управление слайдером
    TRACE = false;
    Calibration=false;
}

void DriverControllerWidget::setModel(ChannelTableModel *model)
{
    mModel=model;
}

//вызывается при приходе новых значений
void DriverControllerWidget::UpdateData()
{
    //показываем номер мотора
    ui->spinNumber->setValue(CurrentNumber);

    //обновляем текущую позицию
    if(Reverce)
    {
        if(Calibration)
            ui->spinPosition->setValue(-1*mReadBuffer->MOTOR_CPOS_get(CurrentNOMB));
        else
            ui->spinPosition->setValue(mReadBuffer->MOTOR_CPOS_get(CurrentNOMB));
    }
    else
    {
        ui->spinPosition->setValue(mReadBuffer->MOTOR_CPOS_get(CurrentNOMB));
    }

    //если слайдер не управляет обновляем и на нем
    if(!TRACE)
    {
        ui->SliderPosition->setValue(mReadBuffer->MOTOR_CPOS_get(CurrentNOMB));
    }

    //обновляем информацию о токе и напряжении на моторах
    ui->lineStatusI->setText(QString::number(-1*mReadBuffer->MOTOR_IMOT_get(CurrentNOMB)/100.0,'g',6));
    ui->lineStatusU->setText(QString::number(mReadBuffer->MOTOR_UBATT_get(CurrentNOMB)/100.0,'g',6));

    //начало чтения статуса
    unsigned char status = mReadBuffer->MOTOR_STAT_get(CurrentNOMB);
    int BRK=0,DT=0,RELAX=0,TRACE=0;
    QString statusString;

    if((unsigned char)(status & 0) == 0)
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
    //конец чтения статуса
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
    ui->groupBoxCalibration->setEnabled(false);
}

void DriverControllerWidget::on_ButtonPosSet_clicked()
{
    mWriteBuffer->MOTOR_ANGLE_set(CurrentNOMB,(short)ui->spinPosSet->value());
}

//происходит при входе и выходе в режим калибрации
void DriverControllerWidget::on_groupBoxCalibration_clicked(bool checked)
{
    if(!checked)
    {
        //выходим из режима калибровки

        //записываем в мотор калибровочные коэффициенты
        mWriteBuffer->MOTOR_ILIM_set(CurrentNOMB,AR600ControllerConf::Instance()->getConfMap()->at(CurrentNumber).getIlim());
        mWriteBuffer->MOTOR_ANGLE_set(CurrentNOMB, mReadBuffer->MOTOR_CPOS_get(CurrentNOMB));
        Calibration=false;

        //разрешаем вход в режим управления слайдером
        mWriteBuffer->MOTOR_STOP_BR(CurrentNOMB);
        TRACE=false;
        ui->checkBoxTrace->setEnabled(true);
    }
    else
    {
        //входим в режим калибровки

        //записываем в мотор нулевой колибровочный коэфиициент
        mWriteBuffer->MOTOR_STOP_BR(CurrentNOMB);
        mWriteBuffer->MOTOR_ILIM_set(CurrentNOMB,0);
        Calibration=true;

        //запрещаем вход в режим управления слайдером
        TRACE=false;
        ui->checkBoxTrace->setEnabled(false);
    }
}

//Происходит при нажатии кнопики установки нуля
void DriverControllerWidget::on_ButtonSaveZero_clicked()
{
    //записываем в файл настроек новые калибровочные коэффициенты
    AR600ControllerConf::Instance()->getConfMap()->at(CurrentNumber).setIlim(-1*mReadBuffer->MOTOR_CPOS_get(CurrentNOMB));
    AR600ControllerConf::Instance()->saveFile("config.xml");

    //записываем в мотор калибровочные коэффициенты
    mWriteBuffer->MOTOR_ILIM_set(CurrentNOMB,AR600ControllerConf::Instance()->getConfMap()->at(CurrentNumber).getIlim());
    mWriteBuffer->MOTOR_ANGLE_set(CurrentNOMB, mReadBuffer->MOTOR_CPOS_get(CurrentNOMB));

    //разрешаем вход в режим управления слайдером
    ui->groupBoxCalibration->setChecked(false);
    Calibration=false;
    ui->checkBoxTrace->setEnabled(true);
}

//происходит при изменении позиции слайдером
void DriverControllerWidget::on_SliderPosition_sliderMoved(int position)
{
    if(TRACE)
    {
        mWriteBuffer->MOTOR_ANGLE_set(CurrentNOMB,position);
    }
}

//происходит при входе и выходе в режим управления слайдером
void DriverControllerWidget::on_checkBoxTrace_clicked(bool checked)
{
    TRACE=checked;
    if(TRACE)
    {
        //входим в режим управления
        SliderInit();
        mWriteBuffer->MOTOR_TRACE(CurrentNOMB);

        //запрещаем вход в режим калибровки
        ui->groupBoxCalibration->setEnabled(false);
    }
    else
    {
        //выходим из режима управления
        mWriteBuffer->MOTOR_STOP_BR(CurrentNOMB);

        //разрешаем вход в режим калибровки
        ui->groupBoxCalibration->setEnabled(true);
    }
}

//инициализация слайдера и мин макс
void DriverControllerWidget::SliderInit()
{

    ui->SliderPosition->setMinimum(mReadBuffer->MOTOR_POS_MIN_get(CurrentNOMB));
    ui->SliderPosition->setMaximum(mReadBuffer->MOTOR_POS_MAX_get(CurrentNOMB));
    ui->spinMinPos->setValue(mReadBuffer->MOTOR_POS_MIN_get(CurrentNOMB));
    ui->spinMaxPos->setValue(mReadBuffer->MOTOR_POS_MAX_get(CurrentNOMB));
    ui->spinDump->setValue(mReadBuffer->MOTOR_DAMP_get(CurrentNOMB));
    ui->spinStiff->setValue(mReadBuffer->MOTOR_STIFF_get(CurrentNOMB));

    ui->SliderPosition->setValue(mReadBuffer->MOTOR_CPOS_get(CurrentNOMB));
    mWriteBuffer->MOTOR_ANGLE_set(CurrentNOMB, mReadBuffer->MOTOR_CPOS_get(CurrentNOMB));
}

void DriverControllerWidget::on_ButtonStiffWrite_clicked()
{
    mWriteBuffer->MOTOR_STIFF_set(CurrentNOMB,ui->spinStiff->value());
}

void DriverControllerWidget::on_ButtonStiffSave_clicked()
{
    AR600ControllerConf::Instance()->getConfMap()->at(CurrentNumber).SetStiff(ui->spinStiff->value());
}

void DriverControllerWidget::on_ButtonDumpSave_clicked()
{
    AR600ControllerConf::Instance()->getConfMap()->at(CurrentNumber).SetDump(ui->spinDump->value());
}


void DriverControllerWidget::on_ButtonDumpWrite_clicked()
{
    mWriteBuffer->MOTOR_DAMP_set(CurrentNOMB,ui->spinDump->value());
}
