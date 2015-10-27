#include "MoveControlWidget.h"
#include "ui_MoveControlWidget.h"
#include <QDebug>

MoveControlWidget::MoveControlWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MoveControlWidget)
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
    statePlay->addTransition(MoveController::Inst(), SIGNAL(PlayEnd()), stateStop);

    machine->setInitialState(stateNotOpenFile);
    machine->start();

    isFileCommand = false;

    connect(ui->ButtonLoadDRIVEMAT, SIGNAL(toggled(bool)), this, SLOT(on_ButtonLoadDRIVEMAT_clicked()));

}

MoveControlWidget::~MoveControlWidget()
{
    delete ui;
}

void MoveControlWidget::on_ButtonLoadFile_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(0,"Open Commands List Dialog","","*.txt");
    openFile(fileName, true);
}

void MoveControlWidget::on_ButtonLoadDRIVEMAT_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(0,"Open DRIVEMAT File Dialog","","*.TXT *.txt");

    if ( !fileName.isEmpty() )
    {
        bool isOk = MoveCorrector::Inst()->OpenDriveMatFile(fileName.toStdString());

        if(isOk)
        {
            ui->DRIVEMATPathTextBox->setText(fileName);
            ui->MessageTextBox->append( "Прочитан DRIVEMAT.TXT \n");

            ui->MessageTextBox->append( "Прочитано " + QString::number(MoveCorrector::Inst()->mCountRows) +
                                        " строк" + "\n");

            ui->MessageTextBox->append( "Время записи " +
                                        QString::number((double)MoveCorrector::Inst()->mDuration/1e6) +
                                        " секунд" + "\n");

            qDebug() << "Файл DRIVEMAT успешно загружен из " << fileName << endl;
        }
        else
        {
            qDebug() << "Файл DRIVEMAT не был загружен из " << fileName << endl;
            qDebug() << "Возможно, имя или формат файла заданы неверно" << endl;
        }
    }
}

void MoveControlWidget::on_ButtonPlayPause_clicked()
{
    isFileCommand = true;
    MoveController::Inst()->StartGoPos(true);
}

void MoveControlWidget::on_ButtonStop_clicked()
{
    isFileCommand = false;
    MoveController::Inst()->StopPlay();

    if(IsLog)
    {
        emit StopWriteLog();
    }

    emit PlayStop();
}

void MoveControlWidget::on_ButtonNext_clicked()
{
    MoveController::Inst()->NextCommand();
}

void MoveControlWidget::on_checkBoxLog_clicked(bool checked)
{
    IsLog = checked;
}

void MoveControlWidget::on_ButtonGoStartPos_clicked()
{
    isFileCommand = false;
    MoveController::Inst()->StartGoPos(false);
}

void MoveControlWidget::on_ButtonStartFile_clicked()
{
    isFileCommand = false;
    MoveController::Inst()->StartGoPos(true);
}

void MoveControlWidget::startCommand()
{
    if(isFileCommand)
    {
        MoveController::Inst()->StartPlay();
        if(IsLog)
        {
            emit StartWriteLog(MoveController::Inst()->GetDuration()/1e3);

        }
        emit PlayStart();
    }
}

void MoveControlWidget::openFile(QString fileName, bool mode)
{
    if (!fileName.isEmpty())
    {
        ui->FilePathTextBox->setText(fileName);
        bool isOk = MoveController::Inst()->OpenFile(fileName.toStdString());
        if(isOk)
        {
            qDebug() << "Файл списка команд успешно загружен из " << fileName << endl;
            qDebug() << "Команды успешно прочитаны" <<endl;
            int CountRows = MoveController::Inst()->GetCountRows();
            int Duration = MoveController::Inst()->GetDuration();
            //ui->MessageTextBox->clear();
            ui->MessageTextBox->append( "Прочитано " + QString::number(CountRows) + " строк" + "\n");
            ui->MessageTextBox->append( "Время записи " + QString::number((double)Duration/1e6) + " секунд" + "\n");

            emit FileLoaded(fileName,CountRows,Duration, mode);
        }
        else
        {
            qDebug() << "Файл списка команд не был загружен из " << fileName << endl;
            qDebug() << "Возможно имя, или формат файла заданы неверно" <<endl;
        }
    }

    if(!mode)
    {
        isFileCommand = true;
        MoveController::Inst()->StartGoPos(true);
        emit PlayStart();
    }
}
