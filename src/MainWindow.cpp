#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //инициализация контроллеров
    LogMaster::Inst()->Init();

    SettingsStorage::Inst()->Init();
    BufferController::Inst()->Init();

    //чтение настроек их XML файла
    bool isOk = SettingsStorage::Inst()->OpenFile("config.xml");

    if(isOk)
    {
        mUpdateDelay = SettingsStorage::Inst()->GetReceiveDelay();

        BufferController::Inst()->Initialize();
        MoveController::Inst()->Init();
        RecordController::Inst()->Init();

        mMoveControlWidget = new MoveControlWidget();
        ui->MoveControlLayout->addWidget(mMoveControlWidget);
        LogMaster::Inst()->addLine("Конфигурация успешно прочитана");
    }
    else
    {
        QMessageBox::warning(this,"Ошибка при чтении файла настроек","Возможно указан не верный путь или файл содержит ошибки");
        LogMaster::Inst()->addLine("Ошибка при чтении конфигурации");
        exit(0);
    }
    //конец чтения настроек

    //настраиваем виджеты
    WidgetsInit();
    //конец настройки виджетов
    mLogWidget->startWrite();
    //mLogWidget->addMessage(" Настройки успешно прочитаны");//!!!!

    //настройка кнопок тулбара
    ActionsLoad();

    TBactionPlay->setEnabled(false);
    TBactionStop->setEnabled(false);

    ToolBarInit();

    mConnectStatusLabel = new QLabel(this);
    mConnectStatusLabel->setText("Соединение не установлено");
    ui->statusbar->addWidget(mConnectStatusLabel);

    mCommandControllerStatusLabel = new QLabel(this);
    mCommandControllerStatusLabel->setText("Файл команд не загружен");
    ui->statusbar->addWidget(mCommandControllerStatusLabel);

    //создание потоков на отправку и прием буфера
    mSender = new Sender;
    mReceiver = new Receiver;
    mConsoleReceiver = new ConsoleReceiver;

    FrundTransiver::Inst()->Inst();

    ConnectionsInit();

    //заполнение таблицы приводов
    mMotorTableWidget->ShowConfigData();
    mSensorTableWidget->ShowConfigData();

    mTimerUpdate = new QTimer();
    mTimerUpdate->setInterval(mUpdateDelay);
    connect(mTimerUpdate,SIGNAL(timeout()),this,SLOT(ProcessTheDatagram()));

    MoveCorrector::Inst()->initialize();
}

MainWindow::~MainWindow()
{
    mReceiver->Disconnect();
    mSender->Disconnect();
    mReceiver->wait();
    mSender->wait();
    delete ui;
    mStdMovesWidget->close();
    delete mStdMovesWidget;

    LogMaster::Inst()->addLine("Работа программы успешно завершена");
}

//Настройка кнопок тулбара
void MainWindow::ActionsLoad()
{
    LogMaster::Inst()->addLine("Настройка Actions начата");

    TBactionOpenCF = new QAction("Открыть файл настроек",0);
    TBactionOpenCF->setToolTip("Открыть файл настроек");
    TBactionOpenCF->setIcon(QIcon(":/MyIcons/Icons/open.ico"));
    connect(TBactionOpenCF, SIGNAL(triggered()),this,SLOT(OpenXML()));

    TBactionSaveCF = new QAction("Сохранить файл настроек",0);
    TBactionSaveCF->setToolTip("Сохранить файл настроек");
    TBactionSaveCF->setIcon(QIcon(":/MyIcons/Icons/save.ico"));
    connect(TBactionSaveCF, SIGNAL(triggered()),this,SLOT(SaveXML()));

    TBactionPlay = new QAction("Начать выполнение",0);
    TBactionPlay->setToolTip("Начать выполнение");
    TBactionPlay->setIcon(QIcon(":/MyIcons/Icons/play.ico"));
    connect(TBactionPlay, SIGNAL(triggered()),mMoveControlWidget,SLOT(on_ButtonPlayPause_clicked()));

    TBactionStop = new QAction("Остановить выполнение",0);
    TBactionStop->setToolTip("Остановить выполнение");
    TBactionStop->setIcon(QIcon(":/MyIcons/Icons/stop.ico"));
    connect(TBactionStop, SIGNAL(triggered()),mMoveControlWidget,SLOT(on_ButtonStop_clicked()));

    TBactionOpenMoveFile = new QAction("Загрузить файл команд",0);
    TBactionOpenMoveFile->setToolTip("Загрузить файл команд");
    TBactionOpenMoveFile->setIcon(QIcon(":/MyIcons/Icons/folder.ico"));
    connect(TBactionOpenMoveFile, SIGNAL(triggered()),mMoveControlWidget,SLOT(on_ButtonLoadFile_clicked()));

    TBactionOnPower = new QAction("Включить все",0);
    TBactionOnPower->setToolTip("Включить все");
    TBactionOnPower->setIcon(QIcon(":/MyIcons/Icons/on.ico"));
    connect(TBactionOnPower, SIGNAL(triggered()),mPowerWidget,SLOT(on_ButtonOnAll_clicked()));

    TBactionOffPower = new QAction("Выключить все",0);
    TBactionOffPower->setToolTip("Выключить все");
    TBactionOffPower->setIcon(QIcon(":/MyIcons/Icons/off.ico"));
    connect(TBactionOffPower, SIGNAL(triggered()),mPowerWidget,SLOT(on_ButtonOffAll_clicked()));

    TBactionOpenConnectSettings = new QAction("Настройки соединения",0);
    TBactionOpenConnectSettings->setToolTip("Настройки соединения");
    TBactionOpenConnectSettings->setIcon(QIcon(":/MyIcons/Icons/settings.ico"));
    connect(TBactionOpenConnectSettings, SIGNAL(triggered()),this,SLOT(OpenConnectConfig()));

    TBactionConnect = new QAction("Подключение",0);
    TBactionConnect->setToolTip("Подключение");

    TBactionConnect->setIcon(QIcon(":/MyIcons/Icons/connect.ico"));
    TBactionConnect->setIconVisibleInMenu(true);
    connect(TBactionConnect, SIGNAL(triggered()),this,SLOT(Connect()));

    TBactionDisconnect = new QAction("Отключение",0);
    TBactionDisconnect->setToolTip("Отключение");
    TBactionDisconnect->setIcon(QIcon(":/MyIcons/Icons/disconnect.ico"));
	
    connect(TBactionDisconnect,SIGNAL(triggered()),this,SLOT(Disconnect()));

    TBactionStartPlayOnline = new QAction("Движения онлайн",0);
    TBactionStartPlayOnline->setToolTip("Движения онлайн");
    TBactionStartPlayOnline->setIcon(QIcon(":/MyIcons/Icons/play.ico"));
    connect(TBactionStartPlayOnline, SIGNAL(triggered()),this, SLOT(StartPlayOnline()));

    TBactionStopPlayOnline = new QAction("Остановка движения онлайн",0);
    TBactionStopPlayOnline->setToolTip("Остановка движения онлайн");
    TBactionStopPlayOnline->setIcon(QIcon(":/MyIcons/Icons/stop.ico"));
    connect(TBactionStopPlayOnline, SIGNAL(triggered()),this, SLOT(StopPlayOnline()));

    TBactionStartFrund = new QAction("Запустить RASHET32.EXE",0);
    TBactionStartFrund->setToolTip("Запустить RASHET32.EXE");
    TBactionStartFrund->setIcon(QIcon(":/MyIcons/Icons/forward.ico"));
    connect(TBactionStartFrund, SIGNAL(triggered()),this,SLOT(StartFrund()));

    LogMaster::Inst()->addLine("Настройка Actions завершена");
}

void MainWindow::WidgetsInit()
{
    LogMaster::Inst()->addLine("Настройка Widgets начата");

    mMotorControlWidget = new MotorControlWidget();
    ui->MotorControlLayout->addWidget(mMotorControlWidget);
    mMotorTableWidget = new MotorTableWidget();
    ui->MotorTableLayout->addWidget(mMotorTableWidget);
    mRecordWidget = new RecordWidget();
    ui->RecordWidgetLayout->addWidget(mRecordWidget);
    mPowerWidget = new PowerWidget();
    ui->PowerWidgetLayout->addWidget(mPowerWidget);
    mSensorTableWidget = new SensorTableWidget();
    ui->SensorTableLayout->addWidget(mSensorTableWidget);
    mMoveFilesWidget = new MoveFilesWidget();
    ui->MoveFilesWidgetLayout->addWidget(mMoveFilesWidget);
    mStdMovesWidget = new StdMovesWidget();
    //mStdMovesWidget->show();
    mLogWidget = new LogWidget();
    ui->LayoutLog->addWidget(mLogWidget);


    mConnectDialog = new ConnectConfigDialog();
    mMotorControlWidget->setModel(mMotorTableWidget->getModel());
    connect(mMotorTableWidget, SIGNAL(RowChanged(int)), mMotorControlWidget, SLOT(RowChanged(int)));

    LogMaster::Inst()->addLine("Настройка Widgets завершена");
}

void MainWindow::ConnectionsInit()
{
    LogMaster::Inst()->addLine("Настройка connect(...) начата");

    //настройка кнопок меню
    connect(ui->actionOpenConfigFile,SIGNAL(triggered()),this,SLOT(OpenXML()));
    connect(ui->actionSaveConfigFile,SIGNAL(triggered()),this,SLOT(SaveXML()));

    connect(ui->actionOpenCorrectionFile,SIGNAL(triggered()),this,SLOT(OpenCorrectionFile()));
    connect(ui->action_Open_DRIVEMAT,SIGNAL(triggered()),this,SLOT(OpenDRIVEMATFile()));

    connect(ui->actionConnect,SIGNAL(triggered()),this,SLOT(Connect()));
    connect(ui->actionDisconnect,SIGNAL(triggered()),this,SLOT(Disconnect()));
    connect(ui->actionOn,SIGNAL(triggered()),mPowerWidget,SLOT(on_ButtonOnAll_clicked()));
    connect(ui->actionOff,SIGNAL(triggered()),mPowerWidget,SLOT(on_ButtonOffAll_clicked()));
    connect(ui->actionReboot,SIGNAL(triggered()),mPowerWidget,SLOT(onReboot()));
    connect(ui->actionOpenConnectConfig,SIGNAL(triggered()),this,SLOT(OpenConnectConfig()));
    //конец настройки кнопок меню

    connect(mMoveControlWidget,SIGNAL(StartWriteRecord(int)),mRecordWidget,SLOT(StartWriteRecord(int)));
    connect(mMoveControlWidget,SIGNAL(StopWriteRecord()),mRecordWidget,SLOT(StopWriteRecord()));
    connect(mMoveControlWidget,SIGNAL(FileLoaded(QString,int,int,bool)),this,SLOT(ActivateActions()));

    connect(mMoveControlWidget,SIGNAL(PlayStart()),mMotorTableWidget,SLOT(Disactivate()));
    connect(mMoveControlWidget,SIGNAL(PlayStop()),mMotorTableWidget,SLOT(Activate()));
    connect(mMoveControlWidget,SIGNAL(FileLoaded(QString,int,int,bool)),mMoveFilesWidget,SLOT(AddFile(QString,int,int,bool)));

    connect(mMoveFilesWidget,SIGNAL(fileChosen(QString,bool)),mMoveControlWidget,SLOT(openFile(QString,bool)));

    connect(mStdMovesWidget,SIGNAL(startStdMove()),mMoveControlWidget,SLOT(startStdMove()));
    connect(mStdMovesWidget,SIGNAL(stopStdMove()),mMoveControlWidget,SLOT(on_ButtonStop_clicked()));

    connect(mConsoleReceiver, SIGNAL(startPlayOnline()), this, SLOT(StartPlayOnline()));
    connect(mConsoleReceiver, SIGNAL(stopPlayOnline()), this, SLOT(StopPlayOnline()));

    LogMaster::Inst()->addLine("Настройка connect(...) завершена");
}

void MainWindow::ToolBarInit()
{
    LogMaster::Inst()->addLine("Настройка ToolBar начата");

    //добавление кнопок на тулбар
    ui->MainToolBar->addAction(TBactionOpenCF);
    ui->MainToolBar->addAction(TBactionSaveCF);
    ui->MainToolBar->addSeparator();
    ui->MainToolBar->addAction(TBactionConnect);
    ui->MainToolBar->addAction(TBactionDisconnect);
    ui->MainToolBar->addAction(TBactionOpenConnectSettings);
    ui->MainToolBar->addSeparator();
    ui->MainToolBar->addAction(TBactionOnPower);
    ui->MainToolBar->addAction(TBactionOffPower);
    ui->MainToolBar->addSeparator();
    ui->MainToolBar->addAction(TBactionOpenMoveFile);
    ui->MainToolBar->addSeparator();
    ui->MainToolBar->addAction(TBactionPlay);
    ui->MainToolBar->addAction(TBactionStop);
    ui->MainToolBar->addSeparator();
    ui->MainToolBar->addAction(TBactionStartPlayOnline);
    ui->MainToolBar->addAction(TBactionStopPlayOnline);
    ui->MainToolBar->addAction(TBactionStartFrund);
    //конец добавление кнопок на тулбар

    LogMaster::Inst()->addLine("Настройка ToolBar завершена");
}

//вызывается при запуске подключения к роботу
void MainWindow::Connect()
{
    mReceiver->Connect();
    mSender->Connect();
    mConsoleReceiver->Connect();
    mTimerUpdate->start();
    mConnectStatusLabel->setText("Соединение установлено");

    LogMaster::Inst()->addLine("Соединение с роботом установлено");
}

//вызывается при запуске остановки подключения к роботу
void MainWindow::Disconnect()
{
    //выключаем напряжения
    BufferController::Inst()->getBufferSend()->offPower6_1();
    BufferController::Inst()->getBufferSend()->offPower6_2();
    BufferController::Inst()->getBufferSend()->offPower8_1();
    BufferController::Inst()->getBufferSend()->offPower8_2();
    BufferController::Inst()->getBufferSend()->offPower48();

    mReceiver->Disconnect();
    mSender->Disconnect();
    mConsoleReceiver->Disconnect();

    mTimerUpdate->stop();
    mConnectStatusLabel->setText("Соединение не установлено");
    mLogWidget->addMessage("Соединение было прервано");

    LogMaster::Inst()->addLine("Соединение с роботом прервано");
}

void MainWindow::ActivateActions()
{
    TBactionPlay->setEnabled(true);
    TBactionStop->setEnabled(true);
    mCommandControllerStatusLabel->setText("Файл команд загружен");
    mLogWidget->addMessage("Файл команд был загружен");
}

//открытие диалога настроек подключения
void MainWindow::OpenConnectConfig()
{
    mConnectDialog->setModal(true);
    mConnectDialog->Update();
    mConnectDialog->show();
}

void MainWindow::StartPlayOnline()
{
    mMoveControlWidget->startMoveOnline();

    LogMaster::Inst()->addLine("Запущено решение онлайн");
}

void MainWindow::StopPlayOnline()
{
    mMoveControlWidget->stopMoveAction();
    LogMaster::Inst()->addLine("Запрос остановки решения онлайн");
}

void MainWindow::StartFrund()
{
//    QProcess* m_process;
//    m_process = new QProcess(this);
//    QString strCommand = "forw125/rashet32.exe";
//    m_process->start(strCommand);
//    if(m_process->isOpen())
//        qDebug() << "RASHET32.exe успешно запущен" << endl;
//    m_process->waitForFinished();
    STARTUPINFO startin;
    startin.cb=sizeof(STARTUPINFO);
    startin.lpReserved=NULL;
    startin.lpDesktop=NULL;
    startin.lpTitle=NULL;//strdup("window1");
    startin.dwX=30;
    startin.dwY=3;
    startin.dwXSize=220;
    startin.dwYSize=220;
    startin.dwXCountChars=30;
    startin.dwYCountChars=10;
    startin.dwFillAttribute=0;
    startin.dwFlags=STARTF_USESHOWWINDOW;
    startin.cbReserved2=NULL;
    startin.lpReserved2=NULL;
    startin.wShowWindow=SW_HIDE;
    startin.hStdInput=NULL;
    startin.hStdOutput=NULL;
    startin.hStdError=NULL;

    SECURITY_ATTRIBUTES sa;
    sa.nLength = sizeof(SECURITY_ATTRIBUTES);
    sa.lpSecurityDescriptor=NULL;
    sa.bInheritHandle=TRUE;

   PROCESS_INFORMATION pinfo;

    CreateProcess(NULL,LPWSTR("H:\\Mokhov\\Dev\\AR-600Controller\\bin\\sinhron\\fmodelxp.bat"),&sa,NULL,TRUE,CREATE_NO_WINDOW+CREATE_SUSPENDED+CREATE_NEW_PROCESS_GROUP,
        NULL,NULL,&startin,&pinfo);

    //WinExec("H:\\Mokhov\\Dev\\AR-600Controller\\bin\\sinhron\\rashet32.exe", 1);
}

//обработка принятого пакета от робота
void MainWindow::ProcessTheDatagram()
{
    mPowerWidget->UpdatePowerLabel();
    mMotorControlWidget->UpdateData();
    mMotorTableWidget->UpdateAngle();
    mSensorTableWidget->UpdatePos();
}

//сохранение файла настроек
void MainWindow::SaveXML()
{
    QString fileName = QFileDialog::getSaveFileName(0,"Save XML Dialog","","*.XML *.xml");
    if (!fileName.isEmpty())
    {
        SettingsStorage::Inst()->SaveFile(fileName.toStdString());
        qDebug() << "Файл настроек успешно сохранен в " << fileName << endl;

        LogMaster::Inst()->addLine("Файл настроек успешно сохранен в " + fileName.toStdString());
    }
}

//открытие файла настроек
void MainWindow::OpenXML()
{
    QString fileName = QFileDialog::getOpenFileName(0,"Open XML Dialog","","*.XML *.xml");
    if (!fileName.isEmpty())
    {
        bool isOk = SettingsStorage::Inst()->OpenFile(fileName.toStdString());

        if(isOk)
        {
            //загоняем в отправляемый массив
            BufferController::Inst()->Initialize();
            qDebug() << "Файл настроек успешно загружен из " << fileName << endl;
            qDebug() << "Настройки успешно прочитаны" <<endl;

            mLogWidget->addMessage("Файл настроек успешно загружен из " +
            fileName + "\nНастройки успешно прочитаны");
        }
        else
        {
            qDebug() << "Файл настроек не был загружен из " << fileName << endl;
            qDebug() << "Возможно, имя или формат файла заданы неверно" <<endl;

            mLogWidget->addMessage("Файл настроек не был загружен из " +
            fileName + "\nВозможно, имя или формат файла заданы неверно");
        }
    }
}

void MainWindow::OpenCorrectionFile()
{
    QString fileName = QFileDialog::getOpenFileName(0,"Open Correction File Dialog","","*.TXT *.txt");
    if (!fileName.isEmpty())
    {
        bool isOk = MoveCorrector::Inst()->openFile(fileName.toStdString());

        if(isOk)
        {
            qDebug() << "Файл коррекции успешно загружен из " << fileName << endl;
            qDebug() << "Настройки успешно прочитаны" <<endl;
        }
        else
        {
            qDebug() << "Файл коррекции не был загружен из " << fileName << endl;
            qDebug() << "Возможно, имя или формат файла заданы неверно" <<endl;
        }
    }

}

void MainWindow::OpenDRIVEMATFile()
{
    QString fileName = QFileDialog::getOpenFileName(0,"Open DRIVEMAT File Dialog","","*.TXT *.txt");

    if ( !fileName.isEmpty() )
    {
        bool isOk = MoveCorrector::Inst()->openDriveMatFile(fileName.toStdString());

        if(isOk)
        {
            qDebug() << "Файл DRIVEMAT успешно загружен из " << fileName << endl;
        }
        else
        {
            qDebug() << "Файл DRIVEMAT не был загружен из " << fileName << endl;
            qDebug() << "Возможно, имя или формат файла заданы неверно" << endl;
        }
    }
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    mStdMovesWidget->close();
}
