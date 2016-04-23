#include "MotionControlW.h"
#include "ui_MotionControlW.h"
#include <QDebug>

MotionControlW::MotionControlW(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MotionControlW)
{
    ui->setupUi(this);
    DefaultText = "Нажмите кнопку \"Загрузить Файл\"";
    ui->MessageTextBox->setText(DefaultText);

    IsLog = false;
}

MotionControlW::~MotionControlW()
{
    delete ui;
}

void MotionControlW::Initialize()
{
    machine = new QStateMachine(this);

    stateStop = new QState(machine);
    statePlay = new QState(machine);
    stateNotOpenFile = new QState(machine);

    stateNotOpenFile->assignProperty(ui->LoadFileB,"enabled",true);
    stateNotOpenFile->assignProperty(ui->StartB,"enabled",false);
    stateNotOpenFile->assignProperty(ui->StopB,"enabled",false);

    stateNotOpenFile->addTransition(this, SIGNAL(FileLoaded(QString,int,int,bool)), stateStop);

    stateStop->assignProperty(ui->LoadFileB,"enabled",true);
    stateStop->assignProperty(ui->StartB,"enabled",true);
    stateStop->assignProperty(ui->StopB,"enabled",false);

    stateStop->addTransition(ui->StartB, SIGNAL(clicked()), statePlay);
    stateStop->addTransition(this, SIGNAL(PlayStart()), statePlay);

    statePlay->assignProperty(ui->LoadFileB,"enabled",false);
    statePlay->assignProperty(ui->StartB,"enabled",true);
    statePlay->assignProperty(ui->StopB,"enabled",true);

    statePlay->addTransition(ui->StopB, SIGNAL(clicked()), stateStop);
    statePlay->addTransition(m_mover, SIGNAL(MoveEnd()), stateStop);

    machine->setInitialState(stateNotOpenFile);
    machine->start();

    isMoveFile = false;

    connect(m_mover, SIGNAL(PrepEnd()), this, SLOT(startMove()));
    connect(m_mover, SIGNAL(MoveEnd()),this, SLOT(on_StopB_clicked()));

    ui->StartFileB->setEnabled(false);
}

void MotionControlW::on_LoadFileB_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(0,"Загрузка файла движений","","*.txt");

    QProgressDialog progress("Выполняется загрузка файла движений...", "Прервать", 0, 100, this);
    progress.setWindowTitle("Загрузка файла движений");
    progress.setFixedWidth(300);
    progress.setWindowModality(Qt::WindowModal);
    progress.show();
    progress.setValue(50);
    QCoreApplication::processEvents();
    openFile(fileName, true);
    progress.setValue(100);
    QCoreApplication::processEvents();
}

void MotionControlW::on_StartB_clicked()
{
    isMoveFile = true;
    MoveController::Inst()->useUserStiff = ui->UseUserPGateB->isChecked();
    MoveController::Inst()->userStiff = ui->UserPGateValueT->value();
    MoveController::Inst()->useUserDump = ui->UseUserIGateB->isChecked();
    MoveController::Inst()->userDump = ui->UserIGateValueT->value();
    m_mover->startGoToPos(false);
}

void MotionControlW::on_StopB_clicked()
{
    stopMoveAction();
    qDebug() << "Движение остановлено" << endl;
}

void MotionControlW::stopMoveAction()
{
    isMoveFile = false;
    m_mover->stopMove();

    emit StopWriteRecord();
    emit PlayStop();
}

void MotionControlW::on_GoStartPosB_clicked()
{
    isMoveFile = false;
    m_mover->startGoToPos(true);
}

void MotionControlW::on_StartFileB_clicked()
{
    isMoveFile = false;
    m_mover->startGoToPos(false);
}

void MotionControlW::startMove()
{
    if(isMoveFile)
    {
        m_mover->startMove();

        emit StartWriteRecord(MovesStorage::Inst()->getDuration()/1e3);
        emit PlayStart();
    }
}

void MotionControlW::startMoveOnline()
{
    // openFile("sinhron/DRIVEMAR.TXT", true);

    m_mover->startMoveOnline();
    if(IsLog)
    {
        emit StartWriteRecord(2e5);
    }
}

void MotionControlW::StartPlayFile(bool mode)
{
    if(!mode)
    {
        isMoveFile = true;
        m_mover->startGoToPos(false);
        emit PlayStart();
    }
}

void MotionControlW::openFile(QString fileName, bool mode)
{
    if (!fileName.isEmpty())
    {
        ui->FilePathT->setText(fileName);
        bool isOk = MoveController::Inst()->openFile(fileName.toStdString());
        if(isOk)
        {
            qDebug() << "Файл движений успешно загружен из " << fileName << endl;
            qDebug() << "Движения успешно прочитаны" <<endl;
            int CountRows = MovesStorage::Inst()->getRowsNumber();
            int Duration = MovesStorage::Inst()->getDuration();

            ui->MessageTextBox->append( "Прочитано " + QString::number(CountRows) + " строк" + "\n");
            ui->MessageTextBox->append( "Время записи " + QString::number((double)Duration/1e6) + " секунд" + "\n");

            ui->StartB->setEnabled(true);
            ui->StartFileB->setEnabled(true);

            emit FileLoaded(fileName, CountRows, Duration, mode);
        }
        else
        {
            qDebug() << "Файл движения не был загружен из " << fileName << endl;
            qDebug() << "Возможно имя, или формат файла заданы неверно" <<endl;
        }
    }

    StartPlayFile(mode);
}

void MotionControlW::on_UseUserPGateB_clicked(bool checked)
{
    MoveController::Inst()->useUserStiff = checked;
    MoveController::Inst()->userStiff = ui->UserPGateValueT->value();
}

void MotionControlW::on_UseUserIGateB_clicked(bool checked)
{
    MoveController::Inst()->useUserDump = checked;
    MoveController::Inst()->userDump = ui->UserIGateValueT->value();
}

void MotionControlW::startStdMove()
{
    StartPlayFile(false);
}
