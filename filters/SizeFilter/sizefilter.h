#ifndef SIZEFILTER_H
#define SIZEFILTER_H
#include "sizefilter_global.h"
#include "ifilter.h"

class SIZEFILTERSHARED_EXPORT SizeFilter : public QObject, public IFilter
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "IFilter")
    Q_INTERFACES(IFilter)

public:
    // Constructor:
    SizeFilter(QObject *parent=0);

    // Destructor:
    virtual ~SizeFilter();

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
    // Image filters:
    QStringList mImageFilters;
};

#endif // SIZEFILTER_H
