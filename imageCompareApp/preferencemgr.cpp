#include "preferencemgr.h"
#include "utils.h"
#include <QSettings>
#include <QDebug>

// Constructor:
PreferenceMgr::PreferenceMgr(QObject *parent) : QObject(parent),
    mController(0)
{

}

// Set controller:
void PreferenceMgr::setController(Controller *controller)
{
    mController = controller;
}

// Get preference:
QVariant PreferenceMgr::getPreference(const QString &preference) const
{
    return mPreferences[preference];
}

// Startup:
bool PreferenceMgr::startup()
{
    // Do we have an ini folder?
    QDir appDir = Utils::appDir();
    appDir.cdUp();
    if (!appDir.cd("ini"))
        appDir.mkdir("ini");

    // Read preferences:
    readPreferences();

    return true;
}

// Shutdown:
void PreferenceMgr::shutdown()
{
    // Save preferences:
    savePreferences();
}

// Return preferences:
const QVariantMap &PreferenceMgr::preferences() const
{
    return mPreferences;
}

// Set preferences:
void PreferenceMgr::setPreferences(const QVariantMap &preferences)
{
    mPreferences = preferences;
}

// Save preferences:
void PreferenceMgr::savePreferences()
{
    // Read preferences.ini:
    QDir preferenceDir = Utils::preferenceDir();
    QString preferencesFile = preferenceDir.filePath("preferences.ini");
    qDebug() << "SAVING: " << preferencesFile << " INI FILE";

    QSettings settings(preferencesFile, QSettings::IniFormat);
    settings.clear();
    settings.beginGroup("Parameter");
    for (QVariantMap::iterator it=mPreferences.begin(); it!=mPreferences.end(); ++it)
        settings.setValue(it.key(), it.value());
    settings.endGroup();
}

// Read preferences:
void PreferenceMgr::readPreferences()
{
    // Read preferences.ini:
    QDir preferenceDir = Utils::preferenceDir();
    QString preferencesFile = preferenceDir.filePath("preferences.ini");
    QFileInfo fi(preferencesFile);
    if (fi.exists())
    {
        qDebug() << "READING: " << preferencesFile << " INI FILE";

        QSettings settings(preferencesFile, QSettings::IniFormat);
        settings.beginGroup("Parameter");

        // Get all keys:
        QStringList allKeys = settings.allKeys();

        for (int i=0; i<allKeys.size(); i++)
        {
            // Get actual parameter name:
            QString actualParameter = allKeys[i].simplified().toUpper();

            // Read:
            QVariant parameterValue = settings.value(allKeys[i]);
            mPreferences[actualParameter].setValue(parameterValue);
        }

        settings.endGroup();
    }

    // Sanity check:
    sanityCheck();
}

// Sanity check:
void PreferenceMgr::sanityCheck()
{
    QStringList defaultImageFilter;
    defaultImageFilter << "*.png";

    // Check IMAGE_FILTER:
    if (!mPreferences.contains("IMAGE_FILTER"))
        mPreferences["IMAGE_FILTER"] = defaultImageFilter;

    qDebug() << "FOUND PREFERENCES" << "\n";
    qDebug() << mPreferences;
}
