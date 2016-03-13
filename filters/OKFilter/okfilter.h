#ifndef OKFILTER_H
#define OKFILTER_H
#include <QDir>
#include "ifilter.h"
#include "okfilter_global.h"

class OKFILTERSHARED_EXPORT OKFilter : public QObject, public IFilter
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "IFilter")
    Q_INTERFACES(IFilter)

public:
    // Constructor:
    OKFilter(QObject *parent=0);

    // Destructor:
    virtual ~OKFilter();

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
    // Compare images:
    QBitArray imageToVect(const QString &inputImage);

private:
    // Image filters:
    QStringList mImageFilters;
};

#endif // OKFILTER_H
