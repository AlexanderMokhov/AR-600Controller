#include "DeviceLogWidget.h"
#include "ui_DeviceLogWidget.h"

DeviceLogWidget::DeviceLogWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DeviceLogWidget)
{
    ui->setupUi(this);
    mLogger = new Logger;
    connect(mLogger,SIGNAL(UpdateTime(long)),SLOT(OnUpdateTime(long)));
}

DeviceLogWidget::~DeviceLogWidget()
{
    delete ui;
}

void DeviceLogWidget::on_ButtonStartRecord_clicked()
{
    mRecordTime = ui->spinTimeRecord->value();
    mDelay = ui->spinDelayRecord->value();

    mLogger->SetParam(mDelay,mRecordTime);
    mLogger->StartWriting();
}

void DeviceLogWidget::on_ButtonStopRecord_clicked()
{
    mLogger->StopWriting();
}

void DeviceLogWidget::StartWriteLog(int TimeRecord)
{
    mRecordTime = TimeRecord;
    ui->spinTimeRecord->setValue(TimeRecord);
    mDelay = ui->spinDelayRecord->value();

    mLogger->SetParam(mDelay,mRecordTime);
    mLogger->StartWriting();
}

void DeviceLogWidget::StopWriteLog()
{
    mLogger->StopWriting();
}

void DeviceLogWidget::OnUpdateTime(long time)
{
    ui->lineCurrentTime->setText(QString::number(time));
}
