#include "CommandFilesWidget.h"
#include "ui_CommandFilesWidget.h"

CommandFilesWidget::CommandFilesWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CommandFilesWidget)
{
    ui->setupUi(this);
}

CommandFilesWidget::~CommandFilesWidget()
{
    delete ui;
}
