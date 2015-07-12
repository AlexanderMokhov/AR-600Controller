#include "DeviceLogWidget.h"
#include "ui_DeviceLogWidget.h"

DeviceLogWidget::DeviceLogWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DeviceLogWidget)
{
    ui->setupUi(this);
}

DeviceLogWidget::~DeviceLogWidget()
{
    delete ui;
}

void DeviceLogWidget::on_ButtonStartRecord_clicked()
{
    mCurrentTime=0;
    mRecordTime = ui->spinTimeRecord->value();
    mDelay = ui->spinDelayRecord->value();

    mRecordTimer = new QTimer(this);
    connect(mRecordTimer, SIGNAL(timeout()),SLOT(WriteRecord()));
    mRecordTimer->start(mDelay);
    DeviceLogController::Instance()->StartWrite();
}

void DeviceLogWidget::on_ButtonStopRecord_clicked()
{
    mRecordTimer->stop();
    SaveData();
}



void DeviceLogWidget::WriteRecord()
{
    DeviceLogController::Instance()->AddRawData(mCurrentTime);
    //ui->lineCurrentTime->setText(QString::number(mCurrentTime));
    ui->lineCurrentTime->setText(QString::number(DeviceLogController::Instance()->mTime.elapsed()));
    mCurrentTime+=mDelay;

    if(DeviceLogController::Instance()->mTime.elapsed()> mRecordTime)
    {
        mRecordTimer->stop();
        SaveData();
    }

}

void DeviceLogWidget::StartWriteLog(int TimeRecord)
{
    mCurrentTime=0;
    mRecordTime = TimeRecord;
    ui->spinTimeRecord->setValue(TimeRecord);
    mDelay = ui->spinDelayRecord->value();

    mRecordTimer = new QTimer(this);
    connect(mRecordTimer, SIGNAL(timeout()), SLOT(WriteRecord()));
    mRecordTimer->start(mDelay);
    DeviceLogController::Instance()->StartWrite();
}

void DeviceLogWidget::StopWriteLog()
{
    mRecordTimer->stop();
    SaveData();
}

void DeviceLogWidget::SaveData()
{
    QDateTime mCurrentDateTime = QDateTime::currentDateTime();
    QString FileName = "DriverLog_" + mCurrentDateTime.toString("dd_MM_yyyy_HH_mm_ss")+"_.txt";
    DeviceLogController::Instance()->SaveData(FileName.toStdString());
}
