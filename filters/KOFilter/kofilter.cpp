#include "kofilter.h"
#include <QFileInfo>
#include <QImage>
#include <QCryptographicHash>
#include <QBitArray>
#include <QDebug>

// Constructor:
KOFilter::KOFilter(QObject *parent) : QObject(parent)
{

}

// Destructor:
KOFilter::~KOFilter()
{

}

// Compare images:
bool KOFilter::imageCompare(const QString &dir1File, const QString &dir2File)
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
bool KOFilter::execute(const QList<QDir> &directories, const QString &srcFile)
{
    Q_UNUSED(directories);
    Q_UNUSED(srcFile);
    // Note: recomputed by logic:
    // isKO = !isOK
    return false;
    /*
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
            return true;
    }

    return false;
    */
}

// Return label:
QString KOFilter::label() const
{
    return tr("Different Images");
}

// Report problem?
bool KOFilter::reportProblem() const
{
    return true;//_mode == DIRECTORY_COMPARE ? true : false;
}

// Set filters:
void KOFilter::setFilters(const QStringList &filters)
{
    mImageFilters = filters;
}

// Critical?
int KOFilter::order() const
{
    return 3;
}

// Return filter color:
QString KOFilter::filterColor() const
{
    return "#9f00a7";
}

