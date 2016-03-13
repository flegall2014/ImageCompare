#include "node.h"
#include <QStringList>
#include <QFileInfo>
#include <QDebug>

// Constructor:
Node::Node(const QString &fullRelativePath, const Node::Type &type, bool isRootNode) : mType(type), mFullRelativePath(fullRelativePath),
    mBaseName(""), mParent(0), mIsRootNode(isRootNode), mNodeHasProblem(false)
{
    QStringList splitted = fullRelativePath.split("/");
    mBaseName = splitted.size() < 2 ? fullRelativePath : splitted.last();
}

// Destructor:
Node::~Node()
{
    qDeleteAll(mChilds);
}

// Add child:
void Node::addChild(Node *node, bool setParent)
{
    if (node)
    {
        mChilds << node;
        if (setParent)
            node->setParent(this);
    }
}

// Remove child:
void Node::removeChild(Node *node)
{
    mChilds.removeAll(node);
}

// Return child count:
int Node::childCount() const
{
    return mChilds.size();
}

// Return child node at position:
Node *Node::child(int row) const
{
    if ((row < 0) || (row > (mChilds.size()-1)))
        return 0;
    return mChilds[row];
}

// Return full path:
const QString &Node::fullRelativePath() const
{
    return mFullRelativePath;
}

// Return base name:
const QString &Node::baseName() const
{
    return mBaseName;
}

// Set parent:
void Node::setParent(Node *node)
{
    mParent = node;
}

// Return parent:
Node *Node::parent() const
{
    return mParent;
}

// Return row:
int Node::row()
{
    return mParent ? mParent->childs().indexOf(this) : -1;
}

// Return childs:
const QList<Node *> &Node::childs() const
{
    return mChilds;
}

// Set type:
void Node::setType(const Node::Type &type)
{
    mType = type;
}

// Return type:
const Node::Type &Node::type() const
{
    return mType;
}

// Set filter status:
void Node::setFilterStatus(const QBitArray &filterStatus)
{
    mFilterStatus = filterStatus;
}

// Return filter status:
const QBitArray &Node::filterStatus() const
{
    return mFilterStatus;
}

// Root node?
bool Node::isRootNode() const
{
    return mIsRootNode;
}

// Clear:
void Node::clear()
{
    mChilds.clear();
}

// Has child?
bool Node::hasChild(Node *node) const
{
    return mChilds.contains(node);
}

// Remove image nodes:
QList<Node *> Node::removeImageNodes()
{
    QList<Node *> out;
    for (int i=0; i<mChilds.size(); i++)
    {
        Node *child = mChilds[i];
        if (!child || (child->type() != Node::IMAGE))
            continue;
        out << child;
    }
    for (int i=0; i<out.size(); i++)
        mChilds.removeAll(out[i]);
    return out;
}

// Set node has problem:
void Node::setHasProblem(bool hasProblem)
{
    mNodeHasProblem = hasProblem;
}

// Does not have problem?
bool Node::hasProblem() const
{
    return mNodeHasProblem;
}
