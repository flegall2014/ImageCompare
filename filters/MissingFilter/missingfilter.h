#ifndef MISSINGFILTER_H
#define MISSINGFILTER_H
#include <QDir>
#include "ifilter.h"
#include "missingfilter_global.h"

class MISSINGFILTERSHARED_EXPORT MissingFilter : public QObject, public IFilter
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "IFilter")
    Q_INTERFACES(IFilter)

public:
    // Constructor:
    MissingFilter(QObject *parent=0);

    // Destructor:
    virtual ~MissingFilter();

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

#endif // MISSINGFILTER_H
