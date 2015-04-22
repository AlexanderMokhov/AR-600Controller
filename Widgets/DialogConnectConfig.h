#ifndef DIALOGCONNECTCONFIG_H
#define DIALOGCONNECTCONFIG_H

#include <QDialog>
#include "ConfigController.h"

namespace Ui {
class DialogConnectConfig;
}

class DialogConnectConfig : public QDialog
{
    Q_OBJECT

public:
    explicit DialogConnectConfig(QWidget *parent = 0);
    ~DialogConnectConfig();
    void Update();

private:
    Ui::DialogConnectConfig *ui;
    QString mHost;
    int mSendPort;
    int mReceivePort;
public slots:
    accepted();
};

#endif // DIALOGCONNECTCONFIG_H
