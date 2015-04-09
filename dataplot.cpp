#include "DataPlot.h"


DataPlot::DataPlot(QObject *parent) : QObject(parent)
{
    RangeSize=10;
    mPlot->xAxis->setTickLabelType(QCPAxis::ltDateTime);
    mPlot->xAxis->setDateTimeFormat("mm:ss");
    mPlot->xAxis->setAutoTickStep(false);
    mPlot->xAxis->setTickStep(2);//шаг между рисками (мс)
    mPlot->axisRect()->setupFullAxesBox();
}

DataPlot::~DataPlot()
{

}

void DataPlot::setPlotWidget(QCustomPlot *plot)
{
    this->mPlot=plot;
}

void DataPlot::draw()
{
    mPlot->addGraph(); // синяя линия
    mPlot->graph(0)->setPen(QPen(Qt::blue));
    mPlot->addGraph(); // красная линия
    mPlot->graph(1)->setPen(QPen(Qt::red));

    mPlot->xAxis->setTickLabelType(QCPAxis::ltDateTime);
    mPlot->xAxis->setDateTimeFormat("mm:ss");
    mPlot->xAxis->setAutoTickStep(false);
    mPlot->xAxis->setTickStep(2);//шаг между рисками (мс)
    mPlot->axisRect()->setupFullAxesBox();


}

void DataPlot::play()
{
    // вычислить две новых точки данных:
    double key = QDateTime::currentDateTime().toMSecsSinceEpoch()/1000.0;
    static double lastPointKey = 0;
    if (key-lastPointKey > 0.01) // at most add point every 10 ms
    {
      double value0 = qSin(key);
      double value1 = qCos(key);
      // добавить данные в линию:
      mPlot->graph(0)->addData(key, value0);
      mPlot->graph(1)->addData(key, value1);

      // Удаление данных линии, что за пределами видимого диапазона:
      mPlot->graph(0)->removeDataBefore(key-RangeSize);
      mPlot->graph(1)->removeDataBefore(key-RangeSize);
      // масштабировать значение (вертикальное) в соответствии с текущими данными:
      mPlot->graph(0)->rescaleValueAxis();
      mPlot->graph(1)->rescaleValueAxis(true);
      lastPointKey = key;
    }
    // make key axis range scroll with the data (at a constant range size of 8):
    mPlot->xAxis->setRange(key+0.25, RangeSize, Qt::AlignRight);
    mPlot->replot();
}

//добавляем новый график на Плот, возвращаем номер этого графика
int DataPlot::AddGraph(Qt::GlobalColor color)
{
    mPlot->addGraph();
    int currentGraph = mPlot->graphCount()-1;
    mPlot->graph(currentGraph)->setPen(QPen(color));
    return currentGraph;
}

//удаляем график с текушим id
void DataPlot::RemoveGraph(int id)
{
    mPlot->removeGraph(mPlot->graph(id));
}

void DataPlot::setLenght(int size)
{
    this->RangeSize=size;
}

