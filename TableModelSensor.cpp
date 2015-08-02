#include "TableModelSensor.h"

TableModelSensor::TableModelSensor(QObject *parent) : QAbstractTableModel(parent)
{
    //тут записываем названия столбцов
    mHeaderData << QString::fromUtf8(" № ")
                << QString::fromUtf8(" Описание ")
                << QString::fromUtf8(" Значение ");

    //заполняем пустыми ячейками/*
        for(int i = 0; i < 10; i++){
            Sensor* it = new Sensor;
            mDataList.append(it);
        }
}

TableModelSensor::~TableModelSensor()
{

}

int TableModelSensor::rowCount(const QModelIndex &parent) const
{
    return mDataList.size(); // размер списка - это количество строк
}

int TableModelSensor::columnCount(const QModelIndex &parent) const
{
    return 3; // 3 столбца
}

QVariant TableModelSensor::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.row() >= mDataList.size())
        return QVariant();

    // для каждого столбца возвращаем нужные данные
    if (role == Qt::DisplayRole || role == Qt::EditRole){
        if (index.column() == 0 )
            return QString::number(mDataList.at(index.row())->GetNumber());
        if (index.column() == 1 )
            return QString::fromStdString(mDataList.at(index.row())->GetName());
        if (index.column() == 2 )
            return QString::number(mDataList.at(index.row())->GetValue());
    }
    return QVariant();
}

bool TableModelSensor::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.isValid() && role == Qt::EditRole)
    {
        // записываем данные из каждого столбца
        if(index.column()==0){
            mDataList.at(index.row())->SetNumber(value.toString().toInt());
        }
        if(index.column()==1){
            mDataList.at(index.row())->SetName(value.toString().toStdString());
        }
        if(index.column()==2){
            mDataList.at(index.row())->SetValue(value.toString().toInt());
        }
        emit dataChanged(index, index);
        return true;

    }
    return false;
}

QVariant TableModelSensor::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role != Qt::DisplayRole)
        return QVariant();
    if(orientation == Qt::Horizontal && role == Qt::DisplayRole)
    {
        return mHeaderData.at(section); // заголовки столбцов
    }
    else
    {
        return QString("%1").arg( section + 1 ); // возвращаем номера строк
    }
}

Qt::ItemFlags TableModelSensor::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::ItemIsEnabled;
    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}

bool TableModelSensor::insertRows(int position, int rows, const QModelIndex &index)
{
    Q_UNUSED( index );

    beginInsertRows( QModelIndex(), position, position + rows - 1 );

    for (int row = 0; row < rows; ++row )
    {
        Sensor* it = new Sensor;
        mDataList.insert(position,it);
    }

    endInsertRows();

    return true;
}

bool TableModelSensor::removeRows(int position, int rows, const QModelIndex &index)
{
    Q_UNUSED( index );

    beginRemoveRows( QModelIndex(), position, position + rows - 1 );

    for( int row = 0; row < rows; ++row )
    {
        mDataList.removeAt(position);
    }

    endRemoveRows();

    return true;
}

void TableModelSensor::insertRow(const QString &Number, const QString &Name, const QString &Value)
{
    insertRows( mDataList.size(), 1 );

    setData( index( mDataList.size()-1, 0 ), Number );
    setData( index( mDataList.size()-1, 1 ), Name );
    setData( index( mDataList.size()-1, 2 ), Value );
}



