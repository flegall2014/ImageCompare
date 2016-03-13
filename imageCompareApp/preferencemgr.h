#ifndef PREFERENCEMGR_H
#define PREFERENCEMGR_H
#include <QObject>
#include <QVariantMap>
#include "iservice.h"
class Controller;

class PreferenceMgr : public QObject, public IService
{
public:
    // Constructor:
    PreferenceMgr(QObject *parent=0);

    // Startup:
    virtual bool startup();

    // Shutdown:
    virtual void shutdown();

    // Return preferences:
    const QVariantMap &preferences() const;

    // Set preferences:
    void setPreferences(const QVariantMap &preferences);

    // Set controller:
    void setController(Controller *controller);

    // Get preference:
    QVariant getPreference(const QString &preference) const;

private:
    // Save preferences:
    void savePreferences();

    // Read preferences:
    void readPreferences();

    // Sanity check:
    void sanityCheck();

private:
    // Controller:
    Controller *mController;

    // Preferences:
    QVariantMap mPreferences;
};

#endif // PREFERENCEMGR_H
