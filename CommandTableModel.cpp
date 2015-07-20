#include "CommandTableModel.h"

CommandTableModel::CommandTableModel(QObject *parent) : QAbstractTableModel(parent)
{
    //тут записываем названия столбцов
    mHeaderData << QString::fromUtf8(" № ")
                << QString::fromUtf8(" Путь ")
                << QString::fromUtf8(" Название ")
                << QString::fromUtf8(" Строк ")
                << QString::fromUtf8(" Время ");

    //заполняем пустыми ячейками/*
        for(int i = 0; i < 20; i++){
            CommandFile* it = new CommandFile;
            it->Number = i+1;
            it->File = "NewFile";
            it->Name = "HelloCommand";
            it->RowsCount = 20;
            it->DurationMs = 3000;
            mDataList.append(it);
        }
}

CommandTableModel::~CommandTableModel()
{

}

int CommandTableModel::rowCount(const QModelIndex &parent) const
{
    return mDataList.size(); // размер списка - это количество строк
}

int CommandTableModel::columnCount(const QModelIndex &parent) const
{
    return 5; // 4 столбца
}

QVariant CommandTableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.row() >= mDataList.size())
        return QVariant();

    // для каждого столбца возвращаем нужные данные
    if (role == Qt::DisplayRole || role == Qt::EditRole){
        if (index.column() == 0 )
            return QString::number(mDataList.at(index.row())->Number);
        if (index.column() == 1 )
            return mDataList.at(index.row())->File;
        if (index.column() == 2 )
            return mDataList.at(index.row())->Name;
        if (index.column() == 3 )
            return QString::number(mDataList.at(index.row())->RowsCount);
        if (index.column() == 4 )
            return QString::number(mDataList.at(index.row())->DurationMs);
    }
    return QVariant();
}

bool CommandTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.isValid() && role == Qt::EditRole)
    {
        // записываем данные из каждого столбца
        if(index.column()==0){
            mDataList.at(index.row())->Number = value.toString().toInt();
        }
        if(index.column()==1){
            mDataList.at(index.row())->File = value.toString();
        }
        if(index.column()==2){
            mDataList.at(index.row())->Name = value.toString();
        }
        if(index.column()==3){
            mDataList.at(index.row())->RowsCount = value.toString().toInt();
        }
        if(index.column()==4){
            mDataList.at(index.row())->DurationMs = value.toString().toDouble();
        }
        emit dataChanged(index, index);
        return true;

    }
    return false;
}

QVariant CommandTableModel::headerData(int section, Qt::Orientation orientation, int role) const
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

Qt::ItemFlags CommandTableModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::ItemIsEnabled;
    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}

bool CommandTableModel::insertRows(int position, int rows, const QModelIndex &index)
{
    Q_UNUSED( index );

    beginInsertRows( QModelIndex(), position, position + rows - 1 );

    for (int row = 0; row < rows; ++row )
    {
        CommandFile* it = new CommandFile;
        mDataList.insert(position,it);
    }

    endInsertRows();

    return true;
}

bool CommandTableModel::removeRows(int position, int rows, const QModelIndex &index)
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

void CommandTableModel::insertRow(const QString &Number, const QString &File, const QString &Name, const QString &Rows, const QString &Duration)
{
    insertRows( mDataList.size(), 1 );

    setData( index( mDataList.size()-1, 0 ), Number );
    setData( index( mDataList.size()-1, 1 ), File );
    setData( index( mDataList.size()-1, 2 ), Name );
    setData( index( mDataList.size()-1, 3 ), Rows );
    setData( index( mDataList.size()-1, 4 ), Duration );
}
