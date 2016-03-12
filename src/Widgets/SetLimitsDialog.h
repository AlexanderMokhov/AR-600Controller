#ifndef SETLIMITSDIALOG_H
#define SETLIMITSDIALOG_H

#include <QDialog>

#include "Management/SettingsStorage.h"
#include "Buffers/BufferController.h"

namespace Ui {
class SetLimitsDialog;
}

class SetLimitsDialog : public QDialog
{
    Q_OBJECT
public:
    //public methods
    explicit SetLimitsDialog(QWidget *parent = 0);
    ~SetLimitsDialog();
    void Update(int cNumber);

public slots:
    void accepted();

private:
    //private variable
    Ui::SetLimitsDialog *ui;
    int cNumber;
};

#endif // SETLIMITSDIALOG_H
