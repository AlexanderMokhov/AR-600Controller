#ifndef COMMANDCONTROLLERWIDGET_H
#define COMMANDCONTROLLERWIDGET_H

#include <QWidget>
#include "AR600ControllerConf.h"
#include "BufferController.h"
#include "ChannelTableModel.h"
#include <QFileDialog>
#include "CommandController.h"

namespace Ui {
class CommandControllerWidget;
}

class CommandControllerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CommandControllerWidget(QWidget *parent = 0);
    ~CommandControllerWidget();

private slots:
    void on_ButtonLoadFile_clicked();

    void on_ButtonPlayPause_clicked();

    void on_ButtonStop_clicked();

private:
    Ui::CommandControllerWidget *ui;
    QString Defaulttext;
signals:
    void StartPlayForward();
};

#endif // COMMANDCONTROLLERWIDGET_H
