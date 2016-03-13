#include "pictocoverageservice.h"
#include "pictohunter.h"
#include "utils.h"
#include "controller.h"
#include <QThreadPool>
#include <QDebug>

// Constructor:
PictoCoverageService::PictoCoverageService(QObject *parent) : QObject(parent),
    mNFilesToProcess(0), mNProcessedFiles(0), mNCreatedWorkers(0), mNCompletedWorkers(0),
    mMinPictoLength(3)
{
    mPictoTypes << "*.png";
    mSuffixes << "_clicked" << "_disable";
    connect(this, SIGNAL(pictoUsed(QString)), SLOT(onPictoUsed(QString)));
}

// Destructor:
PictoCoverageService::~PictoCoverageService()
{
    for (int i=0; i<mPictoHunters.size(); i++)
        if (mPictoHunters[i])
            mPictoHunters[i]->stop = true;
    mPictoHunters.clear();
}

// Startup:
bool PictoCoverageService::startup()
{
    return true;
}

// Shutdown:
void PictoCoverageService::shutdown()
{
    for (int i=0; i<mPictoHunters.size(); i++)
        if (mPictoHunters[i])
            mPictoHunters[i]->stop = true;
}

// Picto used:
void PictoCoverageService::onPictoUsed(const QString &picto)
{
    if (!mUsedPictos.contains(picto, Qt::CaseInsensitive))
    {
        mUsedPictos << picto;

        for (int i=0; i<mSuffixes.size(); i++)
        {
            QString targetPicto = picto+mSuffixes[i];
            if (mPictoBaseNames.contains(targetPicto, Qt::CaseInsensitive) && (!mUsedPictos.contains(targetPicto, Qt::CaseInsensitive)))
                mUsedPictos << targetPicto;
        }
    }
}

// Picto processed:
void PictoCoverageService::onPictoProcessed()
{
    mNProcessedFiles++;
    if (mNFilesToProcess > 0)
        mController->setProgress((double)mNProcessedFiles/(double)mNFilesToProcess);
}

// Picto hunt finished:
void PictoCoverageService::onPictoHuntFinished()
{
    mNCompletedWorkers++;
    if (mNCompletedWorkers == mNCreatedWorkers)
    {
        mController->setAppBusy(false);
        qDebug() << "PICTO BASE CONTAINS: " << mPictoBaseNames.size() << " ITEMS";
        qDebug() << "FOUND: " << mUsedPictos.size() << " USED PICTOS";
        for (int i=0; i<mPictoBaseNames.size(); i++)
            if (!mUsedPictos.contains(mPictoBaseNames[i]))
                mUnusedPictos << mPictoBaseNames[i];
        qDebug() << "FOUND: " << mUnusedPictos.size() << " UNUSED PICTOS";
        createReport();
    }
}

// Perform picto coverage:
void PictoCoverageService::performPictoCoverage(const QStringList &fileExtensions, const QDir &pictoDir, const QDir &srcCodeDir,
    const QStringList &exclusionList)
{
    // Set picto dir:
    mPictoDir = pictoDir;

    // Set app busy:
    mController->setAppBusy(true);

    // Set exclusion list:
    mExclusionList = exclusionList;

    // Initialize:
    mNFilesToProcess = 0;

    // Reset number of processed files:
    mNProcessedFiles = 0;

    // Reset number of created workers:
    mNCreatedWorkers = 0;

    // Reset number of completed workers:
    mNCompletedWorkers = 0;

    // File extensions:
    mFileExtensions = fileExtensions;

    // Clear status worker list:
    mPictoHunters.clear();

    // Clear used pictos list:
    mUsedPictos.clear();

    // Clear unused pictos list:
    mUnusedPictos.clear();

    // Clear picto base names:
    mPictoBaseNames.clear();

    // Clear picto hunters:
    mPictoHunters.clear();

    // Src code files:
    mSrcCodeFiles.clear();

    // Step 0: read all src code in one string:
    qDebug() << "*** BUILDING SOURCE CODE BASE ***";
    QSet<QString> srcCodeFiles;
    Utils::files(srcCodeDir.absolutePath(), srcCodeFiles, fileExtensions);
    mSrcCodeFiles = srcCodeFiles.toList();

    QFile file;
    QStringList allData;

    // Get number of nodes to process:
    int nSrcCodeFileToProcess = mSrcCodeFiles.size();
    int segment = nSrcCodeFileToProcess/10;
    bool canContinue = true;

    int c = 0;
    for (int i=0; i<10; i++)
    {
        if (!canContinue)
            break;
        int start = i*(segment+1);
        int stop = start+segment;
        if (stop >= (nSrcCodeFileToProcess-1))
        {
            stop = (nSrcCodeFileToProcess-1);
            canContinue = false;
        }

        QString tmp;
        for (int j=start; j<stop; j++)
        {
            file.setFileName(mSrcCodeFiles[j]);
            if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
                  continue;
            tmp.append(file.readAll());
            file.close();
            mController->setProgress((double)++c/(double)nSrcCodeFileToProcess);
        }
        allData << tmp;
    }

    // Step 1: build picto base:
    qDebug() << "*** BUILDING PICTO BASE ***";
    mPictoBaseNames = buildPictoBase(pictoDir.absolutePath());

    // Step 2: create exclusion list:
    QStringList toKeepPictos;
    for (int i=0; i<mExclusionList.size(); i++)
    {
        QFileInfo fi(mExclusionList[i]);
        if (fi.isDir())
        {
            QStringList pictoBaseNames = buildPictoBase(mExclusionList[i]);
            toKeepPictos << pictoBaseNames;
        }
        else toKeepPictos << fi.baseName();
        mController->setProgress((double)i/(double)mExclusionList.size());
    }
    QSet<QString> tmp = toKeepPictos.toSet();
    mToKeepPicto = tmp.toList();

    for (int i=0; i<mToKeepPicto.size(); i++)
    {
        if (!mPictoBaseNames.contains(mToKeepPicto[i], Qt::CaseInsensitive))
            mPictoBaseNames << mToKeepPicto[i];
    }

    // Set number of files to process:
    mNFilesToProcess = mPictoBaseNames.size();

    // Step 3: build search threads:
    qDebug() << "*** BEGIN PICTO HUNT ***";
    int nWorkers = QThread::idealThreadCount();

    // Get number of nodes to process:
    segment = mNFilesToProcess/nWorkers;
    canContinue = true;

    // Clear status workers:
    mPictoHunters.clear();
    mNCreatedWorkers = 0;

    for (int i=0; i<nWorkers; i++)
    {
        if (!canContinue)
            break;
        int start = i*(segment+1);
        int stop = start+segment;
        if (stop >= (mNFilesToProcess-1))
        {
            stop = (mNFilesToProcess-1);
            canContinue = false;
        }

        // Prepare list of files to be processed by thread:
        QStringList subVect = Utils::subVector(mPictoBaseNames, start, stop);

        // Constructor:
        PictoHunter *pictoHunter = new PictoHunter(allData, subVect, mToKeepPicto);

        // Update picto hunters list:
        mPictoHunters << pictoHunter;

        // Increment number of created threads:
        mNCreatedWorkers++;

        // Connect:
        connect(pictoHunter, SIGNAL(pictoUsed(QString)), SLOT(onPictoUsed(QString)));
        connect(pictoHunter, SIGNAL(progressChanged()), SLOT(onPictoProcessed()));
        connect(pictoHunter, SIGNAL(finished()), SLOT(onPictoHuntFinished()));

        QThreadPool::globalInstance()->start(pictoHunter);
    }
}

// Set controller:
void PictoCoverageService::setController(Controller *controller)
{
    mController = controller;
}

// Clean picto directory:
void PictoCoverageService::cleanPictoDirectory()
{
    // Nothing to remove:
    if (mUnusedPictos.isEmpty())
        return;
    QDirIterator it(mPictoDir.absolutePath(), mPictoTypes, QDir::Files, QDirIterator::Subdirectories);
    while (it.hasNext())
    {
        QString file = it.next();
        QFileInfo fi(file);
        QString pictoBaseName = fi.baseName();
        if (!mUsedPictos.contains(pictoBaseName))
        {
            bool removed = QFile::remove(file);
            if (!removed)
                qDebug() << "CAN'T REMOVE: " << file;
            else
                qDebug() << "REMOVED: " << file << " SUCCESSFULLY";
        }
    }
}

// Build picto base:
QStringList PictoCoverageService::buildPictoBase(const QString &srcDir)
{
    QSet<QString> pictoFiles;
    QStringList pictoBaseNames;
    Utils::files(srcDir, pictoFiles, mPictoTypes);
    QSetIterator<QString> i(pictoFiles);
    int c = 0;
    while (i.hasNext())
    {
        QString pictoFile = i.next();
        QFileInfo fi(pictoFile);
        QString baseName = fi.baseName();
        if (!pictoBaseNames.contains(baseName, Qt::CaseInsensitive))
            pictoBaseNames << baseName;
        mController->setProgress((double)++c/(double)pictoFiles.size());
    }

    return pictoBaseNames;
}

// Create report:
void PictoCoverageService::createReport()
{
    // Get report dir:
    QDir reportDir = Utils::reportDir();

    // Build report file name:
    QString reportFileName = "pictocoverage_" + Utils::currentDateSuffix() + ".txt";

    // Get report file path:
    QString reportFile = reportDir.absoluteFilePath(reportFileName);
    qDebug() << "SAVING REPORT TO: " << reportFile;

    // Create a new file
    QFile file(reportFile);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&file);
    out << "ANALYZED: " << mSrcCodeFiles.size() << " SOURCE CODE FILES" << "\n";
    out << "FILE TYPES: " << mFileExtensions.join(", ") << "\n";
    out << "PICTO BASE CONTAINS: " << mPictoBaseNames.size() << " UNIQ ITEMS" << "\n";
    out << "********************************************************** EXCLUSION LIST: " << mToKeepPicto.size() << " **********************************************************\n";
    for (int i=0; i<mToKeepPicto.size(); i++)
        out << "EXCLUDED: " << i << " " << mToKeepPicto[i] << "\n";
    out << "\n";
    out << "********************************************************** USED PICTOS: " << mUsedPictos.size() << " **********************************************************\n";
    for (int i=0; i<mUsedPictos.size(); i++)
        out << "USED: " << i << " " << mUsedPictos[i] << "\n";
    out << "\n";
    out << "********************************************************** UNUSED PICTOS: " << mUnusedPictos.size() << " **********************************************************\n";
    for (int i=0; i<mUnusedPictos.size(); i++)
        out << "UNUSED: " << i << " " << mUnusedPictos[i] << "\n";
    file.close();

    mController->openTextEditor(reportFile, reportFile);
}
