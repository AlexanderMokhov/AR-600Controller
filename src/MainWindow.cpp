#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //инициализация контроллеров
    ConfigController::Inst()->Init();
    BufferController::Inst()->Init();

    //чтение настроек их XML файла
    bool isOk = ConfigController::Inst()->OpenFile("config.xml");

    if(isOk)
    {
        mUpdateDelay = ConfigController::Inst()->GetReceiveDelay();

        BufferController::Inst()->InitBuffers();
        MoveController::Inst()->Init();
        DeviceLogController::Inst()->Init();

        mCommandControlWidget = new CommandControlWidget();
        ui->CommandControlLayout->addWidget(mCommandControlWidget);
        connect(MoveController::Inst(),SIGNAL(InitEnd()),mCommandControlWidget,SLOT(startCommand()));

        qDebug() << "Настройки успешно прочитаны";
    }
    else
    {
        QMessageBox::warning(this,"Ошибка при чтении файла настроек","Возможно указан не верный путь или файл содержит ошибки");
        qDebug() << "Error loading config file...";
        exit(0);
    }
    //конец чтения настроек

    //настраиваем виджеты
    WidgetsInit();

    mConnectDialog = new ConnectConfigDialog();
    mMotorControlWidget->setModel(mMotorTableWidget->getModel());
    connect(mMotorTableWidget,SIGNAL(RowChanged(int)),mMotorControlWidget,SLOT(RowChanged(int)));
    //конец настройки виджетов

    //настройка кнопок тулбара
    ActionsLoad();

    TBactionPlay->setEnabled(false);
    TBactionStop->setEnabled(false);
    TBactionNext->setEnabled(false);

    ToolBarInit();

    mConnectStatusLabel = new QLabel(this);
    mConnectStatusLabel->setText("Соединение не установлено");
    ui->statusbar->addWidget(mConnectStatusLabel);

    mCommandControllerStatusLabel = new QLabel(this);
    mCommandControllerStatusLabel->setText("Файл команд не загружен");
    ui->statusbar->addWidget(mCommandControllerStatusLabel);

    ConnectionsInit();

    //заполнение таблицы приводов
    mMotorTableWidget->ShowConfigData();
    mSensorTableWidget->ShowConfigData();

    mTimerUpdate = new QTimer();
    mTimerUpdate->setInterval(mUpdateDelay);
    connect(mTimerUpdate,SIGNAL(timeout()),this,SLOT(ProcessTheDatagram()));
    //создание потоков на отправку и прием буфера

    mSender = new Sender;
    mReceiver = new Receiver;

    MoveCorrector::Inst()->Init();
}

MainWindow::~MainWindow()
{
    mReceiver->Disconnect();
    mSender->Disconnect();
    mReceiver->wait();
    mSender->wait();
    delete ui;
}

//Настройка кнопок тулбара
void MainWindow::ActionsLoad()
{
    TBactionOpenCF = new QAction("Открыть файл настроек",0);
    TBactionOpenCF->setToolTip("Открыть файл настроек");
    TBactionOpenCF->setIcon(QIcon(":/MyIcons/Icons/open.ico"));
    connect(TBactionOpenCF,SIGNAL(triggered()),this,SLOT(OpenXML()));

    TBactionSaveCF = new QAction("Сохранить файл настроек",0);
    TBactionSaveCF->setToolTip("Сохранить файл настроек");
    TBactionSaveCF->setIcon(QIcon(":/MyIcons/Icons/save.ico"));
    connect(TBactionSaveCF,SIGNAL(triggered()),this,SLOT(SaveXML()));

    TBactionPlay = new QAction("Начать выполнение",0);
    TBactionPlay->setToolTip("Начать выполнение");
    TBactionPlay->setIcon(QIcon(":/MyIcons/Icons/play.ico"));
    connect(TBactionPlay,SIGNAL(triggered()),mCommandControlWidget,SLOT(on_ButtonPlayPause_clicked()));

    TBactionStop = new QAction("Остановить выполнение",0);
    TBactionStop->setToolTip("Остановить выполнение");
    TBactionStop->setIcon(QIcon(":/MyIcons/Icons/stop.ico"));
    connect(TBactionStop,SIGNAL(triggered()),mCommandControlWidget,SLOT(on_ButtonStop_clicked()));

    TBactionNext = new QAction("Следующая команда",0);
    TBactionNext->setToolTip("Следующая команда");
    TBactionNext->setIcon(QIcon(":/MyIcons/Icons/redo.ico"));
    connect(TBactionNext,SIGNAL(triggered()),mCommandControlWidget,SLOT(on_ButtonNext_clicked()));

    TBactionOpenCommandFile = new QAction("Загрузить файл команд",0);
    TBactionOpenCommandFile->setToolTip("Загрузить файл команд");
    TBactionOpenCommandFile->setIcon(QIcon(":/MyIcons/Icons/folder.ico"));
    connect(TBactionOpenCommandFile,SIGNAL(triggered()),mCommandControlWidget,SLOT(on_ButtonLoadFile_clicked()));

    TBactionOnPower = new QAction("Включить все",0);
    TBactionOnPower->setToolTip("Включить все");
    TBactionOnPower->setIcon(QIcon(":/MyIcons/Icons/on.ico"));
    connect(TBactionOnPower,SIGNAL(triggered()),mPowerControlWidget,SLOT(on_ButtonOnAll_clicked()));

    TBactionOffPower = new QAction("Выключить все",0);
    TBactionOffPower->setToolTip("Выключить все");
    TBactionOffPower->setIcon(QIcon(":/MyIcons/Icons/off.ico"));
    connect(TBactionOffPower,SIGNAL(triggered()),mPowerControlWidget,SLOT(on_ButtonOffAll_clicked()));

    TBactionOpenConnectSettings = new QAction("Настройки соединения",0);
    TBactionOpenConnectSettings->setToolTip("Настройки соединения");
    TBactionOpenConnectSettings->setIcon(QIcon(":/MyIcons/Icons/settings.ico"));
    connect(TBactionOpenConnectSettings,SIGNAL(triggered()),this,SLOT(OpenConnectConfig()));

    TBactionConnect = new QAction("Подключение",0);
    TBactionConnect->setToolTip("Подключение");

    TBactionConnect->setIcon(QIcon(":/MyIcons/Icons/connect.ico"));
    TBactionConnect->setIconVisibleInMenu(true);
    connect(TBactionConnect,SIGNAL(triggered()),this,SLOT(Connect()));

    TBactionDisconnect = new QAction("Отключение",0);
    TBactionDisconnect->setToolTip("Отключение");
    TBactionDisconnect->setIcon(QIcon(":/MyIcons/Icons/disconnect.ico"));
    connect(TBactionDisconnect,SIGNAL(triggered()),this,SLOT(Disconnect()));
}

void MainWindow::WidgetsInit()
{
    mMotorControlWidget = new MotorControlWidget();
    ui->MotorControlLayout->addWidget(mMotorControlWidget);
    mMotorTableWidget = new MotorTableWidget();
    ui->MotorTableLayout->addWidget(mMotorTableWidget);
    mDeviceLogWidget = new DeviceLogWidget();
    ui->DeviceLogWidgetLayout->addWidget(mDeviceLogWidget);
    mPowerControlWidget = new PowerControlWidget();
    ui->PowerControlLayout->addWidget(mPowerControlWidget);
    mSensorTableWidget = new SensorTableWidget();
    ui->SensorTableLayout->addWidget(mSensorTableWidget);
    mCommandFilesWidget = new CommandFilesWidget();
    ui->CommandFilesLayout->addWidget(mCommandFilesWidget);
}

void MainWindow::ConnectionsInit()
{
    //настройка кнопок меню
    connect(ui->actionOpenConfigFile,SIGNAL(triggered()),this,SLOT(OpenXML()));
    connect(ui->actionSaveConfigFile,SIGNAL(triggered()),this,SLOT(SaveXML()));

    connect(ui->actionOpenCorrectionFile,SIGNAL(triggered()),this,SLOT(OpenCorrectionFile()));

    connect(ui->actionConnect,SIGNAL(triggered()),this,SLOT(Connect()));
    connect(ui->actionDisconnect,SIGNAL(triggered()),this,SLOT(Disconnect()));
    connect(ui->actionOn,SIGNAL(triggered()),mPowerControlWidget,SLOT(on_ButtonOnAll_clicked()));
    connect(ui->actionOff,SIGNAL(triggered()),mPowerControlWidget,SLOT(on_ButtonOffAll_clicked()));
    connect(ui->actionOpenConnectConfig,SIGNAL(triggered()),this,SLOT(OpenConnectConfig()));
    //конец настройки кнопок меню

    connect(mCommandControlWidget,SIGNAL(StartWriteLog(int)),mDeviceLogWidget,SLOT(StartWriteLog(int)));
    connect(mCommandControlWidget,SIGNAL(StopWriteLog()),mDeviceLogWidget,SLOT(StopWriteLog()));
    connect(mCommandControlWidget,SIGNAL(FileLoaded(QString,int,int,bool)),this,SLOT(ActivateActions()));

    connect(mCommandControlWidget,SIGNAL(PlayStart()),mMotorTableWidget,SLOT(Disactivate()));
    connect(mCommandControlWidget,SIGNAL(PlayStop()),mMotorTableWidget,SLOT(Activate()));
    connect(MoveController::Inst(),SIGNAL(InitStart()),mMotorTableWidget,SLOT(Disactivate()));
    connect(MoveController::Inst(),SIGNAL(PlayEnd()),mMotorTableWidget,SLOT(Activate()));
    connect(MoveController::Inst(),SIGNAL(InitEnd()),mMotorTableWidget,SLOT(Activate()));
    connect(mCommandControlWidget,SIGNAL(FileLoaded(QString,int,int,bool)),mCommandFilesWidget,SLOT(AddFile(QString,int,int,bool)));

    connect(mCommandFilesWidget,SIGNAL(fileChosen(QString,bool)),mCommandControlWidget,SLOT(openFile(QString,bool)));
}

void MainWindow::ToolBarInit()
{
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
    ui->MainToolBar->addAction(TBactionOpenCommandFile);
    ui->MainToolBar->addSeparator();
    ui->MainToolBar->addAction(TBactionPlay);
    ui->MainToolBar->addAction(TBactionPlay);
    ui->MainToolBar->addAction(TBactionStop);
    ui->MainToolBar->addSeparator();
    ui->MainToolBar->addAction(TBactionNext);
    ui->MainToolBar->addSeparator();
    //конец добавление кнопок на тулбар
}

//вызывается при запуске подключения к роботу
void MainWindow::Connect()
{
    mReceiver->Connect();
    mSender->Connect();
    mTimerUpdate->start();
    mConnectStatusLabel->setText("Соединение установлено");
}

//вызывается при запуске остановки подключения к роботу
void MainWindow::Disconnect()
{
    //выключаем напряжения
    BufferController::Inst()->GetBufferS()->PowerOff61();
    BufferController::Inst()->GetBufferS()->PowerOff62();
    BufferController::Inst()->GetBufferS()->PowerOff81();
    BufferController::Inst()->GetBufferS()->PowerOff82();
    BufferController::Inst()->GetBufferS()->PowerOff48();

    mReceiver->Disconnect();
    mSender->Disconnect();

    mTimerUpdate->stop();
    mConnectStatusLabel->setText("Соединение не установлено");
}

void MainWindow::ActivateActions()
{
    TBactionPlay->setEnabled(true);
    TBactionStop->setEnabled(true);
    TBactionNext->setEnabled(true);
    mCommandControllerStatusLabel->setText("Файл команд загружен");
}

//открытие диалога настроек подключения
void MainWindow::OpenConnectConfig()
{
    mConnectDialog->setModal(true);
    mConnectDialog->Update();
    mConnectDialog->show();
}

//обработка принятого пакета от робота
void MainWindow::ProcessTheDatagram()
{
    mPowerControlWidget->UpdatePowerLabel();
    mMotorControlWidget->UpdateData();
    mMotorTableWidget->UpdatePos();
    mSensorTableWidget->UpdatePos();
}

//сохранение файла настроек
void MainWindow::SaveXML()
{
    QString fileName = QFileDialog::getSaveFileName(0,"Save XML Dialog","","*.XML *.xml");
    if (!fileName.isEmpty())
    {
        ConfigController::Inst()->SaveFile(fileName.toStdString());
        qDebug() << "Файл настроек успешно сохранен в " << fileName << endl;
    }
}

//открытие файла настроек
void MainWindow::OpenXML()
{
    QString fileName = QFileDialog::getOpenFileName(0,"Open XML Dialog","","*.XML *.xml");
    if (!fileName.isEmpty())
    {
        bool isOk = ConfigController::Inst()->OpenFile(fileName.toStdString());

        if(isOk)
        {
            //загоняем в отправляемый массив
            BufferController::Inst()->InitBuffers();
            qDebug() << "Файл настроек успешно загружен из " << fileName << endl;
            qDebug() << "Настройки успешно прочитаны" <<endl;
        }
        else
        {
            qDebug() << "Файл настроек не был загружен из " << fileName << endl;
            qDebug() << "Возможно, имя или формат файла заданы неверно" <<endl;
        }
    }
}

void MainWindow::OpenCorrectionFile()
{
    QString fileName = QFileDialog::getOpenFileName(0,"Open Correction File Dialog","","*.TXT *.txt");
    if (!fileName.isEmpty())
    {
        bool isOk = MoveCorrector::Inst()->OpenFile(fileName.toStdString());

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
