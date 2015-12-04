#include "MotorControlWidget.h"
#include "ui_MotorControlWidget.h"

MotorControlWidget::MotorControlWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MotorControlWidget)
{
    ui->setupUi(this);

    mReadBuffer = BufferController::Inst()->GetBufferR();
    mWriteBuffer = BufferController::Inst()->GetBufferS();

    state = States::STOPBRAKE;
}

MotorControlWidget::~MotorControlWidget()
{
    delete ui;
}

void MotorControlWidget::setModel(MotorTableModel *model)
{
    mModel = model;
}

void MotorControlWidget::RowChanged(int cRow)
{
    state = States::STOPBRAKE;

    //останавливаем предыдущий мотор
    mWriteBuffer->MotorStopBrake(CurrentNumber);
    //отключаем режим калибрации и управление слайдером
    on_checkBoxTrace_clicked(false);

    ui->checkBoxTrace->setChecked(false);
    ui->groupBoxCalibration->setChecked(false);
    ui->checkBoxTrace->setEnabled(true);

    //Считываем номер мотра, адрес буфера, реверс
    currentRow = cRow;
    CurrentNumber = mModel->data(mModel->index(currentRow,0),Qt::EditRole).toInt();
    ui->lineNumber->setText(QString::number(CurrentNumber));
    Reverce = ConfigController::Inst()->GetMotors()->at(CurrentNumber).GetReverce();
    if(Reverce)
        ReverceCoeff = -1;
    else
        ReverceCoeff = 1;

    state = States::STOPBRAKE;

    //инициализируем слайдер
    SliderInit();
    UpdateData();
}

//вызывается при приходе новых значений
void MotorControlWidget::UpdateData()
{
    //обновляем текущую позицию
    int CurrentPos = mReadBuffer->GetMotorAngle(CurrentNumber);
    if(Reverce && state == States::CALIBRATE)
    {
        ui->lineCurrentAngle->setText(QString::number(-1*CurrentPos));
    }
    else
    {
        ui->lineCurrentAngle->setText(QString::number(CurrentPos));
    }

    //если слайдер не управляет обновляем и на нем
    if(state != States::TRACE)
    {
        ui->SliderAngle->setValue(CurrentPos);
    }

    //обновляем информацию о токе и напряжении на моторах
    ui->lineStatusI->setText(QString::number(-1*mReadBuffer->GetMotorI(CurrentNumber)/100.0,'g',6));
    ui->lineStatusU->setText(QString::number(mReadBuffer->GetMotorU(CurrentNumber)/100.0,'g',6));

    //начало чтения статуса
    unsigned char status = mReadBuffer->GetMotorState(CurrentNumber);
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
    ui->checkBoxTrace->setChecked(false);
    ui->groupBoxCalibration->setEnabled(true);
    state = States::STOP;
}

void MotorControlWidget::on_ButtonBRAKE_clicked()
{
    mWriteBuffer->MotorStop(CurrentNumber);
    ui->checkBoxTrace->setChecked(false);
    ui->groupBoxCalibration->setEnabled(true);
    state = States::STOPBRAKE;

}

void MotorControlWidget::on_ButtonRELAX_clicked()
{
    mWriteBuffer->MotorRelax(CurrentNumber);
    ui->checkBoxTrace->setChecked(false);
    ui->groupBoxCalibration->setEnabled(true);
    state = States::RELAX;
}

//происходит при входе и выходе в режим калибрации
void MotorControlWidget::on_groupBoxCalibration_clicked(bool checked)
{
    if(!checked)
    {
        //выходим из режима калибровки
        mWriteBuffer->SetMotorCalibration(CurrentNumber, ConfigController::Inst()->GetMotors()->at(CurrentNumber).GetCalibration());
        mWriteBuffer->SetMotorAngle(CurrentNumber, mReadBuffer->GetMotorAngle(CurrentNumber));

        //разрешаем вход в режим управления слайдером
        mWriteBuffer->MotorStopBrake(CurrentNumber);

        ui->checkBoxTrace->setEnabled(true);

        state = States::STOPBRAKE;
    }
    else
    {
        //входим в режим калибровки
        mWriteBuffer->MotorStopBrake(CurrentNumber);
        mWriteBuffer->SetMotorCalibration(CurrentNumber,0);

        //запрещаем вход в режим управления слайдером
        ui->checkBoxTrace->setEnabled(false);

        state = States::CALIBRATE;
    }
}

//Происходит при нажатии кнопики установки нуля
void MotorControlWidget::on_ButtonSaveZero_clicked()
{
    //записываем в файл настроек новые калибровочные коэффициенты
    int CurrentPos = mReadBuffer->GetMotorAngle(CurrentNumber);
    int NewCalibration=ReverceCoeff*CurrentPos;
    ConfigController::Inst()->GetMotors()->at(CurrentNumber).SetCalibration(NewCalibration);
    mModel->setData(mModel->index(currentRow,10),QString::number(NewCalibration));
    ConfigController::Inst()->SaveFile("config.xml");

    //записываем в мотор калибровочные коэффициенты
    mWriteBuffer->SetMotorCalibration(CurrentNumber,NewCalibration);
    mWriteBuffer->SetMotorAngle(CurrentNumber, CurrentPos);

    //разрешаем вход в режим управления слайдером
    ui->groupBoxCalibration->setChecked(false);
    ui->checkBoxTrace->setEnabled(true);

    state = States::STOPBRAKE;
}

//происходит при изменении позиции слайдером
void MotorControlWidget::on_SliderAngle_sliderMoved(int position)
{
    if(state == States::TRACE)
    {
        mWriteBuffer->SetMotorAngle(CurrentNumber, position);
    }
}

//происходит при входе и выходе в режим управления слайдером
void MotorControlWidget::on_checkBoxTrace_clicked(bool checked)
{
    if(checked) state = States::TRACE;
    else state = States::STOPBRAKE;

    if(state == States::TRACE)
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
    int cAngle = mReadBuffer->GetMotorAngle(CurrentNumber);
    ui->SliderAngle->setMinimum(MinPos);
    ui->SliderAngle->setMaximum(MaxPos);

    ui->lineMinAngle->setText(QString::number(MinPos));
    ui->lineMaxAngle->setText(QString::number(MaxPos));

    ui->spinDump->setValue(mReadBuffer->GetMotorDamp(CurrentNumber));
    ui->spinStiff->setValue(mReadBuffer->GetMotorStiff(CurrentNumber));
    ui->spinTorque->setValue(mWriteBuffer->GetMotorTorque(CurrentNumber));
    ui->spinPosToGo->setMinimum(MinPos);
    ui->spinPosToGo->setMaximum(MaxPos);

    ui->SliderAngle->setValue(cAngle);
    mWriteBuffer->SetMotorAngle(CurrentNumber, cAngle);

}

void MotorControlWidget::on_ButtonStiffWrite_clicked()
{
    mWriteBuffer->SetMotorStiff(CurrentNumber,ui->spinStiff->value());
}

void MotorControlWidget::on_ButtonStiffSave_clicked()
{
    ConfigController::Inst()->GetMotors()->at(CurrentNumber).SetStiff(ui->spinStiff->value());
}

void MotorControlWidget::on_ButtonDumpSave_clicked()
{
    ConfigController::Inst()->GetMotors()->at(CurrentNumber).SetDump(ui->spinDump->value());
}


void MotorControlWidget::on_ButtonDumpWrite_clicked()
{
    mWriteBuffer->SetMotorDump(CurrentNumber, ui->spinDump->value());
}

void MotorControlWidget::on_ButtonGoToPos_clicked()
{
    MoveController::Inst()->StartGoToAngle(CurrentNumber,
                                              ui->spinPosToGo->value(),
                                              ui->spinTimeToGo->value());
}

void MotorControlWidget::on_ButtonStopGoToPos_clicked()
{

    MoveController::Inst()->StopGoToAngle();
}

