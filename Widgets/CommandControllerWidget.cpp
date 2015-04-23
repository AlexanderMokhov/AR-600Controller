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

    IsLog=false;

    machine = new QStateMachine(this);
    stateStop = new QState(machine);
    statePlay = new QState(machine);
    statePause = new QState(machine);
    stateNotOpenFile = new QState(machine);

    stateNotOpenFile->assignProperty(ui->ButtonLoadFile,"enabled",true);
    stateNotOpenFile->assignProperty(ui->ButtonPlayPause,"enabled",false);
    stateNotOpenFile->assignProperty(ui->ButtonStop,"enabled",false);
    stateNotOpenFile->assignProperty(ui->ButtonNext,"enabled",false);

    stateNotOpenFile->addTransition(this, SIGNAL(FileLoaded()), stateStop);

    stateStop->assignProperty(ui->ButtonLoadFile,"enabled",true);
    stateStop->assignProperty(ui->ButtonPlayPause,"enabled",true);
    stateStop->assignProperty(ui->ButtonStop,"enabled",false);
    stateStop->assignProperty(ui->ButtonNext,"enabled",true);

    stateStop->addTransition(ui->ButtonPlayPause, SIGNAL(clicked()), statePlay);

    statePause->assignProperty(ui->ButtonLoadFile,"enabled",true);
    statePause->assignProperty(ui->ButtonPlayPause,"enabled",true);
    statePause->assignProperty(ui->ButtonStop,"enabled",true);
    statePause->assignProperty(ui->ButtonNext,"enabled",true);

    statePause->addTransition(ui->ButtonPlayPause, SIGNAL(clicked()), statePlay);
    statePause->addTransition(ui->ButtonStop, SIGNAL(clicked()), stateStop);

    statePlay->assignProperty(ui->ButtonLoadFile,"enabled",false);
    statePlay->assignProperty(ui->ButtonPlayPause,"enabled",true);
    statePlay->assignProperty(ui->ButtonStop,"enabled",true);
    statePlay->assignProperty(ui->ButtonNext,"enabled",true);

    statePlay->addTransition(ui->ButtonPlayPause, SIGNAL(clicked()), statePause);
    statePlay->addTransition(ui->ButtonStop, SIGNAL(clicked()), stateStop);

    machine->setInitialState(stateNotOpenFile);
    machine->start();

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
        //пауза
        CommandController::Instance()->SetPlayForwardState(false);
    }
    else
    {
        CommandController::Instance()->SetPlayForwardState(true);
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
