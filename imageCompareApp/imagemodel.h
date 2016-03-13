#ifndef IMAGEMODEL_H
#define IMAGEMODEL_H
#include <QAbstractListModel>
#include <QDir>
class Node;
class Controller;

class ImageModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum Roles {
        ImageRowRole,
        ImageBaseNameRole,
        ImageProblemRole
    };

    // Constructor:
    ImageModel(QObject *parent=0);

    // Destructor:
    virtual ~ImageModel();

    // Set controller:
    void setController(Controller *controller);

    // Row count:
    virtual int rowCount(const QModelIndex &parent=QModelIndex()) const;

    // Role names:
    QHash<int, QByteArray> roleNames() const;

    // Data:
    virtual QVariant data(const QModelIndex &index, int role) const;

    // Setup model:
    void setupModel(Node *rootNode, const QList<QDir> &imageDirList, const QStringList &dirIds);

    // Root node:
    Node *rootNode() const;

    // Get node:
    Node *getNode(int row) const;

    // Get image:
    QString getImage(int row, int col) const;   

    // Get dir name:
    QString getDirName(int col) const;

    // Get dir id:
    QString getDirId(int col) const;

    // Return number of columns:
    int nCols() const;

private:
    // Controller:
    Controller *mController;

    // Root node:
    Node *mRootNode;

    // Image dir list:
    QList<QDir> mImageDirList;

    // Dir ids:
    QStringList mDirIds;

signals:
    // Number of columns changed:
    void nColsChanged();
};

#endif // IMAGEMODEL_H
