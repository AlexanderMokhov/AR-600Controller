#include "MotorControlWidget.h"
#include "ui_MotorControlWidget.h"

MotorControlWidget::MotorControlWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MotorControlWidget)
{
    ui->setupUi(this);
    mReadBuffer = BufferController::Instance()->GetReadBuffer();
    mWriteBuffer = BufferController::Instance()->GetWriteBuffer();
    Calibration = false;
    TRACE = false;
}

MotorControlWidget::~MotorControlWidget()
{
    delete ui;
}

void MotorControlWidget::setModel(MotorTableModel *model)
{
    mModel=model;
}

void MotorControlWidget::RowChanged(int cRow)
{
    //останавливаем предыдущий мотор
    mWriteBuffer->MotorStopBrake(CurrentNumber);
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
    Reverce = ConfigController::Instance()->GetMotorMap()->at(CurrentNumber).GetReverce();
    if(Reverce)
        ReverceCoeff = -1;
    else
        ReverceCoeff = 1;
    //инициализируем слайдер
    SliderInit();

    UpdateData();
}

//вызывается при приходе новых значений
void MotorControlWidget::UpdateData()
{
    //обновляем текущую позицию
    int CurrentPos = mReadBuffer->GetMotorAngle(CurrentNumber);
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
    ui->lineStatusI->setText(QString::number(-1*mReadBuffer->GetMotorI(CurrentNumber)/100.0,'g',6));
    ui->lineStatusU->setText(QString::number(mReadBuffer->GetMotorU(CurrentNumber)/100.0,'g',6));

    //начало чтения статуса
    unsigned char status = mReadBuffer->GetMotorStatus(CurrentNumber);
    QString statusString;

    if((unsigned char)(status & 0) == 0)
    {statusString="BRAKE";}
    if((unsigned char)(status & 1) == 1)
    {statusString+="-DT";}
    if((unsigned char)(status & 2) == 2)
    {statusString="RELAX";}
    if((unsigned char)(status & 3) == 3)
    {statusString="TRACE";}

    ui->lineStatus->setText(statusString);
    //конец чтения статуса
}

void MotorControlWidget::on_ButtonSTOP_clicked()
{
    mWriteBuffer->MotorStopBrake(CurrentNumber);

}

void MotorControlWidget::on_ButtonBRAKE_clicked()
{
    mWriteBuffer->MotorStop(CurrentNumber);

}

void MotorControlWidget::on_ButtonRELAX_clicked()
{
    mWriteBuffer->MotorRelax(CurrentNumber);
}

void MotorControlWidget::on_ButtonTRACE_clicked()
{
    mWriteBuffer->MotorTrace(CurrentNumber);
    ui->groupBoxCalibration->setEnabled(false);
}


//происходит при входе и выходе в режим калибрации
void MotorControlWidget::on_groupBoxCalibration_clicked(bool checked)
{
    if(!checked)
    {
        //выходим из режима калибровки

        //записываем в мотор калибровочные коэффициенты
        mWriteBuffer->SetMotorCalibration(CurrentNumber,ConfigController::Instance()->GetMotorMap()->at(CurrentNumber).GetCalibration());
        mWriteBuffer->SetMotorAngle(CurrentNumber, mReadBuffer->GetMotorAngle(CurrentNumber));
        Calibration=false;

        //разрешаем вход в режим управления слайдером
        mWriteBuffer->MotorStopBrake(CurrentNumber);
        TRACE=false;
        ui->checkBoxTrace->setEnabled(true);
    }
    else
    {
        //входим в режим калибровки

        //записываем в мотор нулевой колибровочный коэфиициент
        mWriteBuffer->MotorStopBrake(CurrentNumber);
        mWriteBuffer->SetMotorCalibration(CurrentNumber,0);
        Calibration=true;

        //запрещаем вход в режим управления слайдером
        TRACE=false;
        ui->checkBoxTrace->setEnabled(false);
    }
}

//Происходит при нажатии кнопики установки нуля
void MotorControlWidget::on_ButtonSaveZero_clicked()
{
    //записываем в файл настроек новые калибровочные коэффициенты
    int CurrentPos = mReadBuffer->GetMotorAngle(CurrentNumber);
    int NewCalibration=ReverceCoeff*CurrentPos;
    ConfigController::Instance()->GetMotorMap()->at(CurrentNumber).SetCalibration(NewCalibration);
    mModel->setData(mModel->index(currentRow,10),QString::number(NewCalibration));
    ConfigController::Instance()->SaveFile("config.xml");

    //записываем в мотор калибровочные коэффициенты
    mWriteBuffer->SetMotorCalibration(CurrentNumber,NewCalibration);
    mWriteBuffer->SetMotorAngle(CurrentNumber, CurrentPos);

    //разрешаем вход в режим управления слайдером
    ui->groupBoxCalibration->setChecked(false);
    Calibration=false;
    ui->checkBoxTrace->setEnabled(true);
}

//происходит при изменении позиции слайдером
void MotorControlWidget::on_SliderPosition_sliderMoved(int position)
{
    if(TRACE)
    {
        mWriteBuffer->SetMotorAngle(CurrentNumber,position);
    }
}

//происходит при входе и выходе в режим управления слайдером
void MotorControlWidget::on_checkBoxTrace_clicked(bool checked)
{
    TRACE=checked;
    if(TRACE)
    {
        //входим в режим управления
        SliderInit();
        mWriteBuffer->MotorTrace(CurrentNumber);

        //запрещаем вход в режим калибровки
        ui->groupBoxCalibration->setEnabled(false);
    }
    else
    {
        //выходим из режима управления
        mWriteBuffer->MotorStopBrake(CurrentNumber);

        //разрешаем вход в режим калибровки
        ui->groupBoxCalibration->setEnabled(true);
    }
}

//инициализация слайдера и мин макс
void MotorControlWidget::SliderInit()
{
    int MinPos = mReadBuffer->GetMotorMinAngle(CurrentNumber);
    int MaxPos = mReadBuffer->GetMotorMaxAngle(CurrentNumber);
    int CurrentPos = mReadBuffer->GetMotorAngle(CurrentNumber);
    int CalibrateValue = ConfigController::Instance()->GetMotorMap()->at(CurrentNumber).GetCalibration();
    ui->SliderPosition->setMinimum(MinPos);
    ui->SliderPosition->setMaximum(MaxPos);
    ui->lineMinPos->setText(QString::number(MinPos));
    ui->lineMaxPos->setText(QString::number(MaxPos));
    ui->lineCalibrateValue->setText(QString::number(CalibrateValue));

    ui->spinDump->setValue(mReadBuffer->GetMotorDamp(CurrentNumber));
    ui->spinStiff->setValue(mReadBuffer->GetMotorStiff(CurrentNumber));
    ui->spinTorque->setValue(mWriteBuffer->GetMotorTorque(CurrentNumber));
    ui->spinPosToGo->setMinimum(MinPos);
    ui->spinPosToGo->setMaximum(MaxPos);

    ui->SliderPosition->setValue(CurrentPos);
    mWriteBuffer->SetMotorAngle(CurrentNumber, CurrentPos);

}

void MotorControlWidget::on_ButtonStiffWrite_clicked()
{
    mWriteBuffer->SetMotorStiff(CurrentNumber,ui->spinStiff->value());
}

void MotorControlWidget::on_ButtonStiffSave_clicked()
{
    ConfigController::Instance()->GetMotorMap()->at(CurrentNumber).SetStiff(ui->spinStiff->value());
}

void MotorControlWidget::on_ButtonDumpSave_clicked()
{
    ConfigController::Instance()->GetMotorMap()->at(CurrentNumber).SetDump(ui->spinDump->value());
}


void MotorControlWidget::on_ButtonDumpWrite_clicked()
{
    mWriteBuffer->SetMotorDump(CurrentNumber,ui->spinDump->value());
}

void MotorControlWidget::on_ButtonGoToPos_clicked()
{
    int CurrentPos = mReadBuffer->GetMotorAngle(CurrentNumber);

    mWriteBuffer->SetMotorAngle(CurrentNumber, CurrentPos);
    mWriteBuffer->MotorTrace(CurrentNumber);

    CommandController::Instance()->SetDestPos(ui->spinPosToGo->value());
    CommandController::Instance()->SetStartPos(CurrentPos);
    CommandController::Instance()->SetTimeToGo(ui->spinTimeToGo->value());
    CommandController::Instance()->SetMotorNumber(CurrentNumber);
    CommandController::Instance()->CalcGoToPos();
    CommandController::Instance()->SetGoToPosState(true);
}

void MotorControlWidget::on_ButtonStopGoToPos_clicked()
{
    mWriteBuffer->MotorStop(CurrentNumber);
    CommandController::Instance()->SetGoToPosState(false);
}

