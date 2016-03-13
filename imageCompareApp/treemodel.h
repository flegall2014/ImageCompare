#ifndef TREEMODEL_H
#define TREEMODEL_H
#include <QAbstractItemModel>
#include <QModelIndex>
#include <QVariant>
#include <QDir>
class Tree;
class Controller;

class Node;
class TreeModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    enum Roles {
        BaseNameRole = Qt::UserRole+1,
        FullRelativePathRole
    };

    // Constructor:
    explicit TreeModel(QObject *parent = 0);

    // Destructor:
    virtual ~TreeModel();

    // Set controller:
    void setController(Controller *controller);

    // Get node:
    Node *getNode(const QModelIndex &index) const;

    // Data:
    virtual QVariant data(const QModelIndex &index, int role) const;

    // Return flags:
    virtual Qt::ItemFlags flags(const QModelIndex &index) const;

    // Index:
    virtual QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;

    // Parent:
    virtual QModelIndex parent(const QModelIndex &index) const;

    // Row count:
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;

    // Column count:
    virtual int columnCount(const QModelIndex &parent = QModelIndex()) const;

    // Set root node:
    void setRootNode(Node *node);

protected:
    // Controller:
    Controller *mController;

    // Root node:
    Node *mRootNode;
};

#endif // TREEMODEL_H
