#ifndef SETLIMITSDIALOG_H
#define SETLIMITSDIALOG_H

#include <QDialog>

#include "Management/ConfigController.h"
#include "Buffers/BufferController.h"

namespace Ui {
class SetLimitsDialog;
}

class SetLimitsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SetLimitsDialog(QWidget *parent = 0);
    ~SetLimitsDialog();
    void Update(int cNumber);

private:
    Ui::SetLimitsDialog *ui;
    int cNumber;
public slots:
    void accepted();
};

#endif // SETLIMITSDIALOG_H
