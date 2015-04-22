#ifndef CHANNELTABLEMODEL_H
#define CHANNELTABLEMODEL_H

#include <QAbstractTableModel>
#include <QString>
#include <QList>
#include <QStringList>
#include "ChannelListItem.h"

class ChannelTableModel : public QAbstractTableModel
{

    Q_OBJECT
public:
    explicit ChannelTableModel(QObject *parent = 0);
    ~ChannelTableModel();

    QList<ChannelListItem*> mDataList; // список, в котором хранятся все данные
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

    void insertRow( const QString & Number,const QString & ChannelDesc, const QString & Status,
                    const QString & Pos, const QString & MinPos, const QString & MaxPos,
                    const QString & Reverce,const QString & KP,const QString & KI,const QString & KD,
                    const QString & Ilim, const QString & Enable);

signals:
    void editCompleted(const QString &);
public slots:

private:
};

#endif // CHANNELTABLEMODEL_H
