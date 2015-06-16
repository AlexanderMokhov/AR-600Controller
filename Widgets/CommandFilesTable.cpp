#include "CommandFilesTable.h"
#include "ui_CommandFilesTable.h"

CommandFilesTable::CommandFilesTable(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CommandFilesTable)
{
    ui->setupUi(this);
    mModel = new QStringListModel(this);
    mCommandFilesList = new QList<CommandFileItem>();

}

CommandFilesTable::~CommandFilesTable()
{
    delete ui;
}
