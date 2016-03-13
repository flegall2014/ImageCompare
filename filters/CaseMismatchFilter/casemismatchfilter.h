#ifndef CASEMISMATCHFILTER_H
#define CASEMISMATCHFILTER_H
#include "casemismatchfilter_global.h"
#include "ifilter.h"

class CASEMISMATCHFILTERSHARED_EXPORT CaseMismatchFilter : public QObject, public IFilter
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "IFilter")
    Q_INTERFACES(IFilter)

public:
    // Constructor:
    CaseMismatchFilter(QObject *parent=0);

    // Destructor:
    virtual ~CaseMismatchFilter();

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

    // Return color:
    virtual QString filterColor() const;

    // Get actual casing:
    QString getActualCasing(const QString &inputFile);

private:
    // Image filters:
    QStringList mImageFilters;
};

#endif // CASEMISMATCHFILTER_H
