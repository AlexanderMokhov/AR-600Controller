#ifndef NEWMAINW_H
#define NEWMAINW_H

#include <QWidget>

namespace Ui {
class NewMainW;
}

class NewMainW : public QWidget
{
    Q_OBJECT

public:
    explicit NewMainW(QWidget *parent = 0);
    ~NewMainW();

private:
    Ui::NewMainW *ui;
};

#endif // NEWMAINW_H
