#include "weightfilter.h"
#include <QFileInfo>
#include <QImage>

// Constructor:
WeightFilter::WeightFilter(QObject *parent) : QObject(parent)
{

}

// Destructor:
WeightFilter::~WeightFilter()
{

}

// Execute:
bool WeightFilter::execute(const QList<QDir> &directories, const QString &srcFile)
{
    if (directories.size() < 2)
        return false;
    QList<int> allWeight;
    for (int i=0; i<directories.size(); i++)
    {
        QString file = directories[i].absoluteFilePath(srcFile);
        QFileInfo fi(file);
        if ((allWeight.size() > 0) && (!allWeight.contains(fi.size())))
            return true;
        allWeight << fi.size();
    }
    return false;
}

// Return label:
QString WeightFilter::label() const
{
    return tr("Weight Mismatch");
}

// Report problem?
bool WeightFilter::reportProblem() const
{
    return false;
}

// Critical:
int WeightFilter::order() const
{
    return 8;
}

// Set filters:
void WeightFilter::setFilters(const QStringList &filters)
{
    mImageFilters = filters;
}

// Return filter color:
QString WeightFilter::filterColor() const
{
    return "#ffc40d";
}
