#ifndef CHANNELTABLEMODEL_H
#define CHANNELTABLEMODEL_H

#include <QAbstractTableModel>
#include <QString>
#include <QList>
#include <QStringList>
#include "ChannelListItem.h"

const int COLS = 3;
const int ROWS = 2;

class ChannelTableModel : public QAbstractTableModel
{

    Q_OBJECT
public:
    explicit ChannelTableModel(QObject *parent = 0);
    ~ChannelTableModel();

    QList<ChannelListItem*> m_List; // список, в котором хранятся все данные
    QStringList header_data; // список заголовков столбцов

    int rowCount(const QModelIndex &parent=QModelIndex()) const; //метод возвращает количество строк
    int columnCount(const QModelIndex &parent) const; //метод возвращает количество столбцов
    QVariant data(const QModelIndex &index, int role) const; // метод для отображения данных

    // метод требуется для возможности редактирования данных
    bool setData(const QModelIndex & index, const QVariant & value, int role = Qt::EditRole);

    // метод для отображения заголовков столбцов
    QVariant headerData(int section,Qt::Orientation orientation, int role=Qt::DisplayRole) const;
    Qt::ItemFlags flags(const QModelIndex &index) const; // возвращает установленные флаги
signals:
    void editCompleted(const QString &);
public slots:

private:
};

#endif // CHANNELTABLEMODEL_H
