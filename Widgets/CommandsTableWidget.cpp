#include "CommandsTableWidget.h"
#include "ui_CommandsTableWidget.h"

CommandsTableWidget::CommandsTableWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CommandsTableWidget)
{
    ui->setupUi(this);

    //заполнение таблицы приводов
    mModel = new CommandsTableModel();
    ui->CommandsTable->setModel(mModel);

    mSelectionModel = ui->CommandsTable->selectionModel();

    ui->CommandsTable->verticalHeader()->hide();
    ui->CommandsTable->verticalHeader()->resizeSections(QHeaderView::Fixed);
    ui->CommandsTable->resizeColumnsToContents();
    ui->CommandsTable->horizontalHeader()->setSectionResizeMode(1,QHeaderView::Stretch);
    ui->CommandsTable->horizontalHeader()->setSectionResizeMode(2,QHeaderView::Stretch);
    ui->CommandsTable->setEditTriggers(QAbstractItemView::NoEditTriggers);

    connect(ui->CommandsTable,SIGNAL(clicked(QModelIndex)),this,SLOT(OnRowChanged()));
}

CommandsTableWidget::~CommandsTableWidget()
{
    delete ui;
}

CommandsTableModel *CommandsTableWidget::getModel()
{
    return mModel;
}

void CommandsTableWidget::Clear()
{
    mModel->removeRows(0,mModel->rowCount());
}

void CommandsTableWidget::AddRow(QString Description, QString CountRows, QString Duration)
{
    QString Number = QString::number(mModel->rowCount());
    mModel->insertRow(Number,Description,CountRows,Duration);

    ui->CommandsTable->selectRow(0);
    emit RowChanged(0);
}

//происходит при выборе строки в талице моторов
void CommandsTableWidget::OnRowChanged()
{
    int cRow = mSelectionModel->currentIndex().row();
    emit RowChanged(cRow);
}
