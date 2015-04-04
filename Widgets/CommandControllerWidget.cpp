#include "CommandControllerWidget.h"
#include "ui_CommandControllerWidget.h"
#include <QDebug>

CommandControllerWidget::CommandControllerWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CommandControllerWidget)
{
    ui->setupUi(this);
    Defaulttext = "Нажмите кнопку \"Загрузить\"";
    ui->MessageTextBox->setText(Defaulttext);
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

}
