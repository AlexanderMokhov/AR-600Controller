#ifndef COMMANDTABLEMODEL_H
#define COMMANDTABLEMODEL_H

#include <QObject>
#include <QAbstractTableModel>
#include <QString>
#include <QList>
#include <QStringList>

struct Move_File
{
    int Number;
    QString FileName;
    QString Description;
    int RowsCount;
    double Duration;
};

class CommandTableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    //public methods
    explicit CommandTableModel(QObject *parent = 0);
    ~CommandTableModel();

    QList<Move_File*> mDataList; // список, в котором хранятся все данные
    QStringList mHeaderData; // список заголовков столбцов

    int rowCount(const QModelIndex &parent = QModelIndex()) const; //количество строк
    int columnCount(const QModelIndex &parent) const; //количество столбцов
    QVariant data(const QModelIndex &index, int role) const; //отображение данных

    //редактирование данных
    bool setData(const QModelIndex & index, const QVariant & value, int role = Qt::EditRole);

    //отображение заголовков столбцов
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    Qt::ItemFlags flags(const QModelIndex &index) const; // возвращает установленные флаги

    //вставляет пустые строки перед текущей позицией
    bool insertRows( int position, int rows,const QModelIndex & index = QModelIndex());
    bool removeRows( int position, int rows,const QModelIndex & index = QModelIndex());

    void insertRow( const QString & Number,
                    const QString & FileName,
                    const QString & Description,
                    const QString & RowsCount,
                    const QString & Duration);

signals:
    void editCompleted(const QString &);
};

#endif // COMMANDTABLEMODEL_H
