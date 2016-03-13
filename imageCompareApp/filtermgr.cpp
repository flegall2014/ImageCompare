#include "filtermgr.h"
#include <QDir>
#include <QPluginLoader>
#include "utils.h"
#include "controller.h"

// Constructor:
FilterMgr::FilterMgr(QObject *parent) : QObject(parent),
    mController(0)
{

}

// Destructor:
FilterMgr::~FilterMgr()
{

}

// Return filters:
const QList<IFilter *> &FilterMgr::filters() const
{
    return mFilters;
}

// Startup:
bool FilterMgr::startup()
{
    mFilters = loadPlugins();
    return true;
}

// Release plugins:
void FilterMgr::releasePlugins()
{
    for (int i=0; i<mFilters.size(); i++)
        if (mFilters[i])
            delete mFilters[i];
    mFilters.clear();
}

// Shutdown:
void FilterMgr::shutdown()
{
    //releasePlugins();
}

// Load plugins:
QList<IFilter *> FilterMgr::loadPlugins()
{
    // Get plugin dir:
    QDir pluginsDir = Utils::appDir();

    // CD up:
    pluginsDir.cdUp();

    // CD plugins:
    if (!pluginsDir.cd("plugins"))
        return QList<IFilter *>();

    // Filter plugins:
    QList<IFilter *> filterPlugins;
    QMap<int, IFilter *> filterPluginMap;

    // Loop through plugins:
    foreach (QString fileName, pluginsDir.entryList(QDir::Files))
    {
        QPluginLoader pluginLoader(pluginsDir.absoluteFilePath(fileName));
        QObject *plugin = pluginLoader.instance();
        if (plugin)
        {
            // This is a filter:
            IFilter *filterPlugin = qobject_cast<IFilter *>(plugin);
            if (!filterPlugin)
                continue;

            filterPlugin->setFilters(mController->imageFilter());
            filterPlugin->_id = plugin->metaObject()->className();

            filterPluginMap[filterPlugin->order()] = filterPlugin;
        }
    }

    filterPlugins = filterPluginMap.values();
    qDebug() << "DETECTED FILTERS:";
    for (int i=0; i<filterPlugins.size(); i++)
        qDebug() << i << filterPlugins[i]->label();

    return filterPlugins;
}

// Set controller:
void FilterMgr::setController(Controller *controller)
{
    mController = controller;
}

// Set mode:
void FilterMgr::setMode(const IFilter::Mode &mode)
{
    for (int i=0; i<mFilters.size(); i++)
    {
        IFilter *filter = mFilters[i];
        if (!filter)
            continue;
        filter->_mode = mode;
    }
}

// Return filter label at index:
QString FilterMgr::filterLabel(int index) const
{
    if ((index < 0) || (index > (mFilters.size()-1)))
        return "";
    IFilter *filter = mFilters[index];
    return filter ? filter->label() : "";
}

// Return number of filters:
int FilterMgr::nFilters() const
{
    return mFilters.size();
}

// Filter report problem?
bool FilterMgr::reportProblem(int index) const
{
    if ((index < 0) || (index > (mFilters.size()-1)))
        return "";
    IFilter *filter = mFilters[index];
    return filter ? filter->reportProblem() : false;
}
