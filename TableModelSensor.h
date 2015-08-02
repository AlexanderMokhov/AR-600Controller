#ifndef SENSORTABLEMODEL_H
#define SENSORTABLEMODEL_H

#include <QAbstractTableModel>
#include <QString>
#include <QList>
#include <QStringList>
#include "Sensor.h"

class TableModelSensor : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit TableModelSensor(QObject *parent = 0);
    ~TableModelSensor();

    QList<Sensor*> mDataList; // список, в котором хранятся все данные
    QStringList mHeaderData; // список заголовков столбцов

    int rowCount(const QModelIndex &parent = QModelIndex()) const; //количество строк
    int columnCount(const QModelIndex &parent) const; //количество столбцов
    QVariant data(const QModelIndex &index, int role) const; //отображение данных

    //редактирование данных
    bool setData(const QModelIndex & index, const QVariant & value, int role = Qt::EditRole);

    //отображение заголовков столбцов
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    Qt::ItemFlags flags(const QModelIndex &index) const; //установленные флаги

    //вставляет пустые строки перед текущей позицией
    bool insertRows( int position, int rows,const QModelIndex & index = QModelIndex());
    bool removeRows( int position, int rows,const QModelIndex & index = QModelIndex());

    void insertRow( const QString & Number,const QString & Name, const QString & Value);

signals:
    void editCompleted(const QString &);
};

#endif // SENSORTABLEMODEL_H
