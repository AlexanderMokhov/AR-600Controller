#include "LogWidget.h"
#include "ui_LogWidget.h"

LogWidget::LogWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LogWidget)
{
    ui->setupUi(this);

    mTimer = new QTimer(this);
    mInterval = 10;
    mTimer->setInterval(mInterval);//интервал 0.5 секунды
    connect(mTimer,SIGNAL(timeout()),this,SLOT(OnTimerTick()));
}

LogWidget::~LogWidget()
{
    delete ui;
}

void LogWidget::addMessage(QString message)
{
    QDateTime mCurrentDateTime = QDateTime::currentDateTime();
    QString prefix = "<font color = 'brown'>" + mCurrentDateTime.toString("dd.MM.yyyy HH:mm:ss")+"</font> - ";
    ui->textLog->append(prefix + message);
}

void LogWidget::startWrite()
{
    mTimer->start();
}

void LogWidget::OnTimerTick()
{
    updateData();
}

void LogWidget::updateData()
{
    std::vector<std::string> mData = LogMaster::Inst()->getLastStrings();
    for(int i = 0; i < mData.size(); i++)
        addMessage(QString::fromStdString(mData.at(i)));
}
