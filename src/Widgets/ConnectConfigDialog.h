#ifndef CONNECTCONFIGDIALOG_H
#define CONNECTCONFIGDIALOG_H

#include <QDialog>

#include "Management/SettingsStorage.h"

namespace Ui {
class ConnectConfigDialog;
}

class ConnectConfigDialog : public QDialog
{
    Q_OBJECT
public:
    //public methods
    explicit ConnectConfigDialog(QWidget *parent = 0);
    ~ConnectConfigDialog();
    void Update();

private:
    //private variable
    Ui::ConnectConfigDialog *ui;
    QString mHost;
    int mSendPort;
    int mReceivePort;
public slots:
    void accepted();
};

#endif // CONNECTCONFIGDIALOG_H
