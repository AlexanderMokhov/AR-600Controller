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

    mDriverControllerWidget->setModel(mChannelTableWidget->getModel());
    connect(mChannelTableWidget,SIGNAL(RowChanged(int)),mDriverControllerWidget,SLOT(RowChanged(int)));

    mDialog = new DialogConnectConfig();
    //конец настройки виджетов

    ActionsLoad();

    actionPlay->setEnabled(false);
    actionStop->setEnabled(false);
    actionNext->setEnabled(false);

    //добавление кнопок на тулбар
    ui->MainToolBar->addAction(actionOpen);
    ui->MainToolBar->addAction(QIcon("Icons/save.ico"),"Сохранить файл настроек",this,SLOT(SaveXML()));
    ui->MainToolBar->addSeparator();
    ui->MainToolBar->addAction(QIcon("Icons/connect.ico"),"Подключение",this,SLOT(Connect()));
    ui->MainToolBar->addAction(QIcon("Icons/disconnect.ico"),"Отключение",this,SLOT(Disconnect()));
    ui->MainToolBar->addAction(actionOpenConnectSettings);
    ui->MainToolBar->addSeparator();
    ui->MainToolBar->addAction(actionOnPower);
    ui->MainToolBar->addAction(actionOffPower);
    ui->MainToolBar->addSeparator();
    ui->MainToolBar->addAction(QIcon("Icons/folder.ico"),"Загрузить файл команд",mCommandControllerWidget,SLOT(on_ButtonLoadFile_clicked()));
    ui->MainToolBar->addSeparator();
    ui->MainToolBar->addAction(actionPlay);
    ui->MainToolBar->addAction(actionPlay);
    ui->MainToolBar->addAction(actionStop);
    ui->MainToolBar->addSeparator();
    ui->MainToolBar->addAction(actionNext);
    ui->MainToolBar->addSeparator();
    //конец добавление кнопок на тулбар
    mConnectStatusLabel = new QLabel(this);
    mConnectStatusLabel->setText("Соединение не установленно");
    ui->statusbar->addWidget(mConnectStatusLabel);

    mCommandControllerStatusLabel = new QLabel(this);
    mCommandControllerStatusLabel->setText("Файл команд не загружен");
    ui->statusbar->addWidget(mCommandControllerStatusLabel);


    connect(ui->actionOpenConfigFile,SIGNAL(triggered()),this,SLOT(OpenXML()));
    connect(ui->actionSaveConfigFile,SIGNAL(triggered()),this,SLOT(SaveXML()));
    connect(ui->actionConnect,SIGNAL(triggered()),this,SLOT(Connect()));
    connect(ui->actionDisconnect,SIGNAL(triggered()),this,SLOT(Disconnect()));
    connect(ui->actionOn,SIGNAL(triggered()),mPowerWidget,SLOT(on_ButtonOnAll_clicked()));
    connect(ui->actionOff,SIGNAL(triggered()),mPowerWidget,SLOT(on_ButtonOffAll_clicked()));
    connect(ui->actionOpenConnectConfig,SIGNAL(triggered()),this,SLOT(OpenConnectConfig()));

    connect(mCommandControllerWidget,SIGNAL(StartWriteLog(int)),mDriverLogWidget,SLOT(StartWriteLog(int)));
    connect(mCommandControllerWidget,SIGNAL(StopWriteLog()),mDriverLogWidget,SLOT(StopWriteLog()));
    connect(mCommandControllerWidget,SIGNAL(FileLoaded()),this,SLOT(ActivateActions()));

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

void AR600MainWindow::ActionsLoad()
{
    actionOpen = new QAction("Открыть файл настроек",0);
    actionOpen->setToolTip("Открыть файл настроек");
    actionOpen->setIcon(QIcon("Icons/open.ico"));
    connect(actionOpen,SIGNAL(triggered()),this,SLOT(OpenXML()));

    actionPlay = new QAction("Начать выполнение",0);
    actionPlay->setToolTip("Начать выполнение");
    actionPlay->setIcon(QIcon("Icons/play.ico"));
    connect(actionPlay,SIGNAL(triggered()),mCommandControllerWidget,SLOT(on_ButtonPlayPause_clicked()));

    actionStop = new QAction("Остановить выполнение",0);
    actionStop->setToolTip("Остановить выполнение");
    actionStop->setIcon(QIcon("Icons/stop.ico"));
    connect(actionStop,SIGNAL(triggered()),mCommandControllerWidget,SLOT(on_ButtonStop_clicked()));

    actionNext = new QAction("Следующая команда",0);
    actionNext->setToolTip("Следующая команда");
    actionNext->setIcon(QIcon("Icons/redo.ico"));
    connect(actionNext,SIGNAL(triggered()),mCommandControllerWidget,SLOT(on_ButtonNext_clicked()));

    actionOnPower = new QAction("Включить все",0);
    actionOnPower->setToolTip("Включить все");
    actionOnPower->setIcon(QIcon("Icons/on.ico"));
    connect(actionOnPower,SIGNAL(triggered()),mPowerWidget,SLOT(on_ButtonOnAll_clicked()));

    actionOffPower = new QAction("Выключить все",0);
    actionOffPower->setToolTip("Выключить все");
    actionOffPower->setIcon(QIcon("Icons/off.ico"));
    connect(actionOffPower,SIGNAL(triggered()),mPowerWidget,SLOT(on_ButtonOffAll_clicked()));

    actionOpenConnectSettings = new QAction("Настройки соединения",0);
    actionOpenConnectSettings->setToolTip("Настройки соединения");
    actionOpenConnectSettings->setIcon(QIcon("Icons/settings.ico"));
    connect(actionOpenConnectSettings,SIGNAL(triggered()),this,SLOT(OpenConnectConfig()));

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
    actionPlay->setEnabled(true);
    actionStop->setEnabled(true);
    actionNext->setEnabled(true);
    mCommandControllerStatusLabel->setText("Файл команд загружен");
}

void AR600MainWindow::OpenConnectConfig()
{
    mDialog->setModal(true);
    mDialog->Update();
    mDialog->show();
    //mDialog->activateWindow();
}

//обработка принятого пакета от робота
void AR600MainWindow::ProcessTheDatagram()
{
    mPowerWidget->UpdatePowerLabel();
    mDriverControllerWidget->UpdateData();
    mChannelTableWidget->UpdatePos();
}

void AR600MainWindow::SaveXML()
{
    QString fileName = QFileDialog::getSaveFileName(0,"Save XML Dialog","","*.XML *.xml");
    if (!fileName.isEmpty())
    {
        ConfigController::Instance()->SaveFile(fileName.toStdString());
        qDebug() << "Файл настроек успешно сохранен в " << fileName << endl;
    }
}

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

void AR600MainWindow::play()
{

}

void AR600MainWindow::pause()
{

}

void AR600MainWindow::stop()
{

}
