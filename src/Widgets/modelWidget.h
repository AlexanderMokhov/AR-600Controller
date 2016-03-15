#ifndef MODELWIDGET_H
#define MODELWIDGET_H

#include <QWidget>

namespace Ui {
class modelWidget;
}

class modelWidget : public QWidget
{
    Q_OBJECT

public:
    explicit modelWidget(QWidget *parent = 0);
    ~modelWidget();

private:
    Ui::modelWidget *ui;
};

#endif // MODELWIDGET_H
