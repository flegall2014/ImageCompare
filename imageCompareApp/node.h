#ifndef NODE_H
#define NODE_H
#include <QString>
#include <QList>
#include <QHash>
#include <QBitArray>

class Node
{
public:
    enum Type {
        UNDEFINED=0,
        IMAGE,
        DIR
    };

    // Constructor:
    Node(const QString &fullRelativePath, const Node::Type &type=UNDEFINED, bool isRootNode=true);

    // Destructor:
    virtual ~Node();

    // Add child:
    void addChild(Node *node, bool setParent=true);

    // Remove child:
    void removeChild(Node *node);

    // Child count:
    int childCount() const;

    // Return child node at position:
    Node *child(int row) const;

    // Return full path:
    const QString &fullRelativePath() const;

    // Retur base name:
    const QString &baseName() const;

    // Set parent:
    void setParent(Node *node);

    // Return parent:
    Node *parent() const;

    // Return row:
    int row();

    // Return childs:
    const QList<Node *> &childs() const;

    // Set type:
    void setType(const Node::Type &type);

    // Return type:
    const Node::Type &type() const;

    // Set filter status:
    void setFilterStatus(const QBitArray &bitArray);

    // Return filter status:
    const QBitArray &filterStatus() const;

    // Root node?
    bool isRootNode() const;

    // Clear:
    void clear();

    // Has child:
    bool hasChild(Node *node) const;

    // Remove image nodes:
    QList<Node *> removeImageNodes();

    // Set node has problem:
    void setHasProblem(bool hasProblem);

    // Does not have problem?
    bool hasProblem() const;

private:
    // Node type:
    Type mType;

    // Full relative path:
    QString mFullRelativePath;

    // Base name:
    QString mBaseName;

    // Parent:
    Node *mParent;

    // Childs:
    QList<Node *> mChilds;

    // Filter status:
    QBitArray mFilterStatus;

    // Root node:
    bool mIsRootNode;

    // Has problem?
    bool mNodeHasProblem;
};

#endif // NODE_H
