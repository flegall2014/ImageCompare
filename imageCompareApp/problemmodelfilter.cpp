#include "problemmodelfilter.h"
#include "imagemodel.h"
#include "node.h"
#include "utils.h"
#include "defs.h"
#include "controller.h"
#include "filtermgr.h"
#include <QDebug>

// Constructor:
ProblemModelFilter::ProblemModelFilter(QObject *parent) : QSortFilterProxyModel(parent),
    mController(0), mActiveFilter(-1)
{
    setDynamicSortFilter(false);
    sort(0);
}

// Destructor:
ProblemModelFilter::~ProblemModelFilter()
{
}

// Set controller:
void ProblemModelFilter::setController(Controller *controller)
{
    mController = controller;
}

// Accept row:
bool ProblemModelFilter::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const
{
    // Get src model:
    ImageModel *srcModel  = dynamic_cast<ImageModel *>(sourceModel());
    if (!srcModel)
        return false;

    // Get src index:
    QModelIndex srcIndex = srcModel->index(source_row, 0, source_parent);
    if (!srcIndex.isValid())
        return false;

    // Get node:
    Node *node = srcModel->getNode(srcIndex.row());
    if (!node)
        return false;

    // Check type:
    if (node->type() != Node::IMAGE)
        return false;

    // Reg exp condition:
    bool regExpCondition = node->baseName().contains(filterRegExp().pattern(), Qt::CaseInsensitive);

    // Any:
    if (mActiveFilter == -1)
        return regExpCondition;

    // Problem only:
    if (mActiveFilter == -2)
        return node->hasProblem() && regExpCondition;

    // Filter status size:
    int filterStatusSize = node->filterStatus().size();

    // Check active filter:
    if (mActiveFilter > (filterStatusSize-1))
        return false;

    return node->filterStatus()[mActiveFilter] && regExpCondition;
}

// Get image:
QString ProblemModelFilter::getImage(int row, int col) const
{
    // Get src model:
    ImageModel *srcModel  = dynamic_cast<ImageModel *>(sourceModel());
    if (!srcModel)
        return UNKNOWN_PICTO;

    // Get src index:
    QModelIndex srcIndex = srcModel->index(row, 0, QModelIndex());
    if (!srcIndex.isValid())
        return UNKNOWN_PICTO;

    // Return src file:
    QString srcFile = srcModel->getImage(srcIndex.row(), col);

    // Special case:
    if (srcFile == UNKNOWN_PICTO)
        return UNKNOWN_PICTO;

    return Utils::fromLocalFile(srcFile);
}

// Get image weight:
int ProblemModelFilter::getImageWeight(int row, int col) const
{
    // Get src model:
    ImageModel *srcModel  = dynamic_cast<ImageModel *>(sourceModel());
    if (!srcModel)
        return 0;

    // Get src index:
    QModelIndex srcIndex = srcModel->index(row, 0, QModelIndex());
    if (!srcIndex.isValid())
        return 0;

    // Get src image:
    QString srcImage = srcModel->getImage(srcIndex.row(), col);

    QFileInfo fi(srcImage);
    if (!fi.exists())
        return 0;

    return fi.size();
}

// Get dir name:
QString ProblemModelFilter::getDirName(int col) const
{
    // Get src model:
    ImageModel *srcModel  = dynamic_cast<ImageModel *>(sourceModel());
    if (!srcModel)
        return "";

    return srcModel->getDirName(col);
}

// Get dir id:
QString ProblemModelFilter::getDirId(int col) const
{
    // Get src model:
    ImageModel *srcModel  = dynamic_cast<ImageModel *>(sourceModel());
    if (!srcModel)
        return "";

    return srcModel->getDirId(col);
}

// Get image actual casing:
QString ProblemModelFilter::getImageActualCasing(int row, int col)
{
    QString imgPath = getImage(row, col);
    QString imgPathActualCasing = Utils::getActualCasing(imgPath, mController->imageFilter());
    QStringList splitted = imgPathActualCasing.split("/");
    return splitted.last();
}

// Return number of columns:
int ProblemModelFilter::nCols() const
{
    // Get src model:
    ImageModel *srcModel  = dynamic_cast<ImageModel *>(sourceModel());
    if (!srcModel)
        return false;

    return srcModel->nCols();
}

// Set active filter:
void ProblemModelFilter::setActiveFilter(int activeFilter)
{
    mActiveFilter = activeFilter;
    invalidate();
}
