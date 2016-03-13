#ifndef STATUSWORKER_H
#define STATUSWORKER_H
#include <QObject>
#include <QList>
#include <QDir>
#include <QRunnable>
class IFilter;
class Node;

class StatusWorker : public QObject, public QRunnable
{
    Q_OBJECT

public:
    // Constructor:
    StatusWorker(const QStringList &nodeFullRelativePath, const QList<QDir> &directories, const QList<IFilter *> &filters);

    // Destructor:
    virtual ~StatusWorker();

    // Run:
    virtual void run();

    // Set id:
    void setId(int id);

    // Return id:
    int id() const;

    // Stop worker:
    bool stop;

private:
    // Nodes:
    QStringList mNodeFullRelativePath;

    // Directories:
    QList<QDir> mDirectories;

    // Filters:
    QList<IFilter *> mFilters;

    // id:
    int mId;

signals:
    // Finished:
    void finished(int id);

    // Progress changed:
    void progressChanged(double progress);

    // Result available:
    void resultAvailable(const QString &srcFile, const QBitArray &results, bool nodeHasProblem);
};

#endif // STATUSWORKER_H
