#ifndef TYPOFILTER_H
#define TYPOFILTER_H
#include <QDir>
#include "ifilter.h"
#include "typofilter_global.h"

class TYPOFILTERSHARED_EXPORT TypoFilter : public QObject, public IFilter
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "IFilter")
    Q_INTERFACES(IFilter)

public:
    // Constructor:
    TypoFilter(QObject *parent=0);

    // Destructor:
    virtual ~TypoFilter();

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

#endif // TYPOFILTER_H
