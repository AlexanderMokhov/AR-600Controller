#include "LogOutputW.h"
#include "ui_LogOutputW.h"

LogOutputW::LogOutputW(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LogOutputW)
{
    ui->setupUi(this);

    mTimer = new QTimer(this);
    mInterval = 10;
    mTimer->setInterval(mInterval);//интервал 0.5 секунды
    connect(mTimer,SIGNAL(timeout()),this,SLOT(OnTimerTick()));
}

LogOutputW::~LogOutputW()
{
    delete ui;
}

void LogOutputW::addMessage(QString message)
{
    QDateTime mCurrentDateTime = QDateTime::currentDateTime();
    QString prefix = "<font color = 'brown'>" + mCurrentDateTime.toString("dd.MM.yyyy HH:mm:ss")+"</font> - ";
    ui->textLog->append(prefix + message);
}

void LogOutputW::startWrite()
{
    mTimer->start();
}

void LogOutputW::OnTimerTick()
{
    updateData();
}

void LogOutputW::updateData()
{
    std::vector<std::string> mData = LogMaster::Inst()->getLastStrings();
    for(int i = 0; i < mData.size(); i++)
        addMessage(QString::fromStdString(mData.at(i)));
}
