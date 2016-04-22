#include "RecordControlW.h"
#include "ui_RecordControlW.h"

RecordControlW::RecordControlW(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RecordControlW)
{
    ui->setupUi(this);
    mRecorder = new Recorder;
    connect(mRecorder, SIGNAL(UpdateTime(long)), SLOT(OnUpdateTime(long)));

    isWriteForMove = false;
}

RecordControlW::~RecordControlW()
{
    delete ui;
}

void RecordControlW::on_ButtonStartRecord_clicked()
{
    mRecordTime = ui->spinTimeRecord->value();
    mDelay = ui->spinDelayRecord->value();
    mRecorder->SetParam(mDelay, mRecordTime);
    mRecorder->StartWriting();
}

void RecordControlW::on_ButtonStopRecord_clicked()
{
    mRecorder->StopWriting();
}

void RecordControlW::StartWriteRecord(int TimeRecord)
{
    if(!isWriteForMove) return;

    mRecordTime = TimeRecord;
    ui->spinTimeRecord->setValue(TimeRecord);
    mDelay = ui->spinDelayRecord->value();
    mRecorder->SetParam(mDelay, mRecordTime);
    mRecorder->StartWriting();
}

void RecordControlW::StopWriteRecord()
{
    if(!isWriteForMove) return;

    mRecorder->StopWriting();
}

void RecordControlW::on_CheckWriteB_clicked(bool checked)
{
    isWriteForMove = checked;
}

void RecordControlW::OnUpdateTime(long time)
{
    ui->lineCurrentTime->setText(QString::number(time));
}
