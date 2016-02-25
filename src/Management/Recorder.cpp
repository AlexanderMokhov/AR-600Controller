#include "Recorder.h"
#include <QApplication>

Recorder::Recorder(QObject *parent) : QThread(parent)
{
    isRunning = false;
    isRestart = false;
}

Recorder::~Recorder()
{

}

void Recorder::run()
{
    //нить потока создана
pointStart:
    isRestart = false;
    isRunning = true;

    mTimer = new QTimer;
    mTimer->setInterval(mDelay);
    connect(mTimer, SIGNAL(timeout()),SLOT(WriteRecord()),Qt::DirectConnection);
    RecordController::Inst()->StartWrite();
    mTimer->start();
    //Запускаем цикл обработки событий
    exec();
    //Завершился цикл обработки событий
    mTimer->stop();
    SaveData();

    isRunning = false;
    if(isRestart) goto pointStart;
    //нить потока удалена
}

void Recorder::StartWriting()
{
    if(isRunning == false)
    {
        isRunning = true;
        start();
    }
    else
    {
        isRestart = true;
        exit();
    }
}

void Recorder::StopWriting()
{
    isRunning = false;
    exit();
}

void Recorder::SetParam(int delay, long duration)
{
    mDelay = delay;
    mDuration = duration;
}

void Recorder::WriteRecord()
{
    RecordController::Inst()->AddRawData();
    emit UpdateTime(RecordController::Inst()->mTime.elapsed());

    if(RecordController::Inst()->mTime.elapsed()> mDuration)
    {
        exit();
    }
}

void Recorder::SaveData()
{
    qDebug() << "Record was saved" << endl;
    QDateTime mCurrentDateTime = QDateTime::currentDateTime();
    QString FileName = "Records\\Record_" + mCurrentDateTime.toString("dd_MM_yyyy_HH_mm_ss")+"_.txt";
    QString FileName2 = "Records\\RecordCurrents_" + mCurrentDateTime.toString("dd_MM_yyyy_HH_mm_ss")+"_.txt";
    RecordController::Inst()->SaveData(FileName.toStdString());
    RecordController::Inst()->SaveCurData(FileName2.toStdString());
}



