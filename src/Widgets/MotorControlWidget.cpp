#include "MotorControlWidget.h"
#include "ui_MotorControlWidget.h"

MotorControlWidget::MotorControlWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MotorControlWidget)
{
    ui->setupUi(this);

    mReadBuffer = BufferController::Inst()->getBufferRecv();
    mWriteBuffer = BufferController::Inst()->getBufferSend();

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
    mWriteBuffer->motorStopBrake(CurrentNumber);
    //отключаем режим калибрации и управление слайдером
    on_checkBoxTrace_clicked(false);

    ui->checkBoxTrace->setChecked(false);
    ui->groupBoxCalibration->setChecked(false);
    ui->checkBoxTrace->setEnabled(true);

    //Считываем номер мотра, адрес буфера, реверс
    currentRow = cRow;
    CurrentNumber = mModel->data(mModel->index(currentRow,0),Qt::EditRole).toInt();
    QString name = QString::fromLocal8Bit(ARCore::Inst()->getSettingStore()->GetMotors()->at(CurrentNumber).getName().c_str());
    ui->lineName->setText(name);
    Reverce = ARCore::Inst()->getSettingStore()->GetMotors()->at(CurrentNumber).getReverceState();
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
    int CurrentPos = mReadBuffer->getMotorAngle(CurrentNumber);
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
    ui->lineStatusI->setText(QString::number(-1*mReadBuffer->getMotorCurrent(CurrentNumber)/100.0,'g',6));
    ui->lineStatusU->setText(QString::number(mReadBuffer->getMotorVoltage(CurrentNumber)/100.0,'g',6));

    //начало чтения статуса
    unsigned char status = mReadBuffer->getMotorState(CurrentNumber);
    QString statusString;

    if((unsigned char)(status & 0) == 0)
    {statusString = "Фиксация";}
    if((unsigned char)(status & 1) == 1)
    {statusString = "Выключен";}
    if((unsigned char)(status & 2) == 2)
    {statusString = "Свободен";}
    if((unsigned char)(status & 3) == 3)
    {statusString = "Слежение";}

    ui->lineStatus->setText(statusString);
    //конец чтения статуса
}

void MotorControlWidget::on_ButtonSTOP_clicked()
{
    mWriteBuffer->motorStopBrake(CurrentNumber);
    ui->checkBoxTrace->setChecked(false);
    ui->groupBoxCalibration->setEnabled(true);
    state = States::STOP;
}

void MotorControlWidget::on_ButtonBRAKE_clicked()
{
    mWriteBuffer->motorStop(CurrentNumber);
    ui->checkBoxTrace->setChecked(false);
    ui->groupBoxCalibration->setEnabled(true);
    state = States::STOPBRAKE;

}

void MotorControlWidget::on_ButtonRELAX_clicked()
{
    mWriteBuffer->motorRelax(CurrentNumber);
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
        mWriteBuffer->setMotorShiftValue(CurrentNumber, ARCore::Inst()->getSettingStore()->GetMotors()->at(CurrentNumber).getShiftValue());
        mWriteBuffer->setMotorAngle(CurrentNumber, mReadBuffer->getMotorAngle(CurrentNumber));

        //разрешаем вход в режим управления слайдером
        mWriteBuffer->motorStopBrake(CurrentNumber);

        ui->checkBoxTrace->setEnabled(true);

        state = States::STOPBRAKE;
    }
    else
    {
        //входим в режим калибровки
        mWriteBuffer->motorStopBrake(CurrentNumber);
        mWriteBuffer->setMotorShiftValue(CurrentNumber,0);

        //запрещаем вход в режим управления слайдером
        ui->checkBoxTrace->setEnabled(false);

        state = States::CALIBRATE;
    }
}

//Происходит при нажатии кнопики установки нуля
void MotorControlWidget::on_ButtonSaveZero_clicked()
{
    //записываем в файл настроек новые калибровочные коэффициенты
    int CurrentPos = mReadBuffer->getMotorAngle(CurrentNumber);
    int NewCalibration=ReverceCoeff*CurrentPos;
    ARCore::Inst()->getSettingStore()->GetMotors()->at(CurrentNumber).setShiftValue(NewCalibration);
    mModel->setData(mModel->index(currentRow,10),QString::number(NewCalibration));
    ARCore::Inst()->getSettingStore()->SaveFile("config.xml");

    //записываем в мотор калибровочные коэффициенты
    mWriteBuffer->setMotorShiftValue(CurrentNumber,NewCalibration);
    mWriteBuffer->setMotorAngle(CurrentNumber, CurrentPos);

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
        mWriteBuffer->setMotorAngle(CurrentNumber, position);
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
        mWriteBuffer->motorTrace(CurrentNumber);

        //запрещаем вход в режим калибровки
        ui->groupBoxCalibration->setEnabled(false);
    }
    else
    {
        //выходим из режима управления
        mWriteBuffer->motorStopBrake(CurrentNumber);

        //разрешаем вход в режим калибровки
        ui->groupBoxCalibration->setEnabled(true);
    }
}

//инициализация слайдера и мин макс
void MotorControlWidget::SliderInit()
{
    int MinPos = mReadBuffer->getMotorMinAngle(CurrentNumber);
    int MaxPos = mReadBuffer->getMotorMaxAngle(CurrentNumber);
    int cAngle = mReadBuffer->getMotorAngle(CurrentNumber);
    ui->SliderAngle->setMinimum(MinPos);
    ui->SliderAngle->setMaximum(MaxPos);

    ui->lineMinAngle->setText(QString::number(MinPos));
    ui->lineMaxAngle->setText(QString::number(MaxPos));

    ui->spinDump->setValue(mReadBuffer->getMotorIGate(CurrentNumber));
    ui->spinStiff->setValue(mReadBuffer->getMotorPGate(CurrentNumber));
    ui->spinTorque->setValue(mWriteBuffer->getMotorDGate(CurrentNumber));
    ui->spinPosToGo->setMinimum(MinPos);
    ui->spinPosToGo->setMaximum(MaxPos);

    ui->SliderAngle->setValue(cAngle);
    mWriteBuffer->setMotorAngle(CurrentNumber, cAngle);

}

void MotorControlWidget::on_ButtonStiffWrite_clicked()
{
    mWriteBuffer->setMotorPGate(CurrentNumber,ui->spinStiff->value());
}

void MotorControlWidget::on_ButtonStiffSave_clicked()
{
    ARCore::Inst()->getSettingStore()->GetMotors()->at(CurrentNumber).getPIDGates()->setPGate(ui->spinStiff->value());
}

void MotorControlWidget::on_ButtonDumpSave_clicked()
{
    ARCore::Inst()->getSettingStore()->GetMotors()->at(CurrentNumber).getPIDGates()->setIGate(ui->spinDump->value());
}


void MotorControlWidget::on_ButtonDumpWrite_clicked()
{
    mWriteBuffer->setMotorIGate(CurrentNumber, ui->spinDump->value());
}

void MotorControlWidget::on_ButtonGoToPos_clicked()
{
    MoveController::Inst()->startGoToAngle(CurrentNumber,
                                              ui->spinPosToGo->value(),
                                              ui->spinTimeToGo->value());
}

void MotorControlWidget::on_ButtonStopGoToPos_clicked()
{

    MoveController::Inst()->stopGoToAngle();
}

