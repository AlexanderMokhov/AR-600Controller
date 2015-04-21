#ifndef COMMANDCONTROLLERWIDGET_H
#define COMMANDCONTROLLERWIDGET_H

#include <QWidget>
#include "ConfigController.h"
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

    void on_ButtonNext_clicked();

    void on_checkBoxLog_clicked(bool checked);

private:
    Ui::CommandControllerWidget *ui;
    QString DefaultText;
    bool IsLog;
signals:
    StartWriteLog(int LogTime);
    StopWriteLog();
    FileLoaded();
};

#endif // COMMANDCONTROLLERWIDGET_H
