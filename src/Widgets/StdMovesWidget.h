#ifndef STDMOVESWIDGET_H
#define STDMOVESWIDGET_H

#include <QWidget>

#include "Management/MoveStorage.h"
#include "Widgets/MoveControlWidget.h"

namespace Ui {
class StdMovesWidget;
}

class StdMovesWidget : public QWidget
{
    Q_OBJECT

public:
    explicit StdMovesWidget(QWidget *parent = 0);
    ~StdMovesWidget();

private slots:
    void on_ButtonForward_clicked();
    void on_ButtonBack_clicked();
    void on_pushButton_clicked();

private:
    Ui::StdMovesWidget *ui;

signals:
    void startStdMove();
    void stopStdMove();
};

#endif // STDMOVESWIDGET_H
