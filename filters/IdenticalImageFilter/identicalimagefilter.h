#ifndef IDENTICALIMAGEFILTER_H
#define IDENTICALIMAGEFILTER_H
#include <QDir>
#include "ifilter.h"
#include "identicalimagefilter_global.h"

class IDENTICALIMAGEFILTERSHARED_EXPORT IdenticalImageFilter : public QObject, public IFilter
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "IFilter")
    Q_INTERFACES(IFilter)

public:
    // Constructor:
    IdenticalImageFilter(QObject *parent=0);

    // Destructor:
    virtual ~IdenticalImageFilter();

    // Execute:
    virtual bool execute(const QList<QDir> &directories, const QString &srcFile);

    // Return label:
    virtual QString label() const;

    // Report problem?
    virtual bool reportProblem() const;

    // Set filters:
    virtual void setFilters(const QStringList &filters);

    // Critical?
    virtual int order() const;

    // Return filter color:
    virtual QString filterColor() const;

private:
    // Compare images:
    bool imageCompare(const QString &dir1File, const QString &dir2File);

private:
    // Image filters:
    QStringList mImageFilters;
};

#endif // IDENTICALIMAGEFILTER_H
