#include "node.h"
#include "controller.h"
#include "treemodel.h"
#include "utils.h"
#include "filtermgr.h"
#include <QStringList>
#include <QColor>
#include <QIcon>
#include <QDir>
#include <QFileInfo>
#include "defs.h"
#include <QDebug>

// Constructor:
TreeModel::TreeModel(QObject *parent) : QAbstractItemModel(parent), mController(0), mRootNode(0)
{
}

// Destructor:
TreeModel::~TreeModel()
{
}

// Set controller:
void TreeModel::setController(Controller *controller)
{
    mController = controller;
}

// Get node:
Node *TreeModel::getNode(const QModelIndex &index) const
{
    if (!index.isValid())
        return 0;
    return static_cast<Node *>(index.internalPointer());
}

// Return data:
QVariant TreeModel::data(const QModelIndex &index, int role) const
{
    // Check index:
    if (!index.isValid())
        return QVariant();

    // Get node:
    Node *node = getNode(index);
    if (!node)
        return QVariant();

    // Get node base name:
    QString baseName = node->baseName();

    // Get node full relative path:
    QString fullRelativePath = node->fullRelativePath();

    // Node base name:
    if ((role == Qt::DisplayRole) || (role == BaseNameRole))
        return baseName;

    // Full relative path:
    if (role == FullRelativePathRole)
        return fullRelativePath;

    // Foreground role:
    if (role == Qt::ForegroundRole)
        return QColor("black");

    // Decoration:
    if (role == Qt::DecorationRole)
    {
        // Get processed nodes:
        QHash<Node *, bool> processedNodes = mController->processedNodes();
        if (!processedNodes[node])
            return QIcon(BLUE_FOLDER_PICTO);
        return node->hasProblem() ? QIcon(RED_FOLDER_PICTO) : QIcon(GREEN_FOLDER_PICTO);
    }

    return QVariant();
}

// Flags:
Qt::ItemFlags TreeModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return 0;

    return QAbstractItemModel::flags(index);
}

// Index:
QModelIndex TreeModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    Node *parentNode = !parent.isValid() ? mRootNode : static_cast<Node *>(parent.internalPointer());
    Node *childNode = parentNode ? parentNode->child(row) : 0;
    return childNode ? createIndex(row, column, childNode) : QModelIndex();
}

// Parent:
QModelIndex TreeModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();

    Node *childNode = static_cast<Node *>(index.internalPointer());
    if (!childNode)
        return QModelIndex();
    Node *parentNode = childNode->parent();

    return parentNode == mRootNode ? QModelIndex() : createIndex(parentNode->row(), 0, parentNode);
}

// Row count:
int TreeModel::rowCount(const QModelIndex &parent) const
{
    if (parent.column() > 0)
        return 0;

    Node *parentNode = !parent.isValid() ? mRootNode : static_cast<Node *>(parent.internalPointer());

    return parentNode ? parentNode->childCount() : 0;
}

// Column count:
int TreeModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 1;
}

// Setup model:
void TreeModel::setRootNode(Node *node)
{
    if (node == mRootNode)
        return;
    beginResetModel();
    mRootNode = node;
    endResetModel();
}

