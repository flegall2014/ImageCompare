#include "largefilefilter.h"
#include <QFileInfo>
#include <QImage>

// Constructor:
LargeFileFilter::LargeFileFilter(QObject *parent) : QObject(parent),
    mMinimumSize(50000)
{

}

// Destructor:
LargeFileFilter::~LargeFileFilter()
{

}

// Run:
bool LargeFileFilter::execute(const QList<QDir> &directories, const QString &srcFile)
{
    for (int i=0; i<directories.size(); i++)
    {
        QString file = directories[i].absoluteFilePath(srcFile);
        QFileInfo fi(file);
        if (fi.size() > mMinimumSize)
            return true;

    }
    return false;
}

// Return label:
QString LargeFileFilter::label() const
{
    return tr("Large File");
}

// Report problem?
bool LargeFileFilter::reportProblem() const
{
    return false;
}

// Critical?
int LargeFileFilter::order() const
{
    return 5;
}

// Set filters:
void LargeFileFilter::setFilters(const QStringList &filters)
{
    mImageFilters = filters;
}

// Return filter color:
QString LargeFileFilter::filterColor() const
{
    return "#1d1d1d";
}
