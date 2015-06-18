#include "AR600MainWindow.h"
#include "ui_AR600MainWindow.h"

AR600MainWindow::AR600MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AR600MainWindow)
{
    ui->setupUi(this);

    //инициализация контроллеров
    ConfigController::Instance()->Initialize();
    BufferController::Instance()->Initialize();
    CommandController::Instance()->Initialize();
    //конец инициализации контроллеров

    mSendBuffer = BufferController::Instance()->GetWriteBuffer();
    mReceiveBuffer = BufferController::Instance()->GetReadBuffer();

    //настраиваем виджеты
    mDriverControllerWidget = new DriverControllerWidget();
    ui->DriverControlLayout->addWidget(mDriverControllerWidget);
    mCommandControllerWidget = new CommandControllerWidget();
    ui->CommandControlLayout->addWidget(mCommandControllerWidget);
    mChannelTableWidget = new ChannelTableWidget();
    ui->ChannelTableLayout->addWidget(mChannelTableWidget);
    mDriverLogWidget = new DriverLogWidget();
    ui->DriverLogWidgetLayout->addWidget(mDriverLogWidget);
    mPowerWidget = new PowerWidget();
    ui->PowerLayout->addWidget(mPowerWidget);
    mSensorsWidget = new SensorsWidget();
    ui->SensorTableLayout->addWidget(mSensorsWidget);

    mConnectDialog = new ConnectConfigDialog();

    mDriverControllerWidget->setModel(mChannelTableWidget->getModel());
    connect(mChannelTableWidget,SIGNAL(RowChanged(int)),mDriverControllerWidget,SLOT(RowChanged(int)));
    //конец настройки виджетов

    //настройка кнопок тулбара
    ActionsLoad();

    TBactionPlay->setEnabled(false);
    TBactionStop->setEnabled(false);
    TBactionNext->setEnabled(false);

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

    mConnectStatusLabel = new QLabel(this);
    mConnectStatusLabel->setText("Соединение не установленно");
    ui->statusbar->addWidget(mConnectStatusLabel);

    mCommandControllerStatusLabel = new QLabel(this);
    mCommandControllerStatusLabel->setText("Файл команд не загружен");
    ui->statusbar->addWidget(mCommandControllerStatusLabel);

    //настройка кнопок меню
    connect(ui->actionOpenConfigFile,SIGNAL(triggered()),this,SLOT(OpenXML()));
    connect(ui->actionSaveConfigFile,SIGNAL(triggered()),this,SLOT(SaveXML()));
    connect(ui->actionConnect,SIGNAL(triggered()),this,SLOT(Connect()));
    connect(ui->actionDisconnect,SIGNAL(triggered()),this,SLOT(Disconnect()));
    connect(ui->actionOn,SIGNAL(triggered()),mPowerWidget,SLOT(on_ButtonOnAll_clicked()));
    connect(ui->actionOff,SIGNAL(triggered()),mPowerWidget,SLOT(on_ButtonOffAll_clicked()));
    connect(ui->actionOpenConnectConfig,SIGNAL(triggered()),this,SLOT(OpenConnectConfig()));
    //конец настройки кнопок меню

    connect(mCommandControllerWidget,SIGNAL(StartWriteLog(int)),mDriverLogWidget,SLOT(StartWriteLog(int)));
    connect(mCommandControllerWidget,SIGNAL(StopWriteLog()),mDriverLogWidget,SLOT(StopWriteLog()));
    connect(mCommandControllerWidget,SIGNAL(FileLoaded()),this,SLOT(ActivateActions()));

    connect(mCommandControllerWidget,SIGNAL(PlayStart()),mChannelTableWidget,SLOT(DisActivate()));
    connect(mCommandControllerWidget,SIGNAL(PlayStop()),mChannelTableWidget,SLOT(Activate()));

    //чтение настроек их XML файла
    bool isOk = ConfigController::Instance()->OpenFile("config.xml");
    if(isOk)
    {
        mHost=ConfigController::Instance()->GetHost();
        mSendPort=ConfigController::Instance()->GetSendPort();
        mSendDelay=ConfigController::Instance()->GetSendDelay();
        mReceivePort=ConfigController::Instance()->GetReceivePort();
        mReceiveDelay=ConfigController::Instance()->GetReceiveDelay();

        ConfigController::Instance()->Update(mSendBuffer);
        BufferController::Instance()->InitBuffers();
        CommandController::Instance()->Initialize();

        qDebug() << "Настройки успешно прочитаны";
    }
    else
    {
        QMessageBox::warning(this,"Ошибка при чтении файла настроек","Возможно указан не верный путь или файл содержит ошибки");
        qDebug() << "Error loading config file...";
        exit(0);
    }
    //конец чтения настроек

    //заполнение таблицы приводов
    mChannelTableWidget->ShowConfigData();
    mSensorsWidget->ShowConfigData();

    mTimerUpdate = new QTimer();
    mTimerUpdate->setInterval(mReceiveDelay);
    connect(mTimerUpdate,SIGNAL(timeout()),this,SLOT(ProcessTheDatagram()));
    //создание и запуск потоков на отправку и прием буфера
    mThreadRecieve = new ThreadReceive();
    //connect(mThreadRecieve,SIGNAL(ReadyData()),this,SLOT(ProcessTheDatagram()));
    mThreadRecieve->start();

    mThreadSend = new ThreadSend();
    mThreadSend->start();
}

AR600MainWindow::~AR600MainWindow()
{
    delete ui;
}

//Настройка кнопок тулбара
void AR600MainWindow::ActionsLoad()
{
    TBactionOpenCF = new QAction("Открыть файл настроек",0);
    TBactionOpenCF->setToolTip("Открыть файл настроек");
    TBactionOpenCF->setIcon(QIcon("Icons/open.ico"));
    connect(TBactionOpenCF,SIGNAL(triggered()),this,SLOT(OpenXML()));

    TBactionSaveCF = new QAction("Сохранить файл настроек",0);
    TBactionSaveCF->setToolTip("Сохранить файл настроек");
    TBactionSaveCF->setIcon(QIcon("Icons/save.ico"));
    connect(TBactionSaveCF,SIGNAL(triggered()),this,SLOT(SaveXML()));

    TBactionPlay = new QAction("Начать выполнение",0);
    TBactionPlay->setToolTip("Начать выполнение");
    TBactionPlay->setIcon(QIcon("Icons/play.ico"));
    connect(TBactionPlay,SIGNAL(triggered()),mCommandControllerWidget,SLOT(on_ButtonPlayPause_clicked()));

    TBactionStop = new QAction("Остановить выполнение",0);
    TBactionStop->setToolTip("Остановить выполнение");
    TBactionStop->setIcon(QIcon("Icons/stop.ico"));
    connect(TBactionStop,SIGNAL(triggered()),mCommandControllerWidget,SLOT(on_ButtonStop_clicked()));

    TBactionNext = new QAction("Следующая команда",0);
    TBactionNext->setToolTip("Следующая команда");
    TBactionNext->setIcon(QIcon("Icons/redo.ico"));
    connect(TBactionNext,SIGNAL(triggered()),mCommandControllerWidget,SLOT(on_ButtonNext_clicked()));

    TBactionOpenCommandFile = new QAction("Загрузить файл команд",0);
    TBactionOpenCommandFile->setToolTip("Загрузить файл команд");
    TBactionOpenCommandFile->setIcon(QIcon("Icons/folder.ico"));
    connect(TBactionOpenCommandFile,SIGNAL(triggered()),mCommandControllerWidget,SLOT(on_ButtonLoadFile_clicked()));

    TBactionOnPower = new QAction("Включить все",0);
    TBactionOnPower->setToolTip("Включить все");
    TBactionOnPower->setIcon(QIcon("Icons/on.ico"));
    connect(TBactionOnPower,SIGNAL(triggered()),mPowerWidget,SLOT(on_ButtonOnAll_clicked()));

    TBactionOffPower = new QAction("Выключить все",0);
    TBactionOffPower->setToolTip("Выключить все");
    TBactionOffPower->setIcon(QIcon("Icons/off.ico"));
    connect(TBactionOffPower,SIGNAL(triggered()),mPowerWidget,SLOT(on_ButtonOffAll_clicked()));

    TBactionOpenConnectSettings = new QAction("Настройки соединения",0);
    TBactionOpenConnectSettings->setToolTip("Настройки соединения");
    TBactionOpenConnectSettings->setIcon(QIcon("Icons/settings.ico"));
    connect(TBactionOpenConnectSettings,SIGNAL(triggered()),this,SLOT(OpenConnectConfig()));

    TBactionConnect = new QAction("Подключение",0);
    TBactionConnect->setToolTip("Подключение");
    TBactionConnect->setIcon(QIcon("Icons/connect.ico"));
    connect(TBactionConnect,SIGNAL(triggered()),this,SLOT(Connect()));

    TBactionDisconnect = new QAction("Отключение",0);
    TBactionDisconnect->setToolTip("Отключение");
    TBactionDisconnect->setIcon(QIcon("Icons/disconnect.ico"));
    connect(TBactionDisconnect,SIGNAL(triggered()),this,SLOT(Disconnect()));
}

//вызывается при запуске подключения к роботу
void AR600MainWindow::Connect()
{
    mThreadRecieve->ConnectSocket();
    mThreadSend->ConnectSocket();
    mTimerUpdate->start();
    mConnectStatusLabel->setText("Соединение установленно");
}

//вызывается при запуске остановки подключения к роботу
void AR600MainWindow::Disconnect()
{
    //выключаем напряжения
    mSendBuffer->OFF61();
    mSendBuffer->OFF62();
    mSendBuffer->OFF81();
    mSendBuffer->OFF82();
    mSendBuffer->OFF48();
    mThreadSend->DisconnectSocket();
    mThreadRecieve->DisconnectSocket();
    mTimerUpdate->stop();
    mConnectStatusLabel->setText("Соединение не установленно");
}

void AR600MainWindow::ActivateActions()
{
    TBactionPlay->setEnabled(true);
    TBactionStop->setEnabled(true);
    TBactionNext->setEnabled(true);
    mCommandControllerStatusLabel->setText("Файл команд загружен");
}

//открытие диалога настроек подключения
void AR600MainWindow::OpenConnectConfig()
{
    mConnectDialog->setModal(true);
    mConnectDialog->Update();
    mConnectDialog->show();
}

//обработка принятого пакета от робота
void AR600MainWindow::ProcessTheDatagram()
{
    mPowerWidget->UpdatePowerLabel();
    mDriverControllerWidget->UpdateData();
    mChannelTableWidget->UpdatePos();
    mSensorsWidget->UpdatePos();
}

//сохранение файла настроек
void AR600MainWindow::SaveXML()
{
    QString fileName = QFileDialog::getSaveFileName(0,"Save XML Dialog","","*.XML *.xml");
    if (!fileName.isEmpty())
    {
        ConfigController::Instance()->SaveFile(fileName.toStdString());
        qDebug() << "Файл настроек успешно сохранен в " << fileName << endl;
    }
}

//открытие файла настроек
void AR600MainWindow::OpenXML()
{
    QString fileName = QFileDialog::getOpenFileName(0,"Open XML Dialog","","*.XML *.xml");
    if (!fileName.isEmpty())
    {
        bool isOk = ConfigController::Instance()->OpenFile(fileName.toStdString());

        if(isOk)
        {
            //загоняем в отправляемый массив
            ConfigController::Instance()->Update(mSendBuffer);
            qDebug() << "Файл настроек успешно загружен из " << fileName << endl;
            qDebug() << "Настройки успешно прочитаны" <<endl;
        }
        else
        {
            qDebug() << "Файл настроек не был загружен из " << fileName << endl;
            qDebug() << "Возможно имя, или формат файла заданы неверно" <<endl;
        }
    }
}
