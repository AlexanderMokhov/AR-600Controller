#ifndef COMMANDFILESWIDGET_H
#define COMMANDFILESWIDGET_H

#include <QWidget>
#include <QItemSelectionModel>
#include <QMenu>
#include <QDebug>
#include <QInputDialog>

#include "Models/CommandTableModel.h"
#include "Management/ConfigController.h"
#include "Buffers/BufferController.h"
#include "Management/MoveController.h"

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
    CommandTableModel *mModel;
    QItemSelectionModel *mSelectionModel;
    QInputDialog *mSetNameDialog;

    CommandTableModel *getModel();
    void ShowConfigData();
public slots:
    void AddFile(QString fileName,int RowsCount, int Duration, bool mode);
signals:
    void RowChanged(int cRow);
    void fileChosen(QString file, bool mode);
private slots:
    void OnRowChanged();
    void on_FilesTable_doubleClicked(const QModelIndex &index);
    void ShowContextMenu(const QPoint& pos);
    void onDeleteAction();
    void onSetNameAction();
    void onDialogAccepted();
};

#endif // COMMANDFILESWIDGET_H
