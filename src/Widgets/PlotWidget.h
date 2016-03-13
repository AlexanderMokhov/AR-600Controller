#ifndef PLOTWIDGET_H
#define PLOTWIDGET_H

#include <QWidget>

#include "Libs/QCustomPlot/qcustomplot.h"

namespace Ui {
class PlotWidget;
}

struct GraphItem
{
    QCPGraph graph;
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

private slots:
    void slotRangeChanged (const QCPRange &newRange);

private:
    Ui::PlotWidget *ui;
    std::map<int, GraphItem> m_Graphs;
};

#endif // PLOTWIDGET_H
