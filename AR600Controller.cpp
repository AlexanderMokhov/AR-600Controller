#include "AR600Controller.h"
#include "ui_AR600Controller.h"

AR600Controller::AR600Controller(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::Widget)
{
	ui->setupUi(this);

    mUdpSocketResiver = new QUdpSocket(this);
    connect(mUdpSocketResiver, SIGNAL(readyRead()), this, SLOT(ProcessPendingDatagrams()));

    mUdpSocketSender =  new QUdpSocket(this);

    mTimer = new QTimer(this);
    connect(mTimer, SIGNAL(timeout()), SLOT(UdpSend()));

    //инициализация контроллеров
    ConfigController::Instance()->Initialize();
    BufferController::Instance()->Initialize();
    CommandController::Instance()->Initialize();
    //коне инициализации контроллеров

    mSendBuffer = BufferController::Instance()->GetWriteBuffer();
    mReceiveBuffer = BufferController::Instance()->GetReadBuffer();

    //настраиваем виджеты
    mDriverControllerWidget = new DriverControllerWidget();
    ui->DriverControlLayout->addWidget(mDriverControllerWidget);
    mCommandControllerWidget = new CommandControllerWidget();
    ui->CommandControlLayout->addWidget(mCommandControllerWidget);
    mChannelTableWidget = new ChannelTableWidget();
    ui->ChannelTableLayout->addWidget(mChannelTableWidget);

    mDriverControllerWidget->setModel(mChannelTableWidget->getModel());
    connect(mChannelTableWidget,SIGNAL(RowChanged(int)),mDriverControllerWidget,SLOT(RowChanged(int)));
    //конец настройки виджетов

    connect(mCommandControllerWidget,SIGNAL(StartPlayForward()),this,SLOT(OnStartPlayForward()));

    //графики

{
    this->RangeSize=10;
    ui->Plot->addGraph();
    ui->Plot->graph(ui->Plot->graphCount()-1)->setPen(QPen(Qt::blue));
    ui->Plot->addGraph();
    ui->Plot->graph(ui->Plot->graphCount()-1)->setPen(QPen(Qt::red));
    ui->Plot->addGraph();
    ui->Plot->graph(ui->Plot->graphCount()-1)->setPen(QPen(Qt::green));
    ui->Plot->addGraph();
    ui->Plot->graph(ui->Plot->graphCount()-1)->setPen(QPen(Qt::black));
    ui->Plot->addGraph();
    ui->Plot->graph(ui->Plot->graphCount()-1)->setPen(QPen(Qt::gray));
    //работа с графиками

    ui->Plot->xAxis->setTickLabelType(QCPAxis::ltDateTime);
    ui->Plot->xAxis->setDateTimeFormat("mm:ss");
    ui->Plot->xAxis->setAutoTickStep(false);
    ui->Plot->xAxis->setTickStep(2);//шаг между рисками (мс)
    ui->Plot->axisRect()->setupFullAxesBox();

    //конец работы с графиками

    //загрузка файла настроек
}

    //чтение настроек их XML файла
    bool isOk = ConfigController::Instance()->OpenFile("config.xml");
    if(isOk)
    {
        mPort=ConfigController::Instance()->GetPort();
        mHost=ConfigController::Instance()->GetHost();
        mSendDelay=ConfigController::Instance()->GetSendDelay();
        ui->hostLineEdit->setText(QString::fromStdString(mHost));
        ui->portLineEdit->setText(QString::number(mPort));
        //загоняем в отправляемый массив

        ConfigController::Instance()->Update(mSendBuffer);
        BufferController::Instance()->InitBuffers();
        qDebug() << "Настройки успешно прочитаны";
    }


    //заполнение таблицы приводов
    mChannelTableWidget->ShowConfigData();
}

AR600Controller::~AR600Controller()
{
    delete ui;
}

//вызывается при запуске подключения к роботу
void AR600Controller::Connect()
{
	mHost = ui->hostLineEdit->text().toStdString();
    mPort = ui->portLineEdit->text().toInt();

    if (!mUdpSocketResiver->bind(mPort,QUdpSocket::ShareAddress))
    {
        qDebug()<< "Not Bind!";
    }

    mUdpSocketSender->connectToHost(QString::fromStdString(mHost) , mPort);
    mUdpSocketSender->waitForConnected(1000);
    if (mUdpSocketSender->state()==QUdpSocket::ConnectedState)
    {
        qDebug() << "Connected";
    }
    else
    {
        qDebug() << "Disconnected";
    }
    //отправляем каждые 100 мс
    mTimer->start(mSendDelay);
}

void AR600Controller::Disconnect()
{
    //выключаем напряжения
    mSendBuffer->OFF61();
    mSendBuffer->OFF62();
    mSendBuffer->OFF81();
    mSendBuffer->OFF82();
    mSendBuffer->OFF48();
    mTimer->stop();

    mUdpSocketSender->disconnect();
    //mUdpSocketSender->waitForDisconnected();

    mUdpSocketResiver->disconnect();

    if (mUdpSocketSender->state()==QUdpSocket::ConnectedState)
	        qDebug() << "Connected";
	    else
	        qDebug() << "Disconnected";
}

//прием пакета от робота
void AR600Controller::ProcessPendingDatagrams()
{
   qDebug()<< "UDPRead";
   while (mUdpSocketResiver->hasPendingDatagrams())
   {
       QByteArray datagram;
       datagram.resize(mUdpSocketResiver->pendingDatagramSize());
       QHostAddress sender;
       quint16 senderPort;

       mUdpSocketResiver->readDatagram(datagram.data(), datagram.size(),&sender, &senderPort);

       //Отправляем пакет на обработку
       ProcessTheDatagram(datagram);
    }

    realtimeData();
}

void AR600Controller::StartSending()
{
    UdpSend();
}

/*void AR600Controller::SendMessage()
{
    ;
}*/

//включение / отключение питания 48 В
void AR600Controller::On48Slot(bool value)
{
    if(value)
        mSendBuffer->ON48();//вкл
    else
        mSendBuffer->OFF48();//выкл
}

void AR600Controller::On8V1Slot(bool value)
{
    if(value)
        mSendBuffer->ON81();//вкл
    else
        mSendBuffer->OFF81();//выкл
}

void AR600Controller::On8V2Slot(bool value)
{
    if(value)
        mSendBuffer->ON82();//вкл
    else
        mSendBuffer->OFF82();//выкл
}

void AR600Controller::On6V1Slot(bool value)
{
    if(value)
        mSendBuffer->ON61();//вкл
    else
        mSendBuffer->OFF61();//выкл
}

void AR600Controller::On6V2Slot(bool value)
{
    if(value)
        mSendBuffer->ON62();//вкл
    else
        mSendBuffer->OFF62();//выкл
}

//отправка пакета роботу
void AR600Controller::UdpSend()
{
    qDebug() << "Send" << mSendBuffer->GetBuffer();

    mUdpSocketSender->writeDatagram(mSendBuffer->GetBuffer(), mSendBuffer->GetSize()* sizeof(char), QHostAddress(QString::fromStdString(mHost)), mPort);
    mUdpSocketSender->waitForBytesWritten();
    //if включен контроллер команд то апдейт

    if(CommandController::Instance()->GetPlayForwardState())
    {
        CommandController::Instance()->Update(CurrentTimeForCommands);
        CurrentTimeForCommands+=(mSendDelay*1e3);

        //если время закончилось - останавливаем, переводим индекс команды на начало списка
        if(CommandController::Instance()->GetTimeRecord()<=CurrentTimeForCommands)
        {
            CommandController::Instance()->SetPlayForwardState(false);
            CommandController::Instance()->SetCommandId(0);
        }
    }
    if(CommandController::Instance()->GetGoToPosState())
    {
        CommandController::Instance()->GoNextPos();
    }

}

void AR600Controller::SetLenght(double lenght)
{
    this->RangeSize = (int)lenght;
}

void AR600Controller::OnStartPlayForward()
{
    CurrentTimeForCommands = 0;
}

//обработка принятого пакета от робота
void AR600Controller::ProcessTheDatagram(QByteArray &datagramm)
{
    mReceiveBuffer->Init(datagramm.data());
    UpdatePowerLabel();
    mDriverControllerWidget->UpdateData();
}

//обновление значений напряжений и токов
void AR600Controller::UpdatePowerLabel()
{
    ui->label_48V->setText(QString::number(mReceiveBuffer->GetU48()));
    ui->label_48A->setText(QString::number(mReceiveBuffer->GetI48()));

    ui->label_81V->setText(QString::number(mReceiveBuffer->GetU81()));
    ui->label_81A->setText(QString::number(mReceiveBuffer->GetI81()));

    ui->label_82V->setText(QString::number(mReceiveBuffer->GetU82()));
    ui->label_82A->setText(QString::number(mReceiveBuffer->GetI82()));

    ui->label_61V->setText(QString::number(mReceiveBuffer->GetU61()));
    ui->label_61A->setText(QString::number(mReceiveBuffer->GetI61()));

    ui->label_62V->setText(QString::number(mReceiveBuffer->GetU62()));
    ui->label_62A->setText(QString::number(mReceiveBuffer->GetI62()));

}

void AR600Controller::realtimeData()
{
    double key = QDateTime::currentDateTime().toMSecsSinceEpoch()/1000.0;
    ui->Plot->graph(0)->addData(key, mReceiveBuffer->GetU48());
    ui->Plot->graph(1)->addData(key, mReceiveBuffer->GetU81());
    ui->Plot->graph(2)->addData(key, mReceiveBuffer->GetU82());
    ui->Plot->graph(3)->addData(key, mReceiveBuffer->GetU61());
    ui->Plot->graph(4)->addData(key, mReceiveBuffer->GetU62());

    // Удаление данных линии, что за пределами видимого диапазона:
    for(int i=0;i<5;i++)
    {
        ui->Plot->graph(i)->removeDataBefore(key-this->RangeSize);
        ui->Plot->graph(i)->rescaleValueAxis(true);
    }

    ui->Plot->xAxis->setRange(key+0.25, this->RangeSize, Qt::AlignRight);
    ui->Plot->replot();
}

//TODO задать номер привода задать читать значения
//сенсоры

void AR600Controller::on_pButtonSaveXML_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(0,"Save XML Dialog","","*.XML *.xml");
    if (!fileName.isEmpty())
    {
        ConfigController::Instance()->SaveFile(fileName.toStdString());
        qDebug() << "Файл настроек успешно сохранен в " << fileName << endl;
    }
}

void AR600Controller::on_pButtonOpenXML_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(0,"Open XML Dialog","","*.XML *.xml");
    if (!fileName.isEmpty())
    {
        bool isOk = ConfigController::Instance()->OpenFile(fileName.toStdString());

        if(isOk)
        {
            ui->hostLineEdit->setText(QString::fromStdString(ConfigController::Instance()->GetHost()));
            ui->portLineEdit->setText(QString::number(ConfigController::Instance()->GetPort()));
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

void AR600Controller::on_ButtonStartLog_clicked()
{
    mLogTimer = new QTimer(this);
    connect(mLogTimer, SIGNAL(timeout()), SLOT(on_LogWrite()));
    mLogController=new LogController();
    CurrentTime=0;
    mLogTimer->start(ui->spinBoxLog->value());
}

void AR600Controller::on_LogWrite()
{
    mLogController->AddRawData(CurrentTime);
    CurrentTime+=ui->spinBoxLog->value();
    ui->labelLogCTime->setText(QString::number(CurrentTime));
    if(CurrentTime> ui->spinLogEndTime->value())
    {
        mLogTimer->stop();
    }

}

void AR600Controller::on_ButtonStopLog_clicked()
{
    mLogTimer->stop();
}

void AR600Controller::on_ButtonSaveLog_clicked()
{
    mLogController->SaveData(QString("DriverLog_" + QDateTime::currentDateTime().toString("dd_MM_yyyy_HH_mm_ss")+"_.txt").toStdString());
}
