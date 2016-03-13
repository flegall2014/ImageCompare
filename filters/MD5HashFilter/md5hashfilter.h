#ifndef MD5HASHFILTER_H
#define MD5HASHFILTER_H
#include <QDir>
#include "ifilter.h"
#include "md5hashfilter_global.h"

class MD5HASHFILTERSHARED_EXPORT MD5HashFilter : public QObject, public IFilter
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "IFilter")
    Q_INTERFACES(IFilter)

public:
    // Constructor:
    MD5HashFilter(QObject *parent=0);

    // Destructor:
    virtual ~MD5HashFilter();

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
    // Return hash:
    QByteArray md5Hash(const QString &inputImage);

private:
    // Image filters:
    QStringList mImageFilters;
};

#endif // MD5HASHFILTER_H
