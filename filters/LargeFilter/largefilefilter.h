#ifndef LARGEFILEFILTER_H
#define LARGEFILEFILTER_H
#include <QDir>
#include "ifilter.h"
#include "largefilter_global.h"

class LARGEFILTERSHARED_EXPORT LargeFileFilter : public QObject, public IFilter
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "IFilter")
    Q_INTERFACES(IFilter)

public:
    // Constructor:
    LargeFileFilter(QObject *parent=0);

    // Destructor:
    virtual ~LargeFileFilter();

    // Execute:
    virtual bool execute(const QList<QDir> &directories, const QString &srcFile);

    // Return label:
    virtual QString label() const;

    // Report problem?
    virtual bool reportProblem() const;

    // Critical?
    virtual int order() const;

    // Set filters:
    virtual void setFilters(const QStringList &filters);

    // Return filter color:
    virtual QString filterColor() const;

private:
    // Minimum size:
    long mMinimumSize;

    // Image filters:
    QStringList mImageFilters;
};

#endif // LARGEFILEFILTER_H
