#ifndef REPORTMGR_H
#define REPORTMGR_H
#include <QObject>
#include <QVariantMap>
#include <QDir>
#include "iservice.h"
class Controller;
class Node;
class IFilter;

class ReportMgr : public QObject, public IService
{
public:
    // Constructor:
    ReportMgr(QObject *parent=0);

    // Startup:
    virtual bool startup();

    // Shutdown:
    virtual void shutdown();

    // Set controller:
    void setController(Controller *controller);

    // Save preferences:
    void saveReport(Node *problematicNode, const QList<IFilter *> &filters, const QList<QDir> &imageDirList);

    // Save report:
    void saveReport(const QHash<QString, QStringList> &stats, const QList<QDir> &imageDirList);

private:
    // Controller:
    Controller *mController;
};

#endif // REPORTMGR_H
