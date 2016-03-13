#include "treemodelfilter.h"
#include "treemodel.h"
#include "node.h"
#include "controller.h"

// Constructor:
TreeModelFilter::TreeModelFilter(QObject *parent) : QSortFilterProxyModel(parent),
    mController(0)
{
    setDynamicSortFilter(false);
    sort(0);
}

// Destructor:
TreeModelFilter::~TreeModelFilter()
{

}

// Set controller:
void TreeModelFilter::setController(Controller *controller)
{
    mController = controller;
}

// Accept row:
bool TreeModelFilter::acceptRow(int source_row, const QModelIndex &source_parent) const
{
    // Get src model:
    TreeModel *srcModel  = dynamic_cast<TreeModel *>(sourceModel());
    if (!srcModel)
        return false;

    // Get src index:
    QModelIndex srcIndex = srcModel->index(source_row, 0, source_parent);
    if (!srcIndex.isValid())
        return false;

    // Get node:
    Node *node = srcModel->getNode(srcIndex);
    if (!node)
        return false;

    return node->type() == Node::DIR;
}

// Accept row:
bool TreeModelFilter::filterAcceptsRow(int source_row, const QModelIndex & source_parent) const
{
    // get source-model index for current row
    QModelIndex source_index = sourceModel()->index(source_row, 0, source_parent);
    if (source_index.isValid())
    {
        // if any of children matches the filter, then current index matches the filter as well
        int nb = sourceModel()->rowCount(source_index) ;
        for (int i=0; i<nb; ++i)
            if (filterAcceptsRow(i, source_index))
                return true ;
        return acceptRow(source_row, source_parent);
    }

    // Parent call for initial behaviour:
    return QSortFilterProxyModel::filterAcceptsRow(source_row, source_parent) ;
}
