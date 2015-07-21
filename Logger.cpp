#include "Logger.h"

Logger::Logger(QObject *parent) : QThread(parent)
{
    isRunning = false;
    isRestart = false;
}

Logger::~Logger()
{

}

void Logger::run()
{
    //нить потока создана
pointStart:
    isRestart = false;
    isRunning = true;

    mTimer = new QTimer;
    mTimer->setInterval(mDelay);
    connect(mTimer, SIGNAL(timeout()),SLOT(WriteRecord()),Qt::DirectConnection);
    DeviceLogController::Inst()->StartWrite();
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

void Logger::StartWriting()
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

void Logger::StopWriting()
{
    isRunning = false;
    exit();
}

void Logger::SetParam(int delay, long duration)
{
    mDelay = delay;
    mDuration = duration;
}

void Logger::WriteRecord()
{
    DeviceLogController::Inst()->AddRawData();
    emit UpdateTime(DeviceLogController::Inst()->mTime.elapsed());

    if(DeviceLogController::Inst()->mTime.elapsed()> mDuration)
    {
        exit();
    }
}

void Logger::SaveData()
{
    qDebug() << "Log was saved" << endl;
    QDateTime mCurrentDateTime = QDateTime::currentDateTime();
    QString FileName = "DeviceLog_" + mCurrentDateTime.toString("dd_MM_yyyy_HH_mm_ss")+"_.txt";
    DeviceLogController::Inst()->SaveData(FileName.toStdString());
}

