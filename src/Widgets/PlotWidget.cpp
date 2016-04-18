#include "PlotWidget.h"
#include "ui_PlotWidget.h"

PlotWidget::PlotWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PlotWidget)
{
    ui->setupUi(this);

    ui->customPlot->setInteraction(QCP::iRangeZoom, true);   // Включаем взаимодействие удаления/приближения
    ui->customPlot->setInteraction(QCP::iRangeDrag, true);  // Включаем взаимодействие перетаскивания графика

    ui->customPlot->axisRect()->setRangeDrag(Qt::Horizontal | Qt::Vertical);   // Включаем перетаскивание только по горизонтальной оси
    ui->customPlot->axisRect()->setRangeZoom(Qt::Horizontal | Qt::Vertical);   // Включаем удаление/приближение только по горизонтальной оси

    ui->customPlot->xAxis->setTickLabelType(QCPAxis::ltDateTime);   // Подпись координат по Оси X в качестве Даты и Времени
    ui->customPlot->xAxis->setDateTimeFormat("hh:mm:ss");  // Устанавливаем формат даты и времени

    // Настраиваем шрифт по осям координат
    ui->customPlot->xAxis->setTickLabelFont(QFont(QFont().family(), 8));
    ui->customPlot->yAxis->setTickLabelFont(QFont(QFont().family(), 8));

    // Автоматическое масштабирование тиков по Оси X
    ui->customPlot->xAxis->setAutoTickStep(true);

    connect(ui->customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)),
                this, SLOT(slotRangeChanged(QCPRange)));

    /* Делаем видимыми оси X и Y по верхней и правой границам графика,
    * но отключаем на них тики и подписи координат
    * */
    ui->customPlot->xAxis2->setVisible(true);
    ui->customPlot->yAxis2->setVisible(true);
    ui->customPlot->xAxis2->setTicks(false);
    ui->customPlot->yAxis2->setTicks(false);
    ui->customPlot->xAxis2->setTickLabels(false);
    ui->customPlot->yAxis2->setTickLabels(false);

    ui->customPlot->legend->setVisible(true);   //Включаем Легенду графика
    ui->customPlot->legend->setFont(QFont("Helvetica", 9));

    // Устанавливаем Легенду в левый верхний угол графика
    ui->customPlot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignLeft | Qt::AlignTop);

    // Будем строить график с сегодняшнего дни и текущей секунды в будущее
    double now = QDateTime::currentDateTime().toTime_t();

    for(auto it = SettingsStorage::Inst()->GetMotors()->begin();
        it != SettingsStorage::Inst()->GetMotors()->end(); ++it )
    {
        addGraph((*it).first,(*it).second.getName());
    }

    ui->customPlot->xAxis->setTickStep(2);//шаг между рисками (мс)
    ui->customPlot->axisRect()->setupFullAxesBox();

    setRange(10);

    m_timer = new QTimer;
    m_timer->setInterval(10);
    connect(m_timer,SIGNAL(timeout()),SLOT(drawGraphSlot()),Qt::DirectConnection);
    m_timer->start(10);
}

PlotWidget::~PlotWidget()
{
    delete ui;
}

void PlotWidget::addGraph(uint id, std::string name)
{
    QPen pen;
    pen.setColor(QColor(qSin(id + 1.2)*80+80, qSin(id*0.3+0)*80+80, qSin(id*0.3+1.5)*80+80));

    QCPGraph *graphic = new QCPGraph(ui->customPlot->xAxis, ui->customPlot->yAxis);
    graphic->setName(QString::fromLocal8Bit(name.c_str()));       // Устанавливаем
    graphic->setPen(pen); // Устанавливаем цвет графика
    graphic->setAntialiased(false);         // Отключаем сглаживание, по умолчанию включено
    graphic->setLineStyle(QCPGraph::lsLine);

    ui->customPlot->addPlottable(graphic);  // Устанавливаем график на полотно

    GraphItem item;
    item.graphic = graphic;
    item.name = name;
    m_Graphs[id] = item;
}

void PlotWidget::removeGraph(uint id)
{
    m_Graphs.erase(id);
}

void PlotWidget::setRange(int range)
{
    this->rangeSize = range;
}

void PlotWidget::drawPlot()
{
    // вычислить две новых точки данных:
    double key = QDateTime::currentDateTime().toMSecsSinceEpoch() / 1000.0;
    static double lastPointKey = 0;

    if (key - lastPointKey > 0.05) // добавляем точку каждые 10 мс
    {
        for(auto it = m_Graphs.begin(); it != m_Graphs.end(); ++it)
        {
            double value = ARPacketManager::Inst()->getPacketRecv()->getMotorAngle((*it).first);
            (*it).second.graphic->addData(key, value);
            (*it).second.graphic->removeDataBefore(key - rangeSize);
            (*it).second.graphic->rescaleValueAxis(true);
        }
        lastPointKey = key;
    }
    //ui->customPlot->rescaleAxes();      // Масштабируем график по данным
    ui->customPlot->xAxis->setRange(key + 0.25, rangeSize, Qt::AlignRight);
    ui->customPlot->replot();
}

void PlotWidget::slotRangeChanged(const QCPRange &newRange)
{
    /* Если область видимости графика меньше одного дня,
    * то отображаем часы и минуты по Оси X,
    * в противном случае отображаем дату "День Месяц Год"
    * */
    ui->customPlot->xAxis->setDateTimeFormat((newRange.size() <= 3600)? "mm:ss" : "hh:mm:ss");
}

void PlotWidget::drawGraphSlot()
{
    drawPlot();
}
