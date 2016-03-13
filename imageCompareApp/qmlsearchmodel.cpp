#include "qmlsearchmodel.h"
#include <QDebug>

// Constructor:
QMLSearchModel::QMLSearchModel(QObject *parent) : QAbstractListModel(parent)
{

}

// Destructor:
QMLSearchModel::~QMLSearchModel()
{

}

// Role names:
QHash<int, QByteArray> QMLSearchModel::roleNames() const
{
    QHash<int, QByteArray> roleNames;
    roleNames[QMLFileRole] = "qmlFile";
    roleNames[LineNumberRole] = "lineNumber";
    roleNames[LineRole] = "line";
    return roleNames;
}

// Return row count:
int QMLSearchModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return mData.size();
}

// Return data:
QVariant QMLSearchModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();
    if ((index.row() < 0) || (index.row() > (rowCount()-1)))
        return QVariant();
    if (role == QMLFileRole)
        return mData[index.row()]._qmlFile;
    if (role == LineNumberRole)
        return mData[index.row()]._lineNumber;
    if (role == LineRole)
        return mData[index.row()]._line;
    return QVariant();
}

// Add result:
void QMLSearchModel::addResult(const MatchStruct &result)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    mData << result;
    endInsertRows();
}

// Reset:
void QMLSearchModel::reset()
{
    beginResetModel();
    mData.clear();
    endResetModel();
}
