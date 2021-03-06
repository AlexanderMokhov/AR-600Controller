#include "MoveFilesWidget.h"
#include "ui_MoveFilesWidget.h"

MoveFilesWidget::MoveFilesWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MoveFilesWidget)
{
    ui->setupUi(this);

    //заполнение таблицы приводов
    mModel = new CommandTableModel();
    ui->FilesTable->setModel(mModel);

    mSelectionModel = ui->FilesTable->selectionModel();
    mSetNameDialog = new QInputDialog();
    mSetNameDialog->setWindowTitle("Задать название");
    mSetNameDialog->setLabelText("Введите новое название:");
    mSetNameDialog->setModal(true);

    ui->FilesTable->verticalHeader()->hide();
    ui->FilesTable->verticalHeader()->resizeSections(QHeaderView::Fixed);
    ui->FilesTable->resizeColumnsToContents();
    ui->FilesTable->horizontalHeader()->setSectionResizeMode(1,QHeaderView::Stretch);
    ui->FilesTable->horizontalHeader()->setSectionResizeMode(2,QHeaderView::Stretch);
    ui->FilesTable->setEditTriggers(QAbstractItemView::NoEditTriggers);

    mModel->removeRows(0,mModel->rowCount());
    ui->FilesTable->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->FilesTable, SIGNAL(customContextMenuRequested(const QPoint&)),
        this, SLOT(ShowContextMenu(const QPoint&)));
    connect(mSetNameDialog,SIGNAL(accepted()),this,SLOT(onDialogAccepted()));

}

MoveFilesWidget::~MoveFilesWidget()
{
    delete ui;
}

CommandTableModel *MoveFilesWidget::getModel()
{
    return mModel;
}

void MoveFilesWidget::ShowConfigData()
{
    ;
}

void MoveFilesWidget::AddFile(QString fileName,int RowsCount, int Duration, bool mode)
{
    if(mode)
    {
        double DurationSec = (double)Duration/1e6;
        mModel->insertRow(QString::number(mModel->rowCount()+1),
                          fileName,
                          fileName,
                          QString::number(RowsCount),
                          QString::number(DurationSec));
    }
}

void MoveFilesWidget::OnRowChanged()
{

}

void MoveFilesWidget::on_FilesTable_doubleClicked(const QModelIndex &index)
{
    if(mModel->rowCount() == 0) return;
    emit fileChosen(mModel->mDataList.at(
                        mSelectionModel->currentIndex().row())->FileName, false );
}

void MoveFilesWidget::ShowContextMenu(const QPoint &pos)
{
    if( mModel->rowCount() == 0 ) return;

    QPoint globalPos = ui->FilesTable->mapToGlobal(pos);

    QMenu myMenu;
    QAction *SetNameAction = new QAction(tr("Задать название"), this);
    QAction *DeleteAction = new QAction(tr("Удалить"), this);

    connect(DeleteAction,SIGNAL(triggered()),SLOT(onDeleteAction()));
    connect(SetNameAction,SIGNAL(triggered()),SLOT(onSetNameAction()));

    myMenu.addAction(SetNameAction);
    myMenu.addAction(DeleteAction);

    myMenu.exec(globalPos);
}

void MoveFilesWidget::onDeleteAction()
{
    mModel->removeRow(mSelectionModel->currentIndex().row(), mSelectionModel->currentIndex());
}

void MoveFilesWidget::onSetNameAction()
{
    QString name = mModel->mDataList.at(mSelectionModel->currentIndex().row())->Description;
    mSetNameDialog->setTextValue(name);
    mSetNameDialog->show();
}

void MoveFilesWidget::onDialogAccepted()
{
    if(!mSetNameDialog->textValue().isEmpty())
    {
        mModel->mDataList.at(mSelectionModel->currentIndex().row())->Description = mSetNameDialog->textValue();
    }
}
