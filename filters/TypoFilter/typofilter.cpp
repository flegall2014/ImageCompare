#include "typofilter.h"
#include <QDebug>

// Constructor:
TypoFilter::TypoFilter(QObject *parent) : QObject(parent)
{

}

// Destructor:
TypoFilter::~TypoFilter()
{

}

// Run:
bool TypoFilter::execute(const QList<QDir> &directories, const QString &srcFile)
{
    Q_UNUSED(directories);
    QRegExp rx("^[a-zA-Z0-9_]*$");
    QFileInfo fi(srcFile);
    QString fileBaseName = fi.baseName();
    QString tmp = fileBaseName;
    tmp = tmp.replace(" ", "");
    return (tmp != fileBaseName);// || (!rx.exactMatch(fi.baseName()));
}

// Return label:
QString TypoFilter::label() const
{
    return tr("File Typo");
}

// Report problem?
bool TypoFilter::reportProblem() const
{
    return true;
}

// Critical?
int TypoFilter::order() const
{
    return 7;
}

// Set filters:
void TypoFilter::setFilters(const QStringList &filters)
{
    mImageFilters = filters;
}

// Return filter color:
QString TypoFilter::filterColor() const
{
    return "#b91d47";
}
