#ifndef POWERWIDGET_H
#define POWERWIDGET_H

#include <QWidget>
#include <QTimer>
#include "BufferController.h"
#include <QtTest/QTest>

namespace Ui {
class PowerWidget;
}

class PowerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PowerWidget(QWidget *parent = 0);
    ~PowerWidget();

private slots:
    void on_ButtonOnAll_clicked();

private:
    Ui::PowerWidget *ui;
    QTimer mTimer;//для задержек включения/откулючения напряжений

};

#endif // POWERWIDGET_H
