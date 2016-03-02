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
    mMover = new Mover;

    machine = new QStateMachine(this);

    stateStop = new QState(machine);
    statePlay = new QState(machine);
    stateNotOpenFile = new QState(machine);

    stateNotOpenFile->assignProperty(ui->ButtonLoadFile,"enabled",true);
    stateNotOpenFile->assignProperty(ui->ButtonPlayPause,"enabled",false);
    stateNotOpenFile->assignProperty(ui->ButtonStop,"enabled",false);

    stateNotOpenFile->addTransition(this, SIGNAL(FileLoaded(QString,int,int,bool)), stateStop);

    stateStop->assignProperty(ui->ButtonLoadFile,"enabled",true);
    stateStop->assignProperty(ui->ButtonPlayPause,"enabled",true);
    stateStop->assignProperty(ui->ButtonStop,"enabled",false);

    stateStop->addTransition(ui->ButtonPlayPause, SIGNAL(clicked()), statePlay);
    stateStop->addTransition(this, SIGNAL(PlayStart()), statePlay);

    statePlay->assignProperty(ui->ButtonLoadFile,"enabled",false);
    statePlay->assignProperty(ui->ButtonPlayPause,"enabled",true);
    statePlay->assignProperty(ui->ButtonStop,"enabled",true);

    statePlay->addTransition(ui->ButtonStop, SIGNAL(clicked()), stateStop);
    statePlay->addTransition(mMover, SIGNAL(MoveEnd()), stateStop);

    machine->setInitialState(stateNotOpenFile);
    machine->start();

    isMoveFile = false;



    connect(ui->ButtonLoadDRIVEMAT, SIGNAL(toggled(bool)), this, SLOT(on_ButtonLoadDRIVEMAT_clicked()));

    connect(mMover, SIGNAL(PrepEnd()), this, SLOT(startMove()));

    connect(mMover, SIGNAL(MoveEnd()),this, SLOT(on_ButtonStop_clicked()));

}

MoveControlWidget::~MoveControlWidget()
{
    delete ui;
}

void MoveControlWidget::on_ButtonLoadFile_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(0,"Загрузка файла движений","","*.txt");
    openFile(fileName, true);
}

void MoveControlWidget::on_ButtonLoadDRIVEMAT_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(0,"Загрузка DRIVEMAT файла","","*.TXT *.txt");

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
    isMoveFile = true;
    MoveController::Inst()->useUserStiff = ui->cBoxUseUserStiff->isChecked();
    MoveController::Inst()->UserStiff = ui->sBoxUserStiffValue->value();
    MoveController::Inst()->useUserDump = ui->cBoxUseUserDump->isChecked();
    MoveController::Inst()->UserDump = ui->sBoxUserDumpValue->value();
    mMover->StartGoToPos(false);
}

void MoveControlWidget::on_ButtonStop_clicked()
{
    isMoveFile = false;
    mMover->StopMove();

    if(IsLog)
    {
        emit StopWriteRecord();
    }

    emit PlayStop();
}

void MoveControlWidget::on_checkBoxLog_clicked(bool checked)
{
    IsLog = checked;
}

void MoveControlWidget::on_ButtonGoStartPos_clicked()
{
    isMoveFile = false;
    mMover->StartGoToPos(true);
}

void MoveControlWidget::on_ButtonStartFile_clicked()
{
    isMoveFile = false;
    mMover->StartGoToPos(false);
}

void MoveControlWidget::startMove()
{
    if(isMoveFile)
    {
        mMover->StartMove();

        if(IsLog)
        {
            emit StartWriteRecord(MovesStorage::Inst()->GetDuration()/1e3);
        }
        emit PlayStart();
    }
}

void MoveControlWidget::StartPlayFile(bool mode)
{
    if(!mode)
    {
        isMoveFile = true;
        mMover->StartGoToPos(false);
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
            int CountRows = MovesStorage::Inst()->GetCountRows();
            int Duration = MovesStorage::Inst()->GetDuration();

            ui->MessageTextBox->append( "Прочитано " + QString::number(CountRows) + " строк" + "\n");
            ui->MessageTextBox->append( "Время записи " + QString::number((double)Duration/1e6) + " секунд" + "\n");

            emit FileLoaded(fileName, CountRows, Duration, mode);
        }
        else
        {
            qDebug() << "Файл списка команд не был загружен из " << fileName << endl;
            qDebug() << "Возможно имя, или формат файла заданы неверно" <<endl;
        }
    }

    StartPlayFile(mode);
}

void MoveControlWidget::on_cBoxUseUserStiff_clicked(bool checked)
{
    MoveController::Inst()->useUserStiff = checked;
    MoveController::Inst()->UserStiff = ui->sBoxUserStiffValue->value();
}

void MoveControlWidget::on_cBoxUseUserDump_clicked(bool checked)
{
    MoveController::Inst()->useUserDump = checked;
    MoveController::Inst()->UserDump = ui->sBoxUserDumpValue->value();
}

void MoveControlWidget::startStdMove()
{
    StartPlayFile(false);
}
