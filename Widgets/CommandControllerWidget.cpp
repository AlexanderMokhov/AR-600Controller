#include "CommandControllerWidget.h"
#include "ui_CommandControllerWidget.h"
#include <QDebug>

CommandControllerWidget::CommandControllerWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CommandControllerWidget)
{
    ui->setupUi(this);
    DefaultText = "Нажмите кнопку \"Загрузить Файл\"";
    ui->MessageTextBox->setText(DefaultText);

    ui->ButtonPlayPause->setEnabled(false);
    ui->ButtonNext->setEnabled(false);
    ui->ButtonStop->setEnabled(false);
    IsLog=false;
}

CommandControllerWidget::~CommandControllerWidget()
{
    delete ui;
}

void CommandControllerWidget::on_ButtonLoadFile_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(0,"Open Commands List Dialog","","*.txt");
    if (!fileName.isEmpty())
    {
        ui->FilePathTextBox->setText(fileName);
        bool isOk = CommandController::Instance()->LoadFromFile(fileName.toStdString());
        if(isOk)
        {
            qDebug() << "Файл списка команд успешно загружен из " << fileName << endl;
            qDebug() << "Команды успешно прочитаны" <<endl;
            int mCountRows = CommandController::Instance()->GetCountRows();
            int mTimeRecord = CommandController::Instance()->GetTimeRecord();
            ui->MessageTextBox->clear();
            ui->MessageTextBox->append( "Прочитано " + QString::number(mCountRows) + " строк" + "\n");
            ui->MessageTextBox->append( "Время записи " + QString::number((double)mTimeRecord/1e6) + " секунд" + "\n");

            ui->ButtonPlayPause->setEnabled(true);
            ui->ButtonNext->setEnabled(true);
            ui->ButtonStop->setEnabled(true);
            emit FileLoaded();
        }
        else
        {
            qDebug() << "Файл списка команд не был загружен из " << fileName << endl;
            qDebug() << "Возможно имя, или формат файла заданы неверно" <<endl;
        }
    }
}

void CommandControllerWidget::on_ButtonPlayPause_clicked()
{
    if(CommandController::Instance()->GetPlayForwardState())
    {
        CommandController::Instance()->SetPlayForwardState(false);
        ui->ButtonLoadFile->setEnabled(true);

    }
    else
    {
        CommandController::Instance()->SetCurrentTimeForCommands(0);
        CommandController::Instance()->SetPlayForwardState(true);
        ui->ButtonLoadFile->setEnabled(false);
        ui->checkBoxLog->setEnabled(false);
        if(IsLog)
        {
            emit StartWriteLog(CommandController::Instance()->GetTimeRecord()/1e3);
        }
    }
}

void CommandControllerWidget::on_ButtonStop_clicked()
{
    CommandController::Instance()->SetPlayForwardState(false);
    CommandController::Instance()->SetCommandId(0);
    ui->ButtonLoadFile->setEnabled(true);
    ui->checkBoxLog->setEnabled(true);
    if(IsLog)
    {
        emit StopWriteLog();
    }
}

void CommandControllerWidget::on_ButtonNext_clicked()
{
    CommandController::Instance()->NextCommand();
}

void CommandControllerWidget::on_checkBoxLog_clicked(bool checked)
{
    IsLog = checked;
}
