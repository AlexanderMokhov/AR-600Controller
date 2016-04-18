#include "RecordWidget.h"
#include "ui_RecordWidget.h"

RecordWidget::RecordWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RecordWidget)
{
    ui->setupUi(this);
    mRecorder = new Recorder;
    connect(mRecorder, SIGNAL(UpdateTime(long)), SLOT(OnUpdateTime(long)));

    isWriteForMove = false;
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
    if(!isWriteForMove) return;

    mRecordTime = TimeRecord;
    ui->spinTimeRecord->setValue(TimeRecord);
    mDelay = ui->spinDelayRecord->value();
    mRecorder->SetParam(mDelay, mRecordTime);
    mRecorder->StartWriting();
}

void RecordWidget::StopWriteRecord()
{
    if(!isWriteForMove) return;

    mRecorder->StopWriting();
}

void RecordWidget::on_CheckWriteB_clicked(bool checked)
{
    isWriteForMove = checked;
}

void RecordWidget::OnUpdateTime(long time)
{
    ui->lineCurrentTime->setText(QString::number(time));
}
