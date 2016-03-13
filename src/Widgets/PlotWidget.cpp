#include "PlotWidget.h"
#include "ui_PlotWidget.h"

PlotWidget::PlotWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PlotWidget)
{
    ui->setupUi(this);

    ui->customPlot->setInteraction(QCP::iRangeZoom,true);   // Включаем взаимодействие удаления/приближения
    ui->customPlot->setInteraction(QCP::iRangeDrag, true);  // Включаем взаимодействие перетаскивания графика

    ui->customPlot->axisRect()->setRangeDrag(Qt::Horizontal);   // Включаем перетаскивание только по горизонтальной оси
    ui->customPlot->axisRect()->setRangeZoom(Qt::Horizontal);   // Включаем удаление/приближение только по горизонтальной оси

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
    ui->customPlot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignRight | Qt::AlignTop);

    // Будем строить график с сегодняшнего дни и текущей секунды в будущее
    double now = QDateTime::currentDateTime().toTime_t();

    // Объявляем вектора времени и доходов
    QVector <double> time(400), income(400);

    srand(15); // Инициализируем генератор псевдослучайных чисел

    // Заполняем график значениями
    for (int i = 0; i < 400; i++)
    {
        time[i] = now + i;
        income[i] = i;
    }
    QPen pen;
    pen.setColor(QColor(qSin(1*1+1.2)*80+80, qSin(1*0.3+0)*80+80, qSin(1*0.3+1.5)*80+80));

    ui->customPlot->addGraph();
    ui->customPlot->graph()->setPen(pen);
    ui->customPlot->graph()->setName("Напряжение");
    ui->customPlot->graph()->setLineStyle(QCPGraph::lsLine);
    ui->customPlot->graph()->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 5));

    // generate data:
    ui->customPlot->graph()->setData(time, income); // Устанавливаем данные
    ui->customPlot->graph()->rescaleAxes(true);      // Масштабируем график по данным
    ui->customPlot->replot();           // Отрисовываем график

//    QPen pen;
//    QStringList lineNames;
//    lineNames << "Линия";

//    ui->_QCustomPlotWidget->addGraph();
//    pen.setColor(QColor(qSin(1*1+1.2)*80+80, qSin(1*0.3+0)*80+80, qSin(1*0.3+1.5)*80+80));
//    ui->_QCustomPlotWidget->graph()->setPen(pen);
//    ui->_QCustomPlotWidget->graph()->setName(lineNames.at(0));
//    ui->_QCustomPlotWidget->graph()->setLineStyle(QCPGraph::lsLine);
//    ui->_QCustomPlotWidget->graph()->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 5));
//    // generate data:
//    QVector<double> x(200), y(200);
//    for (int j=0; j<200; ++j)
//    {
//    x[j] = j/15.0 * 5*3.14 + 0.01;
//    y[j] = 7*qSin(x[j])/x[j] + (QCPGraph::lsImpulse)*5 + 2;
//    }
//    ui->_QCustomPlotWidget->graph()->setData(x, y);
//    ui->_QCustomPlotWidget->graph()->rescaleAxes(true);

//    // zoom out a bit:
    ui->customPlot->yAxis->scaleRange(1.1, ui->customPlot->yAxis->range().center());
    ui->customPlot->xAxis->scaleRange(1.1, ui->customPlot->xAxis->range().center());
//    // set blank axis lines:

    ui->customPlot->xAxis->setTickStep(2);//шаг между рисками (мс)
    ui->customPlot->axisRect()->setupFullAxesBox();

//    // make top right axes clones of bottom left axes:
//    ui->_QCustomPlotWidget->axisRect()->setupFullAxesBox();
}

PlotWidget::~PlotWidget()
{
    delete ui;


}

void PlotWidget::addGraph(uint id, std::string name)
{
    //GraphItem item;

    //item.graph = QCPGraph();
    //item.name = name;

    //m_Graphs[id] = item;
}

void PlotWidget::removeGraph(uint id)
{
    m_Graphs.erase(id);
}

void PlotWidget::slotRangeChanged(const QCPRange &newRange)
{
    /* Если область видимости графика меньше одного дня,
    * то отображаем часы и минуты по Оси X,
    * в противном случае отображаем дату "День Месяц Год"
    * */
    ui->customPlot->xAxis->setDateTimeFormat((newRange.size() <= 3600)? "mm:ss" : "hh:mm:ss");
}
