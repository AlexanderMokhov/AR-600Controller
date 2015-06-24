#include "DriverControllerWidget.h"
#include "ui_DriverControllerWidget.h"

DriverControllerWidget::DriverControllerWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DriverControllerWidget)
{
    ui->setupUi(this);
    mReadBuffer = BufferController::Instance()->GetReadBuffer();
    mWriteBuffer = BufferController::Instance()->GetWriteBuffer();
    Calibration = false;
    TRACE = false;
}

DriverControllerWidget::~DriverControllerWidget()
{
    delete ui;
}

void DriverControllerWidget::setModel(ChannelTableModel *model)
{
    mModel=model;
}

void DriverControllerWidget::RowChanged(int cRow)
{
    //останавливаем предыдущий мотор
    mWriteBuffer->MOTOR_STOP_BR(CurrentNOMB);
    //отключаем режим калибрации и управление слайдером
    on_checkBoxTrace_clicked(false);
    TRACE=false;
    Calibration=false;
    ui->checkBoxTrace->setChecked(false);
    ui->groupBoxCalibration->setChecked(false);
    ui->checkBoxTrace->setEnabled(true);

    //Считываем номер мотра, адрес буфера, реверс
    currentRow = cRow;
    CurrentNumber = mModel->data(mModel->index(currentRow,0),Qt::EditRole).toInt();
    ui->lineNumber->setText(QString::number(CurrentNumber));
    CurrentNOMB = ConfigController::Instance()->GetConfigMap()->at(CurrentNumber).GetNumberBuffer();
    Reverce = ConfigController::Instance()->GetConfigMap()->at(CurrentNumber).GetReverce();
    if(Reverce)
        ReverceCoeff = -1;
    else
        ReverceCoeff = 1;
    //инициализируем слайдер
    SliderInit();

    UpdateData();
}

//вызывается при приходе новых значений
void DriverControllerWidget::UpdateData()
{
    //обновляем текущую позицию
    int CurrentPos = mReadBuffer->Get_MOTOR_CPOS(CurrentNOMB);
    if(Reverce && Calibration)
    {
        ui->lineCurrentPos->setText(QString::number(-1*CurrentPos));
    }
    else
    {
        ui->lineCurrentPos->setText(QString::number(CurrentPos));
    }

    //если слайдер не управляет обновляем и на нем
    if(!TRACE)
    {
        ui->SliderPosition->setValue(CurrentPos);
    }

    //обновляем информацию о токе и напряжении на моторах
    ui->lineStatusI->setText(QString::number(-1*mReadBuffer->Get_MOTOR_IMOT(CurrentNOMB)/100.0,'g',6));
    ui->lineStatusU->setText(QString::number(mReadBuffer->Get_MOTOR_UBATT(CurrentNOMB)/100.0,'g',6));

    //начало чтения статуса
    unsigned char status = mReadBuffer->Get_MOTOR_STAT(CurrentNOMB);
    int BRK=0,DT=0,RELAX=0,TRACE=0;
    QString statusString;

    if((unsigned char)(status & 0) == 0)
        BRK=1;
    if((unsigned char)(status & 1) == 1)
        DT=1;
    if((unsigned char)(status & 2) == 2)
    {
        RELAX=1; BRK=0;
    }
    if((unsigned char)(status & 3) == 3)
    {
        TRACE=1; BRK=DT=RELAX=0;
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


//происходит при входе и выходе в режим калибрации
void DriverControllerWidget::on_groupBoxCalibration_clicked(bool checked)
{
    if(!checked)
    {
        //выходим из режима калибровки

        //записываем в мотор калибровочные коэффициенты
        mWriteBuffer->Set_MOTOR_CALIBRATION(CurrentNOMB,ConfigController::Instance()->GetConfigMap()->at(CurrentNumber).GetCalibration());
        mWriteBuffer->Set_MOTOR_ANGLE(CurrentNOMB, mReadBuffer->Get_MOTOR_CPOS(CurrentNOMB));
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
        mWriteBuffer->Set_MOTOR_CALIBRATION(CurrentNOMB,0);
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
    int CurrentPos = mReadBuffer->Get_MOTOR_CPOS(CurrentNOMB);
    int NewCalibration=ReverceCoeff*CurrentPos;
    ConfigController::Instance()->GetConfigMap()->at(CurrentNumber).SetCalibration(NewCalibration);
    mModel->setData(mModel->index(currentRow,10),QString::number(NewCalibration));
    ConfigController::Instance()->SaveFile("config.xml");

    //записываем в мотор калибровочные коэффициенты
    mWriteBuffer->Set_MOTOR_CALIBRATION(CurrentNOMB,NewCalibration);
    mWriteBuffer->Set_MOTOR_ANGLE(CurrentNOMB, CurrentPos);

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
        mWriteBuffer->Set_MOTOR_ANGLE(CurrentNOMB,position);
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
    int MinPos = mReadBuffer->Get_MOTOR_MIN_POS(CurrentNOMB);
    int MaxPos = mReadBuffer->Get_MOTOR_MAX_POS(CurrentNOMB);
    int CurrentPos = mReadBuffer->Get_MOTOR_CPOS(CurrentNOMB);
    int CalibrateValue = ConfigController::Instance()->GetConfigMap()->at(CurrentNumber).GetCalibration();
    ui->SliderPosition->setMinimum(MinPos);
    ui->SliderPosition->setMaximum(MaxPos);
    ui->lineMinPos->setText(QString::number(MinPos));
    ui->lineMaxPos->setText(QString::number(MaxPos));
    ui->lineCalibrateValue->setText(QString::number(CalibrateValue));

    ui->spinDump->setValue(mReadBuffer->Get_MOTOR_DAMP(CurrentNOMB));
    ui->spinStiff->setValue(mReadBuffer->Get_MOTOR_STIFF(CurrentNOMB));
    ui->spinTorque->setValue(mWriteBuffer->Get_MOTOR_TORQUE(CurrentNOMB));
    ui->spinPosToGo->setMinimum(MinPos);
    ui->spinPosToGo->setMaximum(MaxPos);

    ui->SliderPosition->setValue(CurrentPos);
    mWriteBuffer->Set_MOTOR_ANGLE(CurrentNOMB, CurrentPos);

}

void DriverControllerWidget::on_ButtonStiffWrite_clicked()
{
    mWriteBuffer->Set_MOTOR_STIFF(CurrentNOMB,ui->spinStiff->value());
}

void DriverControllerWidget::on_ButtonStiffSave_clicked()
{
    ConfigController::Instance()->GetConfigMap()->at(CurrentNumber).SetStiff(ui->spinStiff->value());
}

void DriverControllerWidget::on_ButtonDumpSave_clicked()
{
    ConfigController::Instance()->GetConfigMap()->at(CurrentNumber).SetDump(ui->spinDump->value());
}


void DriverControllerWidget::on_ButtonDumpWrite_clicked()
{
    mWriteBuffer->Set_MOTOR_DAMP(CurrentNOMB,ui->spinDump->value());
}

void DriverControllerWidget::on_ButtonGoToPos_clicked()
{
    int CurrentPos = mReadBuffer->Get_MOTOR_CPOS(CurrentNOMB);

    mWriteBuffer->Set_MOTOR_ANGLE(CurrentNOMB, CurrentPos);
    mWriteBuffer->MOTOR_TRACE(CurrentNOMB);

    CommandController::Instance()->SetDestPos(ui->spinPosToGo->value());
    CommandController::Instance()->SetStartPos(CurrentPos);
    CommandController::Instance()->SetTimeToGo(ui->spinTimeToGo->value());
    CommandController::Instance()->SetDriverNumberBuffer(CurrentNOMB);
    CommandController::Instance()->CalcGoToPos();
    CommandController::Instance()->SetGoToPosState(true);
}

void DriverControllerWidget::on_ButtonStopGoToPos_clicked()
{
    mWriteBuffer->MOTOR_STOP(CurrentNOMB);
    CommandController::Instance()->SetGoToPosState(false);
}

