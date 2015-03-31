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

    AR600ControllerConf::Instance()->initialize();
    BufferController::Instance()->initialize();

    mSendBuffer = BufferController::Instance()->getWriteBuffer();
    mReceiveBuffer = BufferController::Instance()->getReadBuffer();

    m_DriverControllerWidget = new DriverControllerWidget();
    ui->DriverControolerLayout->addWidget(m_DriverControllerWidget);
    //графики

{
    //mPlot= new DataPlot();
    //mPlot.setPlotWidget(ui->Plot);
    //mPlot.draw();
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

    bool isOk = AR600ControllerConf::Instance()->openFile("config.xml");
    if(isOk)
    {
        ui->hostLineEdit->setText(QString::fromStdString(AR600ControllerConf::Instance()->getHost()));
        ui->portLineEdit->setText(QString::number(AR600ControllerConf::Instance()->getPort()));
        //загоняем в отправляемый массив

        AR600ControllerConf::Instance()->Update(mSendBuffer);
        BufferController::Instance()->initBuffers();
        qDebug() << "Настройки успешно прочитаны";
    }

    isOk=AR600ControllerConf::Instance()->saveFile("mynewconfig.xml");

    //загружаем список команд из файла
    CommandController *mc = new CommandController();

    mc->LoadFromFile("1.txt");

    m_CLModel= new ChannelTableModel();
    ui->ChannelTableView->setModel(m_CLModel);
    m_DriverControllerWidget->setModel(m_CLModel);
    m_SelectionModel = ui->ChannelTableView->selectionModel();
    ShowConfigData();

    //m_CLModel->setData(m_CLModel->index(0,1),QObject::tr("ggg"));
    //m_CLModel->insertRows(3,5);
    //m_CLModel->removeRows(7,10);
    connect(ui->ChannelTableView,SIGNAL(clicked(QModelIndex)),this,SLOT(OnEnterTable(QModelIndex)));

    short num=-1456;
    mSendBuffer->MOTOR_ANGLE_set(1,num);
    BufferController::Instance()->initBuffers();
    short num2=mReceiveBuffer->MOTOR_CPOS_get(1);
    int i=0;
}

AR600Controller::~AR600Controller()
{
    delete ui;
}



void AR600Controller::Connect()
{
    //mSendBuffer->init();
	mHost = ui->hostLineEdit->text().toStdString();
	mPort = ui->portLineEdit->text().toInt();

    //!listenSocket->bind(QHostAddress::Any, 8888)
    //HostAddress::Any, 8888, QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint
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
     mTimer->start(100);



}

void AR600Controller::Disconnect()
{
    mTimer->stop();
    mSendBuffer->init();

    mUdpSocketSender->disconnect();
    mUdpSocketSender->waitForDisconnected();

    mUdpSocketResiver->disconnect();

    if (mUdpSocketSender->state()==QUdpSocket::ConnectedState)
	        qDebug() << "Connected";
	    else
	        qDebug() << "Disconnected";
}

void AR600Controller::ProcessPendingDatagrams()
{
   qDebug()<< "UDPRead";
        while (mUdpSocketResiver->hasPendingDatagrams()) {
            QByteArray datagram;
            datagram.resize(mUdpSocketResiver->pendingDatagramSize());
            QHostAddress sender;
            quint16 senderPort;

            mUdpSocketResiver->readDatagram(datagram.data(), datagram.size(),
                                    &sender, &senderPort);
            //qDebug() << "Data:" << datagram;
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

void AR600Controller::On48Slot(bool value)
{
    if(value)
    {
        mSendBuffer->ON48();
    }
    else
    {
        mSendBuffer->OFF48();
    }
}

void AR600Controller::On8V1Slot(bool value)
{
    if(value)
    {
        mSendBuffer->ON81();
    }
    else
    {
        mSendBuffer->OFF81();
    }
}

void AR600Controller::On8V2Slot(bool value)
{
    if(value)
    {
        mSendBuffer->ON82();
    }
    else
    {
        mSendBuffer->OFF82();
    }
}

void AR600Controller::On6V1Slot(bool value)
{
    if(value)
    {
        mSendBuffer->ON61();
    }
    else
    {
        mSendBuffer->OFF61();
    }
}

void AR600Controller::On6V2Slot(bool value)
{
    if(value)
    {
        mSendBuffer->ON62();
    }
    else
    {
        mSendBuffer->OFF62();
    }
}

void AR600Controller::UdpSend()
{
    SetConfigData();
    //mSendBuffer->AddressUpdate(1,1);
    //mSendBuffer.AddressUpdate(2,2);

    //mSendBuffer.MOTOR_STIFF_set(1,100);
    //mSendBuffer.MOTOR_POS_MIN_set(1,-500);
    //mSendBuffer.MOTOR_POS_MAX_set(1,500);

    //mSendBuffer.MOTOR_STIFF_set(2,100);
   // mSendBuffer.MOTOR_POS_MIN_set(2,-700);
    //mSendBuffer.MOTOR_POS_MAX_set(2,700);



    qDebug() << "Send" << mSendBuffer->GetBuffer();

    mUdpSocketSender->writeDatagram(mSendBuffer->GetBuffer(), mSendBuffer->GetSize()* sizeof(char), QHostAddress(QString::fromStdString(mHost)), mPort);
    mUdpSocketSender->waitForBytesWritten();

}

void AR600Controller::AddRow()
{
    ;
}

void AR600Controller::SetLenght(double lenght)
{
    this->RangeSize = (int)lenght;
}

void AR600Controller::OnEnterTable(QModelIndex index)
{
    int row = m_SelectionModel->currentIndex().row();
    m_DriverControllerWidget->setCurrentRow(row);
    m_CLModel->data(m_CLModel->index(row,0),Qt::EditRole);
    m_DriverControllerWidget->UpdateData();

    QString value = QString::number(row);
    ui->label_8->setText(value);
}


void AR600Controller::ProcessTheDatagram(QByteArray &datagramm)
{
    mReceiveBuffer->init(datagramm.data());
    UpdatePowerLabel();

    for (unsigned int i = 1; i < 3; i++)
    {
        qDebug()     << "Pos [" << i << "]: "<< mReceiveBuffer->MOTOR_CPOS_get(i) <<  " "
                     << mReceiveBuffer->MOTOR_POS_MIN_get(i) <<  " "
                     << mReceiveBuffer->MOTOR_POS_MAX_get(i) << " "
                     << mReceiveBuffer->MOTOR_U_get(i) << " "
                     << mReceiveBuffer->MOTOR_I_get(i)<< " "
                     << mReceiveBuffer->MOTOR_STAT_get(i);

    }
    //AR600ControllerConf::Instance()->UpdateIlim(mSendBuffer,mReceiveBuffer);
    m_DriverControllerWidget->UpdateData();
}

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

    //mPlot.play();
}

void AR600Controller::SetConfigData()
{

}

void AR600Controller::ShowConfigData()
{
    std::map<unsigned int,DriverSettingsItem> *mMap = AR600ControllerConf::Instance()->getConfMap();
    m_CLModel->removeRows(0,m_CLModel->rowCount());

    std::map<unsigned int,DriverSettingsItem>::iterator it;

    for(it = mMap->begin();it!=mMap->end();++it)
    {
        QString Number = QString::number((*it).first);
        QString NumberBuffer = QString::number((*it).second.getNumberBuffer());
        QString Name = QString::fromStdString((*it).second.getName());
        QString Status = "0";
        QString MinPos = QString::number((*it).second.getMinPos());
        QString MaxPos = QString::number((*it).second.getMaxPos());
        QString Reverce = QString::number((*it).second.getReverce());
        QString KP = QString::number((*it).second.getStiff());
        QString KI = QString::number((*it).second.getDump());
        QString KD = QString::number((*it).second.getTorque());
        QString Ilim = QString::number((*it).second.getIlim());
        m_CLModel->insertRow(Number,Name,Status,"0",MinPos,MaxPos,Reverce,KP,KI,KD,Ilim);
    }
}

//TODO задать номер привода задать читать значения
//сенсоры

void AR600Controller::on_pButtonSaveXML_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(0,"Save XML Dialog","","*.XML *.xml");
    if (!fileName.isEmpty())
    {
        AR600ControllerConf::Instance()->saveFile(fileName.toStdString());
        qDebug() << "Файл настроек успешно сохранен в " << fileName << endl;
    }
}

void AR600Controller::on_pButtonOpenXML_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(0,"Open XML Dialog","","*.XML *.xml");
    if (!fileName.isEmpty())
    {
        bool isOk = AR600ControllerConf::Instance()->openFile(fileName.toStdString());

        if(isOk)
        {
            ui->hostLineEdit->setText(QString::fromStdString(AR600ControllerConf::Instance()->getHost()));
            ui->portLineEdit->setText(QString::number(AR600ControllerConf::Instance()->getPort()));
            //загоняем в отправляемый массив
            AR600ControllerConf::Instance()->Update(mSendBuffer);
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

void AR600Controller::on_pButtonCFOpen_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(0,"Open Commands List Dialog","","*.txt");
    if (!fileName.isEmpty())
    {
        m_CommandController=new CommandController();
        bool isOk = m_CommandController->LoadFromFile(fileName.toStdString());
        if(isOk)
        {
            qDebug() << "Файл списка команд успешно загружен из " << fileName << endl;
            qDebug() << "Команды успешно прочитаны" <<endl;
        }
        else
        {
            qDebug() << "Файл списка команд не был загружен из " << fileName << endl;
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
    mLogController->SaveData("123.txt");
}
