#ifndef COMMANDFILESWIDGET_H
#define COMMANDFILESWIDGET_H

#include <QWidget>

namespace Ui {
class CommandFilesWidget;
}

class CommandFilesWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CommandFilesWidget(QWidget *parent = 0);
    ~CommandFilesWidget();

private:
    Ui::CommandFilesWidget *ui;
};

#endif // COMMANDFILESWIDGET_H
