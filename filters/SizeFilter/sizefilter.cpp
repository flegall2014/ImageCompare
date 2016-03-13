#include "sizefilter.h"
#include <QFileInfo>
#include <QImage>
#include <QMap>

// Constructor:
SizeFilter::SizeFilter(QObject *parent) : QObject(parent)
{

}

// Destructor:
SizeFilter::~SizeFilter()
{

}

// Run:
bool SizeFilter::execute(const QList<QDir> &directories, const QString &srcFile)
{
    QList<int> allWidth;
    QList<int> allHeight;
    for (int i=0; i<directories.size(); i++)
    {
        QString file1 = directories[i].absoluteFilePath(srcFile);
        QImage img1(file1);
        if ((allWidth.size() > 0) && (!allWidth.contains(img1.width())))
            return true;
        if ((allHeight.size() > 0) && (!allHeight.contains(img1.height())))
            return true;
        allWidth << img1.width();
        allHeight << img1.height();
    }
    return false;
}

// Return label:
QString SizeFilter::label() const
{
    return tr("Size Mismatch");
}

// Report problem?
bool SizeFilter::reportProblem() const
{
    return true;
}

// Critical?
int SizeFilter::order() const
{
    return 6;
}

// Set filters:
void SizeFilter::setFilters(const QStringList &filters)
{
    mImageFilters = filters;
}

// Return filter color:
QString SizeFilter::filterColor() const
{
    return "#e3a21a";
}
