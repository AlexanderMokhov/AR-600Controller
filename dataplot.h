#ifndef DATAPLOT_H
#define DATAPLOT_H

#include <QObject>
#include "qcustomplot.h"
class DataPlot : public QObject
{
    Q_OBJECT
public:
    explicit DataPlot(QObject *parent = 0);
    ~DataPlot();
    void setPlotWidget(QCustomPlot *plot);
    void draw();
    void play();
    int AddGraph(Qt::GlobalColor color);
    void RemoveGraph(int id);
    void setLenght(int size);
    void DrawPower();
    QCustomPlot *mPlot;
    int RangeSize;
signals:

public slots:

private:


};

#endif // DATAPLOT_H
