#ifndef ADDITIONCONTROLW_H
#define ADDITIONCONTROLW_H

#include <QWidget>

namespace Ui {
class AdditionControlW;
}

class AdditionControlW : public QWidget
{
    Q_OBJECT

public:
    explicit AdditionControlW(QWidget *parent = 0);
    ~AdditionControlW();

private:
    Ui::AdditionControlW *ui;
};

#endif // ADDITIONCONTROLW_H
