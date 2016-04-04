#include "LogWidget.h"
#include "ui_LogWidget.h"

LogWidget::LogWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LogWidget)
{
    ui->setupUi(this);
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
