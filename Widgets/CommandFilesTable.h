#ifndef COMMANDFILESTABLE_H
#define COMMANDFILESTABLE_H

#include <QWidget>
#include <QStringListModel>

class CommandFileItem
{
    QString mName;
    QString mPath;
};

namespace Ui {
class CommandFilesTable;
}

class CommandFilesTable : public QWidget
{
    Q_OBJECT

public:
    explicit CommandFilesTable(QWidget *parent = 0);
    ~CommandFilesTable();

private:
    Ui::CommandFilesTable *ui;
    QStringListModel *mModel;
    QList<CommandFileItem> * mCommandFilesList;
};

#endif // COMMANDFILESTABLE_H
