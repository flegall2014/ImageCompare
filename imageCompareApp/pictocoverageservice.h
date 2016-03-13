#ifndef PICTOCOVERAGESERVICE_H
#define PICTOCOVERAGESERVICE_H
#include <QObject>
#include <QDir>
#include "iservice.h"
class PictoHunter;
class Controller;

class PictoCoverageService : public QObject, public IService
{
    Q_OBJECT

public:
    // Constructor:
    PictoCoverageService(QObject *parent = 0);

    // Destructor:
    virtual ~PictoCoverageService();

    // Startup:
    virtual bool startup();

    // Shutdown:
    virtual void shutdown();

    // Perform picto coverage:
    void performPictoCoverage(const QStringList &fileExtensions, const QDir &pictoDir, const QDir &srcCodeDir,
        const QStringList &exclusionList);

    // Set controller:
    void setController(Controller *controller);

    // Clean picto directory:
    void cleanPictoDirectory();

public slots:
    // Picto used:
    void onPictoUsed(const QString &picto);

    // Picto processed:
    void onPictoProcessed();

    // Picto hunt finished:
    void onPictoHuntFinished();

private:
    // Build picto base:
    QStringList buildPictoBase(const QString &srcDir);

    // Create report:
    void createReport();

private:
    // Picto dir:
    QDir mPictoDir;

    // List of used pictos:
    QStringList mUsedPictos;

    // List of unused pictos:
    QStringList mUnusedPictos;

    // Picto base names:
    QStringList mPictoBaseNames;

    // Picto types:
    QStringList mPictoTypes;

    // Exclusion list:
    QStringList mExclusionList;

    // To keep picto:
    QStringList mToKeepPicto;

    // Initialize:
    int mNFilesToProcess;

    // Reset number of processed files:
    int mNProcessedFiles;

    // Reset number of created workers:
    int mNCreatedWorkers;

    // Reset number of completed workers:
    int mNCompletedWorkers;

    // File extensions:
    QStringList mFileExtensions;

    // Clear status worker list:
    QList<PictoHunter *> mPictoHunters;

    // Src code files:
    QStringList mSrcCodeFiles;

    // Controller:
    Controller *mController;

    // Minimum picto length:
    int mMinPictoLength;

    // Suffixes:
    QStringList mSuffixes;

signals:
    // Picto used:
    void pictoUsed(const QString &picto);
};

#endif // PICTOCOVERAGESERVICE_H
