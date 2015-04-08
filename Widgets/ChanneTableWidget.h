#ifndef CHANNETABLEWIDGET_H
#define CHANNETABLEWIDGET_H

#include <QWidget>
#include "ConfigController.h"
#include "ChannelTableModel.h"
#include <QItemSelectionModel>
#include "BufferController.h"

namespace Ui {
class ChannelTableWidget;
}

class ChannelTableWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ChannelTableWidget(QWidget *parent = 0);
    ~ChannelTableWidget();

    void ShowConfigData();
    ChannelTableModel *getModel();
    void UpdatePos();
private:
    Ui::ChannelTableWidget *ui;
    ChannelTableModel *mModel;
    QItemSelectionModel *mSelectionModel;
public slots:
    //void OnEnterTableRow(QModelIndex Index);
signals:
    void RowChanged(int cRow);
private slots:
    void OnRowChanged(QModelIndex index);
};

#endif // CHANNETABLEWIDGET_H
