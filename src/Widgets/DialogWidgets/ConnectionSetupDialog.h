#ifndef CONNECTIONSETUPDIALOG_H
#define CONNECTIONSETUPDIALOG_H

#include <QDialog>

#include "Management/SettingsStorage.h"

namespace Ui {
class ConnectionSetupDialog;
}

class ConnectionSetupDialog : public QDialog
{
    Q_OBJECT
public:
    //public methods
    explicit ConnectionSetupDialog(QWidget *parent = 0);
    ~ConnectionSetupDialog();
    void Update();

private:
    //private variable
    Ui::ConnectionSetupDialog *ui;
    QString mHost;
    int mSendPort;
    int mReceivePort;
public slots:
    void accepted();
};

#endif // CONNECTIONSETUPDIALOG_H
