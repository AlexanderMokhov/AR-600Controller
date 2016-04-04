#ifndef LOGWIDGET_H
#define LOGWIDGET_H

#include <QWidget>
#include <QTime>

namespace Ui {
class LogWidget;
}

class LogWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LogWidget(QWidget *parent = 0);
    ~LogWidget();

    void addMessage(QString message);

private:
    Ui::LogWidget *ui;
};

#endif // LOGWIDGET_H
