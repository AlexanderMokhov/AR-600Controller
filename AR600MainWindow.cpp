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
    //конец настройки виджетов

    //добавление кнопок на тулбар
    ui->MainToolBar->addAction(QIcon("Icons/open.ico"),"Открыть файл настроек",this,SLOT(OpenXML()));
    ui->MainToolBar->addAction(QIcon("Icons/save.ico"),"Сохранить файл настроек",this,SLOT(SaveXML()));
    ui->MainToolBar->addSeparator();
    ui->MainToolBar->addAction(QIcon("Icons/connect.ico"),"Подключение",this,SLOT(Connect()));
    ui->MainToolBar->addAction(QIcon("Icons/disconnect.ico"),"Отключение",this,SLOT(Disconnect()));
    ui->MainToolBar->addSeparator();
    ui->MainToolBar->addAction(QIcon("Icons/folder.ico"),"Загрузить файл команд",mCommandControllerWidget,SLOT(on_ButtonLoadFile_clicked()));
    ui->MainToolBar->addSeparator();
    ui->MainToolBar->addAction(QIcon("Icons/play.ico"),"Начать выполнение",mCommandControllerWidget,SLOT(on_ButtonPlayPause_clicked()));
    ui->MainToolBar->addAction(QIcon("Icons/pause.ico"),"Пауза",mCommandControllerWidget,SLOT(on_ButtonPlayPause_clicked()));
    ui->MainToolBar->addAction(QIcon("Icons/stop.ico"),"Остановить выполнение",mCommandControllerWidget,SLOT(on_ButtonStop_clicked()));
    ui->MainToolBar->addSeparator();
    ui->MainToolBar->addAction(QIcon("Icons/redo.ico"),"Следующая команда",mCommandControllerWidget,SLOT(on_ButtonNext_clicked()));
    ui->MainToolBar->addSeparator();
    //конец добавление кнопок на тулбар

    //чтение настроек их XML файла
    bool isOk = ConfigController::Instance()->OpenFile("config.xml");
    if(isOk)
    {
        mPort=ConfigController::Instance()->GetPort();
        mHost=ConfigController::Instance()->GetHost();
        mSendDelay=ConfigController::Instance()->GetSendDelay();
        ConfigController::Instance()->Update(mSendBuffer);
        BufferController::Instance()->InitBuffers();
        CommandController::Instance()->Initialize();

        qDebug() << "Настройки успешно прочитаны";
    }
    //конец чтения настроек

    //заполнение таблицы приводов
    mChannelTableWidget->ShowConfigData();

    mTimerUpdate = new QTimer();
    mTimerUpdate->setInterval(100);
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

//вызывается при запуске подключения к роботу
void AR600MainWindow::Connect()
{
    mThreadRecieve->ConnectSocket();
    mThreadSend->ConnectSocket();
    mTimerUpdate->start();
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
