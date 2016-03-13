#ifndef IFILTER_H
#define IFILTER_H
#include <QString>
#include <QDir>

class IFilter
{
public:
    // Return label:
    virtual QString label() const = 0;

    // Execute:
    virtual bool execute(const QList<QDir> &directories, const QString &srcFile) = 0;

    // Report problem?
    virtual bool reportProblem() const = 0;

    // Set filters:
    virtual void setFilters(const QStringList &filters) = 0;

    // Critical?
    virtual int order() const = 0;

    // Return filter color:
    virtual QString filterColor() const = 0;

    // Destructor:
    virtual ~IFilter() {

    }
};

QT_BEGIN_NAMESPACE
#define IFilter_iid "IFilter"
Q_DECLARE_INTERFACE(IFilter, IFilter_iid)
QT_END_NAMESPACE

#endif // IFILTER_H
