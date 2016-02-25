#include "StdMovesWidget.h"
#include "ui_StdMovesWidget.h"

StdMovesWidget::StdMovesWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StdMovesWidget)
{
    ui->setupUi(this);
}

StdMovesWidget::~StdMovesWidget()
{
    delete ui;
}

void StdMovesWidget::on_ButtonForward_clicked()
{
    MoveStorage::Inst()->setForwardMoves();
    emit startStdMove();
}

void StdMovesWidget::on_ButtonBack_clicked()
{
    MoveStorage::Inst()->setBackMoves();
    emit startStdMove();
}

void StdMovesWidget::on_pushButton_clicked()
{
    emit stopStdMove();
}
