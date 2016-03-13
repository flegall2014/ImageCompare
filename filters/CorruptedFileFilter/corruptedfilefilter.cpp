#include "corruptedfilefilter.h"
#include <QFileInfo>
#include <QImage>

// Constructor:
CorruptedFileFilter::CorruptedFileFilter(QObject *parent) : QObject(parent)
{

}

// Destructor:
CorruptedFileFilter::~CorruptedFileFilter()
{

}

// Run:
bool CorruptedFileFilter::execute(const QList<QDir> &directories, const QString &srcFile)
{
    for (int i=0; i<directories.size(); i++)
    {
        QString fileName = directories[i].absoluteFilePath(srcFile);
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly))
            return true;
        file.close();
        QImage image(fileName);
        if (image.isNull())
            return true;
    }

    return false;
}

// Return label:
QString CorruptedFileFilter::label() const
{
    return tr("Corrupted");
}

// Report problem?
bool CorruptedFileFilter::reportProblem() const
{
    return true;
}

// Critical?
int CorruptedFileFilter::order() const
{
    return 1;
}

// Set filters:
void CorruptedFileFilter::setFilters(const QStringList &filters)
{
    mImageFilters = filters;
}

// Return filter color:
QString CorruptedFileFilter::filterColor() const
{
    return "#00a300";
}
