#ifndef CONNECTIONCONTROLW_H
#define CONNECTIONCONTROLW_H

#include <QWidget>

namespace Ui {
class ConnectionControlW;
}

class ConnectionControlW : public QWidget
{
    Q_OBJECT

public:
    explicit ConnectionControlW(QWidget *parent = 0);
    ~ConnectionControlW();

private:
    Ui::ConnectionControlW *ui;
};

#endif // CONNECTIONCONTROLW_H
