#include "controller.h"
#include "utils.h"
#include "node.h"
#include "treemodel.h"
#include "treemodelfilter.h"
#include "imagemodel.h"
#include "imagemodelfilter.h"
#include "problemmodelfilter.h"
#include "filtermgr.h"
#include "preferencemgr.h"
#include "reportmgr.h"
#include "statusworker.h"
#include "qmlsearchmodel.h"
#include "pictohunter.h"
#include "pictocoverageservice.h"
#include <stringhunter.h>
#include <QThreadPool>
#include <QProcess>
#include <QDebug>

// Constructor:
Controller::Controller(QObject *parent) : QObject(parent),
    mRootNode(0), mTreeModel(0), mTreeModelFilter(0),
    mImageModel(0), mImageModelFilter(0), mProblemModel(0),
    mTargetSearchModel(0), mFilterMgr(0), mPreferenceMgr(0),
    mReportMgr(0), mDirName(""), mActiveFilter(-1), mNCreatedWorkers(0),
    mNCompletedWorkers(0), mAppIsBusy(false), mNFilesToProcess(0), mNProcessedFiles(0),
    mProgress(0.), mCurrentTreeNode(0), mBatchModeOn(false),
    mShowOverlay(true), mProblematicNode(0), mCurrentTab(0),
    mPictoCoverageService(0), mItemVisible(true)
{
    // Tree model:
    mTreeModel = new TreeModel(this);
    mTreeModel->setController(this);

    // Tree model filter:
    mTreeModelFilter = new TreeModelFilter(this);
    mTreeModelFilter->setController(this);
    mTreeModelFilter->setSourceModel(mTreeModel);

    // Image model:
    mImageModel = new ImageModel(this);
    mImageModel->setController(this);

    // Image model filter:
    mImageModelFilter = new ImageModelFilter(this);
    mImageModelFilter->setController(this);
    mImageModelFilter->setSourceModel(mImageModel);
    connect(mImageModel, SIGNAL(nColsChanged()), mImageModelFilter, SIGNAL(nColsChanged()));

    // Problem model:
    mProblemModel = new ImageModel(this);
    mProblemModel->setController(this);

    // Problem model filter:
    mProblemModelFilter = new ProblemModelFilter(this);
    mProblemModelFilter->setController(this);
    mProblemModelFilter->setSourceModel(mProblemModel);
    connect(mProblemModel, SIGNAL(nColsChanged()), mProblemModelFilter, SIGNAL(nColsChanged()));

    // Problematic node:
    mProblematicNode = new Node("PROBLEMS");

    // Filter manager:
    mFilterMgr = new FilterMgr(this);
    mFilterMgr->setController(this);

    // Preference mgr:
    mPreferenceMgr = new PreferenceMgr(this);
    mPreferenceMgr->setController(this);

    // Report mgr:
    mReportMgr = new ReportMgr(this);
    mReportMgr->setController(this);

    // Picto coverage service:
    mPictoCoverageService = new PictoCoverageService(this);
    mPictoCoverageService->setController(this);
}

// Destructor:
Controller::~Controller()
{
    qDebug() << "DESTROY CONTROLLER";
    if (mRootNode)
        delete mRootNode;
    if (mProblematicNode)
    {
        mProblematicNode->clear();
        delete mProblematicNode;
    }
}

// Startup:
bool Controller::startup()
{
    // Start preference mgr:
    if (!mPreferenceMgr->startup())
        return false;

    // Start report mgr:
    if (!mReportMgr->startup())
        return false;

    // Start plugin manager:
    if (!mFilterMgr->startup())
        return false;

    // Start picto coverage service:
    if (!mPictoCoverageService->startup())
        return false;

    return true;
}

// Shutdown:
void Controller::shutdown()
{
    // Shutdown preference mgr:
    mPreferenceMgr->shutdown();

    // Shutdown report mgr:
    mReportMgr->shutdown();

    // Shutdown plugin mgr:
    mFilterMgr->shutdown();

    // Shutdown picto coverage service:
    mPictoCoverageService->shutdown();
}

// Process image nodes:
void Controller::processImageNodes(Node *node)
{
    // Check node:
    if (!node)
        return;

    // Set application busy:
    setAppBusy(true);

    // Reset number of files to process:
    mNFilesToProcess = 0;

    // Reset number of processed files:
    mNProcessedFiles = 0;

    // Reset number of created workers:
    mNCreatedWorkers = 0;

    // Reset number of completed workers:
    mNCompletedWorkers = 0;

    // Clear status worker list:
    mStatusWorkers.clear();

    // Ideal number of threads:
    int nWorkers = QThread::idealThreadCount();

    // Compute segment size:
    QStringList imageNodePath;
    for (int i=0; i<node->childCount(); i++)
    {
        // Get node:
        Node *child = node->child(i);
        if (!child)
            continue;

        // Check suffix:
        QFileInfo fi(child->fullRelativePath());
        if (!imageFilter().contains("*."+fi.suffix(), Qt::CaseInsensitive))
            continue;
        imageNodePath << child->fullRelativePath();
    }

    // Set number of files to process:
    mNFilesToProcess = imageNodePath.size();

    // Get number of nodes to process:
    int segment = mNFilesToProcess/nWorkers;
    bool canContinue = true;

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
        QStringList subVect = Utils::subVector(imageNodePath, start, stop);

        // Constructor:
        StatusWorker *statusWorker = new StatusWorker(subVect, mImageDirList, mFilterMgr->filters());
        statusWorker->setId(i);
        mStatusWorkers << statusWorker;

        // Increment number of created threads:
        mNCreatedWorkers++;

        // Connect:
        connect(statusWorker, SIGNAL(resultAvailable(QString, QBitArray, bool)), SLOT(onStatusResultAvailable(QString, QBitArray, bool)));
        connect(statusWorker, SIGNAL(finished(int)), SLOT(onProcessingFinished(int)));
        QThreadPool::globalInstance()->start(statusWorker);
    }
}

// Return dir name:
QString Controller::dirName() const
{
    return mDirName;
}

// Set dir name:
void Controller::setDirName(const QString &dirName)
{
    mDirName = dirName;
    emit dirNameChanged();
}

// Return active filter:
int Controller::activeFilter() const
{
    return mActiveFilter;
}

// Set active filter:
void Controller::setActiveFilter(int activeFilter)
{
    mActiveFilter = activeFilter;
    emit activeFilterChanged();
}

// Apply current filter:
void Controller::applyCurrentFilter()
{
    setItemVisible(false);
    mImageModelFilter->setActiveFilter(mActiveFilter);
    mProblemModelFilter->setActiveFilter(mActiveFilter);
    setItemVisible(true);
}

// Show in explorer:
void Controller::showInExplorer(const QString &srcImage)
{
    QStringList args;
    args << "/n," << "/e," << "/select," << srcImage;
    QProcess::startDetached("Explorer", args);
}

// Get filter status:
int Controller::getFilterStatus(int index) const
{
    QMap<int, int> filterStatus = (mCurrentTab == 2) ? mFilterResults[mProblematicNode] : mFilterResults[mCurrentTreeNode];
    return filterStatus[index];
}

// Get filter color:
QString Controller::getFilterColor(int index) const
{
    QList<IFilter *> filters = mFilterMgr->filters();
    if ((index < 0) || (index > (filters.size()-1)))
        return "black";
    return filters[index] ? filters[index]->filterColor() : "black";
}

// Filter report problem?
bool Controller::filterReportProblem(int index) const
{
    QList<IFilter *> filters = mFilterMgr->filters();
    if ((index < 0) || (index > (filters.size()-1)))
        return false;
    return filters[index]->reportProblem();
}

// Reserved picto:
bool Controller::isReservedPicto(const QString &pictoPath) const
{
    return Utils::isReservedPicto(pictoPath);
}

// Build image tree:
void Controller::buildImageTree(const QList<QDir> &imageDirList, const QStringList &dirIds, bool ambiance1Only)
{
    // Check image dir list:
    if (imageDirList.isEmpty())
        return;

    // Check dir ids:
    if (dirIds.isEmpty())
        return;

    // Check count:
    if (imageDirList.size() != dirIds.size())
        return;

    // Clear processed nodes:
    mProcessedNodes.clear();

    // Reset current root node:
    mCurrentTreeNode = 0;

    // Clear filter results:
    mFilterResults.clear();
    emit filterStatusChanged();

    // Set image dir list:
    mImageDirList = imageDirList;

    // Set dir ids:
    mDirIds = dirIds;

    // Store current root node:
    Node *previousRootNode = mRootNode;

    // Clear image nodes:
    mImageNodes.clear();

    // Set root node:
    mRootNode = Utils::buildTree(mImageDirList, imageFilter(), mImageNodes, ambiance1Only);

    // Set dir name:
    if (mRootNode && mRootNode->child(0))
        setDirName(mRootNode->child(0)->baseName());

    // Set root node:
    mTreeModel->setRootNode(mRootNode);

    // Set image root node:
    setImageRootNode(mRootNode->child(0));

    // Delete previous root node:
    if (previousRootNode)
        delete previousRootNode;
}

// Return model filter:
TreeModelFilter *Controller::modelFilter() const
{
    return mTreeModelFilter;
}

// Return image model:
ImageModel *Controller::imageModel() const
{
    return mImageModel;
}

// Return image model filter:
ImageModelFilter *Controller::imageModelFilter() const
{
    return mImageModelFilter;
}

// Return problem model:
ImageModel *Controller::problemModel() const
{
    return mProblemModel;
}

// Return problem model filter:
ProblemModelFilter *Controller::problemModelFilter() const
{
    return mProblemModelFilter;
}

// Return filter mgr:
QObject *Controller::filterMgr() const
{
    return mFilterMgr;
}

// Return preference mgr:
PreferenceMgr *Controller::preferenceMgr() const
{
    return mPreferenceMgr;
}

// Get node:
Node *Controller::getNodeFromProxyIndex(const QModelIndex &proxyIndex) const
{
    if (!proxyIndex.isValid())
        return 0;

    // Get src index:
    QModelIndex srcIndex = mTreeModelFilter->mapToSource(proxyIndex);
    if (!srcIndex.isValid())
        return 0;

    // Return node:
    return mTreeModel->getNode(srcIndex);
}

// Get child node:
Node *Controller::getChildNode(Node *rootNode, int row) const
{
    // Check root node:
    if (!rootNode)
        return 0;
    int childCount = rootNode->childCount();
    if ((row < 0) || (row > (childCount-1)))
        return 0;
    return rootNode->child(row);
}

// Set image root node:
void Controller::setImageRootNode(Node *node)
{
    // Check for identity:
    if (node == mCurrentTreeNode)
    {
        if (mBatchModeOn)
            processNextNode();
        return;
    }

    // Set current node:
    mCurrentTreeNode = node;

    // Process image nodes:
    if (mProcessedNodes[mCurrentTreeNode])
    {
        // Setup image model:
        mImageModel->setupModel(mCurrentTreeNode, mImageDirList, mDirIds);

        // Set active filter on proxy:
        mImageModelFilter->setActiveFilter(mActiveFilter);

        // Notify:
        emit filterStatusChanged();

        // Process next node:
        if (mBatchModeOn)
            processNextNode();

        emit processingFinished();
    }
    else processImageNodes(node);
}

// Process next node (batch mode only):
void Controller::processNextNode()
{
    if (mBatchNodeIndexList.isEmpty())
        emit batchProcessingDone();
    else
    {
        QModelIndex nextNode = mBatchNodeIndexList.takeFirst();
        emit selectNextNode(nextNode);
    }
}

// Status result available:
void Controller::onStatusResultAvailable(const QString &file, const QBitArray &status, bool nodeHasProblem)
{
    // Check node:
    Node *node = mImageNodes[file];
    if (!node)
        return;

    // Update filter status:
    node->setFilterStatus(status);

    // Has problem?
    node->setHasProblem(nodeHasProblem);
    if (nodeHasProblem && node->parent())
        node->parent()->setHasProblem(nodeHasProblem);

    // Store filter results:
    QMap<int, int> current = mFilterResults[mCurrentTreeNode];
    for (int i=0; i<status.size(); i++)
        current[i] += (status[i] ? 1 : 0);
    mFilterResults[mCurrentTreeNode] = current;

    // Update progress:
    if (mNFilesToProcess > 0)
        setProgress((double)++mNProcessedFiles/(double)mNFilesToProcess);

    // Notify:
    emit filterStatusChanged();
}

// Compute problematic nodes:
void Controller::computeProblematicNodes()
{
    // Clear current:
    mProblematicNode->clear();
    mFilterResults[mProblematicNode].clear();
    QMap<int, int> current;

    // Check processed nodes so far:
    for (QHash<Node *, bool>::iterator it=mProcessedNodes.begin(); it!=mProcessedNodes.end(); ++it)
    {
        // Not processed? don't bother:
        if (!it.value())
            continue;

        // Get root node:
        Node *rootNode = it.key();
        if (!rootNode)
            continue;

        // Get child nodes:
        QList<Node *> childs = rootNode->childs();

        for (int i=0; i<childs.size(); i++)
        {
            // Get child:
            Node *child = childs[i];
            if (!child || !child->hasProblem() || mProblematicNode->hasChild(child))
                continue;

            // Add child:
            mProblematicNode->addChild(child, false);

            // Get filter status:
            QBitArray filterStatus = child->filterStatus();

            for (int j=0; j<filterStatus.size(); j++)
                current[j] += (filterStatus[j] ? 1 : 0);
        }
    }

    mFilterResults[mProblematicNode] = current;
}

bool Controller::itemVisible() const
{
    return mItemVisible;
}

void Controller::setItemVisible(bool visible)
{
    mItemVisible = visible;
    emit itemVisibleChanged();
}

// Processing finished:
void Controller::onProcessingFinished(int id)
{
    mNCompletedWorkers++;

    // All workers done:
    if (mNCompletedWorkers == mNCreatedWorkers)
    {
        setAppBusy(false);

        // Keep track of processed tree nodes:
        mProcessedNodes[mCurrentTreeNode] = true;

        // Setup image model:
        mImageModel->setupModel(mCurrentTreeNode, mImageDirList, mDirIds);

        // Setup problem model:
        computeProblematicNodes();
        mProblemModel->setupModel(mProblematicNode, mImageDirList, mDirIds);

        // Set active filter on proxy:
        mImageModelFilter->setActiveFilter(mActiveFilter);

        // Clear status workers:
        mStatusWorkers.clear();

        // Notify:
        emit filterStatusChanged();

        // Processing finished:
        emit processingFinished();

        // Batch mode?
        if (mBatchModeOn)
            processNextNode();
    }

    for (int i=0; i<mStatusWorkers.size(); i++)
    {
        StatusWorker *statusWorker = mStatusWorkers[i];
        if (!statusWorker)
            continue;
        if (statusWorker->id() == id)
        {
            mStatusWorkers.removeAll(statusWorker);
            break;
        }
    }
}

// Return true if app is busy:
bool Controller::appIsBusy() const
{
    return mAppIsBusy;
}

// Set app busy:
void Controller::setAppBusy(bool busy)
{
    mAppIsBusy = busy;
    setProgress(0.);
    emit appIsBusyChanged();
}

// Reprocess current node:
void Controller::reprocessRootNode()
{
    // Reprocess all:
    buildImageTree(mImageDirList, mDirIds);

    // Enter batch mode:
    enterBatchMode();
}

// Return processed nodes:
const QHash<Node *, bool> &Controller::processedNodes() const
{
    return mProcessedNodes;
}

// Return progress:
double Controller::progress() const
{
    return mProgress;
}

// Return status workers:
const QList<StatusWorker *> Controller::statusWorkers() const
{
    return mStatusWorkers;
}

// Return image filter:
QStringList Controller::imageFilter() const
{
    return mPreferenceMgr->getPreference("IMAGE_FILTER").toStringList();
}

// Set mode:
void Controller::setMode(const IFilter::Mode &mode)
{
    mFilterMgr->setMode(mode);
}

// Set progress:
void Controller::setProgress(double progress)
{
    mProgress = progress;
    emit progressChanged();
}

// Show overlay?
bool Controller::showOverlay() const
{
    return mShowOverlay;
}

// Set show overlay:
void Controller::setShowOverlay(bool show)
{
    mShowOverlay = show;
    emit showOverlayChanged();
}

// Return app title:
QString Controller::appTitle() const
{
    return tr("Image Analyzer");
}

// Return app version:
QString Controller::appVersion() const
{
    return "1.0";
}

// Set batch mode:
void Controller::enterBatchMode()
{
    // Clear current batch node list:
    mBatchNodeIndexList.clear();

    // Check available nodes:
    QModelIndexList tmp;
    tmp << mTreeModelFilter->index(0, 0);
    tmp << mTreeModelFilter->match(mTreeModelFilter->index(0,0), Qt::DisplayRole, "*", -1, Qt::MatchWildcard|Qt::MatchRecursive);
    if (tmp.isEmpty())
        return;

    for (int i=0; i<tmp.size(); i++)
    {
        // Get node:
        Node *node = getNodeFromProxyIndex(tmp[i]);
        if (!node)
            continue;
        if (!mProcessedNodes[node])
            mBatchNodeIndexList << tmp[i];
    }

    // Nothing to do:
    if (mBatchNodeIndexList.isEmpty())
        return;

    // Set batch mode flag:
    // Set batch mode flag:
    mBatchModeOn = true;

    // Select first:
    emit selectNextNode(mBatchNodeIndexList.first());
}

// Open text editor:
void Controller::openTextEditor(const QString &fileName, const QString &title, const QString &highlightedString)
{
    qDebug() << "TARGET STRING = " << highlightedString;
    QString localFile = Utils::toLocalFile(fileName);
    QFileInfo fi(localFile);
    if (!fi.exists())
        return;

    // Load report:
    mTextEditor.clear();
    mTextEditor.setTitle(title);
    mTextEditor.loadFile(localFile);
    if (!highlightedString.isEmpty())
        mTextEditor.searchText(highlightedString);
    mTextEditor.showMaximized();
}

// Perform picto coverage:
void Controller::performPictoCoverage(const QStringList &fileExtensions, const QDir &pictoDir, const QDir &srcCodeDir, const QStringList &exclusionList)
{
   mPictoCoverageService->performPictoCoverage(fileExtensions, pictoDir, srcCodeDir, exclusionList);
}

// Perform search:
void Controller::performSearch(const QString &targetString, QMLSearchModel *targetSearchModel)
{
    // Check target string:
    if (targetString.simplified().isEmpty())
        return;

    // Set app busy:
    setAppBusy(true);

    // Reset QML search model:
    mTargetSearchModel = targetSearchModel;

    // Build hunter:
    QStringList filters;
    filters << "*.qml";
    QString qmlDir = mPreferenceMgr->getPreference("QML_DIR").toString();
    StringHunter *hunter = new StringHunter(QDir(qmlDir), filters, targetString);

    // Connect:
    connect(hunter, SIGNAL(resultAvailable(QString, uint, QString, QString)), SLOT(onHuntResultAvailable(QString, uint, QString, QString)));
    connect(hunter, SIGNAL(progressChanged(double)), SLOT(onHuntProgressChanged(double)));
    connect(hunter, SIGNAL(finished()), SLOT(onHuntFinished()));

    // Start:
    QThreadPool::globalInstance()->start(hunter);
}

// Hunt finished:
void Controller::onHuntFinished()
{
    // App not busy anymore:
    setAppBusy(false);
}

// Return current node full relative path:
QString Controller::currentNodeFullRelativePath() const
{
    return mCurrentTreeNode ? mCurrentTreeNode->fullRelativePath() : "";
}

// Hunt result available:
void Controller::onHuntResultAvailable(const QString &targetFile, uint lineNumber, const QString &simplifiedLine, const QString &targetString)
{
    MatchStruct st;
    st._qmlFile = targetFile;
    st._lineNumber = lineNumber;
    st._line = simplifiedLine;
    st._searchedString = targetString;

    // Add search result:
    mTargetSearchModel->addResult(st);
}

// Hunt progress changed:
void Controller::onHuntProgressChanged(double progress)
{
    setProgress(progress);
}

// Current tab changed:
void Controller::onCurrentTabChanged(int tabIndex)
{
    mCurrentTab = tabIndex;
    emit filterStatusChanged();
    emit currentTabChanged();
}

// Create problem report:
void Controller::createProblemReport()
{
    mReportMgr->saveReport(mProblematicNode, mFilterMgr->filters(), mImageDirList);
}

// Request search:
void Controller::requestSearch(const QString &targetString)
{
    emit doSearch(targetString);
}

// Filter current view:
void Controller::filterCurrentView(const QString &searchText)
{
    if (mCurrentTab == 0)
        mImageModelFilter->setFilterRegExp(searchText);
    else
    if (mCurrentTab == 2)
        mProblemModelFilter->setFilterRegExp(searchText);
}

// Get node matching full relative path:
Node *Controller::nodeMatchingFullRelativePath(const QString &fullRelativePath) const
{
    // Check available nodes:
    QModelIndexList tmp;
    tmp << mTreeModelFilter->index(0, 0);
    tmp << mTreeModelFilter->match(mTreeModelFilter->index(0,0), Qt::DisplayRole, "*", -1, Qt::MatchWildcard|Qt::MatchRecursive);
    if (tmp.isEmpty())
        return 0;

    for (int i=0; i<tmp.size(); i++)
    {
        // Get node:
        Node *node = getNodeFromProxyIndex(tmp[i]);
        if (!node)
            continue;
        if (node->fullRelativePath().compare(fullRelativePath, Qt::CaseInsensitive) == 0)
            return node;
    }

    return 0;
}

// Stop status workers:
void Controller::stopStatusWorkers()
{
    QThreadPool::globalInstance()->clear();
}

// Clean picto directory:
void Controller::cleanPictoDirectory()
{
    mPictoCoverageService->cleanPictoDirectory();
}

// Compute file stats:
void Controller::computeFileStats(const QList<QDir> &imageDir)
{
    QHash<QString, QStringList> results;
    Utils::statistics(imageDir, results);
    mReportMgr->saveReport(results, imageDir);
}
