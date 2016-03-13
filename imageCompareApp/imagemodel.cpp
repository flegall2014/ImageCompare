#include "imagemodel.h"
#include "node.h"
#include "utils.h"
#include "defs.h"
#include "controller.h"
#include "filtermgr.h"
#include "ifilter.h"
#include <QImage>
#include <QDebug>

// Constructor:
ImageModel::ImageModel(QObject *parent) : QAbstractListModel(parent),
    mController(0), mRootNode(0)
{

}

// Destructor:
ImageModel::~ImageModel()
{

}

// Set controller:
void ImageModel::setController(Controller *controller)
{
    mController = controller;
}

// Row count:
int ImageModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return mRootNode ? mRootNode->childCount() : 0;
}

// Return column count:
int ImageModel::nCols() const
{
    return mImageDirList.size();
}

// Role names:
QHash<int, QByteArray> ImageModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[ImageRowRole] = "imageRow";
    roles[ImageBaseNameRole] = "imageBaseName";
    roles[ImageProblemRole] = "imageProblem";
    return roles;
}

// Data:
QVariant ImageModel::data(const QModelIndex &index, int role) const
{
    // Check index:
    if (!index.isValid())
        return QVariant();
    if ((index.row() < 0) || (index.row() > (rowCount()-1)))
        return QVariant();
    if (!mRootNode)
        return QVariant();

    // Get node:
    Node *node = mRootNode->child(index.row());
    if (!node)
        return QVariant();

    // Return image row:
    if (role == ImageRowRole)
        return index.row();

    // Return image base name:
    if (role == ImageBaseNameRole)
        return node->baseName();

    // Image problem:
    if (role == ImageProblemRole)
    {
        FilterMgr *filterMgr = dynamic_cast<FilterMgr *>(mController->filterMgr());

        // Build problem list:
        return Utils::problemList(node, filterMgr->filters());
    }

    return QVariant();
}

// Setup model:
void ImageModel::setupModel(Node *rootNode, const QList<QDir> &imageDirList, const QStringList &dirIds)
{
    beginResetModel();
    mRootNode = rootNode;
    mImageDirList = imageDirList;
    mDirIds = dirIds;
    endResetModel();
    emit nColsChanged();
}

// Return root node:
Node *ImageModel::rootNode() const
{
    return mRootNode;
}

// Get node:
Node *ImageModel::getNode(int row) const
{
    if (!mRootNode)
        return 0;

    // Get child:
    int nChilds = mRootNode->childCount();
    if ((row < 0) || (row > (nChilds-1)))
        return 0;

    return mRootNode->child(row);
}

// Get image:
QString ImageModel::getImage(int row, int col) const
{
    // Check row/col:
    if ((row < 0) || (row > (rowCount()-1)))
        return UNKNOWN_PICTO;
    if ((col < 0) || (col > (mImageDirList.size()-1)))
        return UNKNOWN_PICTO;

    // Get target picto:
    Node *node = mRootNode->child(row);
    if (!node)
        return UNKNOWN_PICTO;

    // Get target image dir:
    QDir targetImageDir = mImageDirList[col];
    QString targetPicto = targetImageDir.absoluteFilePath(node->fullRelativePath());
    QFileInfo fi(targetPicto);
    QImage img(targetPicto);

    // Does not exist?
    if (!fi.exists())
        return UNKNOWN_PICTO;

    return targetPicto;
}

// Get dir name:
QString ImageModel::getDirName(int col) const
{
    if ((col < 0) || (col > (mImageDirList.size()-1)))
        return "";
    return mImageDirList[col].dirName();
}

// Get dir id:
QString ImageModel::getDirId(int col) const
{
    if ((col < 0) || (col > (mDirIds.size()-1)))
        return "";
    return mDirIds[col];
}
