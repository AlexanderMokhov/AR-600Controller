#ifndef PLOTWIDGET_H
#define PLOTWIDGET_H

#include <QWidget>
#include <QDebug>
#include <QTime>

#include "Buffers/BufferController.h"
#include "Management/ARCore.h"

#include "Libs/QCustomPlot/qcustomplot.h"

namespace Ui {
class PlotWidget;
}

struct GraphItem
{
    QCPGraph *graphic;
    std::string name;
};

class PlotWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PlotWidget(QWidget *parent = 0);
    ~PlotWidget();

    void addGraph(uint id, std::string name);
    void removeGraph(uint id);
    void setRange(int range);
    void drawPlot();

private slots:
    void slotRangeChanged (const QCPRange &newRange);
    void drawGraphSlot();

private:
    Ui::PlotWidget *ui;
    std::map<int, GraphItem> m_Graphs;
    int rangeSize;
    QTimer * m_timer;

};

#endif // PLOTWIDGET_H
