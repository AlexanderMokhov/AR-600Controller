#include "CommandsTableModel.h"

CommandsTableModel::CommandsTableModel(QObject *parent) : QAbstractTableModel(parent)
{
    //тут записываем названия столбцов
    mHeaderData << QString::fromUtf8(" № ")
                << QString::fromUtf8(" Описание ")
                << QString::fromUtf8(" Строк ")
                << QString::fromUtf8(" Длительность ");

    //заполняем пустыми ячейками/*
        for(int i = 0; i < 20; i++){
            CommandsListItem* it = new CommandsListItem;
            mCommandsList.append(it);
        }
}

CommandsTableModel::~CommandsTableModel()
{

}



int CommandsTableModel::rowCount(const QModelIndex &parent) const
{
    return mCommandsList.size(); // размер списка - это количество строк
}

int CommandsTableModel::columnCount(const QModelIndex &parent) const
{
    return 4; // 4 столбца
}

QVariant CommandsTableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.row() >= mCommandsList.size())
        return QVariant();

    // для каждого столбца возвращаем нужные данные
    if (role == Qt::DisplayRole || role == Qt::EditRole){
        if (index.column() == 0 )
            return QString::number(mCommandsList.at(index.row())->mNumber);
        if (index.column() == 1 )
            return QString::fromStdString(mCommandsList.at(index.row())->mDescription);
        if (index.column() == 2 )
            return QString::number(mCommandsList.at(index.row())->mCountRows);
        if (index.column() == 3 )
            return QString::number(mCommandsList.at(index.row())->mDuration);
    }
    return QVariant();
}

bool CommandsTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.isValid() && role == Qt::EditRole)
    {
        // записываем данные из каждого столбца
        if(index.column()==0){
            mCommandsList.at(index.row())->mNumber = value.toString().toInt();
        }
        if(index.column()==1){
            mCommandsList.at(index.row())->mDescription = value.toString().toStdString();
        }
        if(index.column()==2){
            mCommandsList.at(index.row())->mCountRows = value.toString().toInt();
        }
        if(index.column()==3){
            mCommandsList.at(index.row())->mDuration = value.toString().toInt();
        }
        emit dataChanged(index, index);
        return true;

    }
    return false;
}

QVariant CommandsTableModel::headerData(int section, Qt::Orientation orientation, int role) const
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

Qt::ItemFlags CommandsTableModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::ItemIsEnabled;
    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}

bool CommandsTableModel::insertRows(int position, int rows, const QModelIndex &index)
{
    Q_UNUSED( index );

    beginInsertRows( QModelIndex(), position, position + rows - 1 );

    for (int row = 0; row < rows; ++row )
    {
        CommandsListItem* it = new CommandsListItem;
        mCommandsList.insert(position,it);
    }

    endInsertRows();

    return true;
}

bool CommandsTableModel::removeRows(int position, int rows, const QModelIndex &index)
{
    Q_UNUSED( index );

    beginRemoveRows( QModelIndex(), position, position + rows - 1 );

    for( int row = 0; row < rows; ++row )
    {
        mCommandsList.removeAt(position);
    }

    endRemoveRows();

    return true;

}

void CommandsTableModel::insertRow(const QString &Number, const QString &Description,
                                  const QString &CountRows, const QString &Duration)
{
    insertRows( mCommandsList.size(), 1 );

    setData( index( mCommandsList.size()-1, 0 ), Number );
    setData( index( mCommandsList.size()-1, 1 ), Description );
    setData( index( mCommandsList.size()-1, 2 ), CountRows );
    setData( index( mCommandsList.size()-1, 3 ), Duration );
}
