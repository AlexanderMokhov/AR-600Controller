#ifndef CONNECTIONCONTROLW_H
#define CONNECTIONCONTROLW_H

#include <QWidget>

#include "Management/SettingsStorage.h"

namespace Ui {
class ConnectionControlW;
}

class ConnectionControlW : public QWidget
{
    Q_OBJECT

public:
    explicit ConnectionControlW(QWidget *parent = 0);
    ~ConnectionControlW();

public slots:
    void connectionHandler(bool isConnect);

private slots:
    void on_ButtonConnect_clicked(bool checked);

private:
    Ui::ConnectionControlW *ui;

signals:
    connectEvent(bool);
};

#endif // CONNECTIONCONTROLW_H
