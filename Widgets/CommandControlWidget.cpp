#include "CommandControlWidget.h"
#include "ui_CommandControlWidget.h"
#include <QDebug>

CommandControlWidget::CommandControlWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CommandControlWidget)
{
    ui->setupUi(this);
    DefaultText = "Нажмите кнопку \"Загрузить Файл\"";
    ui->MessageTextBox->setText(DefaultText);

    IsLog = false;

    machine = new QStateMachine(this);

    stateStop = new QState(machine);
    statePlay = new QState(machine);
    stateNotOpenFile = new QState(machine);

    stateNotOpenFile->assignProperty(ui->ButtonLoadFile,"enabled",true);
    stateNotOpenFile->assignProperty(ui->ButtonPlayPause,"enabled",false);
    stateNotOpenFile->assignProperty(ui->ButtonStop,"enabled",false);
    stateNotOpenFile->assignProperty(ui->ButtonNext,"enabled",false);

    stateNotOpenFile->addTransition(this, SIGNAL(FileLoaded(QString,int,int,bool)), stateStop);

    stateStop->assignProperty(ui->ButtonLoadFile,"enabled",true);
    stateStop->assignProperty(ui->ButtonPlayPause,"enabled",true);
    stateStop->assignProperty(ui->ButtonStop,"enabled",false);
    stateStop->assignProperty(ui->ButtonNext,"enabled",true);

    stateStop->addTransition(ui->ButtonPlayPause, SIGNAL(clicked()), statePlay);
    stateStop->addTransition(this, SIGNAL(PlayStart()), statePlay);

    statePlay->assignProperty(ui->ButtonLoadFile,"enabled",false);
    statePlay->assignProperty(ui->ButtonPlayPause,"enabled",true);
    statePlay->assignProperty(ui->ButtonStop,"enabled",true);
    statePlay->assignProperty(ui->ButtonNext,"enabled",true);

    statePlay->addTransition(ui->ButtonStop, SIGNAL(clicked()), stateStop);
    statePlay->addTransition(CommandController::Inst(), SIGNAL(PlayEnd()), stateStop);

    machine->setInitialState(stateNotOpenFile);
    machine->start();

    isFileCommand = false;

}

CommandControlWidget::~CommandControlWidget()
{
    delete ui;
}

void CommandControlWidget::on_ButtonLoadFile_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(0,"Open Commands List Dialog","","*.txt");
    openFile(fileName, true);
}

void CommandControlWidget::on_ButtonPlayPause_clicked()
{
    isFileCommand = true;
    CommandController::Inst()->initPos(true);
}

void CommandControlWidget::on_ButtonStop_clicked()
{
    isFileCommand = false;
    CommandController::Inst()->SetPlaySequenceState(false);
    CommandController::Inst()->SetCurrentTimeForCommands(0);
    CommandController::Inst()->SetCommandId(0);
    if(IsLog)
    {
        emit StopWriteLog();
    }
    emit PlayStop();
}

void CommandControlWidget::on_ButtonNext_clicked()
{
    CommandController::Inst()->NextCommand();
}

void CommandControlWidget::on_checkBoxLog_clicked(bool checked)
{
    IsLog = checked;
}

void CommandControlWidget::on_ButtonGoStartPos_clicked()
{
    isFileCommand = false;
    CommandController::Inst()->initPos(false);
}

void CommandControlWidget::on_ButtonStartFile_clicked()
{
    isFileCommand = false;
    CommandController::Inst()->initPos(true);
}

void CommandControlWidget::startCommand()
{
    if(isFileCommand)
    {
        CommandController::Inst()->SetPlaySequenceState(true);
        if(IsLog)
        {
            emit StartWriteLog(CommandController::Inst()->GetTimeRecord()/1e3);

        }
        emit PlayStart();
    }
}

void CommandControlWidget::openFile(QString fileName, bool mode)
{
    if (!fileName.isEmpty())
    {
        ui->FilePathTextBox->setText(fileName);
        bool isOk = CommandController::Inst()->LoadFromFile(fileName.toStdString());
        if(isOk)
        {
            qDebug() << "Файл списка команд успешно загружен из " << fileName << endl;
            qDebug() << "Команды успешно прочитаны" <<endl;
            int mCountRows = CommandController::Inst()->GetCountRows();
            int mTimeRecord = CommandController::Inst()->GetTimeRecord();
            ui->MessageTextBox->clear();
            ui->MessageTextBox->append( "Прочитано " + QString::number(mCountRows) + " строк" + "\n");
            ui->MessageTextBox->append( "Время записи " + QString::number((double)mTimeRecord/1e6) + " секунд" + "\n");

            emit FileLoaded(fileName,mCountRows,mTimeRecord, mode);
        }
        else
        {
            qDebug() << "Файл списка команд не был загружен из " << fileName << endl;
            qDebug() << "Возможно имя, или формат файл()а заданы неверно" <<endl;
        }
    }

    if(!mode)
    {
        isFileCommand = true;
        CommandController::Inst()->initPos(true);
        emit PlayStart();
    }
}
