#ifndef MOVEFILESWIDGET_H
#define MOVEFILESWIDGET_H

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
class MoveFilesWidget;
}

class MoveFilesWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MoveFilesWidget(QWidget *parent = 0);
    ~MoveFilesWidget();

private:
    Ui::MoveFilesWidget *ui;
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

#endif // MOVEFILESWIDGET_H
