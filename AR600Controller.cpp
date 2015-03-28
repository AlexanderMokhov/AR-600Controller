#include "AR600Controller.h"
#include "ui_AR600Controller.h"
#include "dataplot.h"
#include <QMessageBox>
#include "string.h"


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

    //mTimer2 = new QTimer(this);
    // setup a timer that repeatedly calls MainWindow::realtimeDataSlot:
    //connect(mTimer2, SIGNAL(timeout()), this, SLOT(realtimeDataSlot()));
    //mTimer2->start(100); // Interval 0 means to refresh as fast as possible

    mSendBuffer.init();

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
    AR600ContollerConf::Instance()->initialize();
    bool isOk = AR600ContollerConf::Instance()->openFile("config.xml");
    if(isOk)
    {
        ui->hostLineEdit->setText(QString::fromStdString(AR600ContollerConf::Instance()->getHost()));
        ui->portLineEdit->setText(QString::number(AR600ContollerConf::Instance()->getPort()));
        qDebug() << "Настройки успешно прочитаны";
    }
}

AR600Controller::~AR600Controller()
{
    delete ui;
}



void AR600Controller::Connect()
{
    mSendBuffer.init();
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
    mSendBuffer.init();

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
        mSendBuffer.ON48();
    }
    else
    {
        mSendBuffer.OFF48();
    }
}

void AR600Controller::On8V1Slot(bool value)
{
    if(value)
    {
        mSendBuffer.ON81();
    }
    else
    {
        mSendBuffer.OFF81();
    }
}

void AR600Controller::On8V2Slot(bool value)
{
    if(value)
    {
        mSendBuffer.ON82();
    }
    else
    {
        mSendBuffer.OFF82();
    }
}

void AR600Controller::On6V1Slot(bool value)
{
    if(value)
    {
        mSendBuffer.ON61();
    }
    else
    {
        mSendBuffer.OFF61();
    }
}

void AR600Controller::On6V2Slot(bool value)
{
    if(value)
    {
        mSendBuffer.ON62();
    }
    else
    {
        mSendBuffer.OFF62();
    }
}

void AR600Controller::UdpSend()
{
    SetConfigData();
    mSendBuffer.AddressUpdate(1,1);
    mSendBuffer.AddressUpdate(2,2);

    mSendBuffer.MOTOR_STIFF_set(1,100);
    mSendBuffer.MOTOR_POS_MIN_set(1,-500);
    mSendBuffer.MOTOR_POS_MAX_set(1,500);

    mSendBuffer.MOTOR_STIFF_set(2,100);
    mSendBuffer.MOTOR_POS_MIN_set(2,-700);
    mSendBuffer.MOTOR_POS_MAX_set(2,700);



    qDebug() << "Send" << mSendBuffer.GetBuffer();

    mUdpSocketSender->writeDatagram(mSendBuffer.GetBuffer(), mSendBuffer.GetSize()* sizeof(char), QHostAddress(QString::fromStdString(mHost)), mPort);
    mUdpSocketSender->waitForBytesWritten();

}

void AR600Controller::AddRow()
{
    int countRows= ui->dataTable->rowCount();
    ui->dataTable->insertRow(countRows);
    QTableWidgetItem *item;
        // Записываем в 1-ю ячейку
        item = new  QTableWidgetItem();
        item->setText(QString("Мотор"));
        ui->dataTable->setItem(countRows, 0, item);
        // Записываем вo 2-ю ячейку
        item = new QTableWidgetItem(QString::number(0));
        item->setTextAlignment(Qt::AlignCenter);
        ui->dataTable->setItem(countRows, 1, item);
        // Записываем вo 3-ю ячейку
        item = new QTableWidgetItem(QString::number(15));
        item->setTextAlignment(Qt::AlignCenter);
        ui->dataTable->setItem(countRows, 2, item);
        // Выделяем добавленную
        ui->dataTable->setCurrentCell(countRows, 0);
}

void AR600Controller::SetLenght(double lenght)
{
    this->RangeSize = (int)lenght;
}


void AR600Controller::ProcessTheDatagram(QByteArray &datagramm)
{
    mResiverBuffer.init(datagramm.data());
    UpdatePowerLabel();

    for (unsigned int i = 1; i < 3; i++)
    {
        qDebug()     << "Pos [" << i << "]: "<< mResiverBuffer.MOTOR_CPOS_get(i) <<  " "
                     << mResiverBuffer.MOTOR_POS_MIN_get(i) <<  " "
                     << mResiverBuffer.MOTOR_POS_MAX_get(i) << " "
                     << mResiverBuffer.MOTOR_U_get(i) << " "
                     << mResiverBuffer.MOTOR_I_get(i)<< " "
                     << mResiverBuffer.MOTOR_STAT_get(i);

    }
    /*
    qDebug()     << "Pos [19]: "<< mResiverBuffer.MOTOR_CPOS_get(25) <<  " "
                 << mResiverBuffer.MOTOR_POS_MIN_get(25) <<  " "
                 << mResiverBuffer.MOTOR_POS_MAX_get(25) << " "
                 << mResiverBuffer.MOTOR_U_get(25) << " "
                 << mResiverBuffer.MOTOR_I_get(25)<< " "
                 << mResiverBuffer.MOTOR_STAT_get(25);


    qDebug()     << "Pos [20]: "<< mResiverBuffer.MOTOR_CPOS_get(27) <<  " "
                 << mResiverBuffer.MOTOR_POS_MIN_get(27) <<  " "
                 << mResiverBuffer.MOTOR_POS_MAX_get(27) << " "
                 << mResiverBuffer.MOTOR_U_get(27) << " "
                 << mResiverBuffer.MOTOR_I_get(27)<< " "
                 << mResiverBuffer.MOTOR_STAT_get(27);

    qDebug()     << "Pos [35]: "<< mResiverBuffer.MOTOR_CPOS_get(36) <<  " "
                 << mResiverBuffer.MOTOR_POS_MIN_get(36) <<  " "
                 << mResiverBuffer.MOTOR_POS_MAX_get(36) << " "
                 << mResiverBuffer.MOTOR_U_get(36) << " "
                 << mResiverBuffer.MOTOR_I_get(36)<< " "
                 << mResiverBuffer.MOTOR_STAT_get(36);

*/

}

void AR600Controller::UpdatePowerLabel()
{
    ui->label_48V->setText(QString::number(mResiverBuffer.GetU48()));
    ui->label_48A->setText(QString::number(mResiverBuffer.GetI48()));

    ui->label_81V->setText(QString::number(mResiverBuffer.GetU81()));
    ui->label_81A->setText(QString::number(mResiverBuffer.GetI81()));

    ui->label_82V->setText(QString::number(mResiverBuffer.GetU82()));
    ui->label_82A->setText(QString::number(mResiverBuffer.GetI82()));

    ui->label_61V->setText(QString::number(mResiverBuffer.GetU61()));
    ui->label_61A->setText(QString::number(mResiverBuffer.GetI61()));

    ui->label_62V->setText(QString::number(mResiverBuffer.GetU62()));
    ui->label_62A->setText(QString::number(mResiverBuffer.GetI62()));

}

void AR600Controller::realtimeData()
{
    double key = QDateTime::currentDateTime().toMSecsSinceEpoch()/1000.0;
    ui->Plot->graph(0)->addData(key, mResiverBuffer.GetU48());
    ui->Plot->graph(1)->addData(key, mResiverBuffer.GetU81());
    ui->Plot->graph(2)->addData(key, mResiverBuffer.GetU82());
    ui->Plot->graph(3)->addData(key, mResiverBuffer.GetU61());
    ui->Plot->graph(4)->addData(key, mResiverBuffer.GetU62());


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

//TODO задать номер привода задать читать значения
//сенсоры
