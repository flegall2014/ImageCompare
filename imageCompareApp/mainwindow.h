#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QDir>
#include "dirselectiondialog.h"
#include "ambianceselectiondialog.h"
#include "dirselectiondialog.h"
#include "preferencesdialog.h"
#include "pictohunterdialog.h"
class Controller;
class QLineEdit;
class QProgressBar;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    // Constructor:
    explicit MainWindow(QWidget *parent = 0);

    // Destructor:
    virtual ~MainWindow();

    // Set controller:
    void setController(Controller *controller);

protected:
    // Close event:
    virtual void closeEvent(QCloseEvent *);

public slots:
    // App is busy changed:
    void onAppIsBusyChanged();

    // Browse single directory:
    void onBrowseSingleDirectory();

    // Compare directories:
    void onCompareDirectories();

    // Compare ambiances:
    void onCompareAmbiances();

    // Process directories:
    void onProcessDirectories();

    // Process ambiances:
    void onProcessAmbiances();

    // Show picto coverage dialog:
    void onShowPictoCoverageDialog();

    // Perform picto coverage:
    void onPerformPictoCoverage();

    // Clean picto directory:
    void onCleanPictoDirectory();

    // Show preferences:
    void onShowPreferences();

    // Compute file stats:
    void onComputeFileStats();

    // Close all:
    void onCloseAll();

    // Apply preferences:
    void onApplyPreferences();

    // Batch processing:
    void onEnterBatchMode();

    // Open report:
    void onOpenReport();

    // Exit:
    void onExit();

    // Selection changed:
    void onSelectionChanged(const QModelIndex &current, const QModelIndex &previous);

    // Search string in QML:
    void onSearchStringInQML();

    // Close tab:
    void onCloseTab(int tabIndex);

    // Select next node:
    void onSelectNextNode(const QModelIndex &nextNode);

    // Progress changed:
    void onProgressChanged();

    // Do search:
    void onDoSearch(const QString &targetString);

private:
    // UI:
    Ui::MainWindow *ui;

    // Ambiance selection dialog:
    AmbianceSelectionDialog mAmbianceSelectionDlg;

    // Directory selection dialog:
    DirSelectionDialog mDirSelectionDialog;

    // Preferences dialog:
    PreferencesDialog mPreferencesDialog;

    // Picto coverage dialog:
    PictoHunterDialog mPictoHunterDialog;

    // Controller:
    Controller *mController;

    // Image dir:
    QList<QDir> mImageDirList;

    // QLineEdit:
    QLineEdit *mLineEdit;

    // Progress bar:
    QProgressBar *mProgressBar;
};

#endif // MAINWINDOW_H
