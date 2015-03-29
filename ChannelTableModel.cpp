#include "ChannelTableModel.h"

ChannelTableModel::ChannelTableModel(QObject *parent) : QAbstractTableModel(parent)
{
    //тут записываем названия столбцов
    header_data << QString::fromUtf8("Номер")
                << QString::fromUtf8("Название")
                << QString::fromUtf8("Статус")
                << QString::fromUtf8("Позиция")
                << QString::fromUtf8("Мин. Поз")
                << QString::fromUtf8("Макс. Поз")
                << QString::fromUtf8("Реверс")
                << QString::fromUtf8("KP")
                << QString::fromUtf8("KI")
                << QString::fromUtf8("KD");

    //заполняем пустыми ячейками
        for(int i = 0; i < 20; i++){
            ChannelListItem* it = new ChannelListItem;
            m_List.append(it);
        }
}

ChannelTableModel::~ChannelTableModel()
{

}

int ChannelTableModel::rowCount(const QModelIndex &parent) const
{
    return m_List.size(); // размер списка - это количество строк
}

int ChannelTableModel::columnCount(const QModelIndex &parent) const
{
    return 10; // 10 столбцов
}

QVariant ChannelTableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.row() >= m_List.size())
        return QVariant();

    // для каждого столбца возвращаем нужные данные
    if (role == Qt::DisplayRole || role == Qt::EditRole){
        if (index.column() == 0 )
            return QString::number(m_List.at(index.row())->mNumber);
        if (index.column() == 1 )
            return QString::fromStdString(m_List.at(index.row())->mChannelDesc);
        if (index.column() == 2 )
            return QString::fromStdString(m_List.at(index.row())->mStatus);
        if (index.column() == 3 )
            return QString::number(m_List.at(index.row())->mPos);
        if (index.column() == 4 )
            return QString::number(m_List.at(index.row())->mMinPos);
        if (index.column() == 5 )
            return QString::number(m_List.at(index.row())->mMaxPos);
        if (index.column() == 6 )
            return QString::number(m_List.at(index.row())->mReverce);
        if (index.column() == 7 )
            return QString::number(m_List.at(index.row())->mKP);
        if (index.column() == 8 )
            return QString::number(m_List.at(index.row())->mKI);
        if (index.column() == 9 )
            return QString::number(m_List.at(index.row())->mKD);
    }
    return QVariant();
}

bool ChannelTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.isValid() && role == Qt::EditRole)
    {
        // записываем данные из каждого столбца
        if(index.column()==0){
            m_List.at(index.row())->mNumber = value.toString().toInt();
        }
        if(index.column()==1){
            m_List.at(index.row())->mChannelDesc = value.toString().toStdString();
        }
        if(index.column()==2){
            m_List.at(index.row())->mStatus = value.toString().toStdString();
        }
        if(index.column()==3){
            m_List.at(index.row())->mPos = value.toString().toInt();
        }
        if(index.column()==4){
            m_List.at(index.row())->mMinPos = value.toString().toInt();
        }
        if(index.column()==5){
            m_List.at(index.row())->mMaxPos = value.toString().toInt();
        }
        if(index.column()==6){
            m_List.at(index.row())->mReverce = value.toString().toInt();
        }
        if(index.column()==7){
            m_List.at(index.row())->mKP = value.toString().toInt();
        }
        if(index.column()==8){
            m_List.at(index.row())->mKI = value.toString().toInt();
        }
        if(index.column()==9){
            m_List.at(index.row())->mKD = value.toString().toInt();
        }
        return true;
    }
    return false;
}

QVariant ChannelTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role != Qt::DisplayRole)
        return QVariant();
    if(orientation == Qt::Horizontal && role == Qt::DisplayRole)
    {
        return header_data.at(section); // заголовки столбцов
    }
    else
    {
        return QString("%1").arg( section + 1 ); // возвращаем номера строк
    }

}

Qt::ItemFlags ChannelTableModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::ItemIsEnabled;
    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}

