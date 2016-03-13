#include "md5hashfilter.h"
#include <QFileInfo>
#include <QCryptographicHash>

// Constructor:
MD5HashFilter::MD5HashFilter(QObject *parent) : QObject(parent)
{

}

// Destructor:
MD5HashFilter::~MD5HashFilter()
{

}

// Run:
bool MD5HashFilter::execute(const QList<QDir> &directories, const QString &srcFile)
{
    if (directories.size() < 2)
        return false;
    // Check input:
    QByteArray refMD5;
    int index = -1;
    for (int i=0; i<directories.size(); i++)
    {
        QString refFile = directories[i].absoluteFilePath(srcFile);
        refMD5 = md5Hash(refFile);
        index = i;
        break;
    }

    // Check ref MD5:
    if (index < 0)
        return false;

    // Browse:
    for (int i=0; i<directories.size(); i++)
    {
        if (i == index)
            continue;

        // Exists?
        QString file = directories[i].absoluteFilePath(srcFile);

        QByteArray currentMD5 = md5Hash(file);
        if (currentMD5 != refMD5)
            return false;
    }

    return true;
}

// Return label:
QString MD5HashFilter::label() const
{
    return tr("MD5 Identical");
}

// Report problem?
bool MD5HashFilter::reportProblem() const
{
    return false;
}

// Critical?
bool MD5HashFilter::order() const
{
    return false;
}

// Set filters:
void MD5HashFilter::setFilters(const QStringList &filters)
{
    mImageFilters = filters;
}

// Return filter color:
QString MD5HashFilter::filterColor() const
{
    return "pink";
}

// Return hash:
QByteArray MD5HashFilter::md5Hash(const QString &inputImage)
{
    QCryptographicHash crypto(QCryptographicHash::Md5);
    QFile file(inputImage);
    if (!file.open(QFile::ReadOnly))
        return "";
    crypto.addData(file.readAll());
    return crypto.result();
}
