#ifndef COMMANDTABLEMODEL_H
#define COMMANDTABLEMODEL_H

#include <QObject>
#include <QAbstractTableModel>
#include <QString>
#include <QList>
#include <QStringList>
struct CommandFile
{
    int Number;
    QString File;
    QString Name;
    int RowsCount;
    double DurationMs;
};

class CommandTableModel : public QAbstractTableModel
{

    Q_OBJECT
public:
    explicit CommandTableModel(QObject *parent = 0);
    ~CommandTableModel();

    QList<CommandFile*> mDataList; // список, в котором хранятся все данные
    QStringList mHeaderData; // список заголовков столбцов

    int rowCount(const QModelIndex &parent=QModelIndex()) const; //метод возвращает количество строк
    int columnCount(const QModelIndex &parent) const; //метод возвращает количество столбцов
    QVariant data(const QModelIndex &index, int role) const; // метод для отображения данных

    // метод требуется для возможности редактирования данных
    bool setData(const QModelIndex & index, const QVariant & value, int role = Qt::EditRole);

    // метод для отображения заголовков столбцов
    QVariant headerData(int section,Qt::Orientation orientation, int role=Qt::DisplayRole) const;
    Qt::ItemFlags flags(const QModelIndex &index) const; // возвращает установленные флаги

    // метод вставляет пустые строки перед текущей позицией
    bool insertRows( int position, int rows,const QModelIndex & index = QModelIndex());
    bool removeRows( int position, int rows,const QModelIndex & index = QModelIndex());

    void insertRow( const QString & Number, const QString & File, const QString & Name, const QString & Rows,
                    const QString & Duration);

signals:
    void editCompleted(const QString &);
public slots:

private:
};

#endif // COMMANDTABLEMODEL_H
