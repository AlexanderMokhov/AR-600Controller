#ifndef STDMOVESWIDGET_H
#define STDMOVESWIDGET_H

#include <QWidget>

#include "Management/MovesStorage.h"
#include "Widgets/MoveControlWidget.h"

namespace Ui {
class StdMovesWidget;
}

class StdMovesWidget : public QWidget
{
    Q_OBJECT
public:
    //public methods
    explicit StdMovesWidget(QWidget *parent = 0);
    ~StdMovesWidget();

signals:
    void startStdMove();
    void stopStdMove();

private slots:
    void on_ButtonForward_clicked();
    void on_ButtonBack_clicked();
    void on_pushButton_clicked();

private:
    //private variable
    Ui::StdMovesWidget *ui;
};

#endif // STDMOVESWIDGET_H
