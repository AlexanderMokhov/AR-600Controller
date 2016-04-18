#include "PowerControlW.h"
#include "ui_PowerControlW.h"

PowerControlW::PowerControlW(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PowerControlW)
{
    ui->setupUi(this);

    initWidgets();

    mTimer = new QTimer(this);
    mInterval = 500;
    mTimer->setInterval(mInterval); //интервал 0.5 секунды
    mTime = 0;
    isOn = true;
    connect(mTimer, SIGNAL(timeout()), this, SLOT( OnTimerTick() ));

}

PowerControlW::~PowerControlW()
{
    delete ui;
}

void PowerControlW::updateInfo()
{
    ui->tableWidget->item(1,1)->setText(QString::number(
       ARPacketManager::Inst()->getPacketRecv()->getPowerVoltage48(), 'f', 2));
    ui->tableWidget->item(2,1)->setText(QString::number(
       ARPacketManager::Inst()->getPacketRecv()->getPowerVoltage8_2(), 'f', 2));
    ui->tableWidget->item(3,1)->setText(QString::number(
       ARPacketManager::Inst()->getPacketRecv()->getPowerVoltage8_1(), 'f', 2));
    ui->tableWidget->item(4,1)->setText(QString::number(
       ARPacketManager::Inst()->getPacketRecv()->getPowerVoltage6_2(), 'f', 2));
    ui->tableWidget->item(5,1)->setText(QString::number(
       ARPacketManager::Inst()->getPacketRecv()->getPowerVoltage6_1(), 'f', 2));

    ui->tableWidget->item(1,2)->setText(QString::number(
       ARPacketManager::Inst()->getPacketRecv()->getPowerCurrent48(), 'f', 2));
    ui->tableWidget->item(2,2)->setText(QString::number(
       ARPacketManager::Inst()->getPacketRecv()->getPowerCurrent8_2(), 'f', 2));
    ui->tableWidget->item(3,2)->setText(QString::number(
       ARPacketManager::Inst()->getPacketRecv()->getPowerCurrent8_1(), 'f', 2));
    ui->tableWidget->item(4,2)->setText(QString::number(
       ARPacketManager::Inst()->getPacketRecv()->getPowerCurrent6_2(), 'f', 2));
    ui->tableWidget->item(5,2)->setText(QString::number(
                                            ARPacketManager::Inst()->getPacketRecv()->getPowerCurrent6_1(), 'f', 2));
}

void PowerControlW::onPowerButtonsClicked()
{
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    if (!button) return;
    QVariant var = button->property("row");

    if (!var.isValid()) return;

    switch (var.toInt()) {
    case 1:
        on48VChanged( button->isChecked() );
        break;
    case 2:
        on8V2Changed( button->isChecked() );
        break;
    case 3:
        on8V1Changed( button->isChecked() );
        break;
    case 4:
        on6V2Changed( button->isChecked() );
        break;
    case 5:
        on6V1Changed( button->isChecked() );
        break;
    case 6:
        onAllPowerChanged( button->isChecked() );
        break;
    default:
        break;
    }
}

void PowerControlW::on48VChanged(bool checked)
{
    if(checked)
    {
        ARPacketManager::Inst()->getPacketSend()->onPower48();
        mTime = 1*500;
    }
    else
    {
       ARPacketManager::Inst()->getPacketSend()->offPower48();
       mTime = 0*500;
    }
}

void PowerControlW::on8V2Changed(bool checked)
{
    if(checked)
    {
        ARPacketManager::Inst()->getPacketSend()->onPower8_2();
        mTime = 2*500;
    }
    else
    {
       ARPacketManager::Inst()->getPacketSend()->offPower8_2();
       mTime = 1*500;
    }
}

void PowerControlW::on8V1Changed(bool checked)
{
    if(checked)
    {
        ARPacketManager::Inst()->getPacketSend()->onPower8_1();
        mTime = 3*500;
    }
    else
    {
       ARPacketManager::Inst()->getPacketSend()->offPower8_1();
       mTime = 2*500;
    }
}

void PowerControlW::on6V2Changed(bool checked)
{
    if(checked)
    {
        ARPacketManager::Inst()->getPacketSend()->onPower6_2();
        mTime = 4*500;
    }
    else
    {
       ARPacketManager::Inst()->getPacketSend()->offPower6_2();
       mTime = 3*500;
    }
}

void PowerControlW::on6V1Changed(bool checked)
{
    if(checked)
    {
        ARPacketManager::Inst()->getPacketSend()->onPower6_1();
        mTime = 5*500;
    }
    else
    {
       ARPacketManager::Inst()->getPacketSend()->offPower6_1();
       mTime = 4*500;
    }
}

void PowerControlW::onAllPowerChanged(bool checked)
{
    //onRebootPower();
    if(checked)
    {
        isOn = true;
        if( !mTimer->isActive() ) mTimer->start();
    }
    else
    {
        isOn = false;
        if( !mTimer->isActive() ) mTimer->start();
    }
}

void PowerControlW::onRebootPower()
{
    if( mTimer->isActive() ) mTimer->stop();
    disconnect(mTimer, SIGNAL(timeout()), this, SLOT( OnTimerTick() ));
    connect(mTimer, SIGNAL(timeout()), this, SLOT( stepRebootPower()));
    if( !mTimer->isActive() ) mTimer->start();
    isOn = false;
    mTime = 4*500;
    m_state = PowerStates::REBOOT_POWER_DOWN;
}

void PowerControlW::stepRebootPower()
{
    switch (m_state) {
    case PowerStates::REBOOT_POWER_DOWN:
        OnTimerTick();
        if(mTime < 0)
        {
            mTimer->start();
            m_state = PowerStates::REBOOT_POWER_UP;
            isOn = true;
        }
        break;
    case PowerStates::REBOOT_POWER_UP:
        OnTimerTick();
        if(mTime > 4 * mInterval)
        {
            m_state = PowerStates::REBOOT_POWER_START;
            mTimer->stop();

            disconnect(mTimer, SIGNAL(timeout()), this, SLOT( stepRebootPower() ));
            connect(mTimer, SIGNAL(timeout()), this, SLOT( OnTimerTick() ));
        }
        break;
    default:
        break;
    }
}

void PowerControlW::OnTimerTick()
{
    if(isOn)
    {
        //включаем очередное напряжение
        switch (mTime)
        {
        case 0:
        {
            ARPacketManager::Inst()->getPacketSend()->onPower48();
            QPushButton *pb = (QPushButton*)ui->tableWidget->cellWidget(1,3);
            pb->setChecked(true);
        }
            break;
        case 500:
        {
            ARPacketManager::Inst()->getPacketSend()->onPower8_2();
            QPushButton *pb = (QPushButton*)ui->tableWidget->cellWidget(2,3);
            pb->setChecked(true);
        }
            break;
        case 2*500:
        {
            ARPacketManager::Inst()->getPacketSend()->onPower8_1();
            QPushButton *pb = (QPushButton*)ui->tableWidget->cellWidget(3,3);
            pb->setChecked(true);
        }
            break;
        case 3*500:
        {
            ARPacketManager::Inst()->getPacketSend()->onPower6_2();
            QPushButton *pb = (QPushButton*)ui->tableWidget->cellWidget(4,3);
            pb->setChecked(true);
        }
            break;
        case 4*500:
        {
            ARPacketManager::Inst()->getPacketSend()->onPower6_1();
            QPushButton *pb = (QPushButton*)ui->tableWidget->cellWidget(5,3);
            pb->setChecked(true);
            mTimer->stop();
        }
            break;
        }

        mTime += mInterval;
    }
    else
    {
        //выключаем очередное напряжение
        switch (mTime)
        {
        case 0:
        {
            ARPacketManager::Inst()->getPacketSend()->offPower48();
            QPushButton *pb = (QPushButton*)ui->tableWidget->cellWidget(1,3);
            pb->setChecked(false);
            mTimer->stop();
        }
            break;

        case 500:
        {
            ARPacketManager::Inst()->getPacketSend()->offPower8_2();
            QPushButton *pb = (QPushButton*)ui->tableWidget->cellWidget(2,3);
            pb->setChecked(false);
        }
            break;
        case 2*500:
        {
            ARPacketManager::Inst()->getPacketSend()->offPower8_1();
            QPushButton *pb = (QPushButton*)ui->tableWidget->cellWidget(3,3);
            pb->setChecked(false);
        }
            break;
        case 3*500:
        {
            ARPacketManager::Inst()->getPacketSend()->offPower6_2();
            QPushButton *pb = (QPushButton*)ui->tableWidget->cellWidget(4,3);
            pb->setChecked(false);
        }
            break;
        case 4*500:
        {
            ARPacketManager::Inst()->getPacketSend()->offPower6_1();
            QPushButton *pb = (QPushButton*)ui->tableWidget->cellWidget(5,3);
            pb->setChecked(false);
        }
            break;
        }
        mTime -= mInterval;
    }
}

void PowerControlW::initWidgets()
{
    int buttonsColumn = 3;

    // заполнение столбца кнопками
    for (int row = 1; row < ui->tableWidget->rowCount(); ++row)
    {
        // создаем кнопку
        QPushButton* button = new QPushButton();
        button->setProperty("row", row);
        button->setCheckable(true);
        button->setIconSize(QSize(50, 18));
        button->setFlat(true);

        // привязываем иконки
        QIcon my_icon;
        my_icon.addFile(":/MyIcons/Icons/on.png", QSize(), QIcon::Normal, QIcon::On);
        my_icon.addFile(":/MyIcons/Icons/off.png", QSize(), QIcon::Normal, QIcon::Off);
        button->setIcon(my_icon);

         // задаем стиль
        button->setStyleSheet("QPushButton:checked { \
                               background: white; \
                               border: 0; \
                               border-style: outset;}");
        // соединяем со слотом
        connect(button, SIGNAL(clicked()), SLOT(onPowerButtonsClicked()));
        ui->tableWidget->setCellWidget(row, buttonsColumn, button);
    }

    ui->tableWidget->setColumnWidth(1, 50);
    ui->tableWidget->setColumnWidth(2, 50);
    ui->tableWidget->setColumnWidth(3, 50);

    // все строки высотой 21px
    for (int row = 0; row < ui->tableWidget->rowCount(); ++row)
        ui->tableWidget->setRowHeight(row, 21);

    QTableWidgetItem *itemVoltage = new QTableWidgetItem;
    itemVoltage->setText("Voltage");
    itemVoltage->setTextAlignment(Qt::AlignCenter);
    ui->tableWidget->setItem(0, 1, itemVoltage);

    QTableWidgetItem *itemCurrent = new QTableWidgetItem;
    itemCurrent->setText("Current");
    itemCurrent->setTextAlignment(Qt::AlignCenter);
    ui->tableWidget->setItem(0, 2, itemCurrent);

    // вставляем ячейки со значениями
    for (int row = 1; row < ui->tableWidget->rowCount(); ++row)
    {
        QTableWidgetItem *itemVoltage = new QTableWidgetItem;
        itemVoltage->setText("0.00");
        itemVoltage->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget->setItem(row,1,itemVoltage);

        QTableWidgetItem *itemCurrent = new QTableWidgetItem;
        itemCurrent->setText("0.00");
        itemCurrent->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget->setItem(row,2,itemCurrent);
    }

    // добавление надписей слева
    QTableWidgetItem *item48 = new QTableWidgetItem;
    item48->setText("48V");
    item48->setTextAlignment(Qt::AlignCenter);
    ui->tableWidget->setItem(1, 0, item48);

    QTableWidgetItem *item82 = new QTableWidgetItem;
    item82->setText("8V (2)");
    item82->setTextAlignment(Qt::AlignCenter);
    ui->tableWidget->setItem(2, 0, item82);

    QTableWidgetItem *item81 = new QTableWidgetItem;
    item81->setText("8V (1)");
    item81->setTextAlignment(Qt::AlignCenter);
    ui->tableWidget->setItem(3, 0, item81);

    QTableWidgetItem *item62 = new QTableWidgetItem;
    item62->setText("6V (2)");
    item62->setTextAlignment(Qt::AlignCenter);
    ui->tableWidget->setItem(4, 0, item62);

    QTableWidgetItem *item61 = new QTableWidgetItem;
    item61->setText("6V (1)");
    item61->setTextAlignment(Qt::AlignCenter);
    ui->tableWidget->setItem(5, 0, item61);

    QTableWidgetItem *itemAll = new QTableWidgetItem;
    itemAll->setText("Все источники");
    itemAll->setTextAlignment(Qt::AlignCenter);
    ui->tableWidget->setItem(6, 0, itemAll);
}
