#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <QObject>
#include <QDir>
#include <QMap>
#include "texteditor.h"
#include "iservice.h"
#include "ifilter.h"
class Node;
class TreeModel;
class TreeModelFilter;
class ImageModel;
class ImageModelFilter;
class ProblemModelFilter;
class FilterMgr;
class QMLSearchModel;
class PreferenceMgr;
class ReportMgr;
class StatusWorker;
class PictoCoverageService;

class Controller : public QObject, public IService
{
    Q_OBJECT
    Q_PROPERTY(QString appTitle READ appTitle NOTIFY appTitleChanged)
    Q_PROPERTY(QString appVersion READ appVersion NOTIFY appVersionChanged)
    Q_PROPERTY(QString dirName READ dirName WRITE setDirName NOTIFY dirNameChanged)
    Q_PROPERTY(int activeFilter READ activeFilter WRITE setActiveFilter NOTIFY activeFilterChanged)
    Q_PROPERTY(bool appIsBusy READ appIsBusy WRITE setAppBusy NOTIFY appIsBusyChanged)
    Q_PROPERTY(double progress READ progress WRITE setProgress NOTIFY progressChanged)
    Q_PROPERTY(bool showOverlay READ showOverlay WRITE setShowOverlay NOTIFY showOverlayChanged)
    Q_PROPERTY(QObject *filterMgr READ filterMgr NOTIFY filterMgrChanged)
    Q_PROPERTY(bool itemVisible READ itemVisible WRITE setItemVisible NOTIFY itemVisibleChanged)

public:
    friend class ImageCompare;

    // Destructor:
    virtual ~Controller();

    // Startup:
    virtual bool startup();

    // Shutdown:
    virtual void shutdown();

    // Build image tree:
    void buildImageTree(const QList<QDir> &imageDirList, const QStringList &dirIds, bool ambiance1Only=false);

    // Return model filter:
    TreeModelFilter *modelFilter() const;

    // Return image model:
    ImageModel *imageModel() const;

    // Return image model filter:
    ImageModelFilter *imageModelFilter() const;

    // Return problem model:
    ImageModel *problemModel() const;

    // Return problem model filter:
    ProblemModelFilter *problemModelFilter() const;

    // Return filter mgr:
    QObject *filterMgr() const;

    // Return preference mgr:
    PreferenceMgr *preferenceMgr() const;

    // Get node:
    Node *getNodeFromProxyIndex(const QModelIndex &proxyIndex) const;

    // Get child node:
    Node *getChildNode(Node *rootNode, int row) const;

    // Set image root node:
    void setImageRootNode(Node *node);

    // Process next node (batch mode only):
    void processNextNode();

    // Return dir name:
    QString dirName() const;

    // Set dir name:
    void setDirName(const QString &dirName);

    // Return active filter:
    int activeFilter() const;

    // Set active filter:
    void setActiveFilter(int activeFilter);

    // Return true if app is busy:
    bool appIsBusy() const;

    // Set app busy:
    void setAppBusy(bool busy);

    // Reprocess root node:
    void reprocessRootNode();

    // Return process nodeds:
    const QHash<Node *, bool> &processedNodes() const;

    // Return app title:
    QString appTitle() const;

    // Return app version:
    QString appVersion() const;

    // Enter batch mode:
    void enterBatchMode();

    // Return progress:
    double progress() const;

    // Return status workers:
    const QList<StatusWorker *> statusWorkers() const;

    // Return image filters:
    QStringList imageFilter() const;

    // Set mode:
    void setMode(const IFilter::Mode &mode);

    // Perform picto coverage:
    void performPictoCoverage(const QStringList &fileExtensions, const QDir &pictoDir, const QDir &srcCodeDir,
        const QStringList &exclusionList);

    // Set progress:
    void setProgress(double progress);

    // Stop status workers:
    void stopStatusWorkers();

    // Clean picto directory:
    void cleanPictoDirectory();

    // Compute file stats:
    void computeFileStats(const QList<QDir> &imageDir);

    // Apply current filter:
    Q_INVOKABLE void applyCurrentFilter();

    // Show in explorer:
    Q_INVOKABLE void showInExplorer(const QString &srcImage);

    // Get filter status:
    Q_INVOKABLE int getFilterStatus(int index) const;

    // Get filter color:
    Q_INVOKABLE QString getFilterColor(int index) const;

    // Filter report problem?
    Q_INVOKABLE bool filterReportProblem(int index) const;

    // Reserved picto:
    Q_INVOKABLE bool isReservedPicto(const QString &pictoPath) const;

    // Open text editor:
    Q_INVOKABLE void openTextEditor(const QString &fileName, const QString &title, const QString &highlightedString="");

    // Perform search:
    Q_INVOKABLE void performSearch(const QString &targetString, QMLSearchModel *searchModel);

    // Return current node full relative path:
    Q_INVOKABLE QString currentNodeFullRelativePath() const;

    // Create report:
    Q_INVOKABLE void createProblemReport();

    // Request search:
    Q_INVOKABLE void requestSearch(const QString &targetString);

    // Filter current view:
    Q_INVOKABLE void filterCurrentView(const QString &searchText);

protected:
    // Constructor:
    explicit Controller(QObject *parent = 0);

private:
    // Return available filters:
    QStringList availableFilters() const;

    // Process image nodes:
    void processImageNodes(Node *node);

    // Show overlay?
    bool showOverlay() const;

    // Set show overlay:
    void setShowOverlay(bool show);

    // Get node matching full relative path:
    Node *nodeMatchingFullRelativePath(const QString &fullRelativePath) const;

    // Compute problematic nodes:
    void computeProblematicNodes();

    // Item visible?
    bool itemVisible() const;

    // Set item visible:
    void setItemVisible(bool visible);

private:
    // Image dir list:
    QList<QDir> mImageDirList;

    // Dir ids:
    QStringList mDirIds;

    // Root node:
    Node *mRootNode;

    // Status workers:
    QList<StatusWorker *> mStatusWorkers;

    // Tree model:
    TreeModel *mTreeModel;

    // Tree model filter:
    TreeModelFilter *mTreeModelFilter;

    // Image model:
    ImageModel *mImageModel;

    // Image model filter:
    ImageModelFilter *mImageModelFilter;

    // Problem model:
    ImageModel *mProblemModel;

    // Problem model filter:
    ProblemModelFilter *mProblemModelFilter;

    // Target search model:
    QMLSearchModel *mTargetSearchModel;

    // Filter mgr:
    FilterMgr *mFilterMgr;

    // Preference mgr:
    PreferenceMgr *mPreferenceMgr;

    // Report mgr:
    ReportMgr *mReportMgr;

    // Dir name:
    QString mDirName;

    // Available filters:
    QStringList mAvailableFilters;

    // Active filter:
    int mActiveFilter;

    // Number of created workers:
    int mNCreatedWorkers;

    // Number of completed workers:
    int mNCompletedWorkers;

    // Image nodes:
    QHash<QString, Node *> mImageNodes;

    // Application busy?
    bool mAppIsBusy;

    // Number of files to process:
    int mNFilesToProcess;

    // Number of processed files:
    int mNProcessedFiles;

    // Progress:
    double mProgress;

    // Current node:
    Node *mCurrentTreeNode;

    // Processed tree nodes:
    QHash<Node *, bool> mProcessedNodes;

    // Filter results:
    QMap<Node *, QMap<int, int> > mFilterResults;

    // Batch nodes:
    QModelIndexList mBatchNodeIndexList;

    // Batch mode on?
    bool mBatchModeOn;

    // Show overlay?
    bool mShowOverlay;

    // Text editor:
    TextEditor mTextEditor;

    // Problem list:
    Node *mProblematicNode;

    // Current tab:
    int mCurrentTab;

    // Picto coverage service:
    PictoCoverageService *mPictoCoverageService;

    // List of used pictos:
    QStringList mUsedPictos;

    // Picto base names:
    QStringList mPictoBaseNames;

    bool mItemVisible;

public slots:
    // Status result available:
    void onStatusResultAvailable(const QString &file, const QBitArray &status, bool nodeHasProblem);

    // Processing finished:
    void onProcessingFinished(int id);

    // Hunt result available:
    void onHuntResultAvailable(const QString &targetFile, uint lineNumber, const QString &simplifiedLine, const QString &targetString);

    // Hunt progress changed:
    void onHuntProgressChanged(double progress);

    // Hunt finished:
    void onHuntFinished();

    // Current tab changed:
    void onCurrentTabChanged(int);

signals:
    // Dir name changed:
    void dirNameChanged();

    // Active filter changed:
    void activeFilterChanged();

    // App is busy:
    void appIsBusyChanged();

    // Progress changed:
    void progressChanged();

    // Filter status changed:
    void filterStatusChanged();

    // Show overlay changed:
    void showOverlayChanged();

    // Procesing finished:
    void processingFinished();

    // App title changed:
    void appTitleChanged();

    // App version changed:
    void appVersionChanged();

    // Show QML search dialog:
    void showQMLSearchDialog(const QString &targetString);

    // Current tab changed:
    void currentTabChanged();

    // Batch processing done:
    void batchProcessingDone();

    // Select next node:
    void selectNextNode(const QModelIndex &nextNode);

    // Filter mgr changed:
    void filterMgrChanged();

    // Request search:
    void doSearch(const QString &targetString);

    void itemVisibleChanged();
};

#endif // CONTROLLER_H
