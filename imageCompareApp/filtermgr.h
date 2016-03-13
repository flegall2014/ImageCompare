#ifndef FILTERMGR_H
#define FILTERMGR_H
#include <QObject>
#include "iservice.h"
#include "ifilter.h"
class Controller;

class FilterMgr : public QObject, public IService
{
    Q_OBJECT

public:
    // Constructor:
    explicit FilterMgr(QObject *parent = 0);

    // Destructor:
    virtual ~FilterMgr();

    // Return plugins:
    const QList<IFilter *> &filters() const;

    // Startup:
    virtual bool startup();

    // Shutdown:
    virtual void shutdown();

    // Set controller:
    void setController(Controller *controller);

    // Set mode:
    void setMode(const IFilter::Mode &mode);

    // Return filter label at index:
    Q_INVOKABLE QString filterLabel(int index) const;

    // Return number of filters:
    Q_INVOKABLE int nFilters() const;

    // Filter report problem?
    Q_INVOKABLE bool reportProblem(int index) const;

private:
    // Load plugins:
    QList<IFilter *> loadPlugins();

    // Release plugins:
    void releasePlugins();

private:
    // Controller:
    Controller *mController;

    // Plugin list:
    QList<IFilter *> mFilters;
};

#endif // FILTERMGR_H
