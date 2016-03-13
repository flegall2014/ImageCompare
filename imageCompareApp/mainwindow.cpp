#include "mainwindow.h"
#include "controller.h"
#include "treemodelfilter.h"
#include "imagemodelfilter.h"
#include "problemmodelfilter.h"
#include "preferencemgr.h"
#include "ui_mainwindow.h"
#include "utils.h"
#include "node.h"
#include "spacer.h"
#include "searchqmltab.h"
#include "statisticstab.h"
#include "qmlsearchmodel.h"
#include "statusworker.h"
#include "ifilter.h"
#include <QFileDialog>
#include <QQmlEngine>
#include <QQmlContext>
#include <QToolBar>
#include <QTabWidget>
#include <QDebug>

// Constructor:
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    mController(0)
{
    // Setup ui:
    ui->setupUi(this);

    // Disabled for now:
    ui->pictoCoverageAction->setEnabled(false);

    // Set window title:
    setWindowTitle(mController->appTitle() + " " + mController->appVersion());

    // Hide tree view header:
    ui->treeView->setHeaderHidden(true);

    // Batch processing:
    connect(ui->batchProcessingAction, SIGNAL(triggered()), SLOT(onEnterBatchMode()));

    // Open report:
    connect(ui->openReportAction, SIGNAL(triggered()), SLOT(onOpenReport()));

    // Exit:
    connect(ui->exitAction, SIGNAL(triggered()), SLOT(onExit()));

    // Browse single directory:
    connect(ui->browseSingleDirectoryAction, SIGNAL(triggered()), SLOT(onBrowseSingleDirectory()));

    // Directory compare:
    connect(ui->directoryCompareAction, SIGNAL(triggered()), SLOT(onCompareDirectories()));

    // Ambiance compare:
    connect(ui->ambianceCompareAction, SIGNAL(triggered()), SLOT(onCompareAmbiances()));

    // Picto coverage:
    connect(ui->pictoCoverageAction, SIGNAL(triggered()), SLOT(onShowPictoCoverageDialog()));

    // Select directories:
    connect(&mDirSelectionDialog, SIGNAL(runClicked()), SLOT(onProcessDirectories()));

    // Select ambiance:
    connect(&mAmbianceSelectionDlg, SIGNAL(runClicked()), SLOT(onProcessAmbiances()));

    // Picto hunter:
    connect(&mPictoHunterDialog, SIGNAL(runClicked()), SLOT(onPerformPictoCoverage()));
    connect(&mPictoHunterDialog, SIGNAL(cleanPictoDirectory()), SLOT(onCleanPictoDirectory()));

    // Validate preferences:
    connect(&mPreferencesDialog, SIGNAL(accepted()), SLOT(onApplyPreferences()));

    // Preferences:
    connect(ui->preferencesAction, SIGNAL(triggered()), SLOT(onShowPreferences()));

    // File stats:
    connect(ui->fileStatsAction, SIGNAL(triggered()), SLOT(onComputeFileStats()));

    // Close all:
    connect(ui->closeAllAction, SIGNAL(triggered()), SLOT(onCloseAll()));

    // File toolbar:
    QList<QAction *> actions;
    actions << ui->browseSingleDirectoryAction << ui->directoryCompareAction <<
               ui->ambianceCompareAction << ui->pictoCoverageAction << ui->batchProcessingAction << ui->openReportAction <<
               ui->fileStatsAction << ui->preferencesAction;
    QToolBar *fileToolBar = addToolBar(tr("File"));
    for (int i=0; i<actions.size(); i++)
    {
        QToolButton *button = new QToolButton(this);
        button->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        button->setDefaultAction(actions[i]);
        fileToolBar->addWidget(button);
    }
    fileToolBar->addWidget(new Spacer(this));

    // Progress bar:
    mProgressBar = new QProgressBar(this);
    mProgressBar->setVisible(false);
    statusBar()->addWidget(mProgressBar, 1);

    // Label:
    QLabel *label = new QLabel(this);
    label->setText(tr("Search in QML files:  "));
    fileToolBar->addWidget(label);

    // Text input:
    mLineEdit = new QLineEdit(this);
    mLineEdit->setMaximumWidth(128);
    mLineEdit->setMaximumHeight(24);

    connect(mLineEdit, SIGNAL(returnPressed()), SLOT(onSearchStringInQML()));
    fileToolBar->addWidget(mLineEdit);

    // Close tab:
    connect(ui->tabWidget, SIGNAL(tabCloseRequested(int)), SLOT(onCloseTab(int)));

    // Create search action:
    QAction *searchAction = new QAction(QIcon(":/qml/icons/ico-search.png"), "", this);
    connect(searchAction, SIGNAL(triggered()), SLOT(onSearchStringInQML()));
    fileToolBar->addAction(searchAction);
}

// Destructor:
MainWindow::~MainWindow()
{
    delete ui;
}

// Set controller:
void MainWindow::setController(Controller *controller)
{
    // Set controller:
    mController = controller;

    // Listen to app busy state:
    connect(mController, SIGNAL(appIsBusyChanged()), SLOT(onAppIsBusyChanged()));

    // Listen to selectNextNode signal:
    connect(mController, SIGNAL(selectNextNode(QModelIndex)), SLOT(onSelectNextNode(QModelIndex)));

    // List to progress changed:
    connect(mController, SIGNAL(progressChanged()), SLOT(onProgressChanged()));

    // Do search:
    connect(mController, SIGNAL(doSearch(QString)), SLOT(onDoSearch(QString)));

    // Set model on tree view:
    ui->treeView->setModel(mController->modelFilter());

    // Listen to tab changed:
    connect(ui->tabWidget, SIGNAL(currentChanged(int)), mController, SLOT(onCurrentTabChanged(int)));

    // Manage selection:
    connect(ui->treeView->selectionModel(), SIGNAL(currentChanged(QModelIndex, QModelIndex)), SLOT(onSelectionChanged(QModelIndex, QModelIndex)));

    /*
    Setup processing QML view
    */

    // Expose controller to QML:
    ui->processingQmlView->engine()->rootContext()->setContextProperty("_controller", mController);

    // Expose imageModel to QML:
    ui->processingQmlView->engine()->rootContext()->setContextProperty("_imageModel", mController->imageModelFilter());

    // Report problem only:
    ui->processingQmlView->engine()->rootContext()->setContextProperty("_reportProblemOnly", qVariantFromValue(false));

    // Set QML source:
    ui->processingQmlView->setSource(QUrl("qrc:/qml/ProcessingQmlView.qml"));

    /*
    Setup quick stats QML view
    */

    // Expose controller to QML:
    ui->quickStatsQmlView->engine()->rootContext()->setContextProperty("_controller", mController);

    // Set QML source:
    ui->quickStatsQmlView->setSource(QUrl("qrc:/qml/StatisticsPage.qml"));

    /*
    Setup problem QML view
    */

    // Export controller to QML:
    ui->problemQmlView->engine()->rootContext()->setContextProperty("_controller", mController);

    // Expose imageModel to QML:
    ui->problemQmlView->engine()->rootContext()->setContextProperty("_imageModel", mController->problemModelFilter());

    // Report problem only:
    ui->problemQmlView->engine()->rootContext()->setContextProperty("_reportProblemOnly", qVariantFromValue(true));

    // Set QML source:
    ui->problemQmlView->setSource(QUrl("qrc:/qml/ProcessingQmlView.qml"));
}

// App is busy changed:
void MainWindow::onAppIsBusyChanged()
{
    mProgressBar->setVisible(mController->appIsBusy());
    setEnabled(!mController->appIsBusy());
}

// Compare directories:
void MainWindow::onCompareDirectories()
{
    mDirSelectionDialog.exec();
}

// Compare ambiances:
void MainWindow::onCompareAmbiances()
{
    mAmbianceSelectionDlg.exec();
}

// Browse single directory:
void MainWindow::onBrowseSingleDirectory()
{
    // Get dir1:
    QDir selectedDir = QFileDialog::getExistingDirectory(this,  tr("Select Directory"));

    // Clear current list:
    mImageDirList.clear();
    mImageDirList << selectedDir;
    QStringList dirIds;
    dirIds << "Dir1";
    mController->buildImageTree(mImageDirList, dirIds);

    // Expand tree:
    ui->treeView->expandAll();
}

// Process directories:
void MainWindow::onProcessDirectories()
{
    // Get directory 1:
    QStringList dirIds;
    QList<QDir> validDirectories = mDirSelectionDialog.validDirectories(dirIds);
    if (validDirectories.isEmpty())
        return;

    // Clear current list:
    mImageDirList = validDirectories;
    mController->buildImageTree(mImageDirList, dirIds, mDirSelectionDialog.ambiance1Only());
    mController->setMode(IFilter::DIRECTORY_COMPARE);

    // Expand tree:
    ui->treeView->expandAll();
}

// Process ambiances:
void MainWindow::onProcessAmbiances()
{
    // Get root dir:
    QDir rootDir = mAmbianceSelectionDlg.rootDir();

    // Check universe:
    QList<QDir> ambianceDirList;
    if (!Utils::checkImagesDirectory(rootDir, ambianceDirList))
    {
        QString errorMsg = rootDir.absolutePath() + " DOES NOT CONTAIN ANY AMBIANCE";
        QMessageBox::critical(this, tr("Image Compare Error"), errorMsg);
        return;
    }

    // Clear current list:
    mImageDirList.clear();
    mImageDirList = ambianceDirList;
    QStringList dirIds;
    for (int i=0; i<ambianceDirList.size(); i++)
        dirIds << "Dir" + QString::number(i+1);
    mController->buildImageTree(mImageDirList, dirIds);
    mController->setMode(IFilter::AMBIANCE_COMPARE);

    // Expand tree:
    ui->treeView->expandAll();
}

// Perform picto coverage:
void MainWindow::onShowPictoCoverageDialog()
{
    mPictoHunterDialog.exec();
}

// Perform picto coverage:
void MainWindow::onPerformPictoCoverage()
{
    QStringList fileExtensions = mPictoHunterDialog.fileExtensions();
    QDir srcCodeDir = mPictoHunterDialog.srcCodeDir();
    qDebug() << "SRC CODE DIR = " << srcCodeDir.absolutePath();
    QDir pictoDir = mPictoHunterDialog.pictoDir();
    qDebug() << "PICTO DIR = " << pictoDir.absolutePath();
    QStringList exclusionList = mPictoHunterDialog.exclusionDirectories();
    mController->performPictoCoverage(fileExtensions, pictoDir, srcCodeDir, exclusionList);
}

// Clean picto directory:
void MainWindow::onCleanPictoDirectory()
{
    mController->cleanPictoDirectory();
}

// Show preferences:
void MainWindow::onShowPreferences()
{
    mPreferencesDialog.setPreferences(mController->preferenceMgr()->preferences());
    mPreferencesDialog.exec();
}

// Compute file stats:
void MainWindow::onComputeFileStats()
{
    mController->computeFileStats(mImageDirList);
}

// Close all:
void MainWindow::onCloseAll()
{
    while (ui->tabWidget->count() > 3)
        ui->tabWidget->removeTab(ui->tabWidget->count()-1);
}

// Apply preferences:
void MainWindow::onApplyPreferences()
{
    mController->preferenceMgr()->setPreferences(mPreferencesDialog.preferences());
}

// Exit:
void MainWindow::onExit()
{
    close();
}

// Selection changed:
void MainWindow::onSelectionChanged(const QModelIndex &current, const QModelIndex &previous)
{
    Q_UNUSED(previous);

    // Get selected node:
    Node *selectedNode = mController->getNodeFromProxyIndex(current);
    if (!selectedNode)
        return;

    // Set dir name:
    mController->setDirName(selectedNode->baseName());

    // Set it on image model:
    mController->setImageRootNode(selectedNode);
}

// Search string in QML:
void MainWindow::onSearchStringInQML()
{
    onDoSearch(mLineEdit->text());
}

// Batch processing:
void MainWindow::onEnterBatchMode()
{
    // Set batch mode:
    mController->enterBatchMode();
}

// Open report:
void MainWindow::onOpenReport()
{
    // Get dir1:
    QString reportFile = QFileDialog::getOpenFileName(this,  tr("Select ReportFile"),
                                                      Utils::reportDir().absolutePath(), "*.csv");
    if (reportFile.isEmpty())
        return;
    mController->openTextEditor(reportFile, reportFile);
}

// Close tab:
void MainWindow::onCloseTab(int tabIndex)
{
    if (tabIndex < 3)
        return;
    ui->tabWidget->removeTab(tabIndex);
}

// Select next node:
void MainWindow::onSelectNextNode(const QModelIndex &nextNode)
{
    // Check node:
    if (!nextNode.isValid())
        return;

    ui->treeView->selectionModel()->select(nextNode, QItemSelectionModel::ClearAndSelect);
    ui->treeView->scrollTo(nextNode);
    onSelectionChanged(nextNode, QModelIndex());
}

// Progress changed:
void MainWindow::onProgressChanged()
{
    int progress = qRound(mController->progress()*100);
    if (progress < 0)
        progress = 0;
    if (progress > 100)
        progress = 100;
    mProgressBar->setValue(progress);
}

// Do search:
void MainWindow::onDoSearch(const QString &targetString)
{
    QFileInfo fi(targetString);
    QString target = fi.baseName();

    // Create new QML tab:
    SearchQMLTab *newTab = new SearchQMLTab();

    // Create new data model:
    QMLSearchModel *searchModel = new QMLSearchModel(this);

    // Set controller:
    newTab->setContextProperty("_controller", mController);

    // Set search model:
    newTab->setContextProperty("_searchModel", searchModel);

    // Set source:
    newTab->setSource("qrc:/qml/StringHuntResultsPage.qml");

    // Set target string:
    newTab->setTargetString(target);

    // Add tab:
    ui->tabWidget->addTab(newTab, "*"+target+"*");

    // Set current tab:
    ui->tabWidget->setCurrentIndex(ui->tabWidget->count()-1);

    // Perform search:
    mController->performSearch(target, searchModel);
}

// Handle close events:
void MainWindow::closeEvent(QCloseEvent *event)
{
    Q_UNUSED(event);
    qDebug() << "MainWindow::closeEvent";
    mController->stopStatusWorkers();
}
