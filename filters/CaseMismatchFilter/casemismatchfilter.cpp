#include "casemismatchfilter.h"
#include <QFileInfo>
#include <QImage>
#include <QDebug>

// Constructor:
CaseMismatchFilter::CaseMismatchFilter(QObject *parent) : QObject(parent)
{

}

// Destructor:
CaseMismatchFilter::~CaseMismatchFilter()
{

}

// Run:
bool CaseMismatchFilter::execute(const QList<QDir> &directories, const QString &srcFile)
{
    if (directories.size() < 2)
        return false;
    QStringList targetFiles;
    for (int i=0; i<directories.size(); i++)
    {
        QString file = getActualCasing(directories[i].absoluteFilePath(srcFile));
        targetFiles << file.replace(directories[i].absolutePath() + "/", "", Qt::CaseInsensitive);
        if (targetFiles.toSet().size() != 1)
            return true;
    }

    return false;
}

// Return label:
QString CaseMismatchFilter::label() const
{
    return tr("Case Mismatch");
}

// Report problem?
bool CaseMismatchFilter::reportProblem() const
{
    return true;
}

// Set filters:
void CaseMismatchFilter::setFilters(const QStringList &filters)
{
    mImageFilters = filters;
}

// Critical:
int CaseMismatchFilter::order() const
{
    return 4;
}

// Return filter color:
QString CaseMismatchFilter::filterColor() const
{
    return "#99b433";
}

// Get actual casing:
QString CaseMismatchFilter::getActualCasing(const QString &inputFile)
{
    QFileInfo fi(inputFile);
    if (!fi.exists())
        return inputFile;

    // Get file dir:
    QDir fileDir = fi.absoluteDir();

    QString actualCaseFile = "";
    QList<QFileInfo> info = fileDir.entryInfoList(mImageFilters);
    for (int i=0; i<info.size(); i++)
    {
        if (info[i].absoluteFilePath().compare(inputFile, Qt::CaseInsensitive) == 0)
        {
            actualCaseFile = info[i].absoluteFilePath();
            break;
        }
    }

    return actualCaseFile.isEmpty() ? inputFile : actualCaseFile;
}
