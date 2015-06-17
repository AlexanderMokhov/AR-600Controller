#ifndef COMMANDSTABLEWIDGET_H
#define COMMANDSTABLEWIDGET_H

#include <QWidget>
#include "CommandsTableModel.h"
#include <QItemSelectionModel>

namespace Ui {
class CommandsTableWidget;
}

class CommandsTableWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CommandsTableWidget(QWidget *parent = 0);
    ~CommandsTableWidget();

    CommandsTableModel *getModel();

    void Clear();
private:
    Ui::CommandsTableWidget *ui;
    CommandsTableModel *mModel;
    QItemSelectionModel *mSelectionModel;
signals:
    void RowChanged(int cRow);
private slots:
    void OnRowChanged();
    void AddRow(QString Description, QString CountRows, QString Duration);
};

#endif // COMMANDSTABLEWIDGET_H
