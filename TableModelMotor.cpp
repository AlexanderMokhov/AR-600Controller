#include "TableModelMotor.h"

TableModelMotor::TableModelMotor(QObject *parent) : QAbstractTableModel(parent)
{
    //тут записываем названия столбцов
    mHeaderData << QString::fromUtf8(" № ")
                << QString::fromUtf8(" Описание ")
                << QString::fromUtf8(" Статус ")
                << QString::fromUtf8(" Позиция ")
                << QString::fromUtf8(" МинПоз ")
                << QString::fromUtf8(" МаксПоз ")
                << QString::fromUtf8(" Реверс ")
                << QString::fromUtf8(" K_P ")
                << QString::fromUtf8(" K_I ")
                << QString::fromUtf8(" K_D ")
                << QString::fromUtf8(" КалибПол ")
                << QString::fromUtf8(" Enable ");

    //заполняем пустыми ячейками/*
        for(int i = 0; i < 20; i++){
            Motor* it = new Motor;
            mDataList.append(it);
        }

}

TableModelMotor::~TableModelMotor()
{

}

int TableModelMotor::rowCount(const QModelIndex &parent) const
{
    return mDataList.size(); // размер списка - это количество строк
}

int TableModelMotor::columnCount(const QModelIndex &parent) const
{
    return 12; // 12 столбцов
}

QVariant TableModelMotor::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.row() >= mDataList.size())
        return QVariant();

    // для каждого столбца возвращаем нужные данные
    if (role == Qt::DisplayRole || role == Qt::EditRole){
        if (index.column() == 0 )
            return QString::number(mDataList.at(index.row())->mNumber);
        if (index.column() == 1 )
            return QString::fromStdString(mDataList.at(index.row())->mName);
        if (index.column() == 2 )
            return QString::fromStdString(mDataList.at(index.row())->mStatus);
        if (index.column() == 3 )
            return QString::number(mDataList.at(index.row())->mPos);
        if (index.column() == 4 )
            return QString::number(mDataList.at(index.row())->mMinPos);
        if (index.column() == 5 )
            return QString::number(mDataList.at(index.row())->mMaxPos);
        if (index.column() == 6 )
            return QString::number(mDataList.at(index.row())->mReverce);
        if (index.column() == 7 )
            return QString::number(mDataList.at(index.row())->mStiff);
        if (index.column() == 8 )
            return QString::number(mDataList.at(index.row())->mDump);
        if (index.column() == 9 )
            return QString::number(mDataList.at(index.row())->mTorque);
        if (index.column() == 10 )
            return QString::number(mDataList.at(index.row())->mCalibration);
        if (index.column() == 11 )
            return QString::number(mDataList.at(index.row())->mEnable);
    }
    //Роль - выравнивание
    if (role == Qt::TextAlignmentRole)
    {
       return Qt::AlignCenter ;
    }
    return QVariant();
}

bool TableModelMotor::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.isValid() && role == Qt::EditRole)
    {
        // записываем данные из каждого столбца
        if(index.column()==0){
            mDataList.at(index.row())->mNumber = value.toString().toInt();
        }
        if(index.column()==1){
            mDataList.at(index.row())->mName = value.toString().toStdString();
        }
        if(index.column()==2){
            mDataList.at(index.row())->mStatus = value.toString().toStdString();
        }
        if(index.column()==3){
            mDataList.at(index.row())->mPos = value.toString().toInt();
        }
        if(index.column()==4){
            mDataList.at(index.row())->mMinPos = value.toString().toInt();
        }
        if(index.column()==5){
            mDataList.at(index.row())->mMaxPos = value.toString().toInt();
        }
        if(index.column()==6){
            mDataList.at(index.row())->mReverce = value.toString().toInt();
        }
        if(index.column()==7){
            mDataList.at(index.row())->mStiff = value.toString().toInt();
        }
        if(index.column()==8){
            mDataList.at(index.row())->mDump = value.toString().toInt();
        }
        if(index.column()==9){
            mDataList.at(index.row())->mTorque = value.toString().toInt();
        }
        if(index.column()==10){
            mDataList.at(index.row())->mCalibration = value.toString().toInt();
        }
        if(index.column()==11){
            mDataList.at(index.row())->mEnable = value.toString().toInt();
        }
        emit dataChanged(index, index);
        return true;

    }
    return false;
}

QVariant TableModelMotor::headerData(int section, Qt::Orientation orientation, int role) const
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

Qt::ItemFlags TableModelMotor::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::ItemIsEnabled;
    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}

bool TableModelMotor::insertRows(int position, int rows, const QModelIndex &index)
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

bool TableModelMotor::removeRows(int position, int rows, const QModelIndex &index)
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

void TableModelMotor::insertRow(const QString &Number, const QString &Name,
                                  const QString &Status, const QString &Pos,
                                  const QString &MinPos, const QString &MaxPos,
                                  const QString &Reverce, const QString &Stiff,
                                  const QString &Dump, const QString &Torque,const QString &Calibration, const QString & Enable)
{
    insertRows( mDataList.size(), 1 );

    setData( index( mDataList.size()-1, 0 ), Number );
    setData( index( mDataList.size()-1, 1 ), Name );
    setData( index( mDataList.size()-1, 2 ), Status );
    setData( index( mDataList.size()-1, 3 ), Pos );
    setData( index( mDataList.size()-1, 4 ), MinPos );
    setData( index( mDataList.size()-1, 5 ), MaxPos );
    setData( index( mDataList.size()-1, 6 ), Reverce );
    setData( index( mDataList.size()-1, 7 ), Stiff );
    setData( index( mDataList.size()-1, 8 ), Dump );
    setData( index( mDataList.size()-1, 9 ), Torque );
    setData( index( mDataList.size()-1, 10 ), Calibration );
    setData( index( mDataList.size()-1, 11 ), Enable );
}
