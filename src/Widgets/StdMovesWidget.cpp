#include "StdMovesWidget.h"
#include "ui_StdMovesWidget.h"

StdMovesWidget::StdMovesWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StdMovesWidget)
{
    ui->setupUi(this);

    //Запретить изменение размера окна begin
    setMaximumHeight(sizeHint().height());
    setMaximumWidth(sizeHint().width());
    //Запретить изменение размера окна end
}

StdMovesWidget::~StdMovesWidget()
{
    delete ui;
}

void StdMovesWidget::on_ButtonForward_clicked()
{
    ARCore::Inst()->getMovesStore()->setForwardMoves();
    emit startStdMove();
}

void StdMovesWidget::on_ButtonBack_clicked()
{
    ARCore::Inst()->getMovesStore()->setBackMoves();
    emit startStdMove();
}

void StdMovesWidget::on_pushButton_clicked()
{
    emit stopStdMove();
}
