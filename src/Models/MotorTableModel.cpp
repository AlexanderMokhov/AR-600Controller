#include "MotorTableModel.h"

MotorTableModel::MotorTableModel(QObject *parent) : QAbstractTableModel(parent)
{
    //тут записываем названия столбцов
    mHeaderData << QString::fromUtf8(" № ")
                << QString::fromUtf8(" Описание ")
                << QString::fromUtf8(" Угол ")
                << QString::fromUtf8(" Мин Угол ")
                << QString::fromUtf8(" Макс Угол ")
                << QString::fromUtf8(" П ")
                << QString::fromUtf8(" И ")
                << QString::fromUtf8(" Д ")
                << QString::fromUtf8(" Статус ");

    //заполняем пустыми ячейками/*
        for(int i = 0; i < 20; i++){
            Motor* it = new Motor;
            mDataList.append(it);
        }

}

MotorTableModel::~MotorTableModel()
{

}

int MotorTableModel::rowCount(const QModelIndex &parent) const
{
    return mDataList.size(); // размер списка - это количество строк
}

int MotorTableModel::columnCount(const QModelIndex &parent) const
{
    return mHeaderData.size();
    //return 12; // 12 столбцов
}

QVariant MotorTableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.row() >= mDataList.size())
        return QVariant();

    // для каждого столбца возвращаем нужные данные
    if (role == Qt::DisplayRole || role == Qt::EditRole){
        if (index.column() == 0 )
            return QString::number(mDataList.at(index.row())->getNumber());
        if (index.column() == 1 )
            return QString::fromStdString(mDataList.at(index.row())->getName());
        if (index.column() == 2 )
            return QString::number(mDataList.at(index.row())->getAngle());
        if (index.column() == 3 )
            return QString::number(mDataList.at(index.row())->getMinAngle());
        if (index.column() == 4 )
            return QString::number(mDataList.at(index.row())->getMaxAngle());
        if (index.column() == 5 )
            return QString::number(mDataList.at(index.row())->getPIDGates()->getPGate());
        if (index.column() == 6 )
            return QString::number(mDataList.at(index.row())->getPIDGates()->getIGate());
        if (index.column() == 7 )
            return QString::number(mDataList.at(index.row())->getPIDGates()->getDGate());
        if (index.column() == 8 )
            return QString::fromStdString(mDataList.at(index.row())->getState());
    }
    //Роль - выравнивание
    if (role == Qt::TextAlignmentRole)
    {
       return Qt::AlignCenter ;
    }
    return QVariant();
}

bool MotorTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.isValid() && role == Qt::EditRole)
    {
        // записываем данные из каждого столбца
        if(index.column() == 0){
            mDataList.at(index.row())->setNumber(value.toString().toInt());
        }
        if(index.column() == 1){
            mDataList.at(index.row())->setName(value.toString().toStdString());
        }
        if(index.column() == 2){
            mDataList.at(index.row())->setAngle(value.toString().toInt());
        }
        if(index.column() == 3){
            mDataList.at(index.row())->setMinAngle(value.toString().toInt());
        }
        if(index.column() == 4){
            mDataList.at(index.row())->setMaxAngle(value.toString().toInt());
        }
        if(index.column() == 5){
            mDataList.at(index.row())->getPIDGates()->setPGate(value.toString().toInt());
        }
        if(index.column() == 6){
            mDataList.at(index.row())->getPIDGates()->setIGate(value.toString().toInt());
        }
        if(index.column() == 7){
            mDataList.at(index.row())->getPIDGates()->setDGate(value.toString().toInt());
        }
        if(index.column() == 8){
            mDataList.at(index.row())->setState(value.toString().toStdString());
        }
        emit dataChanged(index, index);
        return true;

    }
    return false;
}

QVariant MotorTableModel::headerData(int section, Qt::Orientation orientation, int role) const
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

Qt::ItemFlags MotorTableModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::ItemIsEnabled;
    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}

bool MotorTableModel::insertRows(int position, int rows, const QModelIndex &index)
{
    Q_UNUSED( index );

    beginInsertRows( QModelIndex(), position, position + rows - 1 );

    for (int row = 0; row < rows; ++row )
    {
        Motor* it = new Motor;
        mDataList.insert(position,it);
    }

    endInsertRows();

    return true;
}

bool MotorTableModel::removeRows(int position, int rows, const QModelIndex &index)
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

void MotorTableModel::insertRow(const QString &Number, const QString &Name,
                                const QString &Angle,const QString &MinAngle,
                                const QString &MaxAngle, const QString &PGate,
                                const QString &IGate, const QString &DGate,
                                const QString & Status)
{
    insertRows( mDataList.size(), 1 );

    setData( index( mDataList.size()-1, 0 ), Number );
    setData( index( mDataList.size()-1, 1 ), Name );
    setData( index( mDataList.size()-1, 2 ), Angle );
    setData( index( mDataList.size()-1, 3 ), MinAngle );
    setData( index( mDataList.size()-1, 4 ), MaxAngle );
    setData( index( mDataList.size()-1, 5 ), PGate );
    setData( index( mDataList.size()-1, 6 ), IGate );
    setData( index( mDataList.size()-1, 7 ), DGate );
    setData( index( mDataList.size()-1, 8 ), Status );
}

