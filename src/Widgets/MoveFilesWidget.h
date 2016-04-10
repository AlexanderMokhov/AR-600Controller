#ifndef MOVEFILESWIDGET_H
#define MOVEFILESWIDGET_H

#include <QWidget>
#include <QItemSelectionModel>
#include <QMenu>
#include <QDebug>
#include <QInputDialog>

#include "Models/CommandTableModel.h"
#include "Management/ARCore.h"
#include "Buffers/BufferController.h"
#include "Management/MoveController.h"

namespace Ui {
class MoveFilesWidget;
}

class MoveFilesWidget : public QWidget
{
    Q_OBJECT
public:
    //public methods
    explicit MoveFilesWidget(QWidget *parent = 0);
    ~MoveFilesWidget();

signals:
    void RowChanged(int cRow);
    void fileChosen(QString file, bool mode);

public slots:
    void AddFile(QString fileName,int RowsCount, int Duration, bool mode);

private slots:
    void OnRowChanged();
    void on_FilesTable_doubleClicked(const QModelIndex &index);
    void ShowContextMenu(const QPoint& pos);
    void onDeleteAction();
    void onSetNameAction();
    void onDialogAccepted();

private:
    //private variable
    Ui::MoveFilesWidget *ui;
    CommandTableModel *mModel;
    QItemSelectionModel *mSelectionModel;
    QInputDialog *mSetNameDialog;

    //private methods
    CommandTableModel *getModel();
    void ShowConfigData();
};

#endif // MOVEFILESWIDGET_H
