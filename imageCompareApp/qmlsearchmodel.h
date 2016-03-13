#ifndef QMLSEARCHMODEL_H
#define QMLSEARCHMODEL_H
#include <QAbstractListModel>
#include "defs.h"

class QMLSearchModel : public QAbstractListModel
{
    Q_OBJECT

public:
    // Constructor:
    QMLSearchModel(QObject *parent=0);

    // Destructor:
    ~QMLSearchModel();

    // Row count:
    virtual int rowCount(const QModelIndex &parent=QModelIndex()) const;

    // Data:
    virtual QVariant data(const QModelIndex &index, int role) const;

    // Role names:
    virtual QHash<int, QByteArray> roleNames() const;

    // Add result:
    void addResult(const MatchStruct &result);

    // Reset:
    void reset();

private:
    // Data:
    QVector<MatchStruct> mData;
};

#endif // QMLSEARCHMODEL_H
