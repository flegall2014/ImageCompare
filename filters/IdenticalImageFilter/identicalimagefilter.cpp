#include "identicalimagefilter.h"
#include <QFileInfo>
#include <QImage>
#include <QCryptographicHash>
#include <QBitArray>
#include <QDebug>

// Constructor:
IdenticalImageFilter::IdenticalImageFilter(QObject *parent) : QObject(parent)
{

}

// Destructor:
IdenticalImageFilter::~IdenticalImageFilter()
{

}

// Compare images:
bool IdenticalImageFilter::imageCompare(const QString &dir1File, const QString &dir2File)
{
    // Check src file:
    QFileInfo fi1(dir1File);

    // Check dst file:
    QFileInfo fi2(dir2File);

    // Check files:
    if (!fi1.exists() || !fi2.exists())
        return false;

    QImage img1(dir1File);
    QImage img2(dir2File);
    if (img1.size() != img2.size())
        return false;

    for (int j=0; j<img1.height(); j++)
        for (int i=0; i<img1.width(); i++)
        {
            QRgb color1 = img1.pixel(i, j);
            QRgb color2 = img2.pixel(i, j);
            if (color1 != color2)
                return false;
        }

    return true;
}

// Run:
bool IdenticalImageFilter::execute(const QList<QDir> &directories, const QString &srcFile)
{
    if (directories.size() < 2)
        return false;

    // Get reference file:
    QString refFile = directories.first().absoluteFilePath(srcFile);

    // Get reference state:
    for (int i=1; i<directories.size(); i++)
    {
        // Exists?
        QString file = directories[i].absoluteFilePath(srcFile);
        if (!imageCompare(refFile, file))
            return false;
    }

    return true;
}

// Return label:
QString IdenticalImageFilter::label() const
{
    return tr("Identical Images");
}

// Report problem?
bool IdenticalImageFilter::reportProblem() const
{
    return false;
}

// Set filters:
void IdenticalImageFilter::setFilters(const QStringList &filters)
{
    mImageFilters = filters;
}

// Critical?
bool IdenticalImageFilter::order() const
{
    return false;
}

// Return filter color:
QString IdenticalImageFilter::filterColor() const
{
    return "#ff0097";
}

