#ifndef KOFILTER_H
#define KOFILTER_H
#include <QDir>
#include "ifilter.h"
#include "kofilter_global.h"

class KOFILTERSHARED_EXPORT KOFilter : public QObject, public IFilter
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "IFilter")
    Q_INTERFACES(IFilter)

public:
    // Constructor:
    KOFilter(QObject *parent=0);

    // Destructor:
    virtual ~KOFilter();

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

#endif // KOFILTER_H
