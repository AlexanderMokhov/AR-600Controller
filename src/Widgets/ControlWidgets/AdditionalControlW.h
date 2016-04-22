#ifndef ADDITIONALCONTROLW_H
#define ADDITIONALCONTROLW_H

#include <QWidget>

namespace Ui {
class AdditionalControlW;
}

class AdditionalControlW : public QWidget
{
    Q_OBJECT

public:
    explicit AdditionalControlW(QWidget *parent = 0);
    ~AdditionalControlW();

private:
    Ui::AdditionalControlW *ui;
};

#endif // ADDITIONALCONTROLW_H
