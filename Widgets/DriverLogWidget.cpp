#include "DriverLogWidget.h"
#include "ui_DriverLogWidget.h"

DriverLogWidget::DriverLogWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DriverLogWidget)
{
    ui->setupUi(this);
    mDriverLogController = new DriverLogController();
}

DriverLogWidget::~DriverLogWidget()
{
    delete ui;
}

void DriverLogWidget::on_ButtonStartRecord_clicked()
{
    mCurrentTime=0;
    mRecordTime = ui->spinTimeRecord->value();
    mDelay = ui->spinDelayRecord->value();

    mRecordTimer = new QTimer(this);
    connect(mRecordTimer, SIGNAL(timeout()),this, SLOT(WriteRecord()));
    mDriverLogController=new DriverLogController();
    mRecordTimer->start(mDelay);
}

void DriverLogWidget::on_ButtonStopRecord_clicked()
{
    mRecordTimer->stop();
    SaveData();
}



void DriverLogWidget::WriteRecord()
{
    mDriverLogController->AddRawData(mCurrentTime);
    ui->lineCurrentTime->setText(QString::number(mCurrentTime));
    mCurrentTime+=mDelay;

    if(mCurrentTime> mRecordTime)
    {
        mRecordTimer->stop();
        SaveData();
    }
}

void DriverLogWidget::StartWriteLog(int TimeRecord)
{
    mCurrentTime=0;
    mRecordTime = TimeRecord;
    ui->spinTimeRecord->setValue(TimeRecord);
    mDelay = ui->spinDelayRecord->value();

    mRecordTimer = new QTimer(this);
    connect(mRecordTimer, SIGNAL(timeout()),this, SLOT(WriteRecord()));
    mDriverLogController=new DriverLogController();
    mRecordTimer->start(mDelay);
}

void DriverLogWidget::StopWriteLog()
{
    mRecordTimer->stop();
    SaveData();
}

void DriverLogWidget::SaveData()
{
    QDateTime mCurrentDateTime = QDateTime::currentDateTime();
    QString FileName = "DriverLog_" + mCurrentDateTime.toString("dd_MM_yyyy_HH_mm_ss")+"_.txt";
    mDriverLogController->SaveData(FileName.toStdString());
}
