#include "statusworker.h"
#include <QBitArray>
#include "utils.h"
#include "ifilter.h"
#include "node.h"
#include <QDebug>

// Constructor:
StatusWorker::StatusWorker(const QStringList &nodeFullRelativePath, const QList<QDir> &directories, const QList<IFilter *> &filters) :
    stop(false), mNodeFullRelativePath(nodeFullRelativePath), mDirectories(directories), mFilters(filters), mId(-1)
{
    setAutoDelete(true);
}

// Destructor:
StatusWorker::~StatusWorker()
{

}

// Process:
void StatusWorker::run()
{
    int end = mNodeFullRelativePath.size();
    QBitArray results;
    results.resize(mFilters.size());

    // Reserved slots:
    for (int index=0; index<end; index++)
    {       
        // Get results:
        bool nodeHasProblem = false;
        results = Utils::evaluateFilters(mNodeFullRelativePath[index], mDirectories, mFilters, nodeHasProblem);

        // Notify result is available:
        emit resultAvailable(mNodeFullRelativePath[index], results, nodeHasProblem);

        // Stop:
        if (stop)
        {
            qDebug() << "STOPPING STATUS WORKER";
            break;
        }
    }

    emit finished(mId);
}

// Set id:
void StatusWorker::setId(int id)
{
    mId = id;
}

// Return id:
int StatusWorker::id() const
{
    return mId;
}
