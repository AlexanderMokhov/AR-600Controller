#include "MotorsControlW.h"
#include "ui_MotorsControlW.h"

MotorsControlW::MotorsControlW(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MotorsControlW)
{
    ui->setupUi(this);

    mReadBuffer = ARPacketManager::Inst()->getPacketRecv();
    mWriteBuffer = ARPacketManager::Inst()->getPacketSend();

    state = States::STOPBRAKE;

    initWidgets();
}

MotorsControlW::~MotorsControlW()
{
    delete ui;
}

void MotorsControlW::setModel(MotorTableModel *model)
{
    mModel = model;
}

void MotorsControlW::RowChanged(int cRow)
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
    Reverce = SettingsStorage::Inst()->GetMotors()->at(CurrentNumber).getReverceState();
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
void MotorsControlW::UpdateData()
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

    updateInfo();
}

void MotorsControlW::on_ButtonSTOP_clicked()
{
    mWriteBuffer->motorStopBrake(CurrentNumber);
    ui->checkBoxTrace->setChecked(false);
    ui->groupBoxCalibration->setEnabled(true);
    state = States::STOP;
}

void MotorsControlW::on_ButtonBRAKE_clicked()
{
    mWriteBuffer->motorStop(CurrentNumber);
    ui->checkBoxTrace->setChecked(false);
    ui->groupBoxCalibration->setEnabled(true);
    state = States::STOPBRAKE;

}

void MotorsControlW::on_ButtonRELAX_clicked()
{
    mWriteBuffer->motorRelax(CurrentNumber);
    ui->checkBoxTrace->setChecked(false);
    ui->groupBoxCalibration->setEnabled(true);
    state = States::RELAX;
}

//происходит при входе и выходе в режим калибрации
void MotorsControlW::on_groupBoxCalibration_clicked(bool checked)
{
    if(!checked)
    {
        //выходим из режима калибровки
        mWriteBuffer->setMotorShiftValue(CurrentNumber, SettingsStorage::Inst()->GetMotors()->at(CurrentNumber).getShiftValue());
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
void MotorsControlW::on_ButtonSaveZero_clicked()
{
    //записываем в файл настроек новые калибровочные коэффициенты
    int CurrentPos = mReadBuffer->getMotorAngle(CurrentNumber);
    int NewCalibration=ReverceCoeff*CurrentPos;
    SettingsStorage::Inst()->GetMotors()->at(CurrentNumber).setShiftValue(NewCalibration);
    mModel->setData(mModel->index(currentRow,10),QString::number(NewCalibration));
    SettingsStorage::Inst()->SaveFile("config.xml");

    //записываем в мотор калибровочные коэффициенты
    mWriteBuffer->setMotorShiftValue(CurrentNumber,NewCalibration);
    mWriteBuffer->setMotorAngle(CurrentNumber, CurrentPos);

    //разрешаем вход в режим управления слайдером
    ui->groupBoxCalibration->setChecked(false);
    ui->checkBoxTrace->setEnabled(true);

    state = States::STOPBRAKE;
}

//происходит при изменении позиции слайдером
void MotorsControlW::on_SliderAngle_sliderMoved(int position)
{
    if(state == States::TRACE)
    {
        mWriteBuffer->setMotorAngle(CurrentNumber, position);
    }
}

//происходит при входе и выходе в режим управления слайдером
void MotorsControlW::on_checkBoxTrace_clicked(bool checked)
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
void MotorsControlW::SliderInit()
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

void MotorsControlW::initWidgets()
{
    ui->tableWidget->setColumnWidth(0, 100);

    // все строки высотой 21px
    for (int row = 0; row < ui->tableWidget->rowCount(); ++row)
        ui->tableWidget->setRowHeight(row, 21);

    QTableWidgetItem *itemName = new QTableWidgetItem;
    itemName->setText("Описание");
    itemName->setTextAlignment(Qt::AlignLeft + Qt::AlignVCenter);
    ui->tableWidget->setItem(0, 0, itemName);

    QTableWidgetItem *itemStatus = new QTableWidgetItem;
    itemStatus->setText("Состояние");
    itemStatus->setTextAlignment(Qt::AlignLeft + Qt::AlignVCenter);
    ui->tableWidget->setItem(1, 0, itemStatus);

    QTableWidgetItem *itemVoltage = new QTableWidgetItem;
    itemVoltage->setText("Напряжение");
    itemVoltage->setTextAlignment(Qt::AlignLeft + Qt::AlignVCenter);
    ui->tableWidget->setItem(2, 0, itemVoltage);

    QTableWidgetItem *itemCurrent = new QTableWidgetItem;
    itemCurrent->setText("Ток");
    itemCurrent->setTextAlignment(Qt::AlignLeft + Qt::AlignVCenter);
    ui->tableWidget->setItem(3, 0, itemCurrent);

    QTableWidgetItem *itemNameValue = new QTableWidgetItem;
    itemNameValue->setText("Двигатель");
    itemNameValue->setTextAlignment(Qt::AlignCenter);
    ui->tableWidget->setItem(0, 1, itemNameValue);

    QTableWidgetItem *itemStatusValue = new QTableWidgetItem;
    itemStatusValue->setText("Выключен");
    itemStatusValue->setTextAlignment(Qt::AlignCenter);
    ui->tableWidget->setItem(1, 1, itemStatusValue);

    QTableWidgetItem *itemVoltageValue = new QTableWidgetItem;
    itemVoltageValue->setText("0.00");
    itemVoltageValue->setTextAlignment(Qt::AlignCenter);
    ui->tableWidget->setItem(2, 1, itemVoltageValue);

    QTableWidgetItem *itemCurrentValue = new QTableWidgetItem;
    itemCurrentValue->setText("0.00");
    itemCurrentValue->setTextAlignment(Qt::AlignCenter);
    ui->tableWidget->setItem(3, 1, itemCurrentValue);
}

void MotorsControlW::updateInfo()
{
    QString name = QString::fromLocal8Bit(
                SettingsStorage::Inst()->GetMotors()->at(CurrentNumber).getName().c_str());
    ui->tableWidget->item(0,1)->setText(name);

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

    ui->tableWidget->item(2,1)->setText(statusString);

    //обновляем информацию о токе и напряжении на моторах
    ui->tableWidget->item(2,1)->setText(QString::number(
       ARPacketManager::Inst()->getPacketRecv()->getMotorVoltage(CurrentNumber)/100.0, 'f', 2));

    ui->tableWidget->item(3,1)->setText(QString::number(
       ARPacketManager::Inst()->getPacketRecv()->getMotorCurrent(CurrentNumber)/100.0, 'f', 2));
}

void MotorsControlW::on_ButtonStiffWrite_clicked()
{
    mWriteBuffer->setMotorPGate(CurrentNumber,ui->spinStiff->value());
}

void MotorsControlW::on_ButtonStiffSave_clicked()
{
    SettingsStorage::Inst()->GetMotors()->at(CurrentNumber).getPIDGates()->setPGate(ui->spinStiff->value());
}

void MotorsControlW::on_ButtonDumpSave_clicked()
{
    SettingsStorage::Inst()->GetMotors()->at(CurrentNumber).getPIDGates()->setIGate(ui->spinDump->value());
}


void MotorsControlW::on_ButtonDumpWrite_clicked()
{
    mWriteBuffer->setMotorIGate(CurrentNumber, ui->spinDump->value());
}

void MotorsControlW::on_ButtonGoToPos_clicked()
{
    m_mover->startGoToAngle(CurrentNumber,
                            ui->spinPosToGo->value(),
                            ui->spinTimeToGo->value());
    //MoveController::Inst()->startGoToAngle();
}

void MotorsControlW::on_ButtonStopGoToPos_clicked()
{

    MoveController::Inst()->stopMotorTransit();
}

