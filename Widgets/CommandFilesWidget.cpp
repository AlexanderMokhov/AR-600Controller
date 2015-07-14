#include "CommandFilesWidget.h"
#include "ui_CommandFilesWidget.h"

CommandFilesWidget::CommandFilesWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CommandFilesWidget)
{
    ui->setupUi(this);

    //заполнение таблицы приводов
    mModel = new CommandTableModel();
    ui->FilesTable->setModel(mModel);

    mSelectionModel = ui->FilesTable->selectionModel();

    ui->FilesTable->verticalHeader()->hide();
    ui->FilesTable->verticalHeader()->resizeSections(QHeaderView::Fixed);
    ui->FilesTable->resizeColumnsToContents();
    ui->FilesTable->horizontalHeader()->setSectionResizeMode(1,QHeaderView::Stretch);
    ui->FilesTable->setEditTriggers(QAbstractItemView::NoEditTriggers);

    mModel->removeRows(0,mModel->rowCount());
    ui->FilesTable->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->FilesTable, SIGNAL(customContextMenuRequested(const QPoint&)),
        this, SLOT(ShowContextMenu(const QPoint&)));

}

CommandFilesWidget::~CommandFilesWidget()
{
    delete ui;
}

CommandTableModel *CommandFilesWidget::getModel()
{
    return mModel;
}

void CommandFilesWidget::ShowConfigData()
{
    ;
}

void CommandFilesWidget::AddFile(QString fileName,int RowsCount, int Duration, bool mode)
{
    if(mode)
    {
        double DurationSec = (double)Duration/1e6;
        mModel->insertRow(QString::number(mModel->rowCount()+1),fileName,QString::number(RowsCount),QString::number(DurationSec));
    }
}

void CommandFilesWidget::OnRowChanged()
{

}

void CommandFilesWidget::on_FilesTable_doubleClicked(const QModelIndex &index)
{
    if(mModel->rowCount() == 0)     return;
    emit fileChosen(mModel->mDataList.at(mSelectionModel->currentIndex().row())->Name, false);

}

void CommandFilesWidget::ShowContextMenu(const QPoint &pos)
{
    if(mModel->rowCount() == 0)     return;
    QPoint globalPos = ui->FilesTable->mapToGlobal(pos);

    QMenu myMenu;
    myMenu.addAction("Удалить");

    QAction* selectedItem = myMenu.exec(globalPos);
    if (selectedItem)
    {
        mModel->removeRow(mSelectionModel->currentIndex().row(),mSelectionModel->currentIndex());
        // something was chosen, do stuff
    }
    else
    {
        qDebug() << "nothing was chosen";
    }
}
