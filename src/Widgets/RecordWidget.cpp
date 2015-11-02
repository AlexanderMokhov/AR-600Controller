#include "RecordWidget.h"
#include "ui_RecordWidget.h"

RecordWidget::RecordWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RecordWidget)
{
    ui->setupUi(this);
    mRecorder = new Recorder;
    connect(mRecorder, SIGNAL(UpdateTime(long)), SLOT(OnUpdateTime(long)));
}

RecordWidget::~RecordWidget()
{
    delete ui;
}

void RecordWidget::on_ButtonStartRecord_clicked()
{
    mRecordTime = ui->spinTimeRecord->value();
    mDelay = ui->spinDelayRecord->value();
    mRecorder->SetParam(mDelay, mRecordTime);
    mRecorder->StartWriting();
}

void RecordWidget::on_ButtonStopRecord_clicked()
{
    mRecorder->StopWriting();
}

void RecordWidget::StartWriteRecord(int TimeRecord)
{
    mRecordTime = TimeRecord;
    ui->spinTimeRecord->setValue(TimeRecord);
    mDelay = ui->spinDelayRecord->value();
    mRecorder->SetParam(mDelay, mRecordTime);
    mRecorder->StartWriting();
}

void RecordWidget::StopWriteRecord()
{
    mRecorder->StopWriting();
}

void RecordWidget::OnUpdateTime(long time)
{
    ui->lineCurrentTime->setText(QString::number(time));
}
