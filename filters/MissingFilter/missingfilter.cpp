#include "missingfilter.h"
#include <QFileInfo>
#include <QDebug>

// Constructor:
MissingFilter::MissingFilter(QObject *parent) : QObject(parent)
{

}

// Destructor:
MissingFilter::~MissingFilter()
{

}

// Run:
bool MissingFilter::execute(const QList<QDir> &directories, const QString &srcFile)
{
    if (directories.size() < 2)
        return false;
    for (int i=0; i<directories.size(); i++)
    {
        QString file = directories[i].absoluteFilePath(srcFile);
        QFileInfo fi(file);
        if (!fi.exists())
            return true;
    }

    return false;
}

// Return label:
QString MissingFilter::label() const
{
    return tr("Missing");
}

// Report problem?
bool MissingFilter::reportProblem() const
{
    return true;
}

// Critical?
int MissingFilter::order() const
{
    return 0;
}

// Set filter:
void MissingFilter::setFilters(const QStringList &filters)
{
    mImageFilters = filters;
}

// Return filter color:
QString MissingFilter::filterColor() const
{
    return "#00aba9";
}
