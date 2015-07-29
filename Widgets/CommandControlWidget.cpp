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
    statePlay->addTransition(MotionController::Inst(), SIGNAL(PlayEnd()), stateStop);

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
    MotionController::Inst()->StartGoPos(true);
}

void CommandControlWidget::on_ButtonStop_clicked()
{
    isFileCommand = false;
    MotionController::Inst()->StopPlay();

    if(IsLog)
    {
        emit StopWriteLog();
    }

    emit PlayStop();
}

void CommandControlWidget::on_ButtonNext_clicked()
{
    MotionController::Inst()->NextCommand();
}

void CommandControlWidget::on_checkBoxLog_clicked(bool checked)
{
    IsLog = checked;
}

void CommandControlWidget::on_ButtonGoStartPos_clicked()
{
    isFileCommand = false;
    MotionController::Inst()->StartGoPos(false);
}

void CommandControlWidget::on_ButtonStartFile_clicked()
{
    isFileCommand = false;
    MotionController::Inst()->StartGoPos(true);
}

void CommandControlWidget::startCommand()
{
    if(isFileCommand)
    {
        MotionController::Inst()->StartPlay();
        if(IsLog)
        {
            emit StartWriteLog(MotionController::Inst()->GetDuration()/1e3);

        }
        emit PlayStart();
    }
}

void CommandControlWidget::openFile(QString fileName, bool mode)
{
    if (!fileName.isEmpty())
    {
        ui->FilePathTextBox->setText(fileName);
        bool isOk = MotionController::Inst()->OpenFile(fileName.toStdString());
        if(isOk)
        {
            qDebug() << "Файл списка команд успешно загружен из " << fileName << endl;
            qDebug() << "Команды успешно прочитаны" <<endl;
            int CountRows = MotionController::Inst()->GetCountRows();
            int Duration = MotionController::Inst()->GetDuration();
            ui->MessageTextBox->clear();
            ui->MessageTextBox->append( "Прочитано " + QString::number(CountRows) + " строк" + "\n");
            ui->MessageTextBox->append( "Время записи " + QString::number((double)Duration/1e6) + " секунд" + "\n");

            emit FileLoaded(fileName,CountRows,Duration, mode);
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
        MotionController::Inst()->StartGoPos(true);
        emit PlayStart();
    }
}
