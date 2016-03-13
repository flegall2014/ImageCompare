#ifndef CORRUPTEDFILEFILTER_H
#define CORRUPTEDFILEFILTER_H
#include <QDir>
#include "ifilter.h"
#include "corruptedfilefilter_global.h"

class CORRUPTEDFILEFILTERSHARED_EXPORT CorruptedFileFilter : public QObject, public IFilter
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "IFilter")
    Q_INTERFACES(IFilter)

public:
    // Constructor:
    CorruptedFileFilter(QObject *parent=0);

    // Destructor:
    virtual ~CorruptedFileFilter();

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

#endif // CORRUPTEDFILEFILTER_H
