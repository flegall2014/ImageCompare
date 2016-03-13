#include "okfilter.h"
#include <QFileInfo>
#include <QImage>
#include <QCryptographicHash>
#include <QColor>
#include <QRgb>
#include <QBitArray>
#include <QDebug>

// Constructor:
OKFilter::OKFilter(QObject *parent) : QObject(parent)
{

}

// Destructor:
OKFilter::~OKFilter()
{

}

// Run:
bool OKFilter::execute(const QList<QDir> &directories, const QString &srcFile)
{
    if (directories.size() < 2)
        return false;
    // Get reference file:
    QString refFile = directories.first().absoluteFilePath(srcFile);
    QImage img(refFile);
    int nPixels = img.width()*img.height();
    int threshold = qRound(.5*nPixels);

    // Get reference state:
    QBitArray refState = imageToVect(refFile);
    for (int i=1; i<directories.size(); i++)
    {
        // Exists?
        QString file = directories[i].absoluteFilePath(srcFile);
        QBitArray currentState = imageToVect(file);

        QBitArray tmp = (~refState & currentState) | (refState & ~currentState);
        int nErrors = tmp.count(true);
        if (nErrors > threshold)
            return false;
    }

    return true;
}

// Return label:
QString OKFilter::label() const
{
    return tr("Similar Images");
}

// Report problem?
bool OKFilter::reportProblem() const
{
    return false;
}

// Critical?
int OKFilter::order() const
{
    return 2;
}

// Set filters:
void OKFilter::setFilters(const QStringList &filters)
{
    mImageFilters = filters;
}

// Return filter color:
QString OKFilter::filterColor() const
{
    return "#a13c2b";
}

// Compare images:
QBitArray OKFilter::imageToVect(const QString &inputImage)
{
    // Check src file:
    QFileInfo fi(inputImage);

    // Check files:
    if (!fi.exists())
        return QBitArray();

    QImage img(inputImage);
    if (img.isNull())
        return QBitArray();
    QBitArray result;
    result.resize(img.width()*img.height());
    int c = 0;
    for (int j=0; j<img.height(); j++)
        for (int i=0; i<img.width(); i++)
        {
            QRgb color = img.pixel(i, j);
            int alpha = qAlpha(color);
            result[c++] = (alpha>0);
        }

    return result;
}

