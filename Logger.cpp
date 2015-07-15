#include "Logger.h"

Logger::Logger(QObject *parent) : QThread(parent)
{
    isRunning=false;
}

Logger::~Logger()
{

}

void Logger::run()
{
    mTimer = new QTimer;
    mTimer->setInterval(mDelay);
    connect(mTimer, SIGNAL(timeout()),SLOT(WriteRecord()),Qt::DirectConnection);
    DeviceLogController::Instance()->StartWrite();
    mTimer->start();
    //До окончания работы
    exec();
    //После окончания работы
    mTimer->stop();
    SaveData();
}

void Logger::StartWriting()
{
    isRunning = true;
    start();
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
    DeviceLogController::Instance()->AddRawData();

    if(DeviceLogController::Instance()->mTime.elapsed()> mDuration)
    {
        exit();
    }
}

void Logger::SaveData()
{
    qDebug() << "Log was saved" << endl;
    QDateTime mCurrentDateTime = QDateTime::currentDateTime();
    QString FileName = "DriverLog_" + mCurrentDateTime.toString("dd_MM_yyyy_HH_mm_ss")+"_.txt";
    DeviceLogController::Instance()->SaveData(FileName.toStdString());
}

