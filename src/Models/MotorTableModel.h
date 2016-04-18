#ifndef MOTORTABLEMODEL_H
#define MOTORTABLEMODEL_H

#include <QAbstractTableModel>
#include <QString>
#include <QList>
#include <QStringList>

#include "Devices/Motor.h"

class MotorTableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    //public methods
    explicit MotorTableModel(QObject *parent = 0);
    ~MotorTableModel();

    QList<Motor*> mDataList; // список, в котором хранятся все данные
    QStringList mHeaderData; // список заголовков столбцов

    int rowCount(const QModelIndex &parent = QModelIndex()) const; //количество строк
    int columnCount(const QModelIndex &parent) const; //количество столбцов
    QVariant data(const QModelIndex &index, int role) const; //отображение данных

    //редактирование данных
    bool setData(const QModelIndex & index, const QVariant & value, int role = Qt::EditRole);

    //отображение заголовков столбцов
    QVariant headerData(int section,Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    Qt::ItemFlags flags(const QModelIndex &index) const; // возвращает установленные флаги

    //вставляет пустые строки перед текущей позицией
    bool insertRows( int position, int rows,const QModelIndex & index = QModelIndex());
    bool removeRows( int position, int rows,const QModelIndex & index = QModelIndex());

    void insertRow(const QString &Number, const QString &Name,
                   const QString &Angle, const QString &MinAngle,
                   const QString &MaxAngle, const QString &PGate,
                   const QString &IGate, const QString &DGate,
                   const QString & Status);

signals:
    void editCompleted(const QString &);
};

#endif // MOTORTABLEMODEL_H
